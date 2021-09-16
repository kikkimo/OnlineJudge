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

int main()
{
	string str1 = "mississippi";
	string str2 = "mississippi";
	int n = strStr(str1,str2);
	return n;
}