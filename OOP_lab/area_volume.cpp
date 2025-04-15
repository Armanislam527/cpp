#include <iostream>
using namespace std;

class Area
{
public:
    int calculateArea(int l, int w)
    {
        return l * w;
    }
};

class Volume : public Area
{ // ✅ Corrected inheritance syntax
public:
    int calculateVolume(int l, int w, int h)
    {
        return calculateArea(l, w) * h;
    }
};

int main()
{
    Volume v;
    cout << "Volume: " << v.calculateVolume(2, 3, 4) << endl;
    return 0;
}
