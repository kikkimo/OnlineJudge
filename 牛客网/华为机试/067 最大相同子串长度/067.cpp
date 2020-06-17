#include <iostream>
#include <string>
using namespace std;

int GetMaxSubStringLen(string s1,string s2)
{
	int nlen1 = s1.length();
	int nlen2 = s2.length();

	if(0 == nlen1 || 0 == nlen2)
		return 0;

	int i,j;
	int ** dp = new int*[nlen1+1];
	for (i = 0 ; i < nlen1 + 1 ; i++)
	{
		dp[i] = new int[nlen2+1];
		memset(dp[i],0,sizeof(int)*(nlen2+1));
	}

	int maxlen = 0;
	for (i = 1 ; i < nlen1 + 1 ; i++)
	{
		for (j = 1 ; j < nlen2 + 1 ; j++)
		{
			if (s1[i-1] == s2[j-1])
				dp[i][j] = dp[i-1][j-1] + 1;
			if (dp[i][j] > maxlen)
				maxlen = dp[i][j];
		}
	}
	for (i = 0 ; i < nlen1 + 1 ; i++)
		delete [] dp[i];
	delete [] dp;
	return maxlen;
}

int main()
{
	string str1,str2;
	while(cin >> str1 >> str2)
		cout << GetMaxSubStringLen(str1,str2) << endl;
	return 0;
}