#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define  min(a,b) ((a < b) ? a : b)

int main()
{
    int n,m;
    while(cin >> n)
    {
        int tmp;
        vector<int> vec_n(n,0);
        for(int i = 0 ; i < n ; i++)
        {
            cin >> tmp;
            vec_n[i] = tmp;
        }
        cin >> m;
        vector<int> vec_m(m,0);
        for(int i = 0 ; i < m ; i++)
        {
            cin >> tmp;
            vec_m[i] = tmp;
        }
        sort(vec_n.begin(),vec_n.end());
        sort(vec_m.begin(),vec_m.end());
        int pos1 = 0,pos2 = 0;
        tmp = min(vec_n[0],vec_m[0])-1;
        while(pos1< n && pos2< m)
        {
            if(vec_n[pos1] < vec_m[pos2])
            {
                if(vec_n[pos1] != tmp)
                {
                    cout << vec_n[pos1];
                    tmp = vec_n[pos1];
                }
                else
                    pos1++;
            }
            else
            {
                if(vec_m[pos2] != tmp)
                {
                    cout << vec_m[pos2];
                    tmp = vec_m[pos2];
                }
                else
                    pos2++;
            }
        }
        
        if(pos1 < n)
        {
            for(int i = pos1 ; i < n ; i++)
            {
                if(vec_n[i] != tmp)
                {
                    cout << vec_n[i];
                    tmp = vec_n[i];
                }
            }
        }
        else
            if(pos2 < m)
            {
                for(int i = pos2 ; i < m ; i++)
                {
                    if(vec_m[i] != tmp)
                    {
                        cout << vec_m[i];
                        tmp = vec_m[i];
                    }
                }
            }
        vec_n.clear();
        vec_m.clear();
        cout<<endl;
    }
    return 0;
}