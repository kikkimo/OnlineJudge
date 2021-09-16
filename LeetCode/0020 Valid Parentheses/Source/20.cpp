#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isValid(string s) {
	 int nlen = s.length();
	 if (nlen  == 0)
		 return true;

	 if (nlen % 2 == 1)
		 return false;

	 stack<char> str;
	 bool result = true;
	 for (int i = 0 ; i < nlen ; i++)
	 {
		 char ch = s[i];
		 if (ch == '(' || ch == '[' || ch == '{' )
		 {
			 str.push(ch);
			 continue;
		 }
		 
		 if (ch == ')')
		 {
			 if (str.size() == 0)
			 {
				 result = false;
				 break;
			 }
			 char top = str.top();
			 if (top != '(')
			 {
				 result = false;
				 break;
			 }
			 else
			 {
				 str.pop();
				 continue;
			 }
		 }

		 if (ch == ']')
		 {
			 if (str.size() == 0)
			 {
				 result = false;
				 break;
			 }
			 char top = str.top();
			 if (top != '[')
			 {
				 result = false;
				 break;
			 }
			 else
			 {
				 str.pop();
				 continue;
			 }
		 }

		 if (ch == '}')
		 {
			 if (str.size() == 0)
			 {
				 result = false;
				 break;
			 }
			 char top = str.top();
			 if (top != '{')
			 {
				 result = false;
				 break;
			 }
			 else
			 {
				 str.pop();
				 continue;
			 }
		 }
	 }

	 if (result)
		 return str.size() == 0;
	 else
		 return result;
 }
