#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string countAndSay(int n) {
	string str;
	if (n < 1)
		return str;
	if (1 == n)
	{
		str = "1";
		return str;
	}
	string lastStr = countAndSay(n - 1);
	int len = lastStr.length();
	char lastCh = lastStr[0];
	char counts = '0';		//观察个数不超过10，可以直接用一个字节表示
	for (int i = 0 ; i < len ; ++i)
	{
		char ch = lastStr[i];
		if (ch != lastCh)
		{
			string buf("00");
			buf[0] = counts;
			buf[1] = lastCh;
			str += buf;
			lastCh = ch;
			counts = '1';
		}
		else
		{
			counts++;
		}
	}
	string buf("00");
	buf[0] = counts;
	buf[1] = lastCh;
	str += buf;
	return str;
}

int main()
{
	for (int i = 1 ; i <= 30 ; ++i)
	{
		cout << i << ": " << countAndSay(i) << "\n";
	}
	return 0;
}