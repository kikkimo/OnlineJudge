#include <iostream>
using namespace std;
int main()
{
    int num;
    while(cin >> num)
    {
        if(0 == num)
            cout << "0";
        
        string s = "";
        while(num)
        {
            int a = num % 10;
            num /= 10;
            char ch = a + '0';
            s = s + ch;
        }
        cout << s;
    }
    return 0;
}