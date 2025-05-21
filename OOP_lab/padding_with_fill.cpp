#include <iostream>
#include <iomanip>
using namespace std;
int main() {
cout << "Default output: " << 42 << endl;
cout << setw(10) << setfill(' ') << 42 << endl;
return 0;
}