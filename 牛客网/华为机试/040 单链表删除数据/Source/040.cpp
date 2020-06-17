#include <stdlib.h>
#include <stdio.h>

struct ListNode
{
    int       m_nKey;
    ListNode* m_pNext;
};

#define null 0

ListNode* CreateList(int nhead)
{
    ListNode * p = new ListNode;
    if(p)
    {
        p->m_pNext = null;
        p->m_nKey = nhead;
    }
    return p;
}

void InsertVal(ListNode * pHead,int valPre,int val)
{
    if(pHead)
    {
        ListNode * p = pHead;
        while(p != null && p->m_nKey != valPre)
            p = p->m_pNext;
        
        if(p)
        {
            ListNode * pNext = p->m_pNext;
            ListNode * pNew = new ListNode;
            if(pNew)
            {
                pNew->m_pNext = pNext;
                pNew->m_nKey = val;
                p->m_pNext = pNew;
            }
        }
    }
}

ListNode * DeleteVal(ListNode * pHead,int val)
{
    if(!pHead)
        return pHead;
    
    ListNode * p = pHead;
    while(p != null && p->m_nKey != val)
        p = p->m_pNext;
    
    if(null == p)
        return pHead;
    
    if(p == pHead)
    {
        p = pHead->m_pNext;
        delete pHead;
        pHead = null;
        return p;
    }
    else
    {
        ListNode * p1 = pHead;
        while(p1 != null && p1->m_pNext != p)
            p1 = p1->m_pNext;
        p1->m_pNext = p->m_pNext;
        delete p;
        p = null;
        return pHead;
    }
}

void FreeList(ListNode * pHead)
{
    ListNode * p = pHead;
    while(p)
    {
        ListNode * p1 = p;
        p = p->m_pNext;
        delete p1;
        p1 = null;
    }
}

void PrintfList(ListNode * pHead)
{
    ListNode * p = pHead;
    while(p)
    {
        if(p->m_pNext)
            printf("%d ",p->m_nKey);
        else
            printf("%d ",p->m_nKey);
        p = p->m_pNext;
    }
}

int main()
{
    int numSize;
    while(scanf("%d",&numSize) != EOF)
    {
        int valHead;
        scanf("%d",&valHead);
        ListNode * pList = CreateList(valHead);
        for(int i = 1; i < numSize ;i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            InsertVal(pList,b,a);
        }
        int nDelNum;
        scanf("%d",&nDelNum);
        pList = DeleteVal(pList,nDelNum);
        PrintfList(pList);
        FreeList(pList);
        printf("\n");
    }
    return 0;
}
