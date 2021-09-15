class Solution {
public:
    template <typename _Iter> bool get_next_permutation(_Iter first, _Iter last) {
        auto next = last;
        // 1��Ԫ�ػ���û��Ԫ��
        if (first == last || first == --next) {
            return false;
        }
        for (;;) { // ���Ҳ࿪ʼ�ҵ�һ������Ԫ�������ֵ���
            auto next_1 = next;
            if (*--next < *next_1) { // �ҵ��������ֵ��������Ԫ��
                auto mid = last;     //���Ҳ��ҵ�һ������A_i��Ԫ��,��ΪA_j
                do {                 //����A_j=*mid , A_i=*next
                    --mid;
                } while (!(*next < *mid));
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
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> res;
        if (nums.size() == 0)
            return res;
        std::sort(nums.begin(), nums.end());
        do {
            vector<int> temp;
            temp.assign(nums.begin(), nums.end());
            res.push_back(temp);
        } while (get_next_permutation(nums.begin(), nums.end()));
        return res;
    }
};