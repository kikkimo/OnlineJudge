#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    while(cin >> str)
    {
        int counts[26] = { 0 };
        int nlen = str.length();
        int minNum = nlen;
        for(int i = 0 ; i < nlen ; i++)
            counts[str[i]-'a']++;
        for( i = 0 ; i < 26 ; i++)
			if (counts[i])
				minNum = (minNum < counts[i] ? minNum : counts[i]);
        string s = "";
        for( i = 0 ; i < nlen ; i++)
        {
            if(minNum != counts[str[i]-'a'])
                s += str[i];
        }
        cout << s << "\n";
    }
	return 0;
}