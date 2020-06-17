#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxsublen(string s1)
{
    int nlen = s1.length();
    if(0 == nlen)
        return 0;
    
    string s2 = s1;
    reverse(s2.begin(),s2.end());
    vector< vector<int> > dp(nlen+1,vector<int>(nlen + 1, 0));
    int maxlen = 0;
    for(int i = 1; i <= nlen ; i++)
    {
        for(int j = 1; j <= nlen ; j++)
        {
            if(s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            if (dp[i][j] > maxlen)
				maxlen = dp[i][j];
        }
    }
    return maxlen;
}

int main()
{
    string str;
    while(cin >> str)
        cout << maxsublen(str) << endl;
    return 0;
}