#include <iostream>
using namespace std;

int main()
{
    string str;
    while(cin >> str)
    {
        string result = "";
        int nlen = str.length();
        if(0 == nlen)
        {
            cout << result;
            break;
        }
        
        for(int i = nlen - 1; i >= 0 ; i--)
            result += str[i];
        cout << result;
    }
    return 0;
}