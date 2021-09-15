class Solution {
public:
  int maxSubArray(vector<int> &nums) {
    int size = nums.size();
    if (1 == size) {
      return nums[0];
    }
    int sum = nums[0];
    int maxSum = sum;
    for (int i = 1; i < size; ++i) {
      sum = sum + nums[i] > nums[i] ? sum + nums[i] : nums[i];
      maxSum = maxSum < sum ? sum : maxSum;
    }
    return maxSum;
  }
};