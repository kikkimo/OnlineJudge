#include <iostream>
using namespace std;

int main()
{
    int num;
    while(cin >> num)
    {
        int nCount = 0;
        while(num)
        {
            int a = num % 2;
            nCount = a ? nCount + 1 : nCount;
            num = num >> 1;
        }
        cout << nCount;
    }
    return 0;
}