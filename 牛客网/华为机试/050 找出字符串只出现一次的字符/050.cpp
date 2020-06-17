#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct _tagInfo{
    int index;
    int nCount;
}Info;


bool comp(const Info & a,const Info & b)
{
    if(a.nCount == b.nCount)
        return a.index < b.index ;
    else
        return a.nCount < b.nCount ;
}

int main()
{
    string str;
    while(cin >> str)
    {
        int nlen = str.length();
        if(0 == nlen)
            continue;
        
        map<char,Info> Count;
        for(int i = 0 ; i < nlen ; i++)
        {
            char ch = str[i];
            map<char,Info>::iterator iter = Count.find(ch);
            if(iter == Count.end())
            {
                Info tmp;
                tmp.nCount = 1;
                tmp.index = i;
                Count.insert(make_pair(ch,tmp));
            }
            else
            {
                Info tmp = Count[ch];
				tmp.nCount++;
				Count[ch] = tmp;
            }
        }
        vector<Info> vec_Info;
		for(map<char,Info>::iterator iter = Count.begin(); iter != Count.end() ; iter++)
        {
			Info tmp = iter->second;
			vec_Info.push_back(tmp);
		}
		Count.clear();
		sort(vec_Info.begin(),vec_Info.end(),comp);
		if (vec_Info[0].nCount != 1)
			cout << -1 << endl;
		else
			cout << str[vec_Info[0].index] << endl;
		vec_Info.clear();
    }
	return 0;
}