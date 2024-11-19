#include <iostream>
#include <string>
#include <locale>
using namespace std;
int main()
{
    locale::global(locale());
    string name;
    cout << "Enter your name:";
    cin >> name;
    cout << "Hello, " << name << " !" << endl;
    cerr << "This is a error message" << endl;
    clog << "Logging some program informaation." << endl;
    wstring wname;
    wcout << L"Enter your wide-character name:";
    wcin >> wname;
    wcout << L"Hello, "<< wname <<L" !"<<endl;
    wcerr << L"This is a wide-character error message." << endl;
    wclog << L"Logging some wide-character program information." << endl;
return 0;
} // namespace std;
