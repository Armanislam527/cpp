#include <iostream>
using namespace std;
int fibonacci(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else{
        return fibonacci(n-1)+fibonacci(n-2);
    }
} // namespace std;

int main(){
    int terms;
    cout << "Enter the number to terms: ";
    cin >> terms;
    cout << "Fibonacci series: ";
    for (int i=0; i<terms; i++){
        cout << fibonacci(i)<< " ";
    }
}