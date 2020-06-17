#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    int num;
    while(cin >> str >> num)
    {
        int nlen = str.length();
        if(num == 0)
        {
            str = "";
            cout << str << endl;
            continue;
        }
        if(num == 1)
        {
            if(str[0] < 0)
                cout << "" << endl;
            else
                cout << str[0] << endl;
            continue;
        } 
        if(num >= nlen)
        {
            cout << str << endl;
            continue;
        }
        if(0 <= str[num-1] && str[num-1] <= 127)
			str = str.substr(0,num);
        else
            if(str[num-1] < 0 && str[num-2] < 0)
                str = str.substr(0,num);
            else
                str = str.substr(0,num-1);
			cout << str << endl;
    }
    return 0;
}