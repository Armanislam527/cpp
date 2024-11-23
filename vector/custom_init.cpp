#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec(5, 42); // 5 elements, all initialized to 42
    for (int val : vec) {
        std::cout << val << " "; // Outputs: 42 42 42 42 42
    }
    return 0;
}
