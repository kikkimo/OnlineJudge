#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int GetMaxLen(string s1,string s2)
{
    int nlen1 = s1.length();
    int nlen2 = s2.length();
    if(0 == nlen1 || 0 == nlen2)
        return 0;
    
    reverse(s1.begin(),s1.end());
    int minSize = ( nlen1 < nlen2 ? nlen1 : nlen2 );
    
    int maxlen = 0;
    for(int i = 0 ; i < minSize ; i++)
    {
        if(s1[i] == s2[i])
            maxlen++;
        else
            break;
    }
    return maxlen;
}

int main()
{
    string str;
    while(cin >> str)
    {
        int nlen = str.length();
        if(nlen <= 1)
        {
            cout << nlen << endl;
            continue;
        }
        
        int maxlen = 0;
        for(int i = 1 ; i < nlen ; i++)
        {
            string s1 = str.substr(0,i);
            string s2 = str.substr(i+1,nlen-1-i);
            int len = GetMaxLen(s1,s2) * 2 + 1;
            maxlen = len > maxlen ? len : maxlen;
            s1 = str.substr(0,i);
            s2 = str.substr(i,nlen-i);
            len = GetMaxLen(s1,s2) * 2;
            maxlen = len > maxlen ? len : maxlen;
        }
        cout << maxlen << endl;
    }
    return 0;
}