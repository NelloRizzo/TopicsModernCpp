#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1 = "ab\0\0c";
    string s2 = "ab\0\0c"s;
    cout << s1 << ' ' << s1.length() << endl;
    cout << s2 << ' ' << s2.length() << endl;
}
