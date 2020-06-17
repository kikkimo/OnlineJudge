#include <iostream>
using namespace std;

bool judgeNum(int n)
{
    if(0 == n)        //ÕýÕûÊý
        return false;
    if(n % 7 == 0)
        return true;
    bool bOk = false;
    while(n)
    {
        int a = n % 10;
        n /= 10;
        if(a == 7)
        {
            bOk = true;
            break;
        }
    }
    return bOk;
}

int main()
{
    int n;
    while(cin >> n)
    {
        int nCount = 0;
        for(int i = 1; i <= n ; i++)
            if(judgeNum(i)) nCount++;
        cout << nCount << endl;
    }
    return 0;
}