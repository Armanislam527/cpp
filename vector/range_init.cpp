#include <iostream>
#include <vector>
using namespace std;

int main()
{
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> vec2(vec1.begin() + 1, vec1.end() - 1); // Copy vec1 to vec2
    for (int val : vec2)
    {
        std::cout << val << " "; // Outputs: 1 2 3
    }
    cout << "Size: " << vec2.size()  << endl;        // Outputs: 3
    cout << "Capacity: " << vec2.capacity(); // May output a value >= 3
    return 0;
}
