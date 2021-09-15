class Solution {
  enum Direction { eRight, eDown, eLeft, eUp };

public:
  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    int top = 0;
    int left = -1;
    int right = n;
    int bottom = n;
    Direction dir = eRight;
    int filledNum = 1;
    int col = -1;
    int row = 0;
    while (filledNum <= n * n) {
      switch (dir) {
      case eRight: {
        for (int i = col + 1; i < right; ++i) {
          matrix[row][i] = filledNum++;
        }
        col = --right;
        dir = eDown;
      } break;
      case eDown: {
        for (int i = row + 1; i < bottom; ++i) {
          matrix[i][col] = filledNum++;
        }
        row = --bottom;
        dir = eLeft;
      } break;
      case eLeft: {
        for (int i = col - 1; i > left; --i) {
          matrix[row][i] = filledNum++;
        }
        col = ++left;
        dir = eUp;
      } break;
      case eUp: {
        for (int i = row - 1; i > top; --i) {
          matrix[i][col] = filledNum++;
        }
        row = ++top;
        dir = eRight;
      } break;
      }
    }
    return matrix;
  }
};