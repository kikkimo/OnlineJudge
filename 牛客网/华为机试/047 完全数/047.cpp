#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

bool isPerfectNum(int n)
{
    if(1 == n)
        return true;
    if(2<= n && n < 28)
        return false;
    
    vector<int> divisors;
    int v = (int)sqrt(n) + 1;
    bool bIsPrime = true;
    for(int i = 2 ; i <= v ; i++)
    {
        if(n % i == 0)
        {
            bIsPrime = false;
            divisors.push_back(i);
        }
    }
    
    if(bIsPrime)
        return false;
    else
    {
        int sum = 1;
        for(int i = 0 ; i < (int)divisors.size() ; i++)
        {
            int val = divisors[i];
            sum += val;
            val = n / val;
            sum += val;
        }
        if(n == sum)
            return true;
        else
            return false;
    }
}

int main()
{
    int n;
    while(cin >> n)
    {
        int count = 0;
        for(int i = 1 ; i <= n ; i++)
            if(isPerfectNum(i)) count++;
        cout << count << endl;
    }
    return 0;
}

    