#include <iostream>
#include <vector>
using namespace std;

int maxLenAsc(vector<int> & result,int * array,int pos,int posn,int maxNum)
{
	if (pos > posn)
		return result.size();
	
	if (pos == posn)
	{
		if (result.size() == 0)
		{
			if (array[pos] <= maxNum)
				result.push_back(array[pos]);			
			return result.size();
		}
		else
		{
			if (result[result.size()-1] < array[pos] && array[pos] <= maxNum)
				result.push_back(array[pos]);
			return result.size();
		}
	}
	else
	{
		if (result.size() == 0)
		{
			if (array[pos] <= maxNum)
				result.push_back(array[pos]);		
			return maxLenAsc(result,array,pos+1,posn,maxNum);		//存入一个数后
		}
		else
		{
			int val1 = array[pos];
			int val0 = result[result.size()-1];
			
			if (val0 > val1)
			{
				//一种是将result中所有大于val的数字去掉
				vector<int> res;
				for (int i = 0 ; i < (int)result.size() ; i++)
				{
					if (result[i] < val1)
						res.push_back(result[i]);
				}
				int num1 = maxLenAsc(res,array,pos,posn,maxNum);				
				int num2 = maxLenAsc(result,array,pos+1,posn,maxNum);
				if (num1 > num2)
				{
					result = res;
					return num1;
				}
				else
					return num2;
			}
			else
				if (val0 == val1)
					return maxLenAsc(result,array,pos+1,posn,maxNum);
				else
				{
					if (val1 <= maxNum)
						result.push_back(val1);
					
					return maxLenAsc(result,array,pos+1,posn,maxNum);
				}
		}
	}
}

int maxLenDesc(vector<int> & result,int * array,int pos,int posn,int maxNum)
{
	if (pos > posn)
		return result.size();
	
	if (pos == posn)
	{
		if (result.size() == 0)
		{
			if (array[pos] < maxNum)
				result.push_back(array[pos]);		
			return result.size();
		}
		else
		{
			if (result[result.size()-1] > array[pos] && array[pos] < maxNum)
				result.push_back(array[pos]);
			return result.size();
		}
	}
	else
	{
		if (result.size() == 0)
		{
			if (array[pos] < maxNum)
				result.push_back(array[pos]);	
			return maxLenDesc(result,array,pos+1,posn,maxNum);
		}
		else
		{
			int val1 = array[pos];
			int val0 = result[result.size()-1];
			
			if (val0 < val1)
			{
				//一种是将result中所有小于val1的数字去掉
				vector<int> res;
				for (int i = 0 ; i < (int)result.size() ; i++)
				{
					if (result[i] > val1)
						res.push_back(result[i]);
				}
				int num1 = maxLenDesc(res,array,pos,posn,maxNum);				
				int num2 = maxLenDesc(result,array,pos+1,posn,maxNum);
				if (num1 > num2)
				{
					result = res;
					return num1;
				}
				else
					return num2;
			}
			else
				if (val0 == val1)
					return maxLenDesc(result,array,pos+1,posn,maxNum);
				else
				{
					if (val1 < maxNum)
						result.push_back(val1);
					return maxLenDesc(result,array,pos+1,posn,maxNum);
				}
		}
	}
}

int main()
{
	FILE * fp = NULL;
	fp = fopen("data.txt","r");
    int nSize;
    fscanf(fp,"%d",&nSize);

    if(0 == nSize)
	{
		fclose(fp);
        return 0;
	}
    
    int * height = new int[nSize];
	int i,j;
    for(i = 0 ; i < nSize ; i++)
        fscanf(fp,"%d",height + i);
	fclose(fp);

	int * que_asc = new int[nSize];
	int * que_desc = new int[nSize];
	memset(que_asc,0,sizeof(int)*nSize);
	memset(que_desc,0,sizeof(int)*nSize);

	for (i = 0 ; i < nSize ; i++)
	{
		que_asc[i] = 1;
		for (j = i - 1 ;  j >= 0 ; j --)
		{
			if (height[i] > height[j] && que_asc[i] < que_asc[j] + 1)
				que_asc[i] = que_asc[j] + 1;
		}
	}

	for (i = nSize - 1 ; i >= 0 ; i--)
	{
		que_desc[i] = 1;
		for (j = i + 1 ;  j < nSize  ; j ++)
		{
			if (height[i] > height[j] && que_desc[i] < que_desc[j] + 1)
				que_desc[i] = que_desc[j] + 1;
		}
	}

	int maxlen = 0;
	for (i = 0 ; i < nSize ; i++)
	{
		if (que_asc[i] + que_desc[i] > maxlen)
			maxlen = que_asc[i] + que_desc[i] - 1;
	}

    delete [] height;
	delete [] que_asc;
	delete [] que_desc;
	cout << nSize - maxlen << endl;
	return 0;
}