#include <iostream>
#include <iomanip> // for all manipulators
using namespace std;

int main() {
    int number = 42;
    double value = 123.456789;

    cout << "Demonstrating output manipulators:\n\n";

    // setw and setfill
    cout << "1. setw(10) with setfill('*'):\n";
    cout << setfill('*') << setw(10) << number << endl;

    // left and right alignment
    cout << "\n2. Left and Right alignment with setw(10):\n";
    cout << left << setw(10) << number << " <- left aligned\n";
    cout << right << setw(10) << number << " <- right aligned\n";

    // fixed and scientific notation
    cout << "\n3. Fixed and scientific notation:\n";
    cout << "Fixed:       " << fixed << setprecision(3) << value << endl;
    cout << "Scientific:  " << scientific << setprecision(3) << value << endl;

    // showpos and noshowpos
    cout << "\n4. Show positive sign:\n";
    cout << showpos << number << " (with showpos)\n";
    cout << noshowpos << number << " (with noshowpos)\n";

    return 0;
}
