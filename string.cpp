#include <iostream>
#include <string>
using namespace std;

int main()
{
    string fulName;
cout << "Type your full name: ";
getline (cin, fulName);
cout << "Your name is: " << fulName <<"\n";
    string firstName = "John ";
    string lastName = "Doe";
    string fullName = firstName.append(lastName);
    cout << firstName << "\n";
    firstName.append(lastName, 0, 2); // Appends the first 2 characters of lastName ("Do")
    cout << firstName << "\n";
    string result = firstName.append("Middle ").append(lastName);
    cout << result << "\n";
    string txt = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout << "The length of the txt string is: " << firstName.length() << "\n";
    // string txt = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout << "The length of the txt string is: " << firstName.size() << "\n";
    txt = "We are the so-called \"Vikings\" from the north.";
    cout << txt << "\n";
    string myString = "Hello";
    myString[0] = 'J';
cout << myString << "\n";
cout << myString << "\n"; // Outputs Hello

cout << myString.at(0) << "\n";  // First character
cout << myString.at(1) << "\n";  // Second character
cout << myString.at(myString.length() - 1) << "\n";  // Last character

myString.at(0) = 'J';
cout << myString;  // Outputs Jello
    cout << myString[1] << "\n";
    cout << myString[myString.length() - 1] << "\n";
    // Outputs o
    return 0;
}
