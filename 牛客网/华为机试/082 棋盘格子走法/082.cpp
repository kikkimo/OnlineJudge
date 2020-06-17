#include <iostream>
#include <memory.h>
using namespace std;

int main()
{
    int n,m;
    while(cin >> n >> m)
    {
        if(0 == n || 0 == m)
            cout << 0 << endl;
        int ** dp = new int *[(n+2)*(m+2)];
        for(int i = 0 ; i < m+2 ; i++)
        {
            dp[i] = new int[n+2];
            memset(dp[i],0,sizeof(int)*(n+2));
        }
        
        for(int i = 1 ; i <= m+1 ; i++)
        {
            for(int j = 1 ; j <= n+1 ; j++)
            {
                if(i == 1 && j == 1)
                    dp[i][j] = 1;
                else
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        int result = dp[m+1][n+1];
        for(int i = 0 ; i < m+2 ; i++)
            delete [] dp[i];
        delete [] dp;
        cout << result << endl;
    }
    return 0;
}