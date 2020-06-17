#include <iostream>
#include <string>
using namespace std;

bool MoveTo(int & x,int & y,string s)
{
    int nlen = s.length();
    if( nlen < 2 || nlen > 3)
        return false;
    if(s[0] >= 'a' && s[0] <= 'z')
        s[0] = s[0] - 'a' + 'A';
    bool flag = false;
    int num = 0;
    for(int i = 1 ; i < nlen ; i++)
    {
        if(s[i] < '0' || s[i] > '9')
        {
            flag = true;
            break;
        }
        else
            num = num * 10 + s[i] - '0';
    }
    if(flag)
        return false;
    
    bool bOk = true;
    switch(s[0])
    {
        case 'A': x -= num; break;
        case 'W': y += num; break;
        case 'D': x += num; break;
        case 'S': y -= num; break;
        default : bOk = false; break;
    }
    return bOk;
}

int main()
{
    string str;
    while(cin >> str)
    {
        int x = 0, y = 0;
        int nlen = str.length();
        if(0 == nlen)
        {
            cout << x << "," << y;
            continue;
        }
        string s = "";
        for(int i = 0 ; i < nlen ; i++)
        {
            char ch = str[i];
            if(ch == ';')
            {
                MoveTo(x,y,s);
                s = "";
            }
            else
                s = s + ch;    
        }
        if(s != "")
            MoveTo(x,y,s);
        cout << x << "," << y << endl;
    }
}