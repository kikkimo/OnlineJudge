#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;

void PrintString(string str)
{
    int nlen = str.length();
    if(8 == nlen)
    {
        cout << str << endl;
        return;
    }
    
    if(nlen < 8)
    {
        char sz[10] = { "00000000\0"};
        for(int i = 0 ; i < nlen ; i++)
            sz[i] = str.at(i);
        cout << sz << endl;
        return;
    }
    
    if(nlen > 8)
    {
        char temp[10] = { "00000000\0"};
        char sz[10] = { "00000000\0"};
        int nIndex = 0;
        bool flag = false;
        for(int i = 0 ; i < nlen ; i++)
        {
            sz[nIndex] = str.at(i);
            nIndex++;
            flag = false;
            if(8 == nIndex)
            {
                flag = true;
                cout << sz << endl;
                nIndex = 0;
                strcpy(sz,temp);
            }
        }
        if(!flag) cout << sz << endl;
        return;
    }
}

int main()
{
    string str;
    vector<string> strvec;
    while(getline(cin,str))
    {
        strvec.push_back(str);
        str = "";
    }
    
    for(int i = 0 ; i < strvec.size() ; i++)
    {
        string s = strvec[i];
        PrintString(s);
    }
}