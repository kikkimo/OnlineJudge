#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int lastWordLength(char * str)
{
    if(0 == str)
        return 0;
    char * p = str;
    char * pLast = NULL;
    
    while(*p)
    {
        pLast = p;
        p++;
    }
    
    int nRe = 0;
    while(*pLast != 32 && pLast != str )
    {
        nRe++;
        pLast--;
    }
    return (pLast == str) ? nRe+1 : nRe;
}

int main()
{
    char szBuf[5012] = { 0 };
    while (cin.getline(szBuf, 5000))
    {
        int num = lastWordLength(szBuf);
        printf("%d\n",num);
    }
    return 0;
}