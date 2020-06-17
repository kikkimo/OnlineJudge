#include <iostream>
#include <string>
using namespace std;

string Covert2bit(int n)
{
    string s = "";
    while(n)
    {
        int a = n % 2;
        n >>= 1;
        char ch = '0' + a;
        s = ch + s;
    }
    return s;
}

int GetMaxLen(string s)
{
    int nlen = s.length();
    if(0 == nlen)
        return 0;
    
    int maxlen = 0;
    for(int i = 0 ; i < nlen ; i++)
    {
        if(s[i] == '1')
        {
            int nPos = i;
            while(nPos < nlen && s[nPos] == '1')
                nPos++;
            if(maxlen < nPos - i)
                maxlen = nPos - i;
        }
    }
    return maxlen;
}

int main()
{
    int N;
    while(cin >> N)
        cout << GetMaxLen(Covert2bit(N)) << endl;
    return 0;
}