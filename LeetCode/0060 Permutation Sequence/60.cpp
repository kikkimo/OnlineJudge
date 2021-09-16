class Solution {
public:
  template <typename _Iter> bool get_next_perm(_Iter first, _Iter last) {
    auto next = last;
    // 1��Ԫ�ػ���û��Ԫ��
    if (first == last || first == --next) {
      return false;
    }
    for (;;) { // ���Ҳ࿪ʼ�ҵ�һ������Ԫ�������ֵ���
      auto next_1 = next;
      if (*--next < *next_1) { // �ҵ��������ֵ��������Ԫ��
        auto mid = last; //���Ҳ��ҵ�һ������A_i��Ԫ��,��ΪA_j
        do {             //����A_j=*mid , A_i=*next
          --mid;
        } while (*mid <= *next);
        std::iter_swap(next, mid);  //����A_i��A_j
        std::reverse(next_1, last); //��A_i+1������β��Ԫ�ؽ��з�ת
        return true;
      }
      if (next == first) { // ������Ԫ�ش��ݼ������л�ԭ
        std::reverse(first, last);
        return false;
      }
    }
  }
  string getPermutation(int n, int k) {
    string str = "";
    for (int i = 0; i < n; ++i) {
      str += '0' + i + 1;
    }
    int idx = 1;
    do {
      if (idx++ == k) {
        return str;
      }
    } while (get_next_perm(str.begin(), str.end()));
    return str;
  }
};