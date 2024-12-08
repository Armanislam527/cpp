#include <iostream>
#include <string>
using namespace std;

int main() {
  int time;
  cout << "Ener a number of your age:\n";
  cin >> time;
  string result = (time < 18) ? "Good day." : "Good evening.";
  cout << result;
  return 0;
}
