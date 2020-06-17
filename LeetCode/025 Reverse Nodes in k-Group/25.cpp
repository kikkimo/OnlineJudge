#include <iostream>
#include <vector>
using namespace std;

#define  nullptr  0

class ListNode {
public:
      int val;
      ListNode *next;
      ListNode() {
		  val = 0;
		  next = nullptr;
	  }
      ListNode(int x){
		  val = x;
		  next = nullptr;
	  }
      ListNode(int x, ListNode * _next) {
		  val = x;
		  next = _next;
	  }
};



ListNode * CreateList(vector<int> nums)
{
	size_t size = nums.size();
	if (0 == size)
		return nullptr;
	ListNode * pHead = new ListNode(nums[0]);
	ListNode * pCurrent = pHead;
	for (int i = 1 ; i < size ; ++i)
	{
		ListNode * pNode = new ListNode(nums[i]);
		pCurrent->next = pNode;
		pCurrent = pNode;
	}
	return pHead;
}

void FreeList(ListNode * head)
{
	ListNode * poPointer = head;
	while (poPointer)
	{
		ListNode * poDeleteNode = poPointer; 
		poPointer = poPointer->next;
		delete poDeleteNode;
	}
}
 

ListNode* reverseKGroup(ListNode* head, int k) {
	if (1 == k)
		return head;
	int length = 0;
	ListNode * poPointer = head;
	while(poPointer)
	{
		length++;
		poPointer = poPointer->next;
	}
	ListNode * newhead = nullptr;
	ListNode * lastback = nullptr;		//上一轮最后一个
	poPointer = head;
	vector<ListNode*> vec_node;
	for (int i = 0 ; i < length ; i += k)
	{
		if (length - i < k)	//最后一轮，不轮换
		{
			while (poPointer)
			{
				lastback->next = poPointer;
				lastback = poPointer;
				poPointer = poPointer->next;
			}
		}
		else
		{
			vec_node.clear();
			vec_node.resize(k);
			int j;
			for (j = k-1 ; j >= 0 ; j-- )
			{
				vec_node[j] = poPointer;
				poPointer = poPointer->next;
			}
			for (j = 0 ; j < k ; j++)
			{
				if (lastback == nullptr)
				{
					lastback = vec_node[j];
					newhead = lastback;
					continue;
				}
				else
				{
					lastback->next = vec_node[j];
					lastback = vec_node[j];
				}
			}
		}
	}
	lastback->next = nullptr;
	return newhead;
}

void PrintList(ListNode* head)
{
	while (head)
	{
		cout << head->val;
		if (head->next)
		{
			cout << "→";
		}
		head = head->next;
	}
	cout << endl;
}

int main()
{
	int nums[5] = {1,2,3,4,5};
	vector<int> vec_nums(nums,nums+5);
	ListNode * pList = CreateList(vec_nums);
	PrintList(pList);
	pList = reverseKGroup(pList,5);
	PrintList(pList);
	FreeList(pList);

	pList = CreateList(vec_nums);
	PrintList(pList);
	pList = reverseKGroup(pList,3);
	PrintList(pList);
	FreeList(pList);
	return 0;
}