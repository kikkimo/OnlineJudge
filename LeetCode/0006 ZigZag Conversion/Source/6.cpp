#include <IOSTREAM>
#include <string>
using namespace std;

string convert(string s, int numRows) {
	if (numRows < 1)
		return "";
	int nlen = s.length();
	if (nlen == 0) return "";
	if (numRows == 1)
		return s;

	if (numRows >= nlen)
		return s;
	
	string * str = new string[numRows];
	memset(str,0,sizeof(string)*numRows);
	string strDst = "";
	for (int i = 0 ; i < numRows ; i++)
	{
		str[i] += s.at(i);
		int nIndex0 = i;
		int nColSpace;
		if (i == 0 || i == numRows - 1)
		{
			nColSpace = 2*(numRows-1);
			nIndex0 += nColSpace;
			while(nIndex0 < nlen)
			{
				str[i] += s.at(nIndex0);
				nIndex0 += nColSpace;
			}
		}
		else
		{
			int nColSpace1,nColSpace2;
			nColSpace1 = 2*(numRows-1) - i*2;
			nColSpace2 = i*2;
			nColSpace = nColSpace1;
			nIndex0 += nColSpace;
			while(nIndex0 < nlen)
			{
				str[i] += s.at(nIndex0);
				if (nColSpace == nColSpace1)
					nColSpace = nColSpace2;
				else
					nColSpace = nColSpace1;
				nIndex0 += nColSpace;
			}
		}
		strDst = strDst + str[i];
	}
	delete [] str;
	return strDst;
}


int main()
{
	string s = "PAYPALISHIRING";
	cout << s << "\r\n" << endl;
	string t = convert(s,4);
	cout << t << "\r\n" << endl;
	return 0;
}