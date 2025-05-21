#include <iostream>
using namespace std;
class Example {
private:
int value;
public:
Example(int v) {
    value = v; 
    }
Example(const Example &obj) {
     value = obj.value;
     }
void display() { 
    cout << "Value: " << value << endl; 
}
};
int main() {
Example obj1(50);
Example obj2(obj1);
obj2.display();
return 0;
}