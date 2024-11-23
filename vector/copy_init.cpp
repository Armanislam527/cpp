#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2(vec1); // Copy vec1 to vec2
    for (int val : vec2) {
        std::cout << val << " "; // Outputs: 1 2 3
    }
    return 0;
}
