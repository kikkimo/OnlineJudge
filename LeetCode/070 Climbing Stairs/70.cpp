class Solution {
public:
  int climbStairs(int n) {
    if (n <= 3) {
      return n;
    } else {
      vector<int> result(n, 0);
      result[0] = 1;
      result[1] = 2;
      for (int i = 2; i < n; ++i) {
        result[i] = result[i - 2] + result[i - 1];
      }
      return result[n - 1];
    }
  }
};