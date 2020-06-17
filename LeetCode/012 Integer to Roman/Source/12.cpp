#include <iostream>
#include <string>

using namespace std;

//¢ñ£¨1£©¡¢X£¨10£©¡¢C£¨100£©¡¢M£¨1000£©¡¢V£¨5£©¡¢L£¨50£©¡¢D£¨500£©
string intToRoman(int num) {
	string s;
	int   val[7] = {1000,500,100,50,10,5,1};
	char  ch[7] = {'M','D','C','L','X','V','I'};
	for (int i = 0 ; i < 7 ; i++)
	{
		while(num >= val[i])
		{
			s = s + ch[i];
			num -= val[i];
		}
		if (i % 2 == 0 && i < 5 && num >= val[i] - val[i+2])  //I,X,CµÄ×ó¼õ£¬IX = 9,XC=90£¬CM = 900
		{
			s = s + ch[i+2] + ch[i];
			num = num - val[i] + val[i+2];
		}
		else
		{
			if (i % 2 == 0 && i < 5 && num >= val[i+1] - val[i+2] && 
				num < val[i+1]) //¶ÔÓ¦CD = 400,XL=40,IV=4
			{
				s = s + ch[i+2] + ch[i+1];
				num = num - val[i+1] + val[i+2];
			}
		}
	}
	return s;
}

void main()
{
	cout << intToRoman(444) << "\r\n" << endl;
}