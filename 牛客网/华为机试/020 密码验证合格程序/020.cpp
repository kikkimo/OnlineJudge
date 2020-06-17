#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    while(cin >> str)
    {
        int nlen = str.length();
        if(nlen <= 8)
        {
            cout << "NG\n";
            continue;
        }
        int Counts[4] = { 0 };
        for(int i = 0 ; i < nlen ; i++)
        {
            char ch = str[i];
            if('0' <= ch && ch <= '9')
                Counts[0]++;
            else
                if('a'<=ch && ch <='z')
                    Counts[1]++;
                else
                    if('A' <= ch && ch <= 'Z')
                        Counts[2]++;
                    else
                        Counts[3]++;
        }
        int nums = 0;
        for(int i = 0 ; i < 4 ; i ++)
            if(Counts[i]) nums++;
        
        if(nums < 3)
        {
            cout << "NG\n";
            continue;
        }
        bool bOk = true;
        for(int i = 0 ; i < nlen - 5 ; i++)
        {
            string sl = str.substr(i,3);
            string sr = str.substr(i+3,nlen-i-3);
            if(sr.find(sl) != -1)
            {
                bOk = false;
                break;
            }
        }
        if(bOk)
            cout << "OK\n";
        else
            cout << "NG\n";
    }
}