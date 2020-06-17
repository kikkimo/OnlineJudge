#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef struct _tagMatrix{
    int m;
    int n;
}Mat;

int MultCount(Mat a,Mat b)
{
    if(a.n != b.m)
        return 0;
    else
        return a.m*a.n*b.n;
}

int main()
{
    int N;
    while(cin >> N)
    {
        if(N <= 0)
            continue;
        if(1 == N)
        {
            cout << 0 << endl;
            continue;
        }
        vector<Mat> vec_Mat;
        for(int i = 0 ; i < N ;i++)
        {
            int m,n;
            Mat mt;
            cin >> m >> n;
            mt.m = m;
            mt.n = n;
            vec_Mat.push_back(mt);
        }
        string str;
        cin >> str;
        int nlen = str.length();
        if(0 == nlen)
        {
            cout << 0 << endl;
            continue;
        }
        stack<char> opt_stack;
        stack<int>  index_stack;
        bool bError = false;
        int sum = 0;
        for(int i = 0 ; i < nlen; i ++)
        {
            char ch = str[i];
            if(ch == '(')
            {
                opt_stack.push(ch);
                continue;
            }
            else
                if(ch == ')')
                {
                    if((int)index_stack.size() < 2)
                    {
                        bError = true;
                        break;
                    }
                    int index2 = index_stack.top();
                    index_stack.pop();
                    int index1 = index_stack.top();
                    index_stack.pop();
                    int mult = MultCount(vec_Mat[index1],vec_Mat[index2]);
                    sum += mult;
                    Mat mt;
                    mt.m = vec_Mat[index1].m;
                    mt.n = vec_Mat[index2].n;
                    vec_Mat.push_back(mt);
                    int newIndex = (int)vec_Mat.size() - 1;
                    index_stack.push(newIndex);
                    opt_stack.pop();
                }
                else
                {
                    int val = ch - 'A';
                    index_stack.push(val);
                }
        }
        cout << sum << endl;
    }
    return 0;
}
