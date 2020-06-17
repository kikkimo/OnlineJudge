#include <iostream>
#include <vector>
using namespace std;

vector< vector<int> > insert(vector< vector<int> >& intervals, vector<int>& newInterval) 
{
	vector< vector<int> > result;
	if (intervals.size() == 0)
    {
        if (newInterval.size() != 0)
            result.push_back(newInterval);
        return result;
    }
    else
        if (newInterval.size() == 0)
		    return intervals;

	int low = newInterval[0];
	int high = newInterval[1];

	int i,j,k;
	for (i = 0 ; i < intervals.size() ; i++)
	{
		vector<int> interval = intervals[i];

		if (interval[1] >= low &&
			interval[0] <= low )
			break;

		if (interval[0] > low)
			break;
	}

	for (j = intervals.size() - 1 ; j >= 0; j--)
	{
		vector<int> interval = intervals[j];

		if (interval[1] >= high &&
			interval[0] <= high )
			break;

		if (interval[1] < high)
			break;
	}

	if ( i == j)
	{
		for (k = 0 ; k < intervals.size() ; k++)
		{
			vector<int> interval = intervals[k];
			if (k == i)
			{
				interval[1] = interval[1] > high ? interval[1] : high;
				interval[0] = interval[0] < low ? interval[0] : low;
			}
			result.push_back(interval);
		}
	}

	if ( i > j )
	{
		for (k = 0 ; k < i  ; k++)
		{
			vector<int> interval = intervals[k];
			result.push_back(interval);
		}
		result.push_back(newInterval);
		for (k = j+1 ; k < intervals.size() ; k++)
		{
			vector<int> interval = intervals[k];
			result.push_back(interval);
		}
	}

	if (i < j)
	{
		for (k = 0 ; k < i ; k++)
		{
			vector<int> interval = intervals[k];
			result.push_back(interval);
		}

		vector<int> temp;
		low = low < intervals[i][0] ? low : intervals[i][0];
		high = high > intervals[j][1] ? high : intervals[j][1];
		temp.push_back(low);
		temp.push_back(high);
		result.push_back(temp);

		for (k = j+1 ; k < intervals.size() ; k++)
		{
			vector<int> interval = intervals[k];
			result.push_back(interval);
		}
	}

	return result;

}

void main()
{
	vector< vector<int> > intervals;
	vector<int> newInterval;

	newInterval.push_back(6);
	newInterval.push_back(8);

	vector<int> vals;
	vals.push_back(1);
	vals.push_back(5);
	intervals.push_back(vals);

	for (int i = 0 ; i < intervals.size() ; i ++)
		cout << "[ " << intervals[i][0] << "," << intervals[i][1] << " ]" << endl;
	

	vector< vector<int> > result =insert(intervals,newInterval);
	for (i = 0 ; i < result.size() ; i ++)
		cout << "[ " << result[i][0] << "," << result[i][1] << " ]" << endl;
}