#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Product{
	int price;
	int num;
	string name;
	Product()
	{
		price = 0;
		num = 0;
		name = "";
	}
};

bool comp(const Product & a,const Product & b)
{
	if (a.num == b.num)
		return a.name < b.name;
	else
		return a.num < b.num;
}

struct Money{
	int value;
	int num;
	Money()
	{
		value = 0;
		num = 0;
	}
};

class AutoSelling
{
public:
	vector<Money>		m_VecMoney;
	vector<Product>		m_VecProduct;
	int m_nBalance;
	AutoSelling(){
		m_nBalance = 0;
	}
	bool Init(string str);
	void Pay(string str);
	void Buy(string str);
	void GetChange(string str);
	void Quest(string str);
	void TransMessage(string str);
};

void AutoSelling::TransMessage(string str)
{
	int nlen = str.length();
	if(nlen <= 0)
		return;

	char sz[128] = { 0 };
	while((int)str.length() > 0 && sscanf(str.c_str(),"%[^;]",sz))
	{
		string s(sz);
		nlen = str.length();
		int len = s.length();
		str = str.substr(len+1,nlen-len-1);
		if(0 == nlen)
			continue;

		switch(s[0])
		{
		case 'r': 
			Init(s);
			break;
		case 'p': 
			Pay(s);
			break;
		case 'b': 
			Buy(s);
			break;
		case 'c': 
			GetChange(s);
			break;
		case 'q': 
			Quest(s);
			break;
		}
	}
}

bool AutoSelling::Init(string str)
{
	int nlen = str.length();
	if(nlen <= 0)
		return false;

	if(str[0]!= 'r')
		return false;

	string strP[6] = {"A1","A2","A3","A4","A5","A6"};
	int numP[6] = { 0 };
	int PriceP[6] = {2,3,4,5,8,6};

	int numM[4] = { 0 };
	int valueM[4] = {1,2,5,10};
	char stmp[10] = { 0 };
	sscanf(str.c_str(),"%s%d-%d-%d-%d-%d-%d%d-%d-%d-%d",stmp,
		numP,numP+1,numP+2,numP+3,numP+4,numP+5,numM,numM+1,numM+2,numM+3);


	int i;
	m_VecProduct.clear();
	for (i = 0 ; i < 6 ; i ++)
	{
		Product pt;
		pt.name = strP[i];
		pt.price = PriceP[i];
		pt.num = numP[i];
		m_VecProduct.push_back(pt);
	}

	m_VecMoney.clear();
	for (i = 0 ; i < 4 ; i ++)
	{
		Money mn;
		mn.value = valueM[i];
		mn.num = numM[i];
		m_VecMoney.push_back(mn);
	}
	cout << "S001:Initialization is successful" << endl;
	return true;
}

void AutoSelling::Pay(string str)
{
	if((int)str.length() <= 0)
		return;

	if(str[0] != 'p')
		return;

	char stmp[10] = { 0 };
	int pay = 0;

	sscanf(str.c_str(),"%s%d",stmp,&pay);

	if(!(pay == 1 || pay == 2 || pay == 5 || pay == 10))
	{
		cout << "E002:Denomination error" << endl;
		return;
	}

	int change = m_VecMoney[0].value * m_VecMoney[0].num +
		m_VecMoney[1].value * m_VecMoney[1].num;

	if (change < pay)
	{
		cout << "E003:Change is not enough, pay fail" << endl;
		return;
	}

	if (pay > 10)
	{
		cout << "E004:Pay the balance is beyond the scope biggest" << endl;
		return;
	}

	int count = 0;
	for (int i = 0 ; i < 6 ; i++)
	{
		count += m_VecProduct[i].num;
	}
	if (0==count)
	{
		cout << "E005:All the goods sold out" << endl;
		return;
	}

	switch(pay)
	{
	case 1:
		m_VecMoney[0].num ++;
		break;
	case 2:
		m_VecMoney[1].num ++;
		break;
	case 5:
		m_VecMoney[2].num ++;
		break;
	case 10:
		m_VecMoney[3].num ++;
		break;
	}

	m_nBalance += pay;
	cout << "S002:Pay success,balance=" << m_nBalance << endl;
}

void AutoSelling::Buy(string str)
{
	if((int)str.length() <= 0)
		return;
	if(str[0] != 'b')
		return;
	
	char stmp[10] = { 0 };
	char sz[10] = { 0 };

	sscanf(str.c_str(),"%s%s",stmp,sz);
	string sbuy(sz);

	bool bFind = false;
	int index = -1;
	for (int i = 0 ; i < (int)m_VecProduct.size() ; i++)
	{
		if (m_VecProduct[i].name == sbuy)
		{
			bFind = true;
			index = i;
			break;
		}
	}

	if (!bFind)
	{
		cout << "E006:Goods does not exist" << endl;
		return;
	}

	if (m_VecProduct[index].num == 0)
	{
		cout << "E007:The goods sold out" << endl;
		return;
	}

	if (m_nBalance < m_VecProduct[index].price)
	{
		cout << "E008:Lack of balance" << endl;
		return;
	}

	m_nBalance -= m_VecProduct[index].price;
	m_VecProduct[index].num -= 1;
	cout << "S002:Pay success,balance=" << m_nBalance << endl;
}

void AutoSelling::GetChange(string str)
{
	if((int)str.length() <= 0)
		return;
	if(str[0] != 'c')
		return;

	if (m_nBalance == 0)
	{
		cout << "E009:Work failure";
		return;
	}

	//1 2 5 10
	int C[4] = { 0 };

	int i;
	for (i = 3 ; i >= 0 ; i--)
	{
		while(m_nBalance >= m_VecMoney[i].value && m_VecMoney[i].num > 0)
		{
			m_VecMoney[i].num--;
			m_nBalance -= m_VecMoney[i].value;
			C[i]++;
		}
	}
	
	for (i = 0 ; i < 4 ; i++)
		cout << m_VecMoney[i].value << " yuan coin number=" << C[i] << endl;
}

void AutoSelling::Quest(string str)
{
	if((int)str.length() <= 0)
		return;
	
	if(str[0] != 'q')
		return;
	
	char stmp[10] = { 0 };
	int code = -1;
	
	sscanf(str.c_str(),"%s%d",stmp,&code);

	if (code != 0 && code != 1)
	{
		cout << "E010:Parameter error";
		return;
	}

	if (0 == code)
	{
		sort(m_VecProduct.begin(),m_VecProduct.end(),comp);
		for (int i = 0 ; i < (int)m_VecProduct.size() ; i++)
			cout << m_VecProduct[i].name << " " << m_VecProduct[i].price << " " << m_VecProduct[i].num << endl;
	}

	if (1 == code)
	{
		for (int i = 0 ; i < (int)m_VecMoney.size() ; i++)
			cout << m_VecMoney[i].value << " yuan coin number=" << m_VecMoney[i].num << endl;
	}
}

int main()
{
	AutoSelling Auto;
	Auto.TransMessage("r 25-9-1-1-12-20 7-3-8-14;p 10;p 10;b A3;c;b A1;q0;p 10;p 5;c;p 1;b A5;q0;");
	return 0;
}