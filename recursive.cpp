#include <iostream>
// #include <cstring>
using namespace std;
int recursive(int a);
int main()
{
    int i, sum;
    cout << "Enter the number to count the factorial:" << endl;
    cin >> i;
    if (i < 0)
    {
        cout << "this is a negative number and there is no factorial exist" << endl;
    }
    else
    {
        sum=recursive(i);
    }
    cout << endl
         << "The factorial is " << sum << endl;
    return 0;
}
int recursive(int a)
{ int b;
    if (a == 0)
    {
        return 1;
    }
    else
    {b=a;
        return b * recursive(a-1);
    }
}