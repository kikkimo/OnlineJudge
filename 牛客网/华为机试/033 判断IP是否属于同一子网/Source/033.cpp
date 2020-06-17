#include <iostream>
#include <string>
using namespace std;

bool CheckIP(string str)
{
    int nDots = 0;
    int val[4] = { 0 };
    int nIndex = 0;
    bool isIPAdress = true;
	bool bVaildVal = false;
    int nlen = str.length();
    int pos = 0;
    while(pos < nlen)
    {
        char ch = str[pos];
        if(ch == '.')
        {
            nDots++;
            if (bVaildVal) 
			{
				nIndex++;
				bVaildVal = false;
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
				bVaildVal = true;
                val[nIndex] = val[nIndex] * 10 + ch - '0';
			}
            else
			{
                isIPAdress = false;
                break;
            }
        }
		pos++;
    }
    
    if(!isIPAdress || 3 != nDots || 3 != nIndex)
        return false;
    
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
    
    return isIPAdress;
}

bool CheckMask(string str)
{
    int nDots = 0;
    int val[4] = { 0 };
    int nIndex = 0;
    bool isMask = true;
	bool bVaildVal = false;
    int nlen = str.length();
    int pos = 0;
    while(pos < nlen)
    {
        char ch = str[pos];
        if(ch == '.')
        {
            nDots++;
            if (bVaildVal) 
			{
				nIndex++;
				bVaildVal = false;
			}
            if(nDots >= 4)
            {
                isMask = false;
                break;
            }
        }
        else
        {
            if(ch >= '0' && ch <= '9')
			{
				bVaildVal = true;
                val[nIndex] = val[nIndex] * 10 + ch - '0';
			}
            else
			{
                isMask = false;
                break;
            }
        }
		pos++;
    }
    
    //修正255.255.0 这种为掩码
    if(!isMask || nDots < 2 || nDots > 3 || nIndex < 2 || nIndex > 3)
        return false;
//    if(!isMask || 3 != nDots  || 3 != nIndex)
//        return false;
    
    for(int i = 0 ; i < 4 ;  i ++)
    {
        if(0 <= val[i] && val[i] <= 255)
            continue;
        else
        {
             isMask = false;
             break;
        }   
    }
    
    if(!isMask)
        return isMask;
    
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
		isMask = false;
		return isMask;
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
			isMask = false;
            break;
        }
    }
    return isMask;
}

int checkNetSegment(string mask, string ip1, string ip2) 
{     
    if(!(CheckIP(ip1) && CheckIP(ip2) && CheckMask(mask)))
        return 1;
    
    int valMask[4] = { 0 };
    int valIP1[4] = { 0 };
    int valIP2[4] = { 0 };
    
    sscanf(mask.c_str(),"%d.%d.%d.%d",valMask,valMask+1,valMask+2,valMask+3);
    sscanf(ip1.c_str(),"%d.%d.%d.%d",valIP1,valIP1+1,valIP1+2,valIP1+3);
    sscanf(ip2.c_str(),"%d.%d.%d.%d",valIP2,valIP2+1,valIP2+2,valIP2+3);
    
    int nRe = 0;
    
    for(int i = 0 ; i < 4 ; i ++)
    {
		int m = valIP1[i] & valMask[i];
		int n = valIP2[i] & valMask[i];
        if((valIP1[i] & valMask[i]) != (valIP2[i] & valMask[i]))
        {
            nRe = 2;
            break;
        }
    }
    
    return nRe;
}

int main()
{
    string mask,ip1,ip2;
    while(cin >> mask >> ip1 >> ip2)
        cout << checkNetSegment(mask,ip1,ip2) << endl;
    return 0;
}