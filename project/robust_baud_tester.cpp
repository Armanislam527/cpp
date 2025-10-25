// robust_baud_tester.cpp
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <cstring>
#include <iomanip>
#include <sstream>

// --- Configuration ---
const std::string DEFAULT_DEVICE = "/dev/ttyUSB0";
const int DEFAULT_BAUD_RATE = 115200;
const std::vector<int> BAUD_RATES_TO_TEST = {
    9600, 19200, 38400, 57600, 115200, 230400, 460800, 500000,
    921600, 1000000, 1152000, 1500000, 2000000, 2500000, 3000000,
    3500000, 4000000
};
const int TEST_DURATION_SECONDS = 5;
const int INIT_TIMEOUT_MS = 3000; // Increased timeout for initial connection
const int BAUD_SWITCH_TIMEOUT_MS = 2000; // 2 seconds to get BAUD_OK
const int PING_TIMEOUT_MS = 100;
const useconds_t INTER_COMMAND_DELAY_US = 50000; // 50ms delay between commands
// ----------------------

struct BaudConfig {
    int baud_rate;
    speed_t constant;
};

struct TestResult {
    int baud_rate;
    double success_rate_percent = 0.0;
    double effective_rate_hz = 0.0;
    double avg_rtt_us = 0.0;
    double max_rtt_us = 0.0; // Initialize
    double min_rtt_us = 0.0; // Initialize
    int total_pings = 0;
    int successful_pongs = 0;
    double duration_secs = 0.0;
};

class RobustSerialTester {
private:
    int serial_fd = -1;
    std::string device_path;
    int current_baud_rate = -1;
    std::vector<BaudConfig> baud_configs;

    speed_t intToBaudConstant(int baud_rate) {
        switch(baud_rate) {
            case 9600: return B9600;
            case 19200: return B19200;
            case 38400: return B38400;
            case 57600: return B57600;
            case 115200: return B115200;
            case 230400: return B230400;
#ifdef B460800
            case 460800: return B460800;
#endif
#ifdef B500000
            case 500000: return B500000;
#endif
#ifdef B576000
            case 576000: return B576000;
#endif
#ifdef B921600
            case 921600: return B921600;
#endif
#ifdef B1000000
            case 1000000: return B1000000;
#endif
#ifdef B1152000
            case 1152000: return B1152000;
#endif
#ifdef B1500000
            case 1500000: return B1500000;
#endif
#ifdef B2000000
            case 2000000: return B2000000;
#endif
#ifdef B2500000
            case 2500000: return B2500000;
#endif
#ifdef B3000000
            case 3000000: return B3000000;
#endif
#ifdef B3500000
            case 3500000: return B3500000;
#endif
#ifdef B4000000
            case 4000000: return B4000000;
#endif
            default:
                std::cerr << "Warning: Unsupported baud rate " << baud_rate << " by termios." << std::endl;
                return B0;
        }
    }

    std::vector<BaudConfig> initializeBaudConfigs(const std::vector<int>& rates) {
        std::vector<BaudConfig> configs;
        for (int rate : rates) {
            speed_t constant = intToBaudConstant(rate);
            if (constant != B0) {
                configs.push_back({rate, constant});
            }
        }
        return configs;
    }

public:
    RobustSerialTester(const std::string& device) : device_path(device) {
        baud_configs = initializeBaudConfigs(BAUD_RATES_TO_TEST);
    }

    bool openPort(int baud_rate, speed_t baud_constant) {
        closePort(); // Ensure closed

        serial_fd = open(device_path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (serial_fd == -1) {
            std::cerr << "Error opening " << device_path << ": " << strerror(errno) << std::endl;
            return false;
        }

        struct termios tty;
        if (tcgetattr(serial_fd, &tty) != 0) {
            std::cerr << "Error from tcgetattr: " << strerror(errno) << std::endl;
            closePort();
            return false;
        }

        cfsetospeed(&tty, baud_constant);
        cfsetispeed(&tty, baud_constant);
        cfmakeraw(&tty);

        tty.c_cflag &= ~PARENB; // No parity
        tty.c_cflag &= ~CSTOPB; // 1 stop bit
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;     // 8 bits
        tty.c_cflag |= (CLOCAL | CREAD);

        // Set read timeouts
        tty.c_cc[VMIN] = 0;  // Non-blocking read
        tty.c_cc[VTIME] = 1; // 0.1 seconds inter-character timeout

        if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
            std::cerr << "Error from tcsetattr: " << strerror(errno) << std::endl;
            closePort();
            return false;
        }

        tcflush(serial_fd, TCIOFLUSH);
        current_baud_rate = baud_rate;
        std::cout << "  Pi: Opened port at " << baud_rate << " baud." << std::endl;
        return true;
    }

    void closePort() {
        if (serial_fd >= 0) {
            close(serial_fd);
            serial_fd = -1;
            current_baud_rate = -1;
        }
    }

    bool sendCommand(const std::string& cmd) {
        std::string cmd_with_newline = cmd + "\n";
        ssize_t bytes_written = write(serial_fd, cmd_with_newline.c_str(), cmd_with_newline.length());
        if (bytes_written != static_cast<ssize_t>(cmd_with_newline.length())) {
            std::cerr << "  Pi: Error writing command '" << cmd << "': " << strerror(errno) << std::endl;
            return false;
        }
        tcdrain(serial_fd); // Wait for transmission
        return true;
    }

    // Reads a line (up to \n or \r) with a timeout
    std::string readLine(int timeout_ms = 1000) {
        std::string response;
        char buffer[256];
        int bytes_read = 0;

        auto start_time = std::chrono::steady_clock::now();
        auto timeout_point = start_time + std::chrono::milliseconds(timeout_ms);

        while (std::chrono::steady_clock::now() < timeout_point) {
            bytes_read = read(serial_fd, buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                for (int i = 0; i < bytes_read; i++) {
                    if (buffer[i] == '\n' || buffer[i] == '\r') {
                        return response; // Return line excluding newline
                    }
                    response += buffer[i];
                }
                if (response.length() >= sizeof(buffer) - 1) {
                    break; // Buffer full-ish
                }
            } else if (bytes_read < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
                // std::cerr << "  Pi: Error reading: " << strerror(errno) << std::endl; // Can be noisy
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Small sleep
        }
        return response; // Return partial or empty string on timeout
    }

    // Waits for a specific response with a timeout
    bool waitForResponse(const std::string& expected_prefix, std::string& response_out, int timeout_ms) {
        auto start_time = std::chrono::steady_clock::now();
        auto timeout_point = start_time + std::chrono::milliseconds(timeout_ms);

        while (std::chrono::steady_clock::now() < timeout_point) {
            std::string line = readLine(100); // Read with short internal timeout
            if (!line.empty()) {
                // Debug: Print received line
                // std::cout << "  Pi: Received line: '" << line << "'" << std::endl;
                if (line.rfind(expected_prefix, 0) == 0) { // Starts with prefix
                    response_out = line;
                    return true;
                }
                // Optionally log unexpected responses for debugging
                // std::cerr << "  Pi: Unexpected response: '" << line << "'" << std::endl;
            }
        }
        return false; // Timeout
    }

    bool initializeCommunication(int target_baud_rate, speed_t target_baud_constant) {
        std::cout << "  Pi: Initializing communication at " << target_baud_rate << " baud..." << std::endl;

        if (!openPort(target_baud_rate, target_baud_constant)) {
            std::cerr << "  Pi: Failed to open port for " << target_baud_rate << " baud." << std::endl;
            return false;
        }

        // --- More robust initialization sequence ---
        std::cout << "  Pi: Port opened. Waiting for Nano to stabilize..." << std::endl;
        // Give a moment fr the port to settle and for any initial Nano messages to be sent
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << "  Pi: Flushing input buffer..." << std::endl;
        // Flush any initial garbage or leftover messages
        tcflush(serial_fd, TCIFLUSH);

        std::cout << "  Pi: Sending INIT_MSG command..." << std::endl;
        // Send INIT_MSG command to get Nano's confirmation
        if (!sendCommand("INIT_MSG")) {
            std::cerr << "  Pi: Failed to send INIT_MSG." << std::endl;
            return false;
        }
        std::cout << "  Pi: INIT_MSG sent. Waiting for response..." << std::endl;

        // --- Wait for the specific response ---
        std::string response;
        if (waitForResponse("INIT_OK", response, INIT_TIMEOUT_MS)) {
            std::cout << "  Pi: SUCCESS! Received '" << response << "'. Initialization successful." << std::endl;
            return true;
        } else {
            std::cerr << "  Pi: TIMEOUT! Did not receive 'INIT_OK' at " << target_baud_rate << " baud within " << INIT_TIMEOUT_MS << "ms." << std::endl;

            // --- Diagnostic: See if ANYTHING was received ---
            std::cout << "  Pi: Performing diagnostic read (500ms)..." << std::endl;
            std::string diag_line = readLine(500); // Read for 500ms
            if (!diag_line.empty()) {
                std::cout << "  Pi: Diagnostic read received: '" << diag_line << "'" << std::endl;
                // Check for common issues
                if (diag_line.find("INIT_OK") != std::string::npos) {
                    std::cout << "  Pi: Note: 'INIT_OK' was present but might have had extra characters or wrong format." << std::endl;
                }
            } else {
                std::cout << "  Pi: Diagnostic read received nothing." << std::endl;
            }

            return false;
        }
    }

    bool switchBaudRate(int new_baud_rate, speed_t new_baud_constant, int& last_successful_baud, speed_t& last_successful_constant) {
        std::cout << "\n--- Attempting to switch to " << new_baud_rate << " baud ---" << std::endl;

        // Command Nano to change baud rate
        std::ostringstream baud_cmd;
        baud_cmd << "BAUD:" << new_baud_rate;
        if (!sendCommand(baud_cmd.str())) {
            std::cerr << "  Pi: Failed to send BAUD command." << std::endl;
            return false;
        }

        // Wait a short moment for Nano to process and potentially send BAUD_OK
        // The Nano will send BAUD_OK at the *new* baud rate
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Increased wait slightly

        // NOW, reconfigure the Pi's port to the NEW baud rate
        if (!openPort(new_baud_rate, new_baud_constant)) {
            std::cerr << "  Pi: Failed to reconfigure Pi port to " << new_baud_rate << " baud." << std::endl;
            // Revert Pi port to last known good
            openPort(last_successful_baud, last_successful_constant);
            return false;
        }

        // Try to read the BAUD_OK message from the Nano on the NEW baud rate
        std::string response;
        if (waitForResponse("BAUD_OK", response, BAUD_SWITCH_TIMEOUT_MS)) {
            std::cout << "  Pi: Received '" << response << "' on new baud rate. Switch successful." << std::endl;
            last_successful_baud = new_baud_rate;
            last_successful_constant = new_baud_constant;
            return true;
        } else {
            std::cerr << "  Pi: Timeout waiting for 'BAUD_OK' on " << new_baud_rate << " baud. Switch failed." << std::endl;
            // Revert Pi port to last known good baud rate
            if (!openPort(last_successful_baud, last_successful_constant)) {
                 std::cerr << "  Pi: Critical failure: Could not revert Pi port to last good baud (" << last_successful_baud << ")." << std::endl;
                 return false; // This is bad, we might have lost communication
            }
            std::cout << "  Pi: Reverted Pi port to last known good baud rate (" << last_successful_baud << ")." << std::endl;

            // Optional: Try to get Nano back on the last good baud by sending INIT_MSG again
            // This might help if Nano also needs to be "kicked" back.
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (sendCommand("INIT_MSG")) {
                std::string revert_resp;
                if (waitForResponse("INIT_OK", revert_resp, 1000)) {
                     std::cout << "  Pi: Confirmed communication re-established at " << last_successful_baud << " baud." << std::endl;
                }
            }
            return false;
        }
    }


    TestResult runTestAtBaudRate(int baud_rate) {
        TestResult result;
        result.baud_rate = baud_rate;
        result.min_rtt_us = 1e9; // Initialize to a large number
        result.max_rtt_us = 0.0;  // Initialize to zero

        std::cout << "  Pi: Running performance test for " << TEST_DURATION_SECONDS << " seconds..." << std::endl;

        std::vector<double> rtt_times_us;
        int successful_pings = 0;
        int total_pings_sent = 0;

        auto test_start_time = std::chrono::steady_clock::now();
        auto test_end_time = test_start_time + std::chrono::seconds(TEST_DURATION_SECONDS);

        const std::string ping_cmd = "PING";
        const std::string expected_pong = "PONG";

        while (std::chrono::steady_clock::now() < test_end_time) {
            total_pings_sent++;
            auto ping_send_time = std::chrono::steady_clock::now();

            if (!sendCommand(ping_cmd)) {
                // If sending fails, it's a critical issue, break or continue?
                // Let's continue for now, count as failed ping.
                continue;
            }

            std::string response;
            if (waitForResponse(expected_pong, response, PING_TIMEOUT_MS)) {
                auto pong_received_time = std::chrono::steady_clock::now();
                auto rtt_us = std::chrono::duration_cast<std::chrono::microseconds>(pong_received_time - ping_send_time).count();
                rtt_times_us.push_back(static_cast<double>(rtt_us));
                successful_pings++;

                // Update min/max RTT
                if (rtt_us < result.min_rtt_us) result.min_rtt_us = rtt_us;
                if (rtt_us > result.max_rtt_us) result.max_rtt_us = rtt_us;

            } // else timeout/failure is counted by lower successful_pings

            // Small delay between pings to avoid overwhelming and allow processing
            std::this_thread::sleep_for(std::chrono::microseconds(INTER_COMMAND_DELAY_US));
        }

        auto actual_duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - test_start_time).count() / 1e6;
        result.duration_secs = actual_duration;
        result.total_pings = total_pings_sent;
        result.successful_pongs = successful_pings;

        if (total_pings_sent > 0) {
            result.success_rate_percent = (100.0 * successful_pings) / total_pings_sent;
        }
        if (actual_duration > 0) {
            result.effective_rate_hz = successful_pings / actual_duration;
        }
        if (!rtt_times_us.empty()) {
            double sum_rtt = 0.0;
            for (double t : rtt_times_us) sum_rtt += t;
            result.avg_rtt_us = sum_rtt / rtt_times_us.size();
            // Removed minmax_element usage
            // auto minmax = std::minmax_element(rtt_times_us.begin(), rtt_times_us.end());
            // result.min_rtt_us = *minmax.first; // This was incorrect before, now handled in loop
            // result.max_rtt_us = *minmax.second;
        } else {
            // If no successful pings, set min to a high value, max to 0 or leave as init
            result.min_rtt_us = 0.0; // Or maybe N/A?
            result.max_rtt_us = 0.0;
        }

        std::cout << "  Pi: Test finished at " << baud_rate << " baud." << std::endl;
        return result;
    }

    void runFullTest() {
        std::cout << "=== Robust Pi-Nano Baud Rate Tester ===" << std::endl;
        std::cout << "Device: " << device_path << std::endl;
        std::cout << "Default/Initial Baud Rate: " << DEFAULT_BAUD_RATE << std::endl;
        std::cout << "-------------------------------------------" << std::endl;

        std::vector<TestResult> results;

        // --- 1. Initialize at the default baud rate ---
        BaudConfig default_config = {DEFAULT_BAUD_RATE, intToBaudConstant(DEFAULT_BAUD_RATE)};
        if (default_config.constant == B0) {
            std::cerr << "Error: Default baud rate " << DEFAULT_BAUD_RATE << " is not supported." << std::endl;
            return;
        }

        if (!initializeCommunication(default_config.baud_rate, default_config.constant)) {
            std::cerr << "Fatal: Could not establish initial communication at default baud rate " << DEFAULT_BAUD_RATE << std::endl;
            std::cerr << "Please check:" << std::endl;
            std::cerr << " 1. Arduino Nano is connected to " << device_path << std::endl;
            std::cerr << " 2. Arduino Nano is running the 'RobustBaudRateTester.ino' sketch." << std::endl;
            std::cerr << " 3. Default baud rate in Arduino sketch matches " << DEFAULT_BAUD_RATE << std::endl;
            std::cerr << " 4. Try manually testing with 'screen " << device_path << " " << DEFAULT_BAUD_RATE << "' and sending 'INIT_MSG'" << std::endl;
            return;
        }

        int last_successful_baud = default_config.baud_rate;
        speed_t last_successful_constant = default_config.constant;

        // --- 2. Test the default baud rate performance ---
        std::cout << "\n--- Testing Initial Baud Rate: " << default_config.baud_rate << " ---" << std::endl;
        TestResult initial_result = runTestAtBaudRate(default_config.baud_rate);
        results.push_back(initial_result);

        // --- 3. Iterate through other baud rates ---
        for (const auto& config : baud_configs) {
            // Skip the default rate as we already tested it
            if (config.baud_rate == DEFAULT_BAUD_RATE) {
                continue;
            }

            std::cout << "\n--- Preparing to Test Baud Rate: " << config.baud_rate << " ---" << std::endl;

            // --- Attempt to switch baud rates ---
            bool switch_success = switchBaudRate(config.baud_rate, config.constant, last_successful_baud, last_successful_constant);

            if (switch_success) {
                // --- If switch was successful, run the test ---
                TestResult res = runTestAtBaudRate(config.baud_rate);
                results.push_back(res);
            } else {
                // --- If switch failed, log it and continue ---
                std::cout << "  Pi: Skipping test for " << config.baud_rate << " baud due to failed switch." << std::endl;
                TestResult failed_res;
                failed_res.baud_rate = config.baud_rate;
                // success_rate, etc. remain 0
                results.push_back(failed_res);
            }
        }

        // --- 4. Print Summary Report ---
        std::cout << "\n\n=== Test Summary Report ===" << std::endl;
        std::cout << std::setw(10) << "Baud Rate"
                  << std::setw(12) << "Success %"
                  << std::setw(15) << "Rate (resp/s)"
                  << std::setw(12) << "Avg RTT (us)"
                  << std::setw(12) << "Min RTT (us)" // Added Min RTT
                  << std::setw(12) << "Max RTT (us)"
                  << std::setw(10) << "Sent"
                  << std::setw(10) << "Received"
                  << std::setw(12) << "Duration (s)"
                  << std::endl;
        std::cout << std::string(107, '-') << std::endl; // Adjusted line length

        for (const auto& res : results) {
            std::cout << std::fixed << std::setprecision(2);
            std::cout << std::setw(10) << res.baud_rate
                      << std::setw(12) << res.success_rate_percent
                      << std::setw(15) << res.effective_rate_hz
                      << std::setw(12) << std::setprecision(0) << res.avg_rtt_us
                      << std::setw(12) << std::setprecision(0) << res.min_rtt_us // Print Min RTT
                      << std::setw(12) << std::setprecision(0) << res.max_rtt_us
                      << std::setw(10) << res.total_pings
                      << std::setw(10) << res.successful_pongs
                      << std::setw(12) << std::setprecision(3) << res.duration_secs
                      << std::endl;
        }

        std::cout << "\n--- Fastest Reliable Rates ---" << std::endl;
        const double reliability_threshold = 99.0;
        double max_reliable_rate = 0.0;
        int best_baud_rate = 0;

        for (const auto& res : results) {
            if (res.success_rate_percent >= reliability_threshold) {
                if (res.effective_rate_hz > max_reliable_rate) {
                    max_reliable_rate = res.effective_rate_hz;
                    best_baud_rate = res.baud_rate;
                }
            }
        }

        if (best_baud_rate > 0) {
            std::cout << "Highest rate >= " << reliability_threshold << "% success: "
                      << best_baud_rate << " baud (" << std::fixed << std::setprecision(2) << max_reliable_rate << " responses/sec)" << std::endl;
        } else {
            std::cout << "No baud rate achieved " << reliability_threshold << "% success rate." << std::endl;
        }

        std::cout << "===========================================" << std::endl;
        closePort();
    }

    ~RobustSerialTester() {
        closePort();
    }
};

int main(int argc, char *argv[]) {
    std::string device = DEFAULT_DEVICE;
    if (argc >= 2) {
        device = argv[1];
    }

    RobustSerialTester tester(device);
    tester.runFullTest();

    return 0;
}
