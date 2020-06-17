#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <math.h>
using namespace std;

int Calc(int a,int b,char ch)
{
	int result = 0;
	switch(ch)
	{
	case '+': result = a+b;break;
	case '-': result = a-b;break;
	case '*': result = a*b;break;
	case '/': result = a/b;break;
	case '^': result = pow(a,b);break;
	}
	return result;
}

bool IsOperator(char ch)
{
	return !('0' <= ch && ch <= '9');
}

//�����a���ȼ���b��
bool IsHigher(char a,char b)
{
	//a��b����Ϊ�����
	if (!IsOperator(a) || !IsOperator(b))
		return false;
	
	if (a == b)
		return false;
	
	if (a == '(')
		return false;		//���������ȼ����
	
	if (a == '+' || a == '-')
	{
		if (b == '(')		// +��- ���ȼ�������������
			return true;
		else
			return false;
	}
	
	if (a == '*' || a == '/')
	{
		if (b == '(' || b == '+' || b == '-')		// *��/ ���ȼ����� �����š�+��- 
			return true;
		else
			return false;
	}
	
	if (a == '^')
	{
		if (b == '(' || b == '+' || b == '-'
			|| b == '*' || b == '/')		// ^ ���ȼ����� �����š�+��-��*��/  
			return true;
		else
			return false;
	}
	
	return false;
}

//������תΪ#�ŷ��㴦��,������ȫת��ΪС����
void CovertString(string & s)
{
	int nlen = s.length();
	if(0 == nlen)
		return;

	if(s[0] == '-')		//�׸���Ϊ����
		s[0] = '#';

	for (int i = 1 ; i < nlen ; i++)
	{
		if (s[i] == '{' || s[i] == '[')
			s[i] = '(';

		if (s[i] == '}' || s[i] == ']')
			s[i] = ')';

		//����ǰһ�����������֡�������ʱ���÷����Ǹ���
		if (s[i] == '-')
		{
			if (('0' <= s[i-1] && s[i-1] <= '9') || s[i-1] == ')')
				continue;
			else
				s[i] = '#';
		}
	}
}

int EvaluateExpression(string str)
{
	int nlen = str.length();
	if(0 == nlen)
		return 0;

	int pos = 0;

	stack<int>	num_stack;
	stack<char>	opt_stack;

	char buffer[30] = { 0 };
	int bufferIndex = 0;
	while(pos < nlen)
	{
		if (0 == pos)
		{
			if (!IsOperator(str[pos]))			//��ǰ�ַ�Ϊ����
				buffer[bufferIndex++] = str[pos];
			else
				if(str[pos] == '(' || str[pos] == '#' )	//���ź�������ǿ����ջ
					opt_stack.push(str[pos]);

			pos++;
			continue;
		}
		
		bool flag = IsOperator(str[pos]);
		bool flagLeft = IsOperator(str[pos-1]);

		if (!flag)		//��ǰ�ַ�Ϊ����
		{
			buffer[bufferIndex++] = str[pos];	
			if ( ++pos == nlen)
			{
				//���ʽĩβ���һ�����֣���Ҫѹ������ջ
				int val = atoi(buffer);
				memset(buffer,0,30);
				bufferIndex = 0;
				num_stack.push(val);
			}
			continue;
		}
		else
		{
			if (!flagLeft)		//��ǰ�ַ��������ͬʱ��һ���ַ�������
			{
				//��Ҫ������ѹ������ջ
				int val = atoi(buffer);
				memset(buffer,0,30);
				bufferIndex = 0;
				num_stack.push(val);
			}
			
			
			if (str[pos] == '(' || str[pos] == '#' )		//��ǰ������Ϊ�����Ż��߸���ʱ��ǿ����ջ
			{
				opt_stack.push(str[pos]);
				pos++;
				continue;
			}
			
			if (str[pos] == ')')
			{
				char opt = opt_stack.top();
				while(opt != '(')
				{
					if (opt == '#')		//������
					{
						int val = num_stack.top();
						num_stack.pop();
						val = -val;
						num_stack.push(val);
						opt_stack.pop();
						opt = opt_stack.top();
						continue;
					}
					else
					{
						int v2 = num_stack.top();
						num_stack.pop();
						int v1 = num_stack.top();
						num_stack.pop();
						v1 = Calc(v1,v2,opt);
						num_stack.push(v1);
						opt_stack.pop();
						opt = opt_stack.top();
					}
				}
				
				//�ҵ���Ӧ�������ţ����䵯��ջ
				opt_stack.pop();
				pos++;
				continue;
			}
			else
			{
				if ((int)opt_stack.size() == 0)
				{
					opt_stack.push(str[pos]);
					pos++;
					continue;
				}
				//��ʱΪһ�������
				char opt1 = opt_stack.top();
				if ('#' == opt1)	//ջ��������Ϊ����
				{
					int val = num_stack.top();
					num_stack.pop();
					val = - val;
					num_stack.push(val);
					opt_stack.pop();
					
					if ((int)opt_stack.size() == 0)	//��������ջΪ��
					{
						opt_stack.push(str[pos]);
						pos++;
						continue;
					}
					else
						opt1 = opt_stack.top();
				}

				bool bHigher = IsHigher(str[pos],opt1);

				while(!bHigher)
				{
					int val2 = num_stack.top();
					num_stack.pop();
					int val1 = num_stack.top();
					num_stack.pop();
					val1 = Calc(val1,val2,opt1);
					num_stack.push(val1);
					opt_stack.pop();

					if ((int)opt_stack.size() == 0)	//��������ջΪ��
					{
						bHigher = true;
						break;
					}
					else
					{
						opt1 = opt_stack.top();
						bHigher = IsHigher(str[pos],opt1);
					}
				}

				if (bHigher)
					opt_stack.push(str[pos]);
				
				pos++;
				continue;
			}	
		}
	}

	while( (int)opt_stack.size() > 0 )
	{
		char opt = opt_stack.top();
		if (opt == '#')	//���������ջ��Ϊ����
		{
			int val = num_stack.top();
			val = -val;
			num_stack.pop();
			num_stack.push(val);
			opt_stack.pop();
			continue;
		}
		else
		{
			int val2 = num_stack.top();
			num_stack.pop();
			int val1 = num_stack.top();
			num_stack.pop();
			val1 = Calc(val1,val2,opt);
			num_stack.push(val1);
			opt_stack.pop();
		}
	}

	int result = 0;
	if ((int)num_stack.size() == 1)
	{
		result = num_stack.top();
		num_stack.pop();
	}
	return result;
}


int main(void)
{
	string str;
	while(cin >> str)
	{
		CovertString(str);
		cout << EvaluateExpression(str) << endl;
	}
	return 0;
}