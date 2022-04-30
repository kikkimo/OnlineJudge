class Solution {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> res;
    res.emplace_back(vector<int>{});
    int numSize = nums.size();
    if (0 == numSize) {
      return res;
    }
    for (int i = 0; i < numSize; ++i) {
      auto num = nums[i];
      int size = res.size();
      for (int j = 0; j < size; ++j) {
        vector<int> newSolve(res[j].size() + 1);
        newSolve.assign(res[j].begin(), res[j].end());
        newSolve.emplace_back(num);
        res.emplace_back(newSolve);
      }
    }
    return res;
  }
};