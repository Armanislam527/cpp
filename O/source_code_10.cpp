#include <iostream>
#include <cmath>
using namespace std;

float f(float x)
{
    return x * x - 4 * x - 10;
}

int main()
{
    float a = -2, b = -1.5, c, tolerance = 0.0001;

    if (f(a) * f(b) >= 0)
    {
        cout << "Invalid interval. f(a) and f(b) must have opposite signs." << endl;
        return 1;
    }

    while ((b - a) >= tolerance)
    {
        c = (a + b) / 2;
        if (f(c) == 0.0)
            break;
        else if (f(c) * f(a) < 0)
            b = c;
        else
            a = c;
    }

    cout << "The root is approximately: " << c << endl;
    return 0;
}