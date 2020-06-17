#include <iostream>
using namespace std;


int divide(int dividend, int divisor) {
	int NA = 2147483647;
	if(divisor == 0)
		return NA;
	
	if(dividend == 0)
		return 0;
	
	if(divisor == 1)
		return dividend;
	
	if(dividend == divisor)
		return 1;
	
	if(dividend < 0 && divisor < 0 )
	{
		if(dividend < -NA && divisor < -NA)
			return 1;
		
		if(dividend < -NA)
		{
			if(divisor == -1)
				return NA;
			else
				if(divisor == -2)
					return 1073741824;
				else
					return divide(NA,-divisor);
		}
		else
			if(divisor < -NA)
				return 0;
			else
				return divide(-dividend,-divisor);
	}
	
	if(dividend < 0 && divisor > 0 )
	{ 
		if(dividend < -NA)
		{
			if(divisor == 1)
				return NA;
			else
				if(divisor == 2)
					return -1073741824;
				else
					return -divide(NA,divisor);
		}
		else
			return -divide(-dividend,divisor);
	}
	
	if(dividend > 0 && divisor < 0 )
	{ 
		if(divisor < -NA)
			return 0;
		else
			return -divide(dividend,-divisor);
	}
	
	if(dividend < divisor) 
		return 0;
	else
	{
		int count = 0;
		while(dividend >= divisor)
		{
			dividend -= divisor;
			count++;
		}
		return count;
	}
	
  }


 int main()
 {
	 int m = divide(7,-3);
 }
