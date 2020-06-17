#include <iostream>
#include <string>
using namespace std;

//减法仅仅为加法服务，s1与s2没有负号
string sub(string s1,string s2)
{
    int nlen1 = s1.length();
    int nlen2 = s2.length();
    if(0 == nlen1 || 0 == nlen2)
        return "";
    
    if(s1 == s2)
        return "0";
    else
        if(s1 < s2)
        {
            string s = sub(s2,s1);
            s = "-" + s;
            return s;
        }
        else
        {
            int i = nlen1-1;
            int j = nlen2-1;
            int nSet = 0;
            string s = "";
            while(i >=0 || j>= 0)
            {
                int v1 = ((i >= 0 ) ? s1[i]-'0' : 0);
                int v2 = ((j >= 0 ) ? s2[j]-'0' : 0);
				i--; j--;
                int v = v1 - v2 + nSet;
                if(v < 0)
                {
                    nSet = -1;
                    char ch = '0' + v + 10;
                    s = ch + s;
                }
                else
                {
                    nSet = 0;
                    char ch = '0' + v;
                    s = ch + s;
                }
            }
            //由于s1 > s2不存在最高一位还需要借位的问题，此时nSet不会为-1
            int nPos = 0;
            for(i = 0 ; i < (int)s.length();i++)
            {
                if(s[i] != '0')
                {
                    nPos = i;
                    break;
                }
            }
            s = s.substr(nPos,(int)s.length() - nPos);
            return s;
        }
}

string add(string s1,string s2)
{
    int nlen1 = s1.length();
    int nlen2 = s2.length();
    if(0 == nlen1)
        return s2;
    if(0 == nlen2)
        return s1;
    
    if(s1[0] == '-')
    {
        if(s2[0] == '-')
        {
            s1 = s1.substr(1,nlen1-1);
            s2 = s2.substr(1,nlen2-1);
            string s = add(s1,s2);
            s = "-" + s;
            return s;
        }
        else
        {
            s1 = s1.substr(1,nlen1-1);
            return sub(s2,s1);
        }
    }
    else
    {
        if(s2[0] == '-')
        {
            s2 = s2.substr(1,nlen2-1);
            return sub(s1,s2);
        }
        else
        {
            int i = nlen1-1;
            int j = nlen2-1;
            int nSet = 0;
            string s = "";
            while(i >=0 || j>= 0)
            {
                int v1 = ((i >= 0 ) ? s1[i]-'0' : 0);
                int v2 = ((j >= 0 ) ? s2[j]-'0' : 0);
				i--; j--;
                int v = v1 + v2 + nSet;
                if(v >= 10)
                {
                    nSet = 1;
                    char ch = '0' + v - 10;
                    s = ch + s;
                }
                else
                {
                    nSet = 0;
                    char ch = '0' + v;
                    s = ch + s;
                }
            }
			if (nSet == 1)
				s = "1" + s;
            return s;
        }
    }
}

int main()
{
    string str1,str2;
    while(cin >> str1 >>str2)
    {
        cout << add(str1,str2) << endl;
    }
    return 0;
}