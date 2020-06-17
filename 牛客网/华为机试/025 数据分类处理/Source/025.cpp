#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string num2string(int n)
{
    if(0 == n)
        return "0";
    else
    {
        string s = "";
        while(n)
        {
            int a = n % 10;
            char ch = a + '0';
            n /= 10;
            s = ch + s;
        }
        return s;
    }
}

int main()
{
    int numSize1,numSize2;
    cin >> numSize1;
    if(0 == numSize1)
    {
        cout << 0 << endl;
        return 0;
    }
       
    vector<int> vec_I;
    for(int i = 0 ; i < numSize1 ; i++)
    {
        int tmp;
        cin >> tmp;
        vec_I.push_back(tmp);
    }
    cin >> numSize2;
    if(0 == numSize2)
    {
        cout << 0 << endl;
        return 0;
    }
    
    vector<int> vec_R;
    for( i = 0 ; i < numSize2 ; i++)
    {
        int tmp;
        cin >> tmp;
        vec_R.push_back(tmp);
    }
    sort(vec_R.begin(),vec_R.end());
    int R = vec_R[0] - 1;
    vector<int> result;
    for( i = 0 ; i < numSize2 ; i++)
    {
        if(vec_R[i] == R)
            continue;
        
        R = vec_R[i];
        string strR = num2string(R);
        vector<int> vec_index;
        for(int j = 0 ; j < numSize1 ; j++)
        {
            string strI = num2string(vec_I[j]);
            if(strI.find(strR) != string::npos)
            {
                vec_index.push_back(j);
                vec_index.push_back(vec_I[j]);
            }
        }
        int nSizeIndex = vec_index.size();
        if(nSizeIndex > 0)
        {
           result.push_back(R);
           result.push_back(nSizeIndex / 2);
           for(int j = 0 ; j < nSizeIndex ; j++)
               result.push_back(vec_index[j]);
        }
    }
    int nSize = result.size();
    if(0 == nSize)
        cout << 0 << endl;
    else
    {
        cout << nSize << " ";
        for(int i = 0 ; i < nSize ; i ++)
        {
            cout << result[i];
            if(i != nSize -1)
                cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}