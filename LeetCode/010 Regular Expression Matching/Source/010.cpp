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
		//s字符串为空，p必须为a*.*c*这种字符串才能匹配
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
		//p为 a*或.*开头与s匹配
		do 
		{
			//首先要进行一次匹配，如果直接执行while，那么s ="ab"与 p = "c*ab"无法匹配
			if (isMatch(s.substr(++i),p.substr(2)))  //这里必须为++i,当i为nlenS-1时判断一次while循环条件，还需要匹配一次
			{										 //如果这里是i++,当i为nlenS-1时isMatch返回失败后，会直接跳出循环
				bOk = true;
				break;
			}
			if(i >= nlenS)
				break;
		} while (s[i] == p[0] || p[0] == '.');  //当不匹配时s截取的字符只能和p第一位一致或者p[0]='.'
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