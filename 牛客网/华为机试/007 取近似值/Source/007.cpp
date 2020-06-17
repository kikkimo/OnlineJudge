#include <iostream>
#include <string>
using namespace std;

int string2int(string str)
{
    int nlen = str.length();
    int num = 0;
    for(int i = 0 ; i < nlen ; i ++)
    {
        char ch = str[i];
        if('.' != ch)
        {
            int val = ch - '0';
            num = num * 10 + val;
        }
        else
            break;
    }
    return num;
}

int main()
{
    string str;
    while(getline(cin,str))
    {
        int nlen = str.length();
        int nDotIndex = -1;
        int num = 0;
        for(int i = 0 ; i < nlen ; i ++)
        {
            if('.' == str[i])
            {
                nDotIndex = i;
                break;
            }
        }
        
        if(-1 == nDotIndex || nDotIndex == nlen - 1)
            num = string2int(str);
        else
        {
           if(str[nDotIndex + 1] >= '5')
               num = string2int(str) + 1;
           else
               num = string2int(str);
        }
        cout << num << endl;
    }
}