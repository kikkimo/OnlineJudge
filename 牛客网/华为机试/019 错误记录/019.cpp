#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _tagOutPutInfo
{
    string strFileName;
    int line;
    int counts;
    _tagOutPutInfo(){strFileName = ""; line = 0; counts = 0; }
}OutPutInfo;

bool operator == (const OutPutInfo & a, const OutPutInfo & b)
{
    return a.strFileName == b.strFileName && a.line == b.line;
}

void GetShortFileName(string & strFile)
{
    int nlen =  strFile.length();
    if(0 == nlen) return;
    int npos = strFile.rfind('\\');
    string s = strFile.substr(npos + 1,nlen - 1 - npos);

    nlen = s.length();
    if(nlen > 16)
        strFile = s.substr(nlen-16,16);
    else
        strFile = s;

}

int main()
{
    string strLine;
    int nLine;
    vector<OutPutInfo> VecInfo;
    int nSize;
    while(cin >> strLine)
    {
        cin >> nLine;
        GetShortFileName(strLine);
        OutPutInfo info;
        info.strFileName = strLine;
        info.line = nLine;
        info.counts = 1;
        nSize = VecInfo.size();
        if(0 == nSize)
            VecInfo.push_back(info);
        else
        {
            vector<OutPutInfo>::iterator iter = find(VecInfo.begin(),VecInfo.end(),info);
            if(iter == VecInfo.end())
                VecInfo.push_back(info);
            else
                (*iter).counts ++;
        }
    }
    nSize = VecInfo.size();
    for(int i = (nSize > 8) ?  nSize - 8 : 0 ; i < nSize ; i ++)
    {
        cout << VecInfo[i].strFileName << " " << VecInfo[i].line <<" " << VecInfo[i].counts << "\n";
 //       if(i != nSize - 1)
 //           cout << " ";
    }
}