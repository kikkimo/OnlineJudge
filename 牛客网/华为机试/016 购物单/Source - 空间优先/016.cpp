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
	int  Price;			//�����۸�
	int  Value;			//������ֵ
	int  index1;		//����1�ڸ����������	
	int  index2;		//����2�ڸ����������
	PriceValue(){Price = 0; Value = 0;  index1 = -1; index2 = -1;}
};

bool comp(const PriceValue & a,const PriceValue & b)
{
	return a.Price < b.Price;
}

int max(int a,int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int GetMaxValue(const vector<PriceValue> & PVMap, const vector<Attachment> & attachTable,int index,int moneyLimit)
{
	int nMaxValue = 0;
	if (0 == PVMap.size() || index < 0 || index >= PVMap.size() || moneyLimit <= 0)
		return 0;

	if (moneyLimit < PVMap[0].Price)		//��Ǯ����С�������PV������С���۵���Ʒ
		return 0;

	if(0 == index)
	{
		if (PVMap[0].Price > moneyLimit)
			return 0;
		else
		{
			nMaxValue = nMaxValue > PVMap[0].Value ? nMaxValue : PVMap[0].Value;

			if (-1 != PVMap[0].index1)
			{
				int Price = PVMap[0].Price + attachTable[PVMap[0].index1].v;
				if (Price <= moneyLimit)
				{
					int Value = PVMap[0].Value + attachTable[PVMap[0].index1].v * attachTable[PVMap[0].index1].p;
					nMaxValue = nMaxValue > Value ? nMaxValue : Value;
				}
			}

			if (-1 != PVMap[0].index2)
			{
				int Price = PVMap[0].Price + attachTable[PVMap[0].index2].v;
				if (Price <= moneyLimit)
				{
					int Value = PVMap[0].Value + attachTable[PVMap[0].index2].v * attachTable[PVMap[0].index2].p;
					nMaxValue = nMaxValue > Value ? nMaxValue : Value;
				}
				Price = PVMap[0].Price + attachTable[PVMap[0].index1].v + attachTable[PVMap[0].index2].v;
				if (Price <= moneyLimit)
				{
					int Value = PVMap[0].Value + attachTable[PVMap[0].index1].v * attachTable[PVMap[0].index1].p
						+ attachTable[PVMap[0].index2].v * attachTable[PVMap[0].index2].p;
					nMaxValue = nMaxValue > Value ? nMaxValue : Value;
				}
			}
		}
	}

	if (index > 0)
	{
		if (PVMap[index].Price > moneyLimit)
			nMaxValue = GetMaxValue(PVMap,attachTable,index-1,moneyLimit);
		else
		{
			nMaxValue = GetMaxValue(PVMap,attachTable,index-1,moneyLimit);

			int Price = PVMap[index].Price;
			int Value = PVMap[index].Value;
			nMaxValue = max(nMaxValue , Value+GetMaxValue(PVMap,attachTable,index-1,moneyLimit-Price));

			if (-1 != PVMap[index].index1)
			{
				Price = PVMap[index].Price + attachTable[PVMap[index].index1].v;
				if (Price <= moneyLimit)
				{
					Value = PVMap[index].Value + attachTable[PVMap[index].index1].v * attachTable[PVMap[index].index1].p;
					nMaxValue = max(nMaxValue , Value+GetMaxValue(PVMap,attachTable,index-1,moneyLimit-Price));
				}
			}
			
			if (-1 != PVMap[index].index2)
			{
				Price = PVMap[index].Price + attachTable[PVMap[index].index2].v;
				if (Price <= moneyLimit)
				{
					Value = PVMap[index].Value + attachTable[PVMap[index].index2].v * attachTable[PVMap[index].index2].p;
					nMaxValue = max(nMaxValue , Value+GetMaxValue(PVMap,attachTable,index-1,moneyLimit-Price));
				}
				Price = PVMap[index].Price + attachTable[PVMap[index].index1].v + attachTable[PVMap[index].index2].v;
				if (Price <= moneyLimit)
				{
					Value = PVMap[index].Value + attachTable[PVMap[index].index1].v * attachTable[PVMap[index].index1].p
						+ attachTable[PVMap[index].index2].v * attachTable[PVMap[index].index2].p;
					nMaxValue = max(nMaxValue , Value+GetMaxValue(PVMap,attachTable,index-1,moneyLimit-Price));
				}
			}
		}
	}
//	printf("index = %d,maxvalue = %d\n",index,nMaxValue);
	return nMaxValue;
}

int main()
{
    int nTotalMoney = 0, nProductNum = 0;
	FILE * fp = fopen("data.txt","r");
	fscanf(fp,"%d%d",&nTotalMoney,&nProductNum);
//    cin >> nTotalMoney >> nProductNum;
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
		fscanf(fp,"%d%d%d",&v,&p,&q);
//		cin >> v >> p >> q;
		
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
	fclose(fp);

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

	//�������ռ۸��ɵ͵�������
	sort(PVMap.begin(),PVMap.end(),comp);

	int mapSize = PVMap.size();
	cout << GetMaxValue(PVMap,attachment,mapSize-1,nTotalMoney);
   
	return 0;
}
