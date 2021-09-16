#include <IOSTREAM>
using namespace std;

bool isPalindrome(int x) {
    if (x < 0)
		return false;
	if (x < 10)
		return true;

	int y = x;
	int nlen = 1;
	int a = 1;
	int b = 1;
	while (y >= 10)
	{
		y /= 10;
		nlen ++;
		a *= 10;
	}
	
	bool flag = true;
	for (int i = 0 ; i < nlen / 2 ; i ++)
	{
		if (((x / a) % 10) != ((x % (b*10)) / b))
		{
			flag = false;
			break;
		}
		a /= 10;
		b *= 10;
	}
	return flag;
}

int main()
{
	int m = isPalindrome(12021);
	printf("%s\r\n",m ? "true" : "flase");
	return 0;
}