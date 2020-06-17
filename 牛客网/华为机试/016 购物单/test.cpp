#include <iostream>
#include <math.h>
using namespace std;

#define  M 1738
#define  N 55

int max(int a,int b)
{
	return a > b ? a : b;
}

int main()
{
    int nArr[N+1][M+1] = {{0}};
    int nCost[N] = {0};				//花费
    int nVol[N]   = {0};			//物体体积
    int bagV = 1738;

	int v,p,q;
	FILE * fp = fopen("data.txt","r");
	fscanf(fp,"%d%d",&v,&p);

	for (int i = 0 ; i < N ; i++)
	{
		fscanf(fp,"%d%d%d",&v,&p,&q);
		nVol[i] = v;
		nCost[i] = v*p;
	}
	fclose(fp);

    for( i = 1; i<=N ; i++)
    {
        for( int j = 1; j<=bagV; j++)
        {
            if(j<nVol[i-1])
                nArr[i][j] = nArr[i-1][j];
            else
                nArr[i][j] = max(nArr[i-1][j] , nArr[i-1][j-nVol[i-1]] + nCost[i-1]);       
        }
    }
    cout<<nArr[N][bagV]<<endl;
	
    return 0;
}