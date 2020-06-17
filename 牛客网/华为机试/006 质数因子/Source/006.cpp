#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

bool IsPrimeNumber(long num)
{
    if(2 == num || 3 == num || 5 == num )
        return true;
    
    if(4 == num)
        return false;
    
    long val = (long)sqrt(num*1.0) + 1;
    bool result = true;
    for(long i = 2 ; i < val ; i ++)
    {
        if(num % i == 0)
        {
            result = false;
            break;
        }
    }
    return result;
}

void PrintNumArray(long data)
{
    if(IsPrimeNumber(data))
    {
        cout << data << " ";
        return;
    }
    long val = (long)sqrt(data*1.0) + 1;   
    for(long i = 2 ; i < val ; i ++)
    {
        if(data % i == 0)
        {
           cout << i << " ";
           PrintNumArray(data / i);
           return;
        }
    }
}

int main()
{
    long Data;
    while(cin >> Data)
    {
        PrintNumArray(Data);
        cout << endl;
    }
    return 0;
}