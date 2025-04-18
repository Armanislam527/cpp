#include <iostream>
#include <cmath>
using namespace std;

float f(float x)
{
    return x * x - x - 2;
}

int main()
{
    float a = 1, b = 3, c, tolerance = 0.0001;

    if (f(a) * f(b) >= 0)
    {
        cout << "Invalid interval. f(a) and f(b) must have opposite signs." << endl;
        return 1;
    }

    do
    {
        c = a - (f(a) * (b - a)) / (f(b) - f(a));
        if (f(c) == 0.0)
            break;
        else if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    }
    wh

        ile(fabs(f(c)) > tolerance);

    cout << "The root is approximately: " << c << endl;
    return 0;
}