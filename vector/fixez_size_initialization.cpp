#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec(5); // 5 elements, all initialized to 0
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " "; // Outputs: 0 0 0 0 0
    }
    return 0;
}
