#include <iostream>
#include <string>
#include <math.h>
using namespace std;

bool CheckTwo(int * num,int size,double result)
{
	bool bOk = false;
	if(size == 0)
	{
		if(fabs(result - 24) < 1e-6)
			return true;
		else
			return false;
	}
	double v1 = num[size-1];
	for (int i = size - 2 ; i >= 0 ; i--)
	{
		double v2 = num[i];
		if(i!=size-2)
		{
			num[i] = num[size-2];
			num[size-2] = v2;
		}
		double v[6] = {v1+v2,v1-v2,v2-v1,v1*v2,v1/v2,v2/v1};
		for (int j = 0 ; j < 6 ; j ++)
		{
			double val = v[j];
			if(fabs(result) < 1e-6)
			{
				if(4 == size)  //此时result为0，不能用乘除，否则val值可直接被跳过，例如101 299 12 12这种会误判
					bOk = CheckTwo(num,size-2,result+val) || CheckTwo(num,size-2,result-val) || CheckTwo(num,size-2,val-result);
				else
					if (fabs(val) < 1e-6)
						bOk = CheckTwo(num,size-2,result+val) || CheckTwo(num,size-2,result-val) || CheckTwo(num,size-2,val-result)
						|| CheckTwo(num,size-2,result*val);
					else
						bOk = CheckTwo(num,size-2,result+val) || CheckTwo(num,size-2,result-val) || CheckTwo(num,size-2,val-result)
						|| CheckTwo(num,size-2,result*val) || CheckTwo(num,size-2,result/val);		
			}
			else
			{
				if (fabs(val) < 1e-6)
					bOk = CheckTwo(num,size-2,result+val) || CheckTwo(num,size-2,result-val) || CheckTwo(num,size-2,val-result)
					|| CheckTwo(num,size-2,result*val) || CheckTwo(num,size-2,val/result);
				else
					bOk = CheckTwo(num,size-2,result+val) || CheckTwo(num,size-2,result-val) || CheckTwo(num,size-2,val-result)
						|| CheckTwo(num,size-2,result*val) || CheckTwo(num,size-2,result/val) || CheckTwo(num,size-2,val/result);
			}
			if (bOk)
					break;
		}
		if (bOk)
			break;
	}
	return bOk;
}


//一个数递归只能找到1个数与剩余n-1个数的混合运算，例如101 103  100 112这种无法判断正确
bool CheckOne(int * num,int size,double result)
{
	bool bOk = false;
	if(size == 0)
	{
		if(fabs(result - 24) < 1e-6)
			return true;
		else
			return false;
	}

	for (int i = size - 1 ; i >= 0 ; i--)
	{
		int val = num[i];
		if(i!=size-1)
		{
			num[i] = num[size-1];
			num[size-1] = val;
		}
		if(fabs(result) < 1e-6)
		{
			if(4 == size)  //此时result为0，不能用乘除，否则val值无效，例如100 8 8 8这种会误判
				bOk = CheckOne(num,size-1,result+val) || CheckOne(num,size-1,result-val) || CheckOne(num,size-1,val-result);
			else
				bOk = CheckOne(num,size-1,result+val) || CheckOne(num,size-1,result-val) || CheckOne(num,size-1,val-result)
				|| CheckOne(num,size-1,result*val) || CheckOne(num,size-1,result/val);
			
			if (bOk)
				break;
		}
		else
		{
			bOk = CheckOne(num,size-1,result+val) || CheckOne(num,size-1,result-val) || CheckOne(num,size-1,val-result)
				|| CheckOne(num,size-1,result*val) || CheckOne(num,size-1,result/val) || CheckOne(num,size-1,result/val);
			
			if (bOk)
				break;
		}
	}
	return bOk;
}

int main()
{
	int num[4] = { 0 };
	while(cin >> num[0] >> num[1] >> num[2] >> num[3])
	{
		if (CheckOne(num,4,0) || CheckTwo(num,4,0))
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	return 0;
}