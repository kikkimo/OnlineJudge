#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

typedef struct _tagElement
{
	int x;
	int y;
	int sum_x;
	int sum_y;
}Element;

bool compOrderY(const Element & a,const Element & b)
{
	if (a.sum_y == b.sum_y)
		return a.sum_x < b.sum_x;
	else
		return a.sum_y < b.sum_y;
}

bool compOrderX(const Element & a,const Element & b)
{
	if (a.sum_x == b.sum_x)
		return a.sum_y < b.sum_y;
	else
		return a.sum_x < b.sum_x;
}

vector<Element> GetElementVector(int * val,int w,int h)
{
	vector<Element> vec_element;
	int * sum_x = new int[w*h];
	int * sum_y = new int[w*h];
	memset(sum_x,0,sizeof(int)*w*h);
	memset(sum_y,0,sizeof(int)*w*h);

	int i,j;
	for (i = 0 ; i < h ; i++)
	{
		int sumx = 0;
		for (j = 0 ; j < w ; j++)
			sumx += val[i*w+j];

		for (j = 0 ; j < w ; j++)
			sum_x[i*w+j] = sumx;
	}

	for (j = 0 ; j < w ; j++)
	{
		int sumy = 0;
		for (i = 0 ; i < h ; i++)
			sumy += val[i*w+j];
		
		for (i = 0 ; i < h ; i++)
			sum_y[i*w+j] = sumy;
	}

	for (i = 0 ; i < h ; i++)
	{
		for (j = 0 ; j < w ; j++)
		{
			if (val[i*w+j])
			{
				Element tmp;
				tmp.x = j;
				tmp.y = i;
				tmp.sum_x = sum_x[i*w+j];
				tmp.sum_y = sum_y[i*w+j];
				vec_element.push_back(tmp);
			}
		}
	}

	delete [] sum_x;
	delete [] sum_y;
	return vec_element;
}

bool IsEmpty(int * val,int w,int h)
{
	bool bOk = true;
	for (int i = 0 ; i < h ; i++)
	{
		for (int j = 0 ; j < w ; j++)
		{
			if (val[i*w+j])
			{
				bOk = false;
				break;
			}
		}
	}
	return bOk;
}

bool isPrimeNum(int n)
{
	if (2 == n || 3 == n || 5 == n)
		return true;

	if (4 == n)
		return false;

	int v = (int)sqrt(n) + 1;
	bool bOk = true;
	for (int i = 2 ; i < v ; i++)
	{
		if (n % i == 0)
		{
			bOk = false;
			break;
		}
	}
	return bOk;
}

void GetMatrix(int * val, vector<int> odd, vector<int> even)
{
	int h = odd.size();
	int w = even.size();
	
	for (int i = 0 ; i < h ; i++)
	{
		for (int j = 0 ; j < w ; j++)
		{
			int num = odd[i] + even[j];
			if (isPrimeNum(num))
				val[i*w+j] = 1;
			else
				val[i*w+j] = 0;
		}
	}
	
}

int main()
{
	int nNumSize;
	FILE * fp = NULL;
	fp = fopen("data.txt","r");
	if (fp == NULL)
		return 0;

	fscanf(fp,"%d",&nNumSize);
	if (nNumSize == 0)
	{
		cout << 0 << endl;
		return 0;
	}

	int i,j;
	vector<int> oddNum,evenNum;
	for (i = 0 ; i < nNumSize ; i++)
	{
		int tmp;
		fscanf(fp,"%d",&tmp);
		if (tmp % 2)
			oddNum.push_back(tmp);
		else
			evenNum.push_back(tmp);
	}
	fclose(fp);

	int nOddSize = oddNum.size();
	int nEvenSize = evenNum.size();
	if (nOddSize == 0 || nEvenSize == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	int * val0 = new int[nOddSize*nEvenSize];
	int * val1 = new int[nOddSize*nEvenSize];
	int W = nEvenSize,H = nOddSize;
	GetMatrix(val0,oddNum,evenNum);
	GetMatrix(val1,oddNum,evenNum);

	vector<int> vec_x_xorder,vec_x_yorder;
	vector<int> vec_y_xorder,vec_y_yorder;

	fp = fopen("out.txt","w");

	for (i = 0 ; i < H ; i ++ )
	{
		for (j = 0 ; j < W ; j++)
		{
			cout << val0[i*W+j] << " ";
			fprintf(fp,"%d ",val0[i*W+j]);
		}
		cout << "\n";
		fprintf(fp,"%\n");
	}
	fclose(fp);

	int max_x = 0, max_y = 0;
	while(!IsEmpty(val0,W,H))
	{
		vector<Element> vec_element = GetElementVector(val0,W,H);
		sort(vec_element.begin(),vec_element.end(),compOrderX);
		if (vec_element.size() == 0)
			break;
		int x = vec_element[0].x;
		int y = vec_element[0].y;
		vec_x_xorder.push_back(x);
		vec_y_xorder.push_back(y);
		max_x++;
		
		for (i = 0 ; i < W ;i++)
			val0[y*W+i] = 0;
		
		for (i = 0 ; i < H ;i++)
			val0[i*W+x] = 0;
		vec_element.clear();
	}
	delete [] val0;

	while(!IsEmpty(val1,W,H))
	{
		vector<Element> vec_element = GetElementVector(val1,W,H);
		sort(vec_element.begin(),vec_element.end(),compOrderY);
		if (vec_element.size() == 0)
			break;
		int x = vec_element[0].x;
		int y = vec_element[0].y;
		vec_x_yorder.push_back(x);
		vec_y_yorder.push_back(y);
		max_y++;
		
		for (i = 0 ; i < W ;i++)
			val1[y*W+i] = 0;
		
		for (i = 0 ; i < H ;i++)
			val1[i*W+x] = 0;
		vec_element.clear();
	}
	delete [] val1;


	cout << "===========================================\n";
	if (max_x > max_y)
	{
		cout << "可选数目：" << max_x << "\n";
		for (i = 0 ; i < max_x ; i++)
			cout << "(" << evenNum[vec_x_xorder[i]] << "," << oddNum[vec_y_xorder[i]] << ")\n";
	}
	else
	{
		cout << "可选数目：" << max_y << "\n";
		for (i = 0 ; i < max_y ; i++)
			cout << "(" << evenNum[vec_x_yorder[i]] << "," << oddNum[vec_y_yorder[i]] << ")\n";
	}

	return 0;
}