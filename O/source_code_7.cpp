#include <iostream>
using namespace std;

int factorial(int n)
{
    int fact = 1;
    for (int i = 2; i <= n; i++)
        fact *= i;
    return fact;
}

int main()
{
    const int n = 8;
    float x[] = {1, 2, 3, 4, 5, 6, 7, 8};
    float fx[] = {1, 8, 27, 64, 125, 216, 343, 512};
    float diff[n][n];

    // Fill first column with f(x) values
    for (int i = 0; i < n; i++)
        diff[i][0] = fx[i];

    // Backward difference table
    for (int j = 1; j < n; j++)
    {
        for (int i = n - 1; i >= j; i--)
        {
            diff[i][j] = diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }

    float value = 7.5;
    float h = x[1] - x[0];
    float u = (value - x[n - 1]) / h;

    float result = diff[n - 1][0];
    float u_term = 1;

    for (int i = 1; i < n; i++)
    {
        u_term *= (u + i - 1);
        result += (u_term * diff[n - 1][i]) / factorial(i);
    }

    cout << "Estimated value of f(7.5): " << result << endl;
    return 0;
}