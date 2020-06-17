#include <IOSTREAM>
#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode * next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* swapPairs(ListNode* head) {
	if (NULL == head)
		return NULL;

	if (head->next == NULL)
		return head;

	ListNode * p1 = head;
	ListNode * p2 = head->next;

	p1->next = swapPairs(p2->next);
	p2->next = p1;
	return p2;
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
	int List1[4] = {1,2,3,4};
	ListNode * l1 = new ListNode(List1[0]);
	ListNode * pt1 = l1;
	
	for (int i = 1 ; i < 4 ; i ++)
	{
		ListNode * p = new ListNode(List1[i]);
		pt1->next = p;
		pt1 = p;
	}
	
	PrintList(l1);
	PrintList(swapPairs(l1));
	
}
