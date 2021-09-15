class Solution {
public:
    template <typename _Iter> bool get_next_permutation(_Iter first, _Iter last) {
        auto next = last;
        // 1个元素或者没有元素
        if (first == last || first == --next) {
            return false;
        }
        for (;;) { // 从右侧开始找到一个连续元素满足字典序
            auto next_1 = next;
            if (*--next < *next_1) { // 找到了满足字典序的连续元素
                auto mid = last;     //从右侧找到一个大于A_i的元素,记为A_j
                do {                 //这里A_j=*mid , A_i=*next
                    --mid;
                } while (!(*next < *mid));
                std::iter_swap(next, mid);  //交换A_i与A_j
                std::reverse(next_1, last); //对A_i+1到队列尾的元素进行反转
                return true;
            }
            if (next == first) { // 队列中元素纯递减，进行还原
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