#include <bits/stdc++.h>
using namespace std;
class Student
{
    string name;
    int age;

public:
    Student(string n, int a) : name(n), age(a) {}
    void display()
    {
        cout << "Name:" << endl
             << name << endl
             << "age:" << age << endl;
    }
};
int main()
{
    Student s("Arman Islam", 22);
    s.display();

    return 0;
}