#include <iostream>
#include <string>
using namespace std;

bool compIP(int a[],int b[])
{
	if (a[0] < b[0])
		return false;

	if (a[0] > b[0])
		return true;

	if (a[0] == b[0])
		return (((a[1]<<8)+a[2])<<8)+a[3] >= (((b[1]<<8)+b[2])<<8)+b[3] ;
}

bool CheckAdressRange(int val[],string s1,string s2)
{
    int nValBegin[4] = { 0 };
    int nValEnd[4] = { 0 };
    sscanf(s1.c_str(),"%d.%d.%d.%d",nValBegin,nValBegin+1,nValBegin+2,nValBegin+3);
    sscanf(s2.c_str(),"%d.%d.%d.%d",nValEnd,nValEnd+1,nValEnd+2,nValEnd+3);
	return compIP(val,nValBegin) && compIP(nValEnd,val);
}

void CheckIP(char * str, int * nums)
{
    char * p = str;
    int nDots = 0;
    int val[4] = { 0 };
    int nIndex = 0;
    bool isIPAdress = true;
	bool bVaild = false;
    while(*p != 0)
    {
        char ch = * p;
        if(ch == '.')
        {
            nDots++;
            if (bVaild) 
			{
				nIndex++;
				bVaild = false;
			}
            if(nDots >= 4)
            {
                isIPAdress = false;
                break;
            }
        }
        else
        {
            if(ch >= '0' && ch <= '9')
			{
				bVaild = true;
                val[nIndex] = val[nIndex] * 10 + ch - '0';
			}
            else
			{
                isIPAdress = false;
                break;
            }
        }
		p++;
    }
    
    if(!isIPAdress || 3 != nDots || 3 != nIndex)
    {
        nums[5]++;
        return;
    }
    
    for(int i = 0 ; i < 4 ;  i ++)
    {
        if(0 <= val[i] && val[i] <= 255)
            continue;
        else
        {
             isIPAdress = false;
             break;
        }   
    }
    
    if(!isIPAdress)
    {
        nums[5]++;
        return;
    }
    
    if(CheckAdressRange(val,"1.0.0.0","126.255.255.255"))
        nums[0] ++;
    else
        if(CheckAdressRange(val,"128.0.0.0","191.255.255.255"))
            nums[1] ++;
        else
            if(CheckAdressRange(val,"192.0.0.0","223.255.255.255"))
                nums[2] ++;
            else
                if(CheckAdressRange(val,"224.0.0.0","239.255.255.255"))
                    nums[3] ++;
                else
                    if(CheckAdressRange(val,"240.0.0.0","255.255.255.255"))
                        nums[4] ++;
    
    bool flag1 = CheckAdressRange(val,"10.0.0.0","10.255.255.255");
    bool flag2 = CheckAdressRange(val,"172.16.0.0","172.31.255.255");
    bool flag3 = CheckAdressRange(val,"192.168.0.0","192.168.255.255");
    
    if(flag1 || flag2 || flag3)
	{
        nums[6] ++;
		cout << str << "\n";
	}
}

bool CheckMask(char * str,int * nums)
{
    char * p = str;
    int nDots = 0;
    int val[4] = { 0 };
    int nIndex = 0;
    bool isIPAdress = true;
	bool bVaild = false;
    while(*p != 0)
    {
        char ch = * p;
        if(ch == '.')
        {
            nDots++;
            if (bVaild) 
			{
				nIndex++;
				bVaild = false;
			}
            if(nDots >= 4)
            {
                isIPAdress = false;
                break;
            }
        }
        else
        {
            if(ch >= '0' && ch <= '9')
			{
				bVaild = true;
                val[nIndex] = val[nIndex] * 10 + ch - '0';
			}
            else
			{
                isIPAdress = false;
                break;
            }
        }
		p++;
    }
    
    if(!isIPAdress || 3 != nDots  || 3 != nIndex)
    {
        nums[5]++;
        return isIPAdress;
    }
    
    for(int i = 0 ; i < 4 ;  i ++)
    {
        if(0 <= val[i] && val[i] <= 255)
            continue;
        else
        {
             isIPAdress = false;
             break;
        }   
    }
    
    if(!isIPAdress)
    {
        nums[5]++;
        return isIPAdress;
    }
    
    char strIP[33] = { 0 };
    for( i = 3 ; i >= 0 ; i --)
    {
        int number = val[i];
        for(int j = 7 ; j >= 0 ; j--)
        {
            strIP[i*8+j] = number & 0x1;
            number = number >> 1;
        }
    }
    
    int nPos = 0;
    for( i = 0 ; i < 32 ; i++)
    {
        if(strIP[i]) 
            nPos++;
        else
            break;
    }

	if(32 == nPos || 0 == nPos)
    {
		isIPAdress = false;
		nums[5]++;
		return isIPAdress;
	}
	
//     if(32 == nPos)
//         return true;
//     
//     if(0 == nPos)
//     {
//         //首位是0，其他所有位必须是0
//         if(val[0] || val[1] || val[2] || val[3])
// 		{
// 			isIPAdress = false;
//             nums[5]++;
// 		}
//         
//         return isIPAdress;
//     }
    
    for( i = nPos ; i < 32 ; i++)
    {
        if(strIP[i])
        {
			isIPAdress = false;
            nums[5]++;
            break;
        }
    }
    return isIPAdress;
}


void GetShortFileName(string & strFile)
{
    int nlen =  strFile.length();
    if(0 == nlen) return;
    int npos = strFile.rfind('\\');
    string s = strFile.substr(npos + 1,nlen - 1 - npos);
    string strName = s,strExt = "";
	npos = s.rfind('.');
    if(npos != -1)
    {
        strName = s.substr(0,npos);
        strExt = s.substr(npos,s.length()-npos);
        nlen = strName.length();
        if(nlen > 16)
            strName = strName.substr(nlen-16,16);
    }
    strFile = strName + strExt;
}

int main()
{
	int nums[7] = { 0 };
	FILE * fp = NULL;
	fp = fopen("data.txt","r");
	char str[256] = { 0 };
	while(fscanf(fp,"%s",str)!=EOF)
	{
		char s1[50] = { 0 };
		char s2[50] = { 0 };
        sscanf(str,"%[^~]~%s",s1,s2);
		if (CheckMask(s2,nums))
			CheckIP(s1,nums);
	}

    for(int i = 0 ; i < 7 ; i++)
    {
        if(i != 6)
            cout << nums[i] << " ";
        else
            cout << nums[i] << endl;
    }
	return 0;
}
