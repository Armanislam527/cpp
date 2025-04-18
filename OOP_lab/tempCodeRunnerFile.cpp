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
        cout << "Name:" << name << "age:" << age << endl;
    }
};
int main()
{
    Student s(Arman, 22);
    s.display();

    return 0;
}