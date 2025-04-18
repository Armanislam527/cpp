#include <bits/stdc++.h>
using namespace std;
int *createarray(int size)
{
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = i + 1;
    }
    return arr;
}
/*************  ✨ Windsurf Command ⭐  *************/
/**
 * Main function that prompts the user to enter the size of an array,
 * creates an array of the specified size with sequentially increasing values,
 * prints the array, and then deallocates the memory used by the array.
 */

/*******  c2ccc8a6-3547-4424-8756-bdf2abdc5f87  *******/
int main()
{
    int s;
    cout << "Enter the size of the array: ";
    cin >> s;
    int *arr = createarray(s);
    for (int i = 0; i < s; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    delete[] arr;
    return 0;
}