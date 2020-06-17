#include <iostream>
using namespace std;

//M个苹果，N个盘子
int sort(int M,int N,int minNum)
{
    if(N == 1 || M == 0)
        return 1;
    
    if(N > M)    //盘子数更多必定有盘子为空
        return sort(M,M,minNum);
    
    int maxNum0 = M / N;    //第1个盘子最多能放苹果数（不重复）
    int sum = 0;
    //第1个盘子
    for(int i = minNum ; i <= maxNum0 ; i++)
        sum += sort(M-i,N-1,i);
    return sum;
}

int main()
{
    int M,N;
    while(cin >> M >> N)
        cout << sort(M,N,0) << endl;
    return 0;
}