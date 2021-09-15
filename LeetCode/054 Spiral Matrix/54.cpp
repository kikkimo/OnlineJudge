class Solution {
public:
  enum Direction { eRight, eDown, eLeft, eUp };
  vector<int> spiralOrder(vector<vector<int>> &matrix) {
    vector<int> res;
    int m = matrix.size();
    if (0 == m)
      return res;
    int n = matrix[0].size();
    int top = 0;
    int left = -1;
    int right = n;
    int bottom = m;
    Direction dir = eRight;
    int row = 0;
    int col = -1;
    while (res.size() != m * n) {
      switch (dir) {
      case eRight: {
        for (int i = col + 1; i < right; ++i) {
          res.emplace_back(matrix[row][i]);
        }
        col = --right;
        dir = eDown;
      } break;
      case eDown: {
        for (int i = row + 1; i < bottom; ++i) {
          res.emplace_back(matrix[i][col]);
        }
        row = --bottom;
        dir = eLeft;
      } break;
      case eLeft: {
        for (int i = col - 1; i > left; --i) {
          res.emplace_back(matrix[row][i]);
        }
        col = ++left;
        dir = eUp;
      } break;
      case eUp: {
        for (int i = row - 1; i > top; --i) {
          res.emplace_back(matrix[i][col]);
        }
        row = ++top;
        dir = eRight;
      } break;
      default:
        break;
      }
    }
    return res;
  }
};
