#include <iostream>
// #include <cstring>
using namespace std;

int main()
{
    int i = 0, j = 1, count;
    int sum = 0;

    do
    {
        do
        {
            if (i == 0)
            {
                cout << "=========";
            }
            else
            {
                count = i * j;
                if (count == 0)
                {
                    cout << "||\t";
                }

                else
                {

                    cout << j << "*" << i << "=" << count << "\t";
                }
            }
            j++;
        } while (j < 11);
        cout << "\t||" << endl;
        j = 0;
        // cout << i << " ";
        ++i;
        sum += i;
    } while (i < 11);
    // cout << endl
    //     << "The sum is " << sum << endl;
    return 0;
}
