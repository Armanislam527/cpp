#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

// Function to compress pixel values
vector<uint8_t> compressGrayscaleImage(const vector<uint8_t>& pixels) {
    vector<uint8_t> compressed;
    for (size_t i = 0; i < pixels.size(); i += 2) {
        uint8_t packed = (pixels[i] << 4); // Left shift first pixel into higher 4 bits
        if (i + 1 < pixels.size()) {
            packed |= (pixels[i + 1] & 0x0F); // Pack second pixel into lower 4 bits
        }
        compressed.push_back(packed);
    }
    return compressed;
}

// Function to decompress compressed image
vector<uint8_t> decompressGrayscaleImage(const vector<uint8_t>& compressed) {
    vector<uint8_t> decompressed;
    for (uint8_t byte : compressed) {
        decompressed.push_back((byte >> 4) & 0x0F); // Extract higher 4 bits
        decompressed.push_back(byte & 0x0F);        // Extract lower 4 bits
    }
    return decompressed;
}

int main() {
    // Example grayscale image (intensity values 0 to 15)
    vector<uint8_t> image = {1, 4, 15, 8, 7, 2, 9, 3};

    cout << "Original Image (4-bit values): ";
    for (uint8_t pixel : image) {
        cout << (int)pixel << " ";
    }
    cout << endl;

    // Compress the image
    vector<uint8_t> compressedImage = compressGrayscaleImage(image);

    cout << "Compressed Image (packed bytes): ";
    for (uint8_t byte : compressedImage) {
        cout << (int)byte << " ";
    }
    cout << endl;

    // Decompress the image
    vector<uint8_t> decompressedImage = decompressGrayscaleImage(compressedImage);

    cout << "Decompressed Image (4-bit values): ";
    for (uint8_t pixel : decompressedImage) {
        cout << (int)pixel << " ";
    }
    cout << endl;

    // Calculate storage savings
    size_t originalSize = image.size();               // Original size in bytes
    size_t compressedSize = compressedImage.size();   // Compressed size in bytes
    cout << "Storage Reduced: " << ((originalSize - compressedSize) * 100.0 / originalSize)
         << "%\n";

    return 0;
}
