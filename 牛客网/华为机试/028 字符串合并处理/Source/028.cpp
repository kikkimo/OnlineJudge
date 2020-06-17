#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string sortstring(string left,string right)
{
    string s0 = "",s1 = "";
    string s = left + right;
    int nlen = s.length();
    if(0 == nlen) return s;
    for(int i = 0 ; i < nlen ; i++)
    {
        if(i % 2 == 0)
            s0 += s[i];
        else
            s1 += s[i];
    }
    sort(s0.begin(),s0.end());
    sort(s1.begin(),s1.end());
    for( i = 0 ; i < (int)s0.length() ; i++)
        s[i*2] = s0[i];
    for( i = 0 ; i < (int)s1.length() ; i++)
        s[i*2+1] = s1[i];
    
    return s;
}

void Encrypt(string & s)
{
    int map[] = { 0,8,4,12,2,10,6,14,
			      1,9,5,13,3,11,7,15};
    char charMap[] = {"0123456789ABCDEF\0"};
	//        0b0000,0b0001,0b0010,0b0011,0b0100,0b0101,0b0110,0b0111,
	//        0b1000,0b1001,0b1010,0b1011,0b1100,0b1101,0b1110,0b1111
    int nlen = s.length();
    for(int i = 0 ; i < nlen ; i++)
    {
        int index = -1;
        if('0' <= s[i] && s[i] <= '9')
            index = s[i] - '0';
        else
            if('a' <= s[i] && s[i] <= 'f')
                index = s[i] - 'a' + 10;
            else
                if('A' <= s[i] && s[i] <= 'F')
                    index = s[i] - 'A' + 10;
				if(-1 != index)
					s[i] = charMap[map[index]];
    }
}

void ProcessString(string str1,string str2,string & strOutput)
{
    strOutput = sortstring(str1,str2);
    Encrypt(strOutput);
}

int main()
{
    string s1,s2;
    while(cin >> s1)
    {
        cin >> s2;
        string s;
        ProcessString(s1,s2,s);
        cout << s << endl;
    }
    return 0;
}