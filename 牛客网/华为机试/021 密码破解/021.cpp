#include <iostream>
#include <string>
using namespace std;

int main()
{
    char map[27] = {"22233344455566677778889999"};
    string strPasswd;
    while(cin >> strPasswd)
    {
        int nlen = strPasswd.length();
        for(int i = 0 ; i < nlen ; i ++)
        {
            char ch = strPasswd[i];
            if('a' <= ch && ch <= 'z')
            {
                int index = ch - 'a';
                strPasswd[i] = map[index];
            }
            else
                if('A' <= ch && ch <= 'Z')
                {
                    if('Z' == ch)
                        ch = 'A';
                    else
                        ch = ch + 1;
                    strPasswd[i] = ch - 'A' + 'a';
                }
        }
        cout << strPasswd << "\n";
    }
}
