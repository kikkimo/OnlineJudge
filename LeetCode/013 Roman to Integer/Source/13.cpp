#include <iostream>
#include <string>
using namespace std;

//I£¨1£©¡¢V£¨5£©¡¢X£¨10£©¡¢L£¨50£©¡¢C£¨100£©¡¢D£¨500£©ºÍM£¨1000£©¡£
int romanToInt(string s) {
	int	val[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
	string str[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"}; 

	int num = 0;
	int len = s.length();
	for (int i = 0 ; i < 13 ; i++)
	{
		int len1 = str[i].length();		
		if (len >= len1)
		{
			while (s.substr(0,len1) == str[i])
			{
				num += val[i];
				s = s.substr(len1);
				len -= len1;
			}
		}
	}
	return num;
 }

void main()
{
	cout << romanToInt("DCXXI") << "\r\n" << endl;
}