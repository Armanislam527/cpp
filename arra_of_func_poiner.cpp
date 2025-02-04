#include <iostream>

// Function declarations
int add(int a, int b)
{
    return a + b;
}
int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}
int main()
{

    // Declare and initialize an array of function pointers
    int (*funcArray[3])(int, int) = {add, subtract, multiply};

    // Variables to use as function parameters
    int x = 2, y = 3;
    // Access and call the functions using the array of function pointers
    std::cout
        << "Add: " << funcArray[0](x, y) << std::endl;            // Calls add(10, 5)
    std::cout << "Subtract: " << funcArray[1](x, y) << std::endl; // Calls subtract(10, 5)
    std::cout << "Multiply: " << funcArray[2](x, y) << std::endl; // Calls multiply(10, 5)
    return 0;
}