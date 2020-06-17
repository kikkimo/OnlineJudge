#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

typedef struct _tagAttachment
{
	int  v;
	char p;
}Attachment;


class PriceValue
{
public:
	int  Price;						//�����۸�
	int  Value;						//������ֵ
	char  index1;		//����1�ڸ����������	
	char  index2;		//����2�ڸ����������
	PriceValue(){Price = 0; Value = 0;  index1 = -1; index2 = -1;}
};

int max(int a,int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int GetMaxValue(const vector<PriceValue> & PVMap, const vector<Attachment> & attachTable,int moneyLimit)
{
	int nSize = PVMap.size();
	if (0 == nSize || moneyLimit <= 0)
		return 0;

	int M = nSize + 1, N = moneyLimit+1;
	int * pValue = new int[M*N];
	memset(pValue,0,sizeof(int)*M*N);

	for (int i = 1 ; i < M ; i++)
	{
		for (int j = 1 ; j < N ; j++)
		{
			if (j < PVMap[i-1].Price)		//�޷������i����Ʒ,PVMap������Ϊi-1
				pValue[i*N+j] = pValue[(i-1)*N+j];
			else
			{
				pValue[i*N+j] = max(pValue[(i-1)*N+j], pValue[(i-1)*N+j-PVMap[i-1].Price]+PVMap[i-1].Value);
				int index1 = PVMap[i-1].index1 , index2 = PVMap[i-1].index2;
				if (-1 != index1)		
				{
					int Price = PVMap[i-1].Price + attachTable[index1].v;
					int Value = PVMap[i-1].Value + attachTable[index1].v * attachTable[index1].p;
					if (Price <= j)
						pValue[i*N+j] = max(pValue[i*N+j], pValue[(i-1)*N+j-Price] + Value);
				}
				if (-1 != index2)		
				{
					int Price = PVMap[i-1].Price + attachTable[index2].v;
					int Value = PVMap[i-1].Value + attachTable[index2].v * attachTable[index2].p;
					if (Price <= j)
						pValue[i*N+j] = max(pValue[i*N+j], pValue[(i-1)*N+j-Price] + Value);
					Price = PVMap[i-1].Price + attachTable[index1].v + attachTable[index2].v;
					Value = PVMap[i-1].Value + attachTable[index1].v * attachTable[index1].p
						+ attachTable[index2].v * attachTable[index2].p;
					if (Price <= j)
						pValue[i*N+j] = max(pValue[i*N+j], pValue[(i-1)*N+j-Price] + Value);
				}
			}
		}
	}
	int maxValue = pValue[nSize*N+moneyLimit];
	delete [] pValue;
	return maxValue;
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
	int * m_pV = new int[nProductNum];					//��Ʒ����
	char * m_pP = new char[nProductNum];				//��Ҫ�̶�
	char * m_pQ = new char[nProductNum];				//������Ӧ�������

	int * OriginIndex2VaildIndex = new int[nProductNum];			//ԭʼ��Ʒ���ת��Ч��Ʒ���
	memset(OriginIndex2VaildIndex,255,sizeof(int)*nProductNum);	    //��Ÿ�ֵΪ-1

	vector<PriceValue> PVMap;						//��Ч������Ʒ��ֵ��

    for( i = 0 ; i < nProductNum ; i++)
    {
		int v,p,q;
		cin >> v >> p >> q;
		
		m_pV[i] = v;
		m_pP[i] = p;
		m_pQ[i] = q;

		if (0 == q && v <= nTotalMoney)				//����С���ܼ�Ǯ����Ч������Ʒ
		{
			PriceValue pvtmp;
			pvtmp.Price = v;
			pvtmp.Value = v*p;
			PVMap.push_back(pvtmp);
			int index = PVMap.size() -1;
			OriginIndex2VaildIndex[i] = index;
		}
    }

	vector<Attachment> attachment;
	for (i = 0 ; i < nProductNum ; i++)
	{
		//������Ӧ�������۸�����ܼ�Ǯʱ����ǰ������¼��
		if (m_pQ[i] && -1 != OriginIndex2VaildIndex[m_pQ[i]-1] )
		{
			//��ǰ��������۸�����ܼ�ǮҲ��¼�븽����
			if (m_pV[i] + m_pV[m_pQ[i]-1] <= nTotalMoney)
			{
				Attachment tmp;
				tmp.v = m_pV[i];
				tmp.p = m_pP[i];
				attachment.push_back(tmp);
				int index = attachment.size() - 1;
				int vaildIndex = OriginIndex2VaildIndex[m_pQ[i]-1];
				if (-1 == PVMap[vaildIndex].index1)
					PVMap[vaildIndex].index1 = index;
				else
					PVMap[vaildIndex].index2 = index;
			}
		}
	}

	delete [] OriginIndex2VaildIndex;
	delete [] m_pV;
	delete [] m_pP;
	delete [] m_pQ;

	int maxValue = GetMaxValue(PVMap,attachment,nTotalMoney);

	cout << maxValue << endl;
	
	return 0;
}
