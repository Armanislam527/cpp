#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {10, 20, 30};
    for (int val : vec) {
        std::cout << val << " "; // Outputs: 10 20 30
    }
    return 0;
}
