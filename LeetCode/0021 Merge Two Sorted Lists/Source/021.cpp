#include <iostream>
using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};

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
	int List1[1] = {1};
	int List2[1] = {2};
	ListNode * l1 = new ListNode(List1[0]);
	ListNode * l2 = new ListNode(List2[0]);
	ListNode * pt1 = l1;
	ListNode * pt2 = l2;

	for (int i = 1 ; i < 1 ; i ++)
	{
		ListNode * p = new ListNode(List1[i]);
		pt1->next = p;
		pt1 = p;
	}

	for (int j = 1 ; j < 1 ; j ++)
	{
		ListNode * p = new ListNode(List2[j]);
		pt2->next = p;
		pt2 = p;
	}

	PrintList(l1);
	PrintList(l2);
	PrintList(mergeTwoLists(l1,l2));

}