class Solution {
public:
  bool canJump(vector<int> &nums) {
    int size = nums.size();
    if (size <= 1)
      return true;
    int maxJump = nums[0] ? 1 : 0;
    for (int i = 0; i <= maxJump; ++i) {
      auto currentMaxJump = i + nums[i];
      if (currentMaxJump > maxJump) {
        maxJump = currentMaxJump;
      }
      if (maxJump >= size - 1)
        return true;
    }
    return false;
  }
};