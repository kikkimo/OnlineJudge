#include <iostream>
using namespace std;

int main()
{
    string str;
    while(cin >> str)
    {
        int nlen = str.length();
        if(0 == nlen) break;
        
        int num = 0;
        int map[10] = { 0 };
        for(int i = nlen -1 ; i >= 0 ; i--)
        {
            char ch = str[i];
            int val = ch - '0';
            map[val]++;
            if(map[val] == 1)
                num = num * 10 + val;
        }
        cout << num;
    }
    return 0;
}