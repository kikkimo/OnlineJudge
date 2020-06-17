#include <iostream>
#include <string>
using namespace std;

int strStr(string haystack, string needle) {
	size_t lenstack = haystack.size();
	size_t lensub = needle.size();
	if (lensub > lenstack)
		return -1;
	for (int i = 0 ; i <= lenstack - lensub ; ++i)
	{
		int count = 0;
		int i0 = i;
		for (int j = 0 ; j < lensub ; ++j)
		{
			if (needle[j] == haystack[i0])
			{
				count ++;
				i0 ++;
			}
			else
				break;
		}
		if (count == lensub)
			return i;
	}
	return -1;
}

vector<int> findSubstring(string s, vector<string>& words) {
	int len = s.size();
	size_t wordSize = words.size();
	if (0 == len || wordSize == 0)
	{
		vector<int> buffer;
		return buffer;
	}
	bool bFind = true;
	for (int i = 0 ; i < wordSize ; ++i)
	{
		if (-1 == strStr(s,words[i]))
		{
			bFind = false;
			break;
		}
	}
	if (!bFind)
	{
		vector<int> buffer;
		return buffer;
	}
	vector<int> result;

}

int main()
{
	string str1 = "mississippi";
	string str2 = "mississippi";
	int n = strStr(str1,str2);
	return n;
}