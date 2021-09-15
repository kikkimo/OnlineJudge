class Solution {
public:
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    int rows = obstacleGrid.size();
    if (0 == rows) {
      return 0;
    }
    int cols = obstacleGrid[0].size();
    vector<vector<int>> matrix(rows, vector<int>(cols, 1));
    matrix[0][0] = !obstacleGrid[0][0];
    for (int i = 1; i < cols; ++i) {
      if (obstacleGrid[0][i] || obstacleGrid[0][i - 1] || !matrix[0][i - 1])
        matrix[0][i] = 0;
    }
    for (int i = 1; i < rows; ++i) {
      if (obstacleGrid[i][0] || obstacleGrid[i - 1][0] || !matrix[i - 1][0])
        matrix[i][0] = 0;
    }
    for (int i = 1; i < rows; ++i) {
      for (int j = 1; j < cols; ++j) {
        if (obstacleGrid[i][j - 1] && obstacleGrid[i - 1][j] ||
            obstacleGrid[i][j]) {
          matrix[i][j] = 0;
        } else if (obstacleGrid[i][j - 1]) {
          matrix[i][j] = matrix[i - 1][j];
        } else if (obstacleGrid[i - 1][j]) {
          matrix[i][j] = matrix[i][j - 1];
        } else {
          matrix[i][j] = matrix[i - 1][j] + matrix[i][j - 1];
        }
      }
    }
    return matrix[rows - 1][cols - 1];
  }
};