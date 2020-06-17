#include <iostream>
#include <vector>
#include <string>
using namespace std;

int letterSize[8] = {3,3,3,3,3,4,3,4};
char letterMap[8][4] = {
'a','b','c','\0',
'd','e','f','\0',
'g','h','i','\0',
'j','k','l','\0',
'm','n','o','\0',
'p','q','r','s',
't','u','v','\0',
'w','x','y','z'};

vector<string> letterCombinations(string digits) {
	vector<string> result;
	int nlen = digits.length();
	if (0 == nlen) return result;
	if (1 == nlen)
	{
		int nIndex = digits[0] - '2';
		int nSize = letterSize[nIndex];
		for (int i = 0 ; i < nSize ; i ++)
		{
			char temp[2] = {letterMap[nIndex][i],0};
			string s(temp) ;
			result.push_back(s);
		}
		return result;
	}
	else
	{
		char ch = digits[0];
		string digits0 = digits.substr(1,nlen - 1);
	    vector<string> res = letterCombinations(digits0);

		int nIndex = ch - '2';
		int nSize = letterSize[nIndex];
		for (int i = 0 ; i < nSize ; i ++)
		{
			for (int j = 0 ; j < res.size() ; j++)
			{
				string s = letterMap[nIndex][i] + res[j];
				result.push_back(s);
			}
		}
		return result;
	}
}

void main()
{
	string s = "23\0";
	vector<string> output = letterCombinations(s);
	for (int i = 0 ; i < output.size() ; i++)
	{
		string str = output[i];
		cout << str << endl;
	}
}