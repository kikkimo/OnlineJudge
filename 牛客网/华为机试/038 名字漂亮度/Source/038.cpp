#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int Beauty(string str)
{
	int nlen = str.length();
	if(0 == nlen)
		return 0;
	
	int count[26] = { 0 };
	for(int j = 0 ; j < nlen ; j++)
	{
		char ch = str[j];
		if('a'<=ch&&ch<='z')
			count[ch-'a']++;
		else
			if('A'<=ch&&ch<='Z')
				count[ch-'A']++;
	}
	vector<int> nums;
	for( j = 0 ; j < 26 ; j++)
		if(count[j])
			nums.push_back(count[j]);
		
		if(0 == (int)nums.size())
			return 0;
		
		sort(nums.begin(),nums.end());
		reverse(nums.begin(),nums.end());
		int sum = 0;
		for( j = 0 ; j < (int)nums.size() ; j++)
			sum = sum + nums[j]*(26-j);
		return sum;
}

string sub(string s1,string s2)
{
	return "";
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
			if (nSet)
				s = "1" + s;
            return s;
        }
    }
}

int main()
{
	string s1 = "9876543219";
	string s2 =  "123456789";
	string s3 = add(s1,s2);
    int n;
    while(cin >> n)
    {
        vector<string> vec_s;
        for(int i = 0 ; i < n ; i++)
        {
			string str;
            cin >> str;
			vec_s.push_back(str);
        }
		for( i = 0 ; i < n ; i++)
			cout << Beauty(vec_s[i]) << endl;
    }
    return 0;
}