#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

typedef struct _tagPriceValueMap
{
	int		Price;
	int		Value;
	char	ID;			//ID <= 60
}PriceValueMap;

bool comp(const PriceValueMap & a, const PriceValueMap & b)
{
	return a.ID < b.ID;
}

vector<PriceValueMap> GetPriceValueMap(vector<PriceValueMap> & PVMap, int index,int moneyLimit)
{
	vector<PriceValueMap> result;
	if (0 == PVMap.size() || index < 0 || index >= PVMap.size() || moneyLimit <= 0)
		return result;

	int nIndexDifID = index;
	while(PVMap[nIndexDifID].ID == PVMap[index].ID)
	{
		nIndexDifID--;
		if (nIndexDifID <= 0)
		{
			nIndexDifID = 0;
			break;
		}
	}

	if (PVMap[nIndexDifID].ID == PVMap[index].ID)		//队列第一项商品
	{
		for (int i = nIndexDifID ; i <= index ; i++ )
		{
			if (PVMap[i].Price <= moneyLimit)
				result.push_back(PVMap[i]);
		}
	}
	else
	{
		result = GetPriceValueMap(PVMap,nIndexDifID,moneyLimit);
		int nSize = result.size();
		int i,j;

		for ( j = nIndexDifID+1 ; j <= index ; j++)
		{
			if (PVMap[j].Price <= moneyLimit)
				result.push_back(PVMap[j]);
		}

		for (i = 0 ; i < nSize ; i++)
		{
			for ( j = nIndexDifID+1 ; j <= index ; j++)
			{
				if (result[i].Price + PVMap[j].Price <= moneyLimit)
				{
					PriceValueMap tmp;
					tmp.ID = -1;
					tmp.Price = result[i].Price + PVMap[j].Price;
					tmp.Value = result[i].Value + PVMap[j].Value;
					result.push_back(tmp);
				}
			}
		}
	}
	return result;
}

int main()
{
    int nTotalMoney = 0, nProductNum = 0;
    cin >> nTotalMoney >> nProductNum;
    if(0 == nTotalMoney || 0 == nProductNum)
    {
       cout << 0;
       return 0;
    }
    
	int i = 0,j = 0;
	int * m_pV = new int[nProductNum];					//商品单价
	char * m_pP = new char[nProductNum];				//重要程度
	char * m_pQ = new char[nProductNum];				//附件对应主件序号

	char * OriginIndex2VaildIndex = new char[nProductNum];			//原始商品序号转有效商品序号
	memset(OriginIndex2VaildIndex,255,nProductNum);	    //序号赋值为-1

	char * ChildIndex = new char[nProductNum*2];				//主件所含附件序号
	memset(ChildIndex,255,nProductNum*2);	    //赋值为-1

	vector<PriceValueMap> PVMap;						//有效主件商品价值表

    for( i = 0 ; i < nProductNum ; i++)
    {
		int v,p,q;
		cin >> v >> p >> q;
		
		m_pV[i] = v;
		m_pP[i] = p;
		m_pQ[i] = q;

		if (0 == q && v <= nTotalMoney)				//单价小于总价钱的有效主件商品
		{
			PriceValueMap pvtmp;
			pvtmp.Price = v;
			pvtmp.Value = v*p;
			pvtmp.ID = i;
			PVMap.push_back(pvtmp);
			int index = PVMap.size() -1;
			OriginIndex2VaildIndex[i] = (char)index;
		}
		else
		{
			if (-1 == ChildIndex[(q-1)*2])
				ChildIndex[(q-1)*2] = i;
			else
				ChildIndex[(q-1)*2+1] = i;
		}
    }

	for (i = 0 ; i < nProductNum ; i++)
	{
		int childIndex1 = ChildIndex[i*2]; 
		int childIndex2 = ChildIndex[i*2+1];

		if (-1 != childIndex1)
		{
			if (m_pV[i] + m_pV[childIndex1] <= nTotalMoney)
			{
				PriceValueMap pvtmp;
				pvtmp.Price = m_pV[i]+m_pV[childIndex1];
				pvtmp.Value = m_pV[i]*m_pP[i] + m_pV[childIndex1]*m_pP[childIndex1];
				pvtmp.ID = PVMap[OriginIndex2VaildIndex[i]].ID;		//ID保持一致
				PVMap.push_back(pvtmp);
			}
		}

		if (-1 != childIndex2)
		{
			if (m_pV[i] + m_pV[childIndex2] <= nTotalMoney)
			{
				PriceValueMap pvtmp;
				pvtmp.Price = m_pV[i]+m_pV[childIndex2];
				pvtmp.Value = m_pV[i]*m_pP[i] + m_pV[childIndex2]*m_pP[childIndex2];
				pvtmp.ID = PVMap[OriginIndex2VaildIndex[i]].ID;		//ID保持一致
				PVMap.push_back(pvtmp);
			}

			if (m_pV[i] + m_pV[childIndex1] + m_pV[childIndex2] <= nTotalMoney)
			{
				PriceValueMap pvtmp;
				pvtmp.Price = m_pV[i]+m_pV[childIndex1]+m_pV[childIndex2];
				pvtmp.Value = m_pV[i]*m_pP[i] + m_pV[childIndex1]*m_pP[childIndex1] + m_pV[childIndex2]*m_pP[childIndex2];
				pvtmp.ID = PVMap[OriginIndex2VaildIndex[i]].ID;		//ID保持一致
				PVMap.push_back(pvtmp);
			}
		}
	}

	delete [] OriginIndex2VaildIndex;
	delete [] ChildIndex;
	delete [] m_pV;
	delete [] m_pP;
	delete [] m_pQ;

	sort(PVMap.begin(),PVMap.end(),comp);

	vector<PriceValueMap> result = GetPriceValueMap(PVMap,PVMap.size() - 1,nTotalMoney);
	vector<PriceValueMap> buffer;
	buffer.swap(PVMap);

	int nSize = result.size();
	int nMaxValue = 0;
	for (i = 0 ; i < nSize ; i++)
		nMaxValue = nMaxValue > result[i].Value ? nMaxValue : result[i].Value;

	cout << nMaxValue << endl;
   
	return 0;
}
