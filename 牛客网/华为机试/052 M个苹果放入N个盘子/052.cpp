#include <iostream>
using namespace std;

//M��ƻ����N������
int sort(int M,int N,int minNum)
{
    if(N == 1 || M == 0)
        return 1;
    
    if(N > M)    //����������ض�������Ϊ��
        return sort(M,M,minNum);
    
    int maxNum0 = M / N;    //��1����������ܷ�ƻ���������ظ���
    int sum = 0;
    //��1������
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