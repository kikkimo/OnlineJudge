class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    if (k > n)
      return res;
    std::stack<int> stack;
    stack.push(n);
    bool insertNext = stack.size() < k;
    if (!insertNext) {
      res.emplace_back(vector<int>{n});
    }
    while (stack.size()) {
      int eleT = stack.top();
      if (!insertNext) {
        stack.pop();
      }
      if (eleT == 1) {
        insertNext = false;
        continue;
      }
      stack.push(eleT - 1);
      if (stack.size() == k) {
        auto backup = stack;
        vector<int> temp;
        while (backup.size()) {
          temp.emplace_back(backup.top());
          backup.pop();
        }
        res.emplace_back(temp);
        insertNext = false;
      } else {
        insertNext = true;
      }
    }
    return res;
  }
};