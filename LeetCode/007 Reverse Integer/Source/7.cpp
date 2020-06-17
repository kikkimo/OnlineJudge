#include <IOSTREAM>
using namespace std;

int reverse(int x) {
	if (x == 0)
		return 0;

	if (x < -2147483647)
		return 0;

	if (x < 0)
		return 0 - reverse(-x);

	long long sum = 0;
	while(x)
	{
		sum = x % 10 + 10 * sum;
		x = x / 10;
	}
	if (sum < 2147483647)
		return sum;
	else
		return 0;
}

int main()
{
	return 0;
}
