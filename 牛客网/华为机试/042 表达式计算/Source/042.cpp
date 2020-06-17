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

//运算符a优先级比b高
bool IsHigher(char a,char b)
{
	//a与b必须为运算符
	if (!IsOperator(a) || !IsOperator(b))
		return false;
	
	if (a == b)
		return false;
	
	if (a == '(')
		return false;		//左括号优先级最低
	
	if (a == '+' || a == '-')
	{
		if (b == '(')		// +、- 优先级仅高于左括号
			return true;
		else
			return false;
	}
	
	if (a == '*' || a == '/')
	{
		if (b == '(' || b == '+' || b == '-')		// *、/ 优先级高于 左括号、+、- 
			return true;
		else
			return false;
	}
	
	if (a == '^')
	{
		if (b == '(' || b == '+' || b == '-'
			|| b == '*' || b == '/')		// ^ 优先级高于 左括号、+、-、*、/  
			return true;
		else
			return false;
	}
	
	return false;
}

//将负号转为#号方便处理,将括号全转换为小括号
void CovertString(string & s)
{
	int nlen = s.length();
	if(0 == nlen)
		return;

	if(s[0] == '-')		//首个必为负号
		s[0] = '#';

	for (int i = 1 ; i < nlen ; i++)
	{
		if (s[i] == '{' || s[i] == '[')
			s[i] = '(';

		if (s[i] == '}' || s[i] == ']')
			s[i] = ')';

		//仅当前一个符号是数字、右括号时，该符号是负号
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
			if (!IsOperator(str[pos]))			//当前字符为数字
				buffer[bufferIndex++] = str[pos];
			else
				if(str[pos] == '(' || str[pos] == '#' )	//负号和左括号强制入栈
					opt_stack.push(str[pos]);

			pos++;
			continue;
		}
		
		bool flag = IsOperator(str[pos]);
		bool flagLeft = IsOperator(str[pos-1]);

		if (!flag)		//当前字符为数字
		{
			buffer[bufferIndex++] = str[pos];	
			if ( ++pos == nlen)
			{
				//表达式末尾最后一个数字，需要压入数据栈
				int val = atoi(buffer);
				memset(buffer,0,30);
				bufferIndex = 0;
				num_stack.push(val);
			}
			continue;
		}
		else
		{
			if (!flagLeft)		//当前字符是运算符同时上一个字符是数字
			{
				//需要将数字压入数字栈
				int val = atoi(buffer);
				memset(buffer,0,30);
				bufferIndex = 0;
				num_stack.push(val);
			}
			
			
			if (str[pos] == '(' || str[pos] == '#' )		//当前操作符为左括号或者负号时，强制入栈
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
					if (opt == '#')		//处理负号
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
				
				//找到对应的左括号，将其弹出栈
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
				//此时为一般操作符
				char opt1 = opt_stack.top();
				if ('#' == opt1)	//栈顶操作符为负号
				{
					int val = num_stack.top();
					num_stack.pop();
					val = - val;
					num_stack.push(val);
					opt_stack.pop();
					
					if ((int)opt_stack.size() == 0)	//若操作符栈为空
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

					if ((int)opt_stack.size() == 0)	//若操作符栈为空
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
		if (opt == '#')	//如果操作符栈顶为负号
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