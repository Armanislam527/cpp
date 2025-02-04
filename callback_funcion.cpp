#include <iostream>
// Define a callback function type
typedef void (*CallbackFunction)();

// Function that takes a callback function as an argument
void performAction(CallbackFunction callback)
{
    std::cout << "Performing some action...\n";
    // Call the callback function
    callback();
}

// Example callback function
void myCallback()
{
    std::cout << "Callback function \n";
}
int main()
{
    // Pass the callback function to performAction
    performAction(myCallback);
    return 0;
}