#include <iostream>
using namespace std;
int *createArray(int size)
{
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = i + 1;
    }
    return arr;
}
int main()
{
    int size;
    cout<< "Enter the size:";
    cin >> size;
    int *arr = createArray(size);
    cout << "Array elements: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    delete[] arr;
    return 0;
}