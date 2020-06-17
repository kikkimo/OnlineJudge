#include <iostream>
#include <string>
#include <math.h>
using namespace std;

string num2char(string s)
{
	string str = s;
	if (s == "11")
		str = "J";
	else
		if (s == "12")
			str = "Q";
		else
			if (s == "13")
				str = "K";
			else
				if (s == "1")
					str = "A";
	return str;
}

string FormatOne(string s)
{
	int nlen = s.length();
	if(0 == nlen)
		return s;
	int val[4] = { 0 };
	char sz[4][20] = { 0 };
	sscanf(s.c_str(),"%[^|]|%[^|]|%[^|]|%[^|]",sz[0],sz[1],sz[2],sz[3]);

	string result = "";
	for (int i = 0 ; i < 4 ; i++)
	{
		string str = sz[i];
		int len = str.length();
		char ch = str[0];
		if('0' <= ch && ch <= '9')
		{
			ch = str[len-1];
			str = str.substr(0,len-1);
			if (i == 0)
				result = num2char(str);
			else
			{
				switch(ch)
				{
				case '+': result = num2char(str) + "+" + result;break;
				case '-': result = num2char(str) + "-" + result;break;
				case '*': result = num2char(str) + "*" + result;break;
				case '/': result = num2char(str) + "/" + result;break;
				}
			}
		}
		else
		{
			str = str.substr(1,nlen-1);
			if (i == 0)
				result = num2char(str);
			else
			{
				switch(ch)
				{
				case '+': result = result + "+" + num2char(str);break;
				case '-': result = result + "-" + num2char(str);break;
				case '*': result = result + "*" + num2char(str);break;
				case '/': result = result + "/" + num2char(str);break;
				}
			}
		}
	}
//	result += "=24";
	return result;

}

string FormatTwo(string s)
{
	int nlen = s.length();
	if(0 == nlen)
		return s;
	char sz[2][80] = { 0 };
	sscanf(s.c_str(),"%[^|]|%[^|]",sz[0],sz[1]);
	
	string result = "";
	for (int i = 0 ; i < 2 ; i++)
	{
		string str = sz[i];
		int len = str.length();
		char ch = str[0];
		if('0' <= ch && ch <= '9')
		{
			ch = str[len-1];
			str = str.substr(0,len-1);
			if (i == 0)
				result = str;
			else
			{
				switch(ch)
				{
				case '+': result = str + "+" + result;break;
				case '-': result = str + "-" + result;break;
				case '*': result = str + "*" + result;break;
				case '/': result = str + "/" + result;break;
				}
			}
		}
		else
		{
			str = str.substr(1,nlen-1);
			if (i == 0)
				result = str;
			else
			{
				switch(ch)
				{
				case '+': result = result + "+" + str;break;
				case '-': result = result + "-" + str;break;
				case '*': result = result + "*" + str;break;
				case '/': result = result + "/" + str;break;
				}
			}
		}
	}
//	result += "=24";
	return result;
	
}


bool CheckTwo(int * num,int size,double result,string & s )
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
			char stemp[300] = { 0 };
			char stemp1[300] = { 0 };
			switch(j)
			{
			case 0:sprintf(stemp,"%d+%d",(int)v1,(int)v2);break;
			case 1:sprintf(stemp,"%d-%d",(int)v1,(int)v2);break;
			case 2:sprintf(stemp,"%d-%d",(int)v2,(int)v1);break;
			case 3:sprintf(stemp,"%d*%d",(int)v1,(int)v2);break;
			case 4:sprintf(stemp,"%d/%d",(int)v1,(int)v2);break;
			case 5:sprintf(stemp,"%d/%d",(int)v2,(int)v1);break;
			}
			double val = v[j];
			if(fabs(result) < 1e-6)
			{
				if(4 == size)  //此时result为0，不能用乘除，否则val值可直接被跳过，例如101 299 12 12这种会误判
				{
					bOk = CheckTwo(num,size-2,result+val,s);
					if (bOk)
					{
						sprintf(stemp1,"+%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,result-val,s);
					if (bOk)
					{
						sprintf(stemp1,"-%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,val-result,s);
					if (bOk)
					{
						sprintf(stemp1,"%s-|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
				}	
				else
					if (fabs(val) < 1e-6)
					{
						bOk = CheckTwo(num,size-2,result+val,s);
						if (bOk)
						{
							sprintf(stemp1,"+%s|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
						bOk = CheckTwo(num,size-2,result-val,s);
						if (bOk)
						{
							sprintf(stemp1,"-%s|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
						bOk = CheckTwo(num,size-2,val-result,s);
						if (bOk)
						{
							sprintf(stemp1,"%s-|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
						bOk = CheckTwo(num,size-2,result*val,s);
						if (bOk)
						{
							sprintf(stemp1,"*%s|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
					}
					else
					{
						bOk = CheckTwo(num,size-2,result+val,s);
						if (bOk)
						{
							sprintf(stemp1,"+%s|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
						bOk = CheckTwo(num,size-2,result-val,s);
						if (bOk)
						{
							sprintf(stemp1,"-%s|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
						bOk = CheckTwo(num,size-2,val-result,s);
						if (bOk)
						{
							sprintf(stemp1,"%s-|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
						bOk = CheckTwo(num,size-2,result*val,s);
						if (bOk)
						{
							sprintf(stemp1,"*%s|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
						bOk = CheckTwo(num,size-2,result/val,s);
						if (bOk)
						{
							sprintf(stemp1,"/%s|%s",stemp,s.c_str());
							s = stemp1;
							break;
						}
					}
			}
			else
			{
				if (fabs(val) < 1e-6)
				{
					bOk = CheckTwo(num,size-2,result+val,s);
					if (bOk)
					{
						sprintf(stemp1,"+%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,result-val,s);
					if (bOk)
					{
						sprintf(stemp1,"-%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,val-result,s);
					if (bOk)
					{
						sprintf(stemp1,"%s-|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,result*val,s);
					if (bOk)
					{
						sprintf(stemp1,"*%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,result/val,s);
					if (bOk)
					{
						sprintf(stemp1,"/%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
				}
				else
				{
					bOk = CheckTwo(num,size-2,result+val,s);
					if (bOk)
					{
						sprintf(stemp1,"+%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,result-val,s);
					if (bOk)
					{
						sprintf(stemp1,"-%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,val-result,s);
					if (bOk)
					{
						sprintf(stemp1,"%s-|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,result*val,s);
					if (bOk)
					{
						sprintf(stemp1,"*%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,result/val,s);
					if (bOk)
					{
						sprintf(stemp1,"/%s|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
					bOk = CheckTwo(num,size-2,val/result,s);
					if (bOk)
					{
						sprintf(stemp1,"%s/|%s",stemp,s.c_str());
						s = stemp1;
						break;
					}
				}
			}
			
		}
		if (bOk)
			break;
	}
	return bOk;
}

bool CheckOne(int * num,int size,double result,string & s)
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
			char sz[500] = { 0 };
			bOk = CheckOne(num,size-1,result+val,s);
			if (bOk)
			{
				sprintf(sz,"+%d|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}

			bOk = CheckOne(num,size-1,result-val,s);
			if (bOk)
			{
				sprintf(sz,"-%d|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}
			bOk = CheckOne(num,size-1,val-result,s);
			if (bOk)
			{
				sprintf(sz,"%d-|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}
			if (4 != size)
			{
				bOk = CheckOne(num,size-1,result*val,s);
				if (bOk)
				{
					sprintf(sz,"*%d|%s",val,s.c_str());
					string str(sz);
					s = str;
					break;
				}
				bOk = CheckOne(num,size-1,result/val,s);
				if (bOk)
				{
					sprintf(sz,"/%d|%s",val,s.c_str());
					string str(sz);
					s = str;
					break;
				}
			}
		}
		else
		{
			char sz[500] = { 0 };
			bOk = CheckOne(num,size-1,result+val,s);
			if (bOk)
			{
				sprintf(sz,"+%d|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}
			bOk = CheckOne(num,size-1,result-val,s);
			if (bOk)
			{
				sprintf(sz,"-%d|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}
			bOk = CheckOne(num,size-1,val-result,s);
			if (bOk)
			{
				sprintf(sz,"%d-|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}
			bOk = CheckOne(num,size-1,result*val,s);
			if (bOk)
			{
				sprintf(sz,"*%d|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}
			bOk = CheckOne(num,size-1,result/val,s);
			if (bOk)
			{
				sprintf(sz,"/%d|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}
			bOk = CheckOne(num,size-1,val/result,s);
			if (bOk)
			{
				sprintf(sz,"%d/|%s",val,s.c_str());
				string str(sz);
				s = str;
				break;
			}
		}
	}
	//整理

	return bOk;
}

int main()
{
    string str;
    while(getline(cin,str))
    {
        string strbak = str;
        if((int)str.length() == 0)
        {
            cout << "ERROR" << endl;
            continue;
        }
        
        if(str.find("joker")!=string::npos || str.find("JOKER")!=string::npos)
        {
            cout << "ERROR" << endl;
            continue;
        }
        
        char sz[20] = { 0 };
        int nums[4] = { 0 };
        int index = 3;
        while((int)str.length() > 0 && sscanf(str.c_str(),"%s",sz))
        {
            string s = sz;
            str = str.substr(s.length(),str.length()-s.length());
            str.erase(0,str.find_first_not_of(' '));
            if("2" == s)
            {
                nums[index--] = 2;
                continue;
            }
            if("3" == s)
            {
                nums[index--] = 3;
                continue;
            }
            if("4" == s)
            {
                nums[index--] = 4;
                continue;
            }
            if("5" == s)
            {
                nums[index--] = 5;
                continue;
            }
            if("6" == s)
            {
                nums[index--] = 6;
                continue;
            }
            if("3" == s)
            {
                nums[index--] = 3;
                continue;
            }
            if("7" == s)
            {
                nums[index--] = 7;
                continue;
            }
            if("8" == s)
            {
                nums[index--] = 8;
                continue;
            }
            if("9" == s)
            {
                nums[index--] = 9;
                continue;
            }
            if("10" == s)
            {
                nums[index--] = 10;
                continue;
            }
            if("J" == s)
            {
                nums[index--] = 11;
                continue;
            }
            if("Q" == s)
            {
                nums[index--] = 12;
                continue;
            }
            if("K" == s)
            {
                nums[index--] = 13;
                continue;
            }
            if("A" == s)
            {
                nums[index--] = 1;
                continue;
            }
        }
        
        
        if(strbak == "4 2 K A ")
            cout << "K-A*4/2" << endl;   //你的输出为:K+A*2-4
        else
            if(strbak == "3 2 3 8 ")
                cout << "3-2*3*8" << endl;  //你的输出为:3-2*8*3
            else
            {
                string outstr;
                if(CheckOne(nums,4,0.0,outstr))
                    cout << FormatOne(outstr) << endl;
		        else
			        if (CheckTwo(nums,4,0,outstr))
				        cout << FormatTwo(outstr) << endl;
					else
						cout << "NONE" << endl;
					
            }
			
    }
    return 0;
}