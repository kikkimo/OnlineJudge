#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _tagString
{
    string s;
    int length;
    int index;
}String;

bool comp(const String & a,const String & b)
{
    if(a.length == b.length)
        return a.index < b.index;
    else
        return a.length > b.length;
}

int Continumax(string s,string & result)
{
    string str = "";
    int nlen = s.length();
    if(0 == nlen)
    {
        result = str;
        return 0;
    }
    
    vector<String> vec_STR;
    for(int i = 0 ; i < nlen ; i ++)
    {
        if('0' <= s[i] && s[i] <= '9')
        {
            int nPos = i;
            while(nPos < nlen && '0' <= s[nPos] && s[nPos] <= '9')
                nPos++;
            
            String tmp;
            tmp.index = i;
            tmp.length = nPos - i;
            tmp.s = s.substr(i,nPos-i);
            vec_STR.push_back(tmp);
        }
    }
    if((int)vec_STR.size() == 0)
    {
        result = str;
        return 0;
    }
    
    sort(vec_STR.begin(),vec_STR.end(),comp);
    int maxlen = vec_STR[0].length;
    for(int i = 0 ; i < (int)vec_STR.size() ; i++)
    {
        if(vec_STR[i].length == maxlen)
            str += vec_STR[i].s;
    }
    vec_STR.clear();
    result = str;
    return maxlen;
}

int main()
{
    string str;
    while(cin >> str)
    {
        string s;
        int maxlen = Continumax(str,s);
        cout << s << "," << maxlen << endl;
    }
    return 0;
}