#include <stdio.h>

int myAtoi(char* str) {
    char * p = str;
	long long int integer = 0;
	int x = 0;
	if (*p == '\0')
		return 0;
    while(*p == ' ') p++;
	if (*p == '-')
	{
		++p;
		while(*p!= '\0')
		{
			if (*p >= '0' && *p <= '9')
			{
				int ch = *p - '0';
				integer = integer * 10 + ch;
				if (integer >= 2147483648)
				{
					integer = 2147483648;
					break;
				}
			}
			else
				break;
			p++;
		}
		integer = -integer;
		x = (int)integer;
		return x;
	}
	else
	{
        if (*p == '+')
			++p;
		while(*p!= '\0')
		{
			if (*p >= '0' && *p <= '9')
			{
				int ch = *p - '0';
				integer = integer * 10 + ch;
				if (integer >= 2147483647)
				{
					integer = 2147483647;
					break;
				}
			}
			else
				break;
			p++;
		}
		x = (int)integer;
		return x;
	
	}
}

int main()
{
	int a = myAtoi("9223372036854775809");
	printf("%d\r\n",a);
	return 0;
}