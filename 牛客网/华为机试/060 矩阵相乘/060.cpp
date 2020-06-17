#include <iostream>
using namespace std;

void mult(int * A,int * B,int * N,int m,int n,int p)
{
    for(int i = 0 ; i < m ; i ++)
    {
        for(int j = 0 ; j < p ; j ++)
        {
            //¼ÆËãN[i*p+j],iÐÐjÁÐ
            int sum = 0;
            for(int k = 0 ; k < n ; k++)
                sum += A[i*n+k]*B[k*p+j];
            N[i*p+j] = sum;
        }
    }    
}

int main()
{
    int m,n,p;
    while(cin >> m >> n >> p)
    {
        if(m == 0 || n == 0 || p == 0)
            continue;
        
        int * A =new int[m*n];
        int * B =new int[n*p];
        int * N =new int[m*p];
        for(int i = 0 ; i < m ; i ++)
            for(int j = 0 ; j < n ; j++)
                cin >> A[i*n+j];
        
        for(int i = 0 ; i < n ; i ++)
            for(int j = 0 ; j < p ; j++)
                cin >> B[i*p+j];
        
        mult(A,B,N,m,n,p);
        for(int i = 0 ; i < m ; i ++)
            for(int j = 0 ; j < p ; j++)
            {
                if(j != p-1)
                    cout << N[i*p+j] << " ";
                else
                    cout << N[i*p+j] << "\n";
            }
        delete [] A;
        delete [] B;
        delete [] N;
    }
    return 0;
}