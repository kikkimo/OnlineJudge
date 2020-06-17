#include <iostream>
using namespace std;

int main()
{
    string str;
    while(cin >> str)
    {
        int nlen = str.length();
        int map[128] = { 0 };
        int counts =0;
        for(int i = 0 ; i < nlen ; i ++)
        {
            char ch = str[i];
            if(0 <= ch && ch <= 127)
            {
                map[ch]++;
                if(map[ch] == 1)
                    counts++;
            }
        }
        cout << counts;
    }
}