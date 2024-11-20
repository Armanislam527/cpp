#include <iostream>
#include<cstring>
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
                cout << "========";
            }
            else
            {
                count =i*j;
                int l = size(count);
                if(l==2){
                cout << count <<"      ";
                }
                else{
                    cout << count <<"       ";
                }
            } 
            j++;
        } while (j < 11);
        cout << endl;
        j=1;
        // cout << i << " ";
        i++;
        sum += i;
    } while (i < 11);
    cout << endl
         << "The sum is " << sum << endl;
    return 0;
}
