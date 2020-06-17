#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    while(getline(cin,str))
    {
        long num = 0;
        long val;
        for(int i = 2 ; i < str.length() ; i++)
        {
            char ch = str[i];
            if('0' <= ch && ch <= '9')
                val = ch - '0';
            if('A' <= ch && ch <= 'F')
                val = ch - 'A' + 10;
            num = num * 16 + val;
        }
        cout << num << endl;
    }
    return 0;
}