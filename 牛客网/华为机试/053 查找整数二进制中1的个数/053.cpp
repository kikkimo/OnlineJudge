#include <iostream>
using namespace std;

int main()
{
    int m;
    while(cin >> m)
    {
        int count = 0;
        while(m)
        {
            if(m&1) 
                count++;
            m = m >> 1;
        }
        cout << count << endl;
    }
    return 0;
}