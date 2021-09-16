class Solution {
public:
  void setZeroes(vector<vector<int>> &matrix) {
    int rows = matrix.size();
    if (0 == rows)
      return;
    int cols = matrix[0].size();
    std::unordered_map<int, bool> map;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (matrix[i][j] == 0) {
          map[i * cols + j] = 1;
        }
      }
    }
    for (auto iter = map.begin(); iter != map.end(); ++iter) {
      int row = iter->first / cols;
      int col = iter->first % cols;
      for (int i = 0; i < rows; ++i) {
        matrix[i][col] = 0;
      }
      for (int i = 0; i < cols; ++i) {
        matrix[row][i] = 0;
      }
    }
  }
};