class Solution {
public:
  int minPathSum(vector<vector<int>> &grid) {
    int rows = grid.size();
    if (0 == rows) {
      return 0;
    }
    int cols = grid[0].size();
    if (0 == cols) {
      return 0;
    }
    vector<vector<int>> path(rows, vector<int>(cols, 0));
    path[0][0] = grid[0][0];
    for (int i = 1; i < rows; ++i) {
      path[i][0] = path[i - 1][0] + grid[i][0];
    }
    for (int i = 1; i < cols; ++i) {
      path[0][i] = path[0][i - 1] + grid[0][i];
    }
    for (int i = 1; i < rows; ++i) {
      for (int j = 1; j < cols; ++j) {
        path[i][j] = min(path[i - 1][j] + grid[i][j],
                         path[i][j - 1] + grid[i][j]);
      }
    }
    return path[rows - 1][cols - 1];
  }
};