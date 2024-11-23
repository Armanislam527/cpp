#include<iostream>
using namespace std;
int factorial(int n,int result =1){
    if (n == 0) { // Base case
        return result;
    }
    return factorial(n - 1, n * result); 
}int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    cout << "Factorial of " << num << " is " << factorial(num) << endl;

    return 0;
}