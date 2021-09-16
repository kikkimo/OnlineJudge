#include <iostream>
#include <string>
#include <vector>

using namespace std;

string longestCommonPrefix(vector<string>& strs) {
	string strPrefix;
	int nMinLength = 2147483647;
	string strshortest;
	int size = strs.size();
	if (0 == size) return strPrefix;
	if (1 == size) return strs[0];
	for (int i = 0 ; i < size  ; i++)
	{
		int nlen = strs[i].length();
		if (nlen < nMinLength)
		{
			nMinLength = nlen;
			strshortest = strs[i];
		}
	}

	for (int j = 0 ; j < nMinLength ; j++)
	{
		char ch = strshortest[j];
		bool bBreak = false;
		for (int i = 0 ; i < strs.size() ; i++)
		{
			if (strs[i][j] != ch)
			{
				bBreak = true;
				break;
			}
		}
		if (bBreak)
			break;
		else
			strPrefix += ch;
	}

	return strPrefix;
 }


void main()
{

}