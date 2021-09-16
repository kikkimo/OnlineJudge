#include <STDIO.H>
#include <stdlib.h>
#include <memory.h>

void myQSort(int * s,int l,int r,int * nIndex)
{
	int i,j,temp,nPos;	
	if (l < r)
	{
		i = l;
		j = r;
		temp = s[i];
		nPos = nIndex[i];
		
		while(i < j)
		{
			while(i < j && temp < s[j]) 	j--;
			if (i < j)
			{
				s[i] = s[j];
				nIndex[i++] = nIndex[j];
			}
			
			while(i < j && s[i] < temp)
				i++;
			if (i < j)
			{
				s[j] = s[i];
				nIndex[j--] = nIndex[i];
			}		
		}
		s[i] = temp;
		nIndex[i] = nPos;
        myQSort(s, l, i-1,nIndex); /* µÝ¹éµ÷ÓÃ */
        myQSort(s, i+1, r,nIndex);
	}
}

int GetTargetPos(int * s,int l,int target)
{
	if (target >= s[l-1])
		return l-1;

	if (target <= s[0])
		return 0;

	int nTopPos = 0;
	int nButtomPos = l - 1;
	int nTargetPos = (nTopPos + nButtomPos) / 2;
	while(nTopPos + 1 < nButtomPos)
	{
		if (s[nTargetPos] < target)
		{
			nTopPos = nTargetPos;
			nTargetPos = (nTopPos + nButtomPos) / 2;
		}
		else
		{
			nButtomPos = nTargetPos;
			nTargetPos = (nTopPos + nButtomPos) / 2;
		}
	}

	if (abs(s[nButtomPos] - target) > abs(target - s[nTopPos]))
		return nTopPos;
	else
		return nButtomPos;
}

int* twoSum(int* nums, int numsSize, int target) {
    int i =0 , j = 0;
	int * nIndex = (int*)malloc(sizeof(int)*numsSize);
	for (i = 0 ; i < numsSize ; i++)
		nIndex[i] = i + 1;

	myQSort(nums,0,numsSize-1,nIndex);

	int * nResult = (int*)malloc(sizeof(int)*2);
	memset(nResult,0,sizeof(int)*2);


	if (nums[0] >= 0)
	{
		int nTargetPos = GetTargetPos(nums,numsSize,target);
		i = 0;
		j = nTargetPos;
		while ( i < j )
		{
			int sum = nums[i] + nums[j];
			if (sum == target)
			{
				nResult[0] = nIndex[i];
				nResult[1] = nIndex[j];
				break;
			}
			else
			{
				if (sum > target)
					j--;
				else
					i++;
			}
		}
	}

	if (nums[numsSize - 1] <= 0)
	{
		int nTargetPos = GetTargetPos(nums,numsSize,target);
		i = nTargetPos;
		j = numsSize - 1;
		while ( i < j )
		{
			int sum = nums[i] + nums[j];
			if (sum == target)
			{
				nResult[0] = nIndex[i];
				nResult[1] = nIndex[j];
				break;
			}
			else
			{
				if (sum > target)
					j--;
				else
					i++;
			}
		}
	}

	if (nums[0] <=0 && nums[numsSize-1] >= 0)
	{
		i = 0;
		j = numsSize - 1;
		while ( i < j )
		{
			int sum = nums[i] + nums[j];
			if (sum == target)
			{
				nResult[0] = nIndex[i];
				nResult[1] = nIndex[j];
				break;
			}
			else
			{
				if (sum > target)
					j--;
				else
					i++;
			}
		}
	}

	free(nIndex);
	nIndex = NULL;
	if (nResult[1] < nResult[0])
	{
		nResult[0] ^= nResult[1];
		nResult[1] ^= nResult[0];
		nResult[0] ^= nResult[1];
	}
	return nResult;
}


#define NUMBER_SIZE 3

int main()
{
	int a[NUMBER_SIZE] = {3,2,4};
	int target = 6;
	int * nIndex = twoSum(a,NUMBER_SIZE,target);
	printf("%d %d\r\n",nIndex[0],nIndex[1]);
	return 0;
}