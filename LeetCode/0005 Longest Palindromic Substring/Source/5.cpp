#include <iostream>
#include <string>
using namespace std;

string longestPalindrome(string s);

bool IsPalindromicString(string s) {
	int len = s.length();
	if (len == 0) return false;
	int i = 0 , j = len - 1;

	bool flag = true;
	while(j - i > 1)
	{
		if (s.at(i) != s.at(j))
		{
			flag = false;
			break;
		}
		i++;
		j--;
	}
	if (s.at(j) != s.at(i))
		flag = false;
	return flag;
}

string longestPalindromeSubString(string s,int nPos,int * nlength)
{
	int nlen = s.length();
	if (nlen == 0)
	{
		string str = "";
		*nlength = 0;
		return str;
	}

	if (nPos < 0 || nPos >= nlen)
	{
		string str = "";
		*nlength = 0;
		return str;
	}

	int i = nPos, j = nPos;
	while(i >= 0 )
	{
		if (s.at(i) == s.at(nPos))
			i--;
		else
			break;
	}
	while(j < nlen )
	{
		if (s.at(j) == s.at(nPos))
			j++;
		else
			break;
	}
	while(i >= 0 && j < nlen)
	{
		if (s.at(i) == s.at(j))
		{
			i--;
			j++;
		}
		else
			break;
	}
	string str = s.substr(i+1,j-i-1);
	*nlength = j-i-1;
	return str;
}

string longestPalindrome(string s) {
	int nlen = s.length();
	if (nlen == 0)
	{
		string str = "";
		return str;
	}

	int nMaxLen = 0;
	int nStart,nEnd;
	for (int i = 0 ; i < nlen ; i++)
	{
		char ch = s.at(i);
		int nl = i,nr = i;
		while(nl >=0 && s.at(i) == s.at(nl)) nl--;
		while(nr < nlen && s.at(i) == s.at(nr)) nr++;
		while(nl >= 0 && nr < nlen && s.at(nl) == s.at(nr))
		{
			nl--;
			nr++;
		}
		if (nMaxLen < nr-nl-1)
		{
			nMaxLen = nr-nl-1;
			nStart = nl;
			nEnd = nr;
		}
	}
	string strdst = s.substr(nStart+1,nEnd-nStart-1);
	return strdst;
}

int main()
{

	string s = "ccc";
	cout << s << endl << "\r\n" << longestPalindrome(s) << endl;
	return 0;
}