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

void GetMatrix(int * val, vector<int> odd, vector<int> even,int & w,int & h)
{
	int nOddSize = odd.size();
	int nEvenSize = even.size();

	if (nOddSize < nEvenSize)
	{
		h = nOddSize;
		w = nEvenSize;
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
	else
	{
		h = nEvenSize;
		w = nOddSize;
		for (int i = 0 ; i < h ; i++)
		{
			for (int j = 0 ; j < w ; j++)
			{
				int num = odd[j] + even[i];
				if (isPrimeNum(num))
					val[i*w+j] = 1;
				else
					val[i*w+j] = 0;
			}
		}
	}
}

#define W 23
#define H 20

int main()
{

	int val[W*H] = {
			1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
			0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,
			0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,0,1,0,
			0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,0,
			0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,1,
			0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1,1,
			1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,
			1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,1,1,1,1,0,
			0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,
			0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,
			0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0
	};
	int valBak[W*H] = {
		1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
			0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,
			0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,0,1,0,
			0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,0,
			0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,1,
			0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1,1,
			1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,
			1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,1,1,1,1,0,
			0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,
			0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,
			0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0
	};
//	GetMatrix(val,oddNum,evenNum,W,H);

	
	int i,j;

	for (i = 0 ; i < H ; i ++ )
	{
		for (j = 0 ; j < W ; j++)
		{
			cout << val[i*W+j] << " ";
		}
		cout << "\n";
	}

	vector<int> vec_x_xorder,vec_x_yorder;
	vector<int> vec_y_xorder,vec_y_yorder;
	int max_x = 0,max_y = 0;
	while(!IsEmpty(val,W,H))
	{
		vector<Element> vec_element = GetElementVector(val,W,H);
		sort(vec_element.begin(),vec_element.end(),compOrderX);
		if (vec_element.size() == 0)
			break;
		int x = vec_element[0].x;
		int y = vec_element[0].y;
		vec_x_xorder.push_back(x);
		vec_y_xorder.push_back(y);
		max_x++;

		for (i = 0 ; i < W ;i++)
			val[y*W+i] = 0;

		for (i = 0 ; i < H ;i++)
			val[i*W+x] = 0;
	}
	while(!IsEmpty(valBak,W,H))
	{
		vector<Element> vec_element = GetElementVector(valBak,W,H);
		sort(vec_element.begin(),vec_element.end(),compOrderY);
		if (vec_element.size() == 0)
			break;
		int x = vec_element[0].x;
		int y = vec_element[0].y;
		vec_x_yorder.push_back(x);
		vec_y_yorder.push_back(y);
		max_y++;
		
		for (i = 0 ; i < W ;i++)
			valBak[y*W+i] = 0;
		
		for (i = 0 ; i < H ;i++)
			valBak[i*W+x] = 0;
	}

	cout << "=============================================\n";
	if (max_x > max_y)
	{
		cout << "可选数目：" << max_x << "\n";
		for (i = 0 ; i < max_x ; i++)
		{
			char ch = vec_x_xorder[i] + 'A';
			cout << "(" << ch << "," << vec_y_xorder[i] + 1 << ")\n";
		}
	}
	else
	{
		cout << "可选数目：" << max_y << "\n";
		for (i = 0 ; i < max_y ; i++)
		{
			char ch = vec_x_yorder[i] + 'A';
			cout << "(" << ch << "," << vec_y_yorder[i] + 1 << ")\n";
		}
	}
	

	return 0;
}