#include <iostream>
#include <string>
using namespace std;


bool isMatch(string s, string p) {
	int nlenS = s.length();
	int nlenP = p.length();

	if (0 == nlenS && 0 == nlenP)
		return true;

	if (0 == nlenP && nlenS)
		return false;

	bool bOk = true;
	int i,j;
	if (0 == nlenS && nlenP)
	{
		//s�ַ���Ϊ�գ�p����Ϊa*.*c*�����ַ�������ƥ��
		if(nlenP % 2)
			return false;

		for (i = 0 ; i < nlenP ; i++)
		{
			if (i % 2 == 1 && p[i] != '*')
			{
				bOk = false;
				break;
			}
		}
		return bOk;
	}

	if (nlenP == 1)
		return (nlenS == 1 && (s[0] == p[0] || p[0] == '.'));

	if (p[1] == '*')
	{
		bOk = false;
		i = -1;
		//pΪ a*��.*��ͷ��sƥ��
		do 
		{
			//����Ҫ����һ��ƥ�䣬���ֱ��ִ��while����ôs ="ab"�� p = "c*ab"�޷�ƥ��
			if (isMatch(s.substr(++i),p.substr(2)))  //�������Ϊ++i,��iΪnlenS-1ʱ�ж�һ��whileѭ������������Ҫƥ��һ��
			{										 //���������i++,��iΪnlenS-1ʱisMatch����ʧ�ܺ󣬻�ֱ������ѭ��
				bOk = true;
				break;
			}
			if(i >= nlenS)
				break;
		} while (s[i] == p[0] || p[0] == '.');  //����ƥ��ʱs��ȡ���ַ�ֻ�ܺ�p��һλһ�»���p[0]='.'
	}
	else
	{
		if (s[0] == p[0] || p[0] == '.')
			bOk = isMatch(s.substr(1),p.substr(1));
		else
			bOk = false;
	}
	return bOk;
}

int main()
{
	string s,p;
	while(cin >> s >> p)
	{
		if (isMatch(s,p))
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	return 0;
}