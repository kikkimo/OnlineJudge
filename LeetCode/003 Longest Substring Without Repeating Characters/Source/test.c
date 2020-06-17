#include <stdio.h>
#include <STRING.H>
#include <windows.h>

int nCharPos[128] = { 0 };			//每个字符首次出现的位置
int nCharCount[128] = { 0 };		//每个字符计数


//我的算法思路是将字符串分成2部分：①与②
//①：第一部分是从第一个字符开始的没有任何字符重复的字符串。
//②：第二部分是当某个字符第一次重复时，找到其在原始字符串第一次出现的位置N，查找从字符N+1开始的子串最大不重复长度
//最终最长子串长度是①与②的最大值。特别的，当①长度大于剩余子串长度，②不需要重复查找

int lengthOfLongestSubstring1(char* s) {
	int nlen = strlen(s);
	int nMaxSubStringLen = 0;
	char * p = s;
	int nSublen1 = 0;				//前一个不重复子串的长度
	int nSublen2 = 0;				//去掉第一个重复字后字符串递归查找的最大子串长
	if (nlen <= 1) return nlen;
	
	memset(nCharPos,0,128*sizeof(int));
	memset(nCharCount,0,128*sizeof(int));

	while(*p != '\0')
	{
		nCharCount[*p] ++;
		if (nCharCount[*p] < 2)			//字符表中每个字符出现次数小于2次
		{
			nCharPos[*p] = nSublen1;			//将当前位置记录字符本身的位置
			nSublen1++;
			p++;
		}
		else
		{
			int nPos = nCharPos[*p];
			if (nSublen1 < nlen - nPos - 1)		//若子串1比剩下子串长度更长，则不需要在剩下子串中查找
			{
				p = s + nPos + 1;
				nSublen2 = lengthOfLongestSubstring1(p);
			}
			break;
		}
	}
	nMaxSubStringLen = nSublen1 > nSublen2 ? nSublen1 : nSublen2;
	return nMaxSubStringLen;
}


//最快算法思路：
//1、当遇到重复字符，则最大子串从该重复字符计算起。
//2、用一个标识记录第一个非重复字符开始的地方，当发现有字符重复了，且上一次重复字符位置在start之后，将start更新为上一次位置
int lengthOfLongestSubstring2(char* s){
	int dict[128] = { -1 };			//每个字符的位置
	int maxLen = 0, start = -1;
	int i;
	int nlen = strlen(s);
	for (i = 0 ; i < 128 ; i++)
		dict[i] = -1;
	for ( i = 0; i != nlen; i++) {
		if (dict[s[i]] > start)		//每个字符开始的位置为-1，若当前字符位置比开始计数位置大，说明2点
			start = dict[s[i]];		//1、该字符重复了（不重复位置是-1）；2、该重复的字符是上一次计数起点后的字符重复
		dict[s[i]] = i;				//结合上面2点，应该把新的起始位置记为当前重复字符上一次出现的位置。
		maxLen = maxLen > i - start ? maxLen : i - start ;
	}
	return maxLen;
 }


int main()
{
//	char test1[11119] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()"};

	FILE * fp = NULL;
	char * pTest = NULL;
	int m = 0;
	fp = fopen("test.dat","r");
	pTest = (char*)malloc(40000);
	memset(pTest,0,40000);
	fgets(pTest,40000,fp);
	fclose(fp);
	m = lengthOfLongestSubstring2(pTest);
	free(pTest);
	printf("%d\n",m);
	return 0;
}