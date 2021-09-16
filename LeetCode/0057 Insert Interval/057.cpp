class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>> &intervals,
                             vector<int> &newInterval) {
    intervals.emplace_back(newInterval);
    int size = intervals.size();
    if (size <= 1) {
      return intervals;
    }
    vector<vector<int>> res;
    sort(
        intervals.begin(), intervals.end(),
        [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });
    auto lastInterval = intervals[0];
    for (int i = 0; i < size; ++i) {
      const auto &currentInterval = intervals[i];
      if (lastInterval[1] >= currentInterval[0]) {
        lastInterval[0] = min(currentInterval[0], lastInterval[0]);
        lastInterval[1] = max(currentInterval[1], lastInterval[1]);
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