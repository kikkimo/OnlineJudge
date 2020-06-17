#include <stdio.h>
#include <STRING.H>
#include <windows.h>

int findCharInString(char * s,char ch)
{
	int nPos = 0;
	char * p = s;
	while (*p != '\0')
	{
		if (*p == ch)
			return nPos;
		p ++;
		nPos ++;
	}
	return -1;
}

int lengthOfLongestSubstring(char* s) {
	int nlen = strlen(s);
	int nMaxSubStringLen = 0;
	char * pBuffer = NULL;
	char * p1 = s;
	char * p2 = s;
	int i = 0;					//循环变量
	int nSublen1 = 1;			//前一个不重复子串的长度
	int nSublen2 = 0;			//切分后字符串递归查找的最大子串长
	if (nlen <= 1) return nlen;
	
	pBuffer = (char*)malloc(nlen+1);
	memset(pBuffer,0,nlen+1);
	pBuffer[0] = s[0];
	p1++;
	while(*p1 != '\0')
	{
		int nPos = findCharInString(pBuffer, *p1);
		if (nPos == -1)			//未在子串中找到当前字符
		{
			nSublen1 ++;
			pBuffer[strlen(pBuffer)] = *p1;
			p1++;
		}
		else
		{
			if (nSublen1 < nlen - nPos - 1)
			{
				if (pBuffer)
				{
					free(pBuffer);
					pBuffer = NULL;
				}
				for (i = 0 ; i < nPos + 1 ; i++)
					p2++;
				nSublen2 = lengthOfLongestSubstring(p2);
			}
			break;
		}
	}
	if (pBuffer)
	{
		free(pBuffer);
		pBuffer = NULL;
	}
	nMaxSubStringLen = nSublen1 > nSublen2 ? nSublen1 : nSublen2;
	return nMaxSubStringLen;
}

int main()
{
	char test1[9] = {"abcabcbb"};
	char test2[9] = {"bbbbb"};
	char test3[19] = {"aedvdfq123"};

	printf("%d %d %d\n",lengthOfLongestSubstring(test1),lengthOfLongestSubstring(test2),lengthOfLongestSubstring(test3));
	return 0;
}