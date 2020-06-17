#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define min(a,b) ((a < b) ? a : b)

int calStringDistance(string s1,string s2)
{
    int nlen1 = s1.length();
    int nlen2 = s2.length();
    if(0 == nlen1)
        return nlen2;
    if(0 == nlen2)
        return nlen1;

    int i;
    vector<vector<int> > dp(nlen1 + 1, vector<int>(nlen2 + 1, 0)); 
    dp[0][0] = 0;
    for(i = 1 ; i <= nlen1 ; i++)
        dp[i][0] = i;
    for(i = 1 ; i <= nlen2 ; i++)
        dp[0][i] = i;
    
    for(i = 1; i <= nlen1 ; i++)
    {
        for(int j = 1; j <= nlen2 ; j++)
        {
			int one = dp[i-1][j-1];
			int two = dp[i-1][j]+1;
			int three = dp[i][j-1]+1;
            if(s1[i-1] == s2[j-1])
                dp[i][j] = min(one,min(two,three));
            else
                dp[i][j] = min(one+1,min(two,three));
        }
    }
    return dp[nlen1][nlen2];
}

int main()
{
    string s1,s2;
    while(cin >> s1 >> s2)
    {
        cout << calStringDistance(s1,s2) << endl;
    }
    return 0;
}