#include <iostream>
using namespace std;

int main()
{
    /* code */

char asci[150];
for (int i = 0; i < 150; i++)
{
   asci[i]=i;
   cout << i << "= "<< asci[i] <<  endl;
}


    return 0;
}
