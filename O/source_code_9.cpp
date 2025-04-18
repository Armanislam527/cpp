#include <iostream>
using namespace std;

int main()
{
    const int n = 6;
    float x[] = {4, 5, 7, 10, 11, 13};
    float y[] = {48, 100, 294, 900, 1210, 2028};
    float diff[n][n];

    for (int i = 0; i < n; i++)
    {
        diff[i][0] = y[i];
    }

    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < n - j; i++)
        {
            diff[i][j] = (diff[i + 1][j - 1] - diff[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    float X = 15;
    float result = diff[0][0];
    float term = 1;

    for (int i = 1; i < n; i++)
    {
        term *= (X - x[i - 1]);
        result += term * diff[0][i];
    }

    cout << "Estimated value of f(15): " << result << endl;
    return 0;
}