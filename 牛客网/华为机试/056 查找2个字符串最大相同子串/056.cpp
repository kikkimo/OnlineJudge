#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

#define min(a,b) a < b ? a : b

string FindLongestSubString(string s1,string s2)
{
    string s = "";
    int nlen1 = s1.length();
    int nlen2 = s2.length();
    if(nlen1 == 0 || nlen2 == 0)
        return s;
    if(nlen1 < nlen2)
        return FindLongestSubString(s2,s1);
    
    map<char,vector<int> > letterMap;
    for(int i = 0 ; i < nlen1 ; i++)
    {
        char ch = s1[i];
        if(letterMap.find(ch) == letterMap.end())
        {
            vector<int> vec_index;
            vec_index.push_back(i);
            letterMap[ch] = vec_index;
        }
        else
            letterMap[ch].push_back(i);
    }
    
    int maxlen = 0;
    int nPos0 = 0 ;
    for( i = 0 ; i < nlen2 ; i ++)
    {
        if(nlen2 - i < maxlen)
            break;
        
        char ch = s2[i];
        if(letterMap.find(ch) == letterMap.end())
            continue;
        else
        {
            vector<int> vec_index = letterMap[ch];
            for(int k = 0 ; k < (int)vec_index.size() ; k++)
            {
                int L = vec_index[k];
                if(nlen1 - L < maxlen)
                    continue;
                else
                {
                    int nsize = min(nlen1 - L,nlen2-i);
                    int index0 = i,index1 = i+nsize;
                    for(int j = i; j < i+nsize ; j++)
                    {
                        if(s2[j] != s1[j-i+L])
                        {
                            index1 = j;
                            break;
                        }
                    }
                    if(index1 - index0 > maxlen)
                    {
                        maxlen = index1 - index0;
                        nPos0 = index0;
                    }
                }
            }
        }
    }
	for (map<char,vector<int> >::iterator it = letterMap.begin() ; it != letterMap.end() ; it++)
		it->second.clear();
	letterMap.clear();

    if(maxlen > 0)
        s = s2.substr(nPos0,maxlen);
    return s;
}

int main()
{
    string s1,s2;
    while(cin >> s1 >> s2)
        cout << FindLongestSubString(s1,s2) << endl;
    return 0;
}