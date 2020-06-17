#include <stdio.h>
#include <STRING.H>
#include <windows.h>

int nCharPos[128] = { 0 };			//ÿ���ַ��״γ��ֵ�λ��
int nCharCount[128] = { 0 };		//ÿ���ַ�����


//�ҵ��㷨˼·�ǽ��ַ����ֳ�2���֣������
//�٣���һ�����Ǵӵ�һ���ַ���ʼ��û���κ��ַ��ظ����ַ�����
//�ڣ��ڶ������ǵ�ĳ���ַ���һ���ظ�ʱ���ҵ�����ԭʼ�ַ�����һ�γ��ֵ�λ��N�����Ҵ��ַ�N+1��ʼ���Ӵ�����ظ�����
//������Ӵ������Ǣ���ڵ����ֵ���ر�ģ����ٳ��ȴ���ʣ���Ӵ����ȣ��ڲ���Ҫ�ظ�����

int lengthOfLongestSubstring1(char* s) {
	int nlen = strlen(s);
	int nMaxSubStringLen = 0;
	char * p = s;
	int nSublen1 = 0;				//ǰһ�����ظ��Ӵ��ĳ���
	int nSublen2 = 0;				//ȥ����һ���ظ��ֺ��ַ����ݹ���ҵ�����Ӵ���
	if (nlen <= 1) return nlen;
	
	memset(nCharPos,0,128*sizeof(int));
	memset(nCharCount,0,128*sizeof(int));

	while(*p != '\0')
	{
		nCharCount[*p] ++;
		if (nCharCount[*p] < 2)			//�ַ�����ÿ���ַ����ִ���С��2��
		{
			nCharPos[*p] = nSublen1;			//����ǰλ�ü�¼�ַ������λ��
			nSublen1++;
			p++;
		}
		else
		{
			int nPos = nCharPos[*p];
			if (nSublen1 < nlen - nPos - 1)		//���Ӵ�1��ʣ���Ӵ����ȸ���������Ҫ��ʣ���Ӵ��в���
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


//����㷨˼·��
//1���������ظ��ַ���������Ӵ��Ӹ��ظ��ַ�������
//2����һ����ʶ��¼��һ�����ظ��ַ���ʼ�ĵط������������ַ��ظ��ˣ�����һ���ظ��ַ�λ����start֮�󣬽�start����Ϊ��һ��λ��
int lengthOfLongestSubstring2(char* s){
	int dict[128] = { -1 };			//ÿ���ַ���λ��
	int maxLen = 0, start = -1;
	int i;
	int nlen = strlen(s);
	for (i = 0 ; i < 128 ; i++)
		dict[i] = -1;
	for ( i = 0; i != nlen; i++) {
		if (dict[s[i]] > start)		//ÿ���ַ���ʼ��λ��Ϊ-1������ǰ�ַ�λ�ñȿ�ʼ����λ�ô�˵��2��
			start = dict[s[i]];		//1�����ַ��ظ��ˣ����ظ�λ����-1����2�����ظ����ַ�����һ�μ���������ַ��ظ�
		dict[s[i]] = i;				//�������2�㣬Ӧ�ð��µ���ʼλ�ü�Ϊ��ǰ�ظ��ַ���һ�γ��ֵ�λ�á�
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