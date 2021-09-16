class Solution {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    int size = intervals.size();
    if (size <= 1) {
      return intervals;
    }
    sort(
        intervals.begin(), intervals.end(),
        [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });
    vector<vector<int>> res;
    vector<int> lastInterval = intervals[0];
    for (int i = 0; i < size; ++i) {
      const auto &currentInterval = intervals[i];
      if (currentInterval[0] <= lastInterval[1]) {
        lastInterval[1] = max(lastInterval[1], currentInterval[1]);
        lastInterval[0] = min(lastInterval[0], currentInterval[0]);
      } else {
        res.emplace_back(lastInterval);
        lastInterval = currentInterval;
      }
      if (i == size - 1) {
        res.emplace_back(lastInterval);
      }
    }
    return res;
  }
};