#include <iostream>
#include <math.h>
using namespace std;

bool isPrimeNum(int n)
{
    if(1 == n || 4 == n)
        return false;
    if(2 == n || 3 == n || 5 == n)
        return true;
    
    int v = (int)sqrt(n) + 1;
    bool bOk = true;
    for(int i = 2 ; i <= v ; i++)
    {
        if(n % i == 0)
        {
            bOk = false;
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
        int a,b;
        if(n % 4 == 0)
        {
            a = n / 2 - 1;
            b = n / 2 + 1;
            while(a>1&&b<n&&!(isPrimeNum(a)&&isPrimeNum(b)))
            {
                a -= 2;
                b += 2;
            }
            cout << a << "\n" << b << endl;
        }
        else
            if(n % 2 == 0)
            {
                a = n / 2;
                b = n / 2;
                while(a>1&&b<n&&!(isPrimeNum(a)&&isPrimeNum(b)))
                {
                    a -= 2;
                    b += 2;
                }
                cout << a << "\n" << b << endl;
            }
    }
    return 0;
}