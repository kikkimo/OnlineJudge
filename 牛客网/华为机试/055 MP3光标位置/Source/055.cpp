#include <iostream>
#include <string>
using namespace std;

#define null 0

class ListNode
{
public:
    int m_nVal;
    ListNode * m_pFront;
    ListNode * m_pNext;
    ListNode(){m_nVal = 0;m_pFront=null;m_pNext=null;}
};

ListNode * pTop = null;
ListNode * pBottom = null;

ListNode * CreateList(int numSize)
{
    ListNode * p = null;
    if(numSize <= 0)
        return p;
    ListNode * pHead = new ListNode;
    if(pHead)
    {
        pHead->m_nVal = 1;
        p = pHead;
        for(int i = 2 ; i <= numSize ; i++)
        {
            ListNode * pNew = new ListNode;
            if(pNew)
            {
                pNew->m_nVal = i;
                p->m_pNext = pNew;
                pNew->m_pFront = p;
                p = pNew;
            }
        }
    }
    return pHead;
}

//获取p后第m个指针
ListNode * GetBackPoint(ListNode * p,int m)
{
    ListNode * pList = p;
    for(int i = 0 ; i < m ; i++)
        if(pList) pList = pList->m_pNext;

	return pList;
}

//获取p前第m个指针
ListNode * GetFrontPoint(ListNode * p,int m)
{
    ListNode * pList = p;
    for(int i = 0 ; i < m ; i++)
        if(pList) pList = pList->m_pFront;

	return pList;
}

void FreeList(ListNode * pHead)
{
    ListNode * p = pHead;
    while(p)
    {
        ListNode * p0 = p;
        p = p->m_pFront;
        delete p0;
        p0 = null;
    }
}

ListNode * GetHeadPoint(ListNode * p)
{
    if(null == p)
        return null;
    
    while(p->m_pFront)
        p = p->m_pFront;
    
    return p;
}

ListNode * GetFeetPoint(ListNode * p)
{
    if(null == p)
        return null;
    
    while(p->m_pNext)
        p = p->m_pNext;
    
    return p;
}

ListNode * Up(ListNode * p)
{
    if(p == pTop)
    {
        if(p->m_pFront)
        {
            p = p->m_pFront;
            pTop = p;
            pBottom = pBottom->m_pFront;
        }
        else
        {
            //翻页到末尾
            p = GetFeetPoint(p);
            pBottom = p;
            pTop = GetFrontPoint(pBottom,3);
        }
    }
    else
        p = p->m_pFront;
    return p;    
}

ListNode * Down(ListNode * p)
{
    if(p == pBottom)
    {
        if(p->m_pNext)
        {
            p = p->m_pNext;
            pBottom = p;
            pTop = pTop->m_pNext;
        }
        else
        {
            //翻页到开头
            p = GetHeadPoint(p);
            pTop = p;
            pBottom = GetBackPoint(pTop,3);
        }
    }
    else
        p = p->m_pNext;
    return p;    
}

int main()
{
    int n;
    string str;
    while(cin >> n >> str)
    {
        int nlen = str.length();
        if(n < 0 || nlen == 0)
            continue;
        
		int i;
        if(0< n && n <= 4)
        {
            int nPos = 1;
            for(i = 0 ; i < nlen ; i++)
            {
                if(str[i] == 'U')
                {
                    if(nPos == 1)
                        nPos = n;
                    else
                        nPos--;
                }
                if(str[i] == 'D')
                {
                    if(nPos == n)
                        nPos = 1;
                    else
                        nPos++;
                }
            }
            for(i = 0 ; i < n ; i++)
            {
                if(i!=n-1)
                    cout << i + 1 << " ";
                else
                    cout << i + 1 << "\n";
            }
            cout << nPos  << endl;
        }
        else
        {
            //n大于4的情形
            ListNode * pList = CreateList(n);
            pTop = pList;
            pBottom = GetBackPoint(pTop,3);
            for(i = 0 ; i < nlen ; i++)
            {
                if(str[i] == 'U')
                    pList = Up(pList);
                
                if(str[i] == 'D')
                    pList = Down(pList);
            }
            ListNode * p = pTop;
            while(p!=pBottom)
            {
                cout << p->m_nVal << " ";
                p = p->m_pNext;
            }
            cout << pBottom->m_nVal << "\n";
            cout << pList->m_nVal << endl;
            FreeList(GetHeadPoint(pList));
        }
        
    }
    return 0;
}
