#include <iostream>
#include <string>
#include <math.h>
using namespace std;

string num[10] = {"��","Ҽ","��","��","��","��","½","��","��","��"};
string unit[5] = {"ʰ","��","Ǫ","��","��"};

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
	a = n / 10000000;   //ǧ��
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

	a = n / 1000000;   //����
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

	a = n / 100000;   //ʮ��
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

	a = n / 10000;   //��
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

	a = n / 1000;   //ǧ
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

	a = n / 100;   //��
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

	a = n / 10;   //ʮ
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

	a = n / 10000000;   //ǧ��
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

	a = n / 1000000;   //����
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

	a = n / 100000;   //ʮ��
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

	a = n / 10000;   //��
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

	a = n / 1000;   //ǧ
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

	a = n / 100;   //��
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

	a = n / 10;   //ʮ
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
		s += "Ԫ";
		bWriteZero = true;
	}
	else
	{
		if (bWriteZero)
			s = s + num[0] + num[n] + "Ԫ";
		else
			s = s + num[n] + "Ԫ";
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
			s = num[a] + "��" + num[b] + "��";
		else
			s = num[a] + "��";
	}
	else
		s = num[b] + "��";
	return s;
}

string Covert(double m)
{
	string s = "�����";
	__int64_t n = (__int64_t)m;
	if (fabs(m-n) < 1e-6)
	{
		s = s + CovertPartBeforeDot(n) + "��";
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