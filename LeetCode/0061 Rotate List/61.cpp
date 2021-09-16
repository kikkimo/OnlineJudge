class Solution {
public:
  ListNode *rotateRight(ListNode *head, int k) {
    if (k == 0 || nullptr == head)
      return head;
    int len = 1;
    auto end = head;
    while (end->next != nullptr) {
      len++;
      end = end->next;
    }
    k = k % len;
    k = len - k;
    if (k == 0 || k == len)
      return head;
    ListNode *newHead = head;
    ListNode *newEnd = nullptr;
    for (int i = 0; i < k; ++i) {
      if (i == k - 1) {
        newEnd = newHead;
      }
      newHead = newHead->next;
    }
    end->next = head;
    newEnd->next = nullptr;
    return newHead;
  }
};