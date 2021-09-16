#include <IOSTREAM>
#include <string>
#include <vector>
using namespace std;

int longestValidParentheses(string s) {
	if (s.length() < 2)
		return 0;
	if (s.length() == 2 && s == "()")
		return 2;

	int i = 0, j = s.length() - 1;

	while(i<= j && s[i]!='(') i++;
	while(i<= j && s[j]!=')') j--;
	
	if (j<=i) return 0;

	s = s.substr(i,j-i+1);

	int maxlen = 0;
	for (i = 0; i < s.length() - 1 ; i++)
	{
		int count = 0;
		j = i;
		while( j < s.length())
		{
			if (s[j] == '(')
			{
				count ++;
				j++;
				continue;
			}
			else
			{
				count--;
				j++;
				if (count == 0 && j - i > maxlen)
					maxlen = j - i;

				if (count < 0)
					break;
			}
		}

		if (s.length() - i < maxlen)
			break;
	}
	return maxlen;
}

void main()
{
	cout << longestValidParentheses("(())()(()((") << "\r\n" << endl;
}