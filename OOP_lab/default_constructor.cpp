#include <iostream>
using namespace std;
class Example {
public:
 Example() {
 cout << "Default Constructor Called!" << endl;
 }
};
int main() {
 Example obj;
 return 0;
}