#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <string.h>
#include <stack>
using namespace std;

vector<string> GetArrangement(int * nums,int size)
{
    vector<string> result;
    if(0 == size)
        return result;
    if(1 == size)
    {
        char sz[10] = { 0 };
        sprintf(sz,"%d",nums[0]);
        string s(sz);
        result.push_back(s);
        return result;
    }
    else
    {
        int * N = new int[size];
        memcpy(N,nums,sizeof(int)*size);
        
        for(int i = 0 ; i < size ; i++)
        {
            int val = N[i];
            char sz[10] = { 0 };
            sprintf(sz,"%d",val);
            if(i != 0)
            {
                N[i] = N[0];
                N[0] = val;
            }
            vector<string> vec_s = GetArrangement(N+1,size-1);
            for(int j = 0 ; j < (int)vec_s.size() ; j++)
            {
                string s = vec_s[j];
                s = sz + s;
                result.push_back(s);
            }
        }
        delete [] N;
        return result;
    }
}

bool isAvaild(string s)
{
    int nlen = s.length();
    if(0 == nlen)
        return false;
    if(1 == nlen)
        return true;
    
    stack<int> train_stack;
    bool bOk = true;
    int nPos = 0;
    for(int i = 0 ; i < nlen ; i++)
    {
        if(train_stack.size() == 0)
        {
            int val = s[i] - '0';
            for(int j = nPos + 1 ; j <= val ; j++)
                train_stack.push(j);
            nPos = val;
            train_stack.pop();
        }
        else
        {
            int val = s[i] - '0';
            int top = train_stack.top();
            if(val < top)
            {
                bOk = false;
                break;
            }
            else
                if(val == top)
                    train_stack.pop();
                else
                {
                    for(int j = nPos + 1 ; j <= val ; j++)
                        train_stack.push(j);
                    nPos = val;
                    train_stack.pop();
                }
        }
    }
    return bOk;
}

int main()
{
    int N;
    while(cin >> N)
    {
        vector<int> nums;
        int * A = new int[N];
        for(int i = 0 ; i < N ; i++)
        {
            int tmp;
            cin >> tmp;
            nums.push_back(tmp);
            A[i] = i + 1;
        }
        vector<string> vec_index = GetArrangement(A,N);
        delete [] A;
    
        vector<string> vec_str;
        for( i = 0 ; i < (int)vec_index.size() ; i++)
        {
            string s = vec_index[i];
            if(isAvaild(s))
            {
                string sbuf = "";
                for(int j = 0 ; j < (int)s.size() ; j++)
                {
                    int index = s[j] - '1';
                    char sz[10] = { 0 };
                    if(j != (int)s.size() - 1)
                       sprintf(sz,"%d ",nums[index]);
                    else
                       sprintf(sz,"%d",nums[index]);
                    sbuf += sz;
                }
                vec_str.push_back(sbuf);
            }
        }
        vec_index.clear();
        nums.clear();
        sort(vec_str.begin(),vec_str.end());
        for( i = 0 ; i < (int)vec_str.size() ; i++)
            cout << vec_str[i] << endl;
    }
    return 0;
}