#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool IsAvaild(string s)
{
	int nlen = s.length();
	if (0 == nlen) return false;
	if (nlen % 2 == 1) return false;
	if (s[0] == ')') return false;

	int nCount = 0;
	bool bRe = true;
	for (int i = 0 ; i < nlen ; i++)
	{
		if (s[i] == '(')
		{
			nCount++;
			continue;
		}
		else
		{
			nCount--;
			if (nCount < 0)
			{
				bRe = false;
				break;
			}
		}
	}
	
	return (bRe && nCount == 0);
}

vector<string> generateSeq(int n)		//n>=2
{
	vector<string> result;
	if (1 == n)
	{
		string s = "(";
		result.push_back(s);
		s = ")";
		result.push_back(s);
	}
	if (n >= 2)
	{
		vector<string> res = generateSeq(n-1);
		for (int i = 0 ; i < res.size() ; i++)
		{
			string s = "(" + res[i];
			result.push_back(s);
			s = ")" + res[i];
			result.push_back(s);
		}
	}
	return result;
}

vector<string> generateParenthesis(int n) {
	vector<string> result;
    if (0 == n)
		return result;

	if (1 == n)
	{
		string s = "()";
		result.push_back(s);
		return result;
	}

	if (n > 1)
	{
		vector<string> res = generateSeq(2*n);
		for (int i = 0 ; i < res.size() ; i++)
		{
			if (IsAvaild(res[i]))
				result.push_back(res[i]);
		}
	}

	return result;
}


void main()
{
	vector<string> s = generateParenthesis(4);
	for (int i = 0 ; i < s.size() ; i ++)
	{
		cout << s[i] << endl;
	}
}