#include <iostream>
#include <vector>
#include <map>
using namespace std;

void GetCostMatrix(int * val,int col,int row,int ** cost)
{
	int i,j;
	for ( i = 0 ; i < row ; i++)
	{
		for (j = 0 ; j < col ; j++)
		{
			int n1 = i*col+j;
			if (val[n1])
				continue;

			if(j == col - 1)
			{
				if (i != row - 1)
				{					
					int n2 = (i+1)*col+j;
					if (val[n2] == 0)
					{
						cost[n1][n2] = 1;
						cost[n2][n1] = 1;
					}
				}
			}
			else
			{
				if (i == row - 1)
				{
					int n2 = i*col+j+1;
					if (val[n2] == 0)
					{
						cost[n1][n2] = 1;
						cost[n2][n1] = 1;
					}
				}
				else
				{
					int n2 = i*col+j+1;
					if (val[n2] == 0)
					{
						cost[n1][n2] = 1;
						cost[n2][n1] = 1;
					}
					n2 = (i+1)*col+j;
					if (val[n2] == 0)
					{
						cost[n1][n2] = 1;
						cost[n2][n1] = 1;
					}
				}
			}
		}
	}
}

void Dijkstra(int * val,int col,int row,int source,int end)
{
	int num = col*row;
	int ** cost = new int *[num];
	int i,j;
	for (i =0 ;i < num ; i++)
	{
		cost[i] = new int[num];
		for (j = 0 ; j < num ; j ++)
			cost[i][j] = INT_MAX;
	}
	GetCostMatrix(val,col,row,cost);

	vector<int> vec_v;		//未加入S集合的点集合

	for ( i = 0 ; i < row ; i++)
	{
		for (j = 0 ; j < col ; j++)
		{
			if (val[i*col+j] == 0 && source != i*col+j)
				vec_v.push_back(i*col+j);
		}
	}

	map<int,int> distance;
	map<int,int> path;			//
	int preNode = source , nextNode = -1;
	for (i = 0 ; i < vec_v.size() ; i++)
	{
		nextNode = vec_v[i];
		distance[nextNode] = cost[source][nextNode];
		path[nextNode] = source;
	}

	while((int)vec_v.size() != 0)
	{
		int minDistance = INT_MAX;
		int index = -1;
		for (i = 0 ; i < vec_v.size() ; i++)
		{
			if (distance[vec_v[i]] < minDistance)
			{
				minDistance = distance[vec_v[i]];
				nextNode = vec_v[i];
				index = i;
			}
		
		}
		if (minDistance == INT_MAX || index == -1)		//找不到下一个距离最小点，运算结束
			break;

		if (nextNode == end)					//当前点是迷宫最后点，运算结束
			break;

		vec_v.erase(vec_v.begin()+index);		//V集删掉加入S集合的点

		preNode = nextNode;
		//更新V集合中剩余点的distance
		for (i = 0 ; i < vec_v.size() ; i++)
		{
			nextNode = vec_v[i];
			if (cost[preNode][nextNode] != INT_MAX)
			{
				int tmp = distance[preNode] + cost[preNode][nextNode];
				if( tmp < distance[nextNode] )
				{
					distance[nextNode] = tmp;
					path[nextNode] = preNode;
				}
			}
		}
	}
	vec_v.clear();
	distance.clear();
	for (i =0 ;i < num ; i++)
		delete [] cost[i];
	delete [] cost;

	vector<int> result;
	int posEnd = end;
	result.push_back(posEnd);
	while(path[posEnd] != source)
	{
		posEnd = path[posEnd];
		result.push_back(posEnd);
	}
	result.push_back(source);
	path.clear();

	if((int)result.size() != 0)
	{
		for (i = (int)result.size() - 1 ; i >= 0  ; i-- )
		{
			int index = result[i];
			int x = index % col;
			int y = index / col;
			cout << "(" << y << "," << x << ")" << endl;
		}
		result.clear();
	}
}

int main()
{
	int row,col;
	while(cin >> row >> col)
	{
		if (col == 0 || row == 0)
			continue;
		
		int * val = new int[row*col];
		memset(val,0,sizeof(int)*row*col);
		for (int i = 0 ; i < row ; i++)
		{
			for (int j = 0 ; j < col ; j++)
			{
				int tmp;
				cin >> tmp;
				val[i*col+j] = tmp;
			}
		}

		Dijkstra(val,col,row,0,row*col-1);
		delete [] val;
	}
	return 0;
}