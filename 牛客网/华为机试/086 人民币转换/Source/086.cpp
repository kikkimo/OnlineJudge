#include <iostream>
#include <string>
#include <math.h>
using namespace std;

string num[10] = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
string unit[5] = {"拾","佰","仟","万","亿"};

typedef __int64 __int64_t;

string CovertBeyond100million(long n,bool & bWriteZero)
{
	string s = "";
	if(0 == n)
		return s;

	int a = n / 100000000; 
	n = n % 100000000;
	if (a)
		s += num[a] + unit[4];

	bool bWrite0 = false;
	a = n / 10000000;   //千万
	n = n % 10000000;
	if (a == 0)
	{
		if (s.length() != 0)
			bWrite0 = true;
	}
	else
	{
		s = s + num[a] + unit[2];
		bWrite0 = false;
	}

	a = n / 1000000;   //百万
	n = n % 1000000;
	if(a == 0)
	{
		if (s.length() != 0 && !bWrite0)
				bWrite0 = true;
	}
	else
	{
		if (bWrite0)
			s = s + num[0] + num[a] + unit[1];
		else
			s = s + num[a] + unit[1];
		bWrite0 = false;
	}

	a = n / 100000;   //十万
	n = n % 100000;
	if(a == 0)
	{
		if (s.length() != 0 && !bWrite0)
			bWrite0 = true;
	}
	else
	{
		if (bWrite0)
			s = s + num[0] + num[a] + unit[0];
		else
			s = s + num[a] + unit[0];
		bWrite0 = false;
	}

	a = n / 10000;   //万
	n = n % 10000;
	if(a == 0)
	{
		if (s.length() != 0)
		{
			s += unit[3];
			if (!bWriteZero)
				bWriteZero = true;
		}
	}
	else
	{
		if (bWrite0)
			s = s + num[0] + num[a] + unit[3];
		else
			s = s + num[a] + unit[3];
		bWrite0 = false;
	}

	a = n / 1000;   //千
	n = n % 1000;
	if(a == 0)
	{
		if (s.length() != 0 && !bWrite0)
			bWrite0 = true;
	}
	else
	{
		if (bWrite0)
			s = s + num[0] + num[a] + unit[2];
		else
			s = s + num[a] + unit[2];
		bWrite0 = false;
	}

	a = n / 100;   //百
	n = n % 100;
	if(a == 0)
	{
		if (s.length() != 0 && !bWrite0)
			bWrite0 = true;
	}
	else
	{
		if (bWrite0)
			s = s + num[0] + num[a] + unit[1];
		else
			s = s + num[a] + unit[1];
		bWrite0 = false;
	}

	a = n / 10;   //十
	n = n % 10;
	if(a == 0)
	{
		if (s.length() != 0 && !bWrite0)
			bWrite0 = true;
	}
	else
	{
		if (bWrite0)
			s = s + num[0] + num[a] + unit[0];
		else
		{
			if (s.length() == 0 && a == 1)
				s = s + unit[0];
			else
				s = s + num[a] + unit[0];
		}
		bWrite0 = false;
	}

	if (n == 0)
	{
		s += unit[4];
		bWriteZero = true;
	}
	else
	{
		if (bWrite0)
			s = s + num[0] + num[n] + unit[4];
		else
			s = s + num[n] + unit[4];
		bWriteZero = false;
	}
	return s;
}

string CovertPartBeforeDot(__int64_t n)
{
	string s = "";
	if (0 == n)
		return s;

	bool bWriteZero = false;
	int a = n / 100000000;
	n = n % 100000000;
	if (a)
		s = CovertBeyond100million(a,bWriteZero);

	a = n / 10000000;   //千万
	n = n % 10000000;
	if (a == 0)
	{
		if (s.length() != 0 && !bWriteZero)
			bWriteZero = true;
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[a] + unit[2];
		else
			s = s + num[a] + unit[2];
		bWriteZero = false;
	}

	a = n / 1000000;   //百万
	n = n % 1000000;
	if(a == 0)
	{
		if (s.length() != 0 && !bWriteZero)
			bWriteZero = true;
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[a] + unit[1];
		else
			s = s + num[a] + unit[1];
		bWriteZero = false;
	}

	a = n / 100000;   //十万
	n = n % 100000;
	if(a == 0)
	{
		if (s.length() != 0 && !bWriteZero)
			bWriteZero = true;
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[a] + unit[0];
		else
			s = s + num[a] + unit[0];
		bWriteZero = false;
	}

	a = n / 10000;   //万
	n = n % 10000;
	if(a == 0)
	{
		if (s.length() != 0)
		{
			s += unit[3];
			if (!bWriteZero)
				bWriteZero = true;
		}
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[a] + unit[3];
		else
			s = s + num[a] + unit[3];
		bWriteZero = false;
	}

	a = n / 1000;   //千
	n = n % 1000;
	if(a == 0)
	{
		if (s.length() != 0 && !bWriteZero)
			bWriteZero = true;
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[a] + unit[2];
		else
			s = s + num[a] + unit[2];
		bWriteZero = false;
	}

	a = n / 100;   //百
	n = n % 100;
	if(a == 0)
	{
		if (s.length() != 0 && !bWriteZero)
			bWriteZero = true;
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[a] + unit[1];
		else
			s = s + num[a] + unit[1];
		bWriteZero = false;
	}

	a = n / 10;   //十
	n = n % 10;
	if(a == 0)
	{
		if (s.length() != 0 && !bWriteZero)
			bWriteZero = true;
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[a] + unit[0];
		else
		{
			if (s.length() == 0 && a == 1)
				s = s + unit[0];
			else
				s = s + num[a] + unit[0];
		}
		bWriteZero = false;
	}

	if (n == 0)
	{
		s += "元";
		bWriteZero = true;
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[n] + "元";
		else
			s = s + num[n] + "元";
		bWriteZero = false;
	}
	return s;
}

string CovertPartAfterDot(int n)
{
	string s = "";
	if(0 == n)
		return s;
	int a = n / 10;
	int b = n % 10;

	if (a)
	{
		if (b)
			s = num[a] + "角" + num[b] + "分";
		else
			s = num[a] + "角";
	}
	else
		s = num[b] + "分";
	return s;
}

string Covert(double m)
{
	string s = "人民币";
	__int64_t n = (__int64_t)m;
	if (fabs(m-n) < 1e-6)
	{
		s = s + CovertPartBeforeDot(n) + "整";
	}
	else
	{
		int p = (int)((m-n)*100.0+0.5);
		string s1 = CovertPartBeforeDot(n);
		string s2 = CovertPartAfterDot(p);
		s = s + s1 + s2;
	}
	return s;
}

int main()
{
    double m;
    while(cin >> m)
        cout << Covert(m) << endl;
	return 0;
}