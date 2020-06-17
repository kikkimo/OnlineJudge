#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void sortstring(string & s,int l,int r)
{
	if (l >= r)
		return;

	char ch = s[l];
	int i = l+1, j = r;
	while(i <= j)
	{
		while( j>=i && s[j] >= ch)
			j--;

		while( j>=i && s[i] < ch)
			i++;

		if (i < j)
		{
			char c = s[i];
			s[i] = s[j];
			s[j] = c;
			i++;
			j--;
		}
	}
	s[l] = s[j];
	s[j] = ch;
	sortstring(s,l,j);
	sortstring(s,j+1,r);
}

int main()
{
    int numSize;
	FILE * fp = NULL;
	fp = fopen("data.txt","r");
	fscanf(fp,"%d",&numSize);
	
	vector<string> vec_str;
	for(int i = 0 ; i < numSize ; i++)
	{
		char sz[60] = { 0 };
		fscanf(fp,"%s",sz);
		string strbuf(sz);
		vec_str.push_back(strbuf);
	}

	sort(vec_str.begin(),vec_str.end());
	
	int nIndexLookUp;
	char stemp[60] = { 0 };
	fscanf(fp,"%s%d",stemp,&nIndexLookUp);
	fclose(fp);
	string strLookUp(stemp);

	string strOrdered = strLookUp;
	int nlenLookUp = strLookUp.length();
	sortstring(strOrdered,0,nlenLookUp-1);
//	sort(strOrdered.begin(),strOrdered.end());
	string strBrother;
	int nBrother = 0;
	vector<string> ss;
	for( i = 0 ; i < numSize ; i++)
	{
		string s = vec_str[i];
		int nlen = s.length();
		if(nlen != nlenLookUp)
			continue;
		
//		sort(s.begin(),s.end());
		sortstring(s,0,nlen-1);
		if(s == strOrdered && vec_str[i] != strLookUp)
		{
			ss.push_back(vec_str[i]);
			nBrother++;
			if(nBrother == nIndexLookUp)
				strBrother = vec_str[i];
		}
	}
	if(nBrother)
	{
		if(nBrother >= nIndexLookUp)
			cout << nBrother << "\n" << strBrother << endl;
		else
			cout << nBrother << endl;
	}
	else
		cout << nBrother << endl;
	
	
	fp = fopen("out.txt","w");
	for (i = 0 ; i < ss.size() ; i++ )
	{
		fprintf(fp,"%s ",ss[i].c_str());
	}
	fclose(fp);

	return 0;
}