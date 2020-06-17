#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

void fama(map<int,int> & result,int weight,int num)
{
    vector<int> vec_weight;
    for(int i = 1; i <= num ; i++)
        vec_weight.push_back(i*weight);
    
    int nSize = result.size();
    if(0 == nSize)
    {
		result[0] = 1;
        for(int i = 0 ; i < num ; i++)
            result[vec_weight[i]] = 1;
        vec_weight.clear();
    }
    else
    {
        vector<int> vec_AddWeight;        
        for(map<int,int>::iterator iter = result.begin(); iter != result.end() ; iter++)
        {
            int w = iter->first;
            for(int j = 0; j < num ; j++)
            {
                int addWeight = w + vec_weight[j];
                map<int, int>::iterator iter1;  
                iter1 = result.find(addWeight);
                if(iter1 == result.end())
                    vec_AddWeight.push_back(addWeight);
            }
        }
        vec_weight.clear();
        for( i = 0 ; i < (int)vec_AddWeight.size() ; i++)
            result[vec_AddWeight[i]] = 1;
    }
}

int main()
{
    int numCount;
    while(cin >> numCount)
    {
        vector<int> vec_weight;
        vector<int> vec_num;
        for(int i = 0 ; i < numCount ; i++)
        {
            int tmp;
            cin >> tmp;
            vec_weight.push_back(tmp);
        }
        for( i = 0 ; i < numCount ; i++)
        {
            int tmp;
            cin >> tmp;
            vec_num.push_back(tmp);
        }
        map<int,int> result;
        for( i = 0 ; i < numCount ; i++)
            fama(result,vec_weight[i],vec_num[i]);
        vec_weight.clear();
        vec_num.clear();
        int nSize = result.size();
        result.clear();
        cout << nSize << endl;
    }
    return 0;
}
