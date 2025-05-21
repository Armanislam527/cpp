#include <iostream>
using namespace std;
class Example {
public:
Example() { cout << "Constructor Called!" << endl; }
~Example() { cout << "Destructor Called!" << endl; }
};
int main() {
Example obj;
return 0;
}