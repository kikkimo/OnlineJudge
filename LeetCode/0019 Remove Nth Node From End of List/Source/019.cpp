#include <iostream>
using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };


  ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * p = head;
		int num = 0;
		while (NULL != p)
		{
			num++;
			p = p->next;
		}
		ListNode * result = NULL;
		if (num == n)		//释放头指针
		{
			p = head;
			result = head->next;
			delete p;
			p = NULL;
		}
		else
		{
			result = head;
			int pos = 0;
			p = head;
			while (NULL != p)
			{
				pos++;
				if (pos == num - n)
				{
					//需要删除当前节点的下一个节点
					ListNode * pnext = p->next;
					p->next = pnext->next;
					delete pnext;
					pnext = NULL;
					break;
				}
				p = p->next;
			}
		}
		return result;
   }


  void main()
  {
	  ListNode * head = new ListNode(1);
	  ListNode * feet = head;
	  for (int i = 2 ; i < 6 ; i ++)
	  {
		  ListNode * p = new ListNode(i);
		  feet->next = p;
		  feet = p;
	  }

	  ListNode * pt = head;
	  while(NULL != pt)
	  {
		  cout << pt->val << endl;
		  pt = pt->next;
	  }

	  pt = removeNthFromEnd(head,1);
	  while(NULL != pt)
	  {
		  cout << pt->val << endl;
		  pt = pt->next;
	  }
  }