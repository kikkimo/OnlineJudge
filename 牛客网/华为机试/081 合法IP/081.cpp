#include <iostream>
#include <string>
using namespace std;

bool isAvaildIP(string s)
{
    int nlen = s.length();
    if(0 == nlen)
        return false;
    
    int val[4] = { 0 };
    int nDots = 0;
    int nIndex = 0;
    int nPos = 0;
    bool bVaild = false;
    bool isIPAdress = true;
    
    while(nPos < nlen)
    {
        char ch = s[nPos];
        if('.' == ch)
        {
            nDots ++;
            if (bVaild) 
			{
				nIndex++;
				bVaild = false;
			}
            if(nDots >= 4)
            {
                isIPAdress = false;
                break;
            }
        }
        else{
            if(nIndex >= 4)
            {
                isIPAdress = false;
                break;
            }
            if(ch >= '0' && ch <= '9')
			{
				bVaild = true;
                val[nIndex] = val[nIndex] * 10 + ch - '0';
			}
            else
			{
                isIPAdress = false;
                break;
            }
        }
        nPos++;
    }
    
    if(!isIPAdress || nDots != 3 || nIndex != 3)
        return false;
    
    for(int i = 0 ; i < 4 ; i++)
    {
        if(val[i] < 0 || val[i] > 255)
        {
            isIPAdress = false;
            break;
        }
    }
    return isIPAdress;
}

int main()
{
    string str;
    while(cin >> str)
    {
        if(isAvaildIP(str))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}