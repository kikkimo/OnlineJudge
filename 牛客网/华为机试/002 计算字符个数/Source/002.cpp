#include <iostream>
#include <memory.h>
using namespace std;

int letterCount(char * str,char * c)
{
    char ch = *c;
    if(!((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')))
        return 0;
    bool IsNumber = (ch >= '0' && ch <= '9') ;
    int nCount = 0;
    while(*str!=0)
    {
        char c = * str;
        if(IsNumber)
        {
            if(c == ch) nCount++;
        }
        else
        {
            if(ch >= 'a' && ch <= 'z')
            {
                if(c == ch || c == ch + 'A' - 'a')
                    nCount++;
            }
            else
            {
                if(c == ch || ch == c + 'A' - 'a')
                    nCount++;
            }
        }
        str++;
    }
    return nCount;
}

int main()
{
    char szBuf[1024] = { 0 };
    char ch[2] = { 0 };
    cin >> szBuf >> ch;
    cout << letterCount(szBuf,ch) ;

}

