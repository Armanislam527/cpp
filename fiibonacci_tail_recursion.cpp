#include <iostream>
using namespace std;
int fibonaccihelper(int n, int a, int b)
{
    if (n == 0)
    {
        return a;
    }
    if (n == 1)
    {
        return b;
    }
    return fibonaccihelper(n - 1, b, a + b);
}
int fibonaccitail(int n)
{
    return fibonaccihelper(n, 0, 1);
}
int main()
{
    int terms ; cout << "Enter the number of terms: ";
    cin >> terms;
    cout << "Fibonacci series: ";
    for (int i = 0; i < terms; i++)
    {
        cout << fibonaccitail(i) << " ";
    }
    return 0;
}