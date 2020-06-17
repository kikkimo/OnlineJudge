#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    while(getline(cin,str))
    {
        int nlen = str.length();
        bool flag = false;
        string s;
        for(int i = 0 ; i < nlen ; i++)
        {
            if('0'<=str[i]&&str[i]<='9')
            {
                if(!flag)
                    s = s + "*" + str[i];
                else
                    s = s + str[i];
                flag = true;
            }
            else
            {
                if(flag)
                    s = s + "*" + str[i];
                else
                    s = s + str[i];
                flag = false;
            }
        }
        if('0'<=s[(int)s.length()-1]&&s[(int)s.length()-1]<='9')
            s += "*";
        cout << s << endl;
    }
    return 0;
}