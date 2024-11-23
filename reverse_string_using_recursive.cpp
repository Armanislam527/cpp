#include <iostream>
using namespace std;
void reversestring(string &str, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    swap(str[start], str[end]);
    reversestring(str, start + 1, end - 1);
}

int main()
{
    string str;
    cout << "Enter a striing: ";
    cin >> str;
    reversestring(str, 0, str.length() - 1);
    cout << "Reversed striing is:\t" << str << endl;
    return 0;
}