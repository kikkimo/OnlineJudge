class Solution {
public:
    template <typename _Iter> bool get_next_perm(_Iter first, _Iter last) {
        auto next = last;
        if (first == last || --next == first) {
            return false;
        }
        for (;;) {
            auto next_backup = next;
            if (*--next < *next_backup) {
                auto mid = last;
                do {
                    --mid;
                } while (*mid <= *next);
                std::iter_swap(mid, next);
                std::reverse(next_backup, last);
                return true;
            }
            if (next == first) {
                std::reverse(first, last);
                return false;
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> res;
        if (nums.size() == 0) {
            return res;
        }
        std::sort(nums.begin(), nums.end());
        do {
            res.push_back(nums);
        } while (get_next_perm(nums.begin(), nums.end()));
        return res;
    }
};