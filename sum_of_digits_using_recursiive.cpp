#include <iostream>
using namespace std;
int sumofdigits(int n);
int main()
{
    int number;
    cout << "Enter a number: ";
     cin >> number;
    cout << "Sum of digits is: " << sumofdigits(number) << endl;
    return 0;
}

int sumofdigits(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return (n % 10) + sumofdigits(n / 10);
    }
}