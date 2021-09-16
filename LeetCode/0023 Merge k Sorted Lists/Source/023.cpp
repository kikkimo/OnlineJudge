#include <IOSTREAM>
#include <vector>
using namespace std;

struct ListNode {
      int val;
      ListNode * next;
      ListNode(int x) : val(x), next(NULL) {}
};

// ListNode* mergeKLists(vector<ListNode*>& lists) {
// 	if (lists.size() == 0)
// 		return NULL;
// 	int nsize = lists.size();
// 	int * nums = new int[nsize];
// 	memset(nums,0,sizeof(int)*nsize);
// 	int nSumSize = 0;
// 
// 	for (int i = 0 ; i < nsize ; i++)
// 	{
// 		ListNode * p = lists[i];
// 		while(NULL != p)
// 		{
// 			nums[i]++;
// 			p = p->next;
// 		}
// 		nSumSize += nums[i];
// 	}
// 
// 	ListNode * head = NULL;
// 	ListNode * feet = NULL;
// 	for ( i = 0 ; i < nSumSize ; i ++)
// 	{
// 		int nIndex = 0;
// 		int val = 2147483647;
// 		for (int j = 0 ; j < nsize ; j++)
// 		{
// 			ListNode * p = lists[j];
// 			if(p && p->val < val)
// 			{
// 				val = p->val;
// 				nIndex = j;
// 			}
// 		}
// 		lists[nIndex] = lists[nIndex]->next;
// 		if (head == NULL)
// 		{
// 			ListNode * pt = new ListNode(val);
// 			head = pt;
// 			feet = head;
// 		}
// 		else
// 		{
// 			ListNode * pt = new ListNode(val);
// 			feet->next = pt;
// 			feet = pt;
// 		}
// 	}
// 	return head;
// }


ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	if (NULL == l1 && NULL == l2)
		return NULL;
	if (NULL == l1)
		return l2;
	if (NULL == l2)
		return l1;
	
	ListNode * p1 = l1;
	ListNode * p2 = l2;
	ListNode * head = NULL;
	
	if (p1->val < p2->val)
	{
		head = new ListNode(p1->val);
		p1 = p1->next;
	}
	else
	{
		head = new ListNode(p2->val);
		p2 = p2->next;
	}
	ListNode * pt = head;
	
	while(NULL != p1 && NULL != p2)
	{
		int val1 = p1->val;
		int val2 = p2->val;
		if (val1 < val2)
		{
			ListNode * p =new ListNode(val1);
			pt->next = p;
			p1 = p1->next;
		}
		else
		{
			ListNode * p =new ListNode(val2);
			pt->next = p;
			p2 = p2->next;
		}
		pt = pt->next;
	}
	
	while(NULL != p1)
	{
		int val1 = p1->val;
		ListNode * p =new ListNode(val1);
		pt->next = p;
		pt = pt->next;
		p1 = p1->next;
	}
	
	while(NULL != p2)
	{
		int val2 = p2->val;
		ListNode * p =new ListNode(val2);
		pt->next = p;
		pt = pt->next;
		p2 = p2->next;
	}
	return head;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
	if (lists.empty())  return NULL;
	int n = lists.size();
	while (n > 1) {
		int k = (n + 1) / 2;
		for (int i = 0; i < n/2; ++i) {
			lists[i] = mergeTwoLists(lists[i], lists[i+k]);
		}
		n = k;
	}
	return lists[0];
 }

void PrintList(ListNode* l)
{
	while(NULL != l)
	{
		cout << l->val << endl;
		l = l->next;
	}
}

void main()
{
	int List1[3] = {1,4,5};
	int List2[3] = {1,3,4};
	int List3[2] = {2,6};
	ListNode * l1 = new ListNode(List1[0]);
	ListNode * l2 = new ListNode(List2[0]);
	ListNode * l3 = new ListNode(List3[0]);
	ListNode * pt1 = l1;
	ListNode * pt2 = l2;
	ListNode * pt3 = l3;
	
	for (int i = 1 ; i < 3 ; i ++)
	{
		ListNode * p = new ListNode(List1[i]);
		pt1->next = p;
		pt1 = p;
	}
	
	for (int j = 1 ; j < 3 ; j ++)
	{
		ListNode * p = new ListNode(List2[j]);
		pt2->next = p;
		pt2 = p;
	}

	for (int k = 1 ; k < 2 ; k++)
	{
		ListNode * p = new ListNode(List3[k]);
		pt3->next = p;
		pt3 = p;
	}
	
	PrintList(l1);
	PrintList(l2);
	PrintList(l3);
	vector<ListNode*> list;
	list.push_back(l1);
	list.push_back(l2);
	list.push_back(l3);
	PrintList(mergeKLists(list));
	
}

