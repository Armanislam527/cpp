#include<iostream>
using namespace std;
int add(int a,int b)
{
    return a+b;
} // namespace std;
double add(double a, double b)
{
    return a+b;
}
string add(string a, string b){
    return a+b;
}
int main(){
    cout <<"Integer addition:"<< add(3,4)<<endl;
    cout <<"Double addition:"<< add(3.5,4.5)<<endl;
    cout <<"String addition:"<< add("hello, ","world")<<endl;
}