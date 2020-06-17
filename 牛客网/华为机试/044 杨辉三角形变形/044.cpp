#include <iostream>
#include <vector>
using namespace std;

vector<int> GetHalfLineNumber(int n,int & nPos)
{
    vector<int> result;
    if(1 == n)
    {
        result.push_back(1);
        nPos = -1;
        return result;
    }
    else
		if(2 == n)
		{
			result.push_back(1);
			result.push_back(1);
			nPos = -1;
			return result;
		}
		else
		{
			int tmp = 0;
			vector<int> lastLine = GetHalfLineNumber(n - 1,tmp);
			result.push_back(1);
			nPos = 1;
			bool findPos = false;
			for(int i = 0 ; i < (int)lastLine.size() ; i++ )
			{
				int a =  ((i - 1) >= 0 ? lastLine[i-1] : 0);
				int b = lastLine[i];
				int c =  ((i+1) < (int)lastLine.size() ? lastLine[i+1] : lastLine[i-1]);
				result.push_back(a+b+c);
				if((a + b + c) % 2 == 0 && !findPos)
				{
					nPos = i + 2;
					findPos = true;
				}
			}
			return result;
		}
}

int main()
{
    int n;
    while(cin >> n)
    {
        //大于1的奇数行，偶数必然在第二个数出现。偶数行第三个数出现
        int nPos = 0;
        if(n <= 2)
            nPos = -1;
        else
            GetHalfLineNumber(n,nPos);
        cout << nPos << endl;
    }
    return 0;
}

