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
    int n = 6;
    float year[] = {1911, 1921, 1931, 1941, 1951, 1961};
    float pop[] = {12, 15, 20, 27, 39, 52};
    float diff[10][10];

    for (int i = 0; i < n; i++)
        diff[i][0] = pop[i];

    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < n - j; i++)
        {
            diff[i][j] = diff[i + 1][j - 1] - diff[i][j - 1];
        }
    }

    float x = 1946;
    float h = year[1] - year[0];
    float u = (x - year[0]) / h;
    float result = diff[0][0];
    float u_term = 1;

    for (int i = 1; i < n; i++)
    {
        u_term *= (u - (i - 1));
        result += (u_term * diff[0][i]) / factorial(i);
    }

    cout << "Estimated population in 1946: " << result << endl;
    return 0;
}