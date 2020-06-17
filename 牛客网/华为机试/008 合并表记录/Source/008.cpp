#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

class Data
{
public:
    int index;
    int val;
    Data() { index = -1; val = 0; }
    Data(int _index,int _val) { index = _index; val = _val; }
};

bool comp(const Data &a, const Data &b)
{
    return a.index < b.index;
}

int main()
{
    int numSize = 0;
    while(cin >> numSize)
    {
        if(0 == numSize)
            break;
        
        vector<Data> data , result;
        for(int i = 0 ; i < numSize ; i++)
        {
            int nIndex,nVal;
            cin >> nIndex >> nVal;
            Data tmp(nIndex,nVal);
            data.push_back(tmp);
        }
        if(0 == data.size())
            break;
        sort(data.begin(),data.end(),comp);
        int index = data[0].index;
        int sum = 0;
        for(int i = 0 ; i < data.size() ; i++)
        {
            if(data[i].index == index)
                sum += data[i].val;
            else
            {
                Data tmp(index,sum);
                result.push_back(tmp);
                index = data[i].index;
                sum = data[i].val;
            }
        }
        Data tmp1(index,sum);
        result.push_back(tmp1);
        
        for(int i = 0 ; i < result.size() ; i++)
            cout << result[i].index << " " << result[i].val << "\n";
    }
    return 0;
}