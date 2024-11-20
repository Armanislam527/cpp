#include<iostream>
 using namespace std;
void greetUser(string name ="anamul")
{
    cout << "Hello, " << name << " !" << endl;
}

int main()
{
    string userName;

    cout << "Enter your name: ";
    cin >> userName;
greetUser();
    greetUser(userName); // Call the function with a parameter

    return 0;
}