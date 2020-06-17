#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int num;
    while(cin >> num)
    {
        if(0 == num)
            continue;
        
        vector<string> svec;
        for(int i = 0 ; i < num ; i++)
        {
            string s;
            cin >> s;
            svec.push_back(s);
        }
        sort(svec.begin(),svec.end());
        
        for(int i = 0 ; i < svec.size() ; i++)
        {
            cout << svec[i];
            if(i != svec.size() - 1)
                cout << "\n";
        }
    }
    return 0;
}