class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int rows = matrix.size();
    if (0 == rows)
      return false;
    int cols = matrix[0].size();
    if (0 == cols)
      return false;
    vector<int> firstCol(rows);
    for (int i = 0; i < rows; ++i) {
      firstCol[i] = matrix[i][0];
    }
    int lowerRow = 0;
    int upperRow = rows - 1;
    int mid = 0;
    while (lowerRow + 1 < upperRow) {
      mid = (lowerRow + upperRow) / 2;
      if (firstCol[mid] == target) {
        return true;
      } else if (firstCol[mid] < target) {
        lowerRow = mid;
      } else {
        upperRow = mid;
      }
    }
    if (firstCol[upperRow] > target) {
      mid = lowerRow;
    } else {
      mid = upperRow;
    }
    return std::find(matrix[mid].begin(), matrix[mid].end(), target) !=
           matrix[mid].end();
  }
};