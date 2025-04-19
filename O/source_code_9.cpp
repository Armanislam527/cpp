#include <iostream>
using namespace std;

int main()
{
    const int n = 4;
    float x[] = {5, 6, 9, 11};
    float y[] = {12, 13, 14, 16};
    float X = 10;
    float result = 0;

    for (int i = 0; i < n; i++)
    {
        float term = y[i];
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                term *= (X - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }

    cout << "Estimated value of y at x = 10: " << result << endl;
    return 0;
}