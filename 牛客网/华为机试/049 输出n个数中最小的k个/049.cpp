#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

void sort1(int * num,int l,int r)
{
    if(l >= r)
        return;
    
    int point = num[l];
    int i = l+1, j = r;
    while(i <= j)
    {
        while(j >= i && num[j] >= point)
            j--;
        while(j >=i && num[i] < point)
            i++;
        
        if(i < j)
        {
            int v = num[i];
            num[i] = num[j];
            num[j] = v;
            i++;
            j--;
        }
    }
    num[l] = num[j];
    num[j] = point;
    sort1(num,l,j);
    sort1(num,j+1,r);
}

void swap(int * a, int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void qsort1(int * a, int l, int r)
 {
	// 0����1��Ԫ�أ�����
	if (l >= r)
		return;
	// ѡ����˵�Ϊpivot
	int x = a[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) 
	{
		// С��pivot�ķŵ����
		if (a[i] < x) 
		{
			swap(a, ++j, i);
		}
	}
	// ������˵��pivotλ��
	swap(a, l, j);
	// �ݹ�������
	qsort1(a, l, j - 1);
	qsort1(a, j + 1, r);
}



int main()
{
    int n,index;
    while(scanf("%d%d",&n,&index) != EOF)
    {
        if(0 == n)
            continue;
        
        int * num = new int[n];
		vector<int> vec_num;
		srand(time(0));
        for(int i = 0 ; i < n ; i ++)
		{
			num[i] = rand() % n + 1;
			vec_num.push_back(num[i]);
			printf("%d ",num[i]);
		}
		printf("\n\n\n\n");
 //           scanf("%d",num+i);
		double t0 = clock();
//		sort(num,num+n-1);
		sort(vec_num.begin(),vec_num.end());
		for( i = 0 ; i < n ; i++)
        {
            if(i != n -1)
                printf("%d ",vec_num[i]);
            else
                printf("%d\n",vec_num[i]);
        }
		double t1 = clock();
		printf("time is %f\n\n",t1-t0);


// 		for (i = 0 ; i < n - 1 ; i ++)
// 		{
// 			for(int j = 1+i ; j < n ; j++)
// 			{
// 				if(num[j] < num[i])
// 				{
// 					int a = num[j];
// 					num[j] = num[i];
// 					num[i] = a;
// 				}
// 			}
// 		}
        qsort1(num,0,n-1);
 //       if(index > n) index = n;
        for( i = 0 ; i < n ; i++)
        {
            if(i != n-1)
                printf("%d ",num[i]);
            else
                printf("%d\n",num[i]);
        }
		t0 = clock();
		printf("time is %f\n\n",t0-t1);
        delete [] num;
    }
    return 0;
}