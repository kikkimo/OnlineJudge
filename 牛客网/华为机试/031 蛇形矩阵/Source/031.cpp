#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

void GetResult(int Num,char * pResult)
{
    int * val = new int[Num*Num];
    memset(val,0,sizeof(int)*Num*Num);
    val[0] = 1;
	int i,j;
    for(i = 1 ; i < Num ; i++)
        val[i*Num] = val[(i-1)*Num] + i;
    
    for(i = 0 ; i < Num ; i++)
    {
        for(j = 1 ; j < Num - i ; j++)
            val[i*Num+j] = val[i*Num+j-1] + j + 1 + i;
    }
	
	for (i = 0 ; i < Num ; i++)
	{
		for(j = 0 ; j < Num - i ; j++)
		{
			char stemp[20] = { 0 };
			if (j == Num -i - 1)
				sprintf(stemp,"%d\n",val[i*Num+j]);
			else
				sprintf(stemp,"%d ",val[i*Num+j]);
			strcat(pResult,stemp);
		}
	}
    delete [] val;
}

int main()
{
	int m = 192&255;
    int num;
    while(scanf("%d",&num)!=EOF)
    {
        if(num <= 0) continue;
        int maxNum = (num+1)*num/2;
        int maxlen = 1;
        while(maxNum)
        {
            maxlen++;
            maxNum /= 10;
        }
        char * pResult = new char[maxlen*(num+1)*num/2+10];
        memset(pResult,0,maxlen*num);
		GetResult(num,pResult);
        if(pResult)
        {
            printf("%s",pResult);
            delete [] pResult;
        }
    }
	return 0;
}