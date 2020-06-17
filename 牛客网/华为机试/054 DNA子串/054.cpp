#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    string str;
    while(cin >> str >> n)
    {
        int nlen = str.length();
        if(n > nlen)
            continue;
        
        string strMaxGC = "";
        int nMaxCount = 0;
        for(int i = 0 ; i <= nlen - n ; i++)
        {
            string s = str.substr(i,n);
            int count = 0;
            for(int j = 0 ; j < n ; j++)
                if(s[j] == 'G' || s[j] == 'C')
                    count++;
            if(count > nMaxCount)
            {
                strMaxGC = s;
                nMaxCount = count;
            }
        }
        cout << strMaxGC << endl;
    }
    return 0;
}