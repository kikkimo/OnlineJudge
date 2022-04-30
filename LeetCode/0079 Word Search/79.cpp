class Solution {
public:
  int getLastDir(int numCols, int lastElePos, int curElePos) {
    int lastEleRow = lastElePos / numCols;
    int lastEleCol = lastElePos % numCols;
    int curEleRow = curElePos / numCols;
    int curEleCol = curElePos % numCols;
    if (curEleRow == lastEleRow - 1 && curEleCol == lastEleCol) {
      return 0;
    }
    if (curEleRow == lastEleRow && curEleCol == lastEleCol + 1) {
      return 1;
    }
    if (curEleRow == lastEleRow + 1 && curEleCol == lastEleCol) {
      return 2;
    }
    if (curEleRow == lastEleRow && curEleCol == lastEleCol - 1) {
      return 3;
    }
    return 4;
  }
  bool matchChar(vector<vector<char>> &board, int numRows, int numCols,
                 int lastRow, int lastCol, int dir, char ch) {
    switch (dir) {
    case 0: {
      if (0 == lastRow) {
        return false;
      } else {
        return board[lastRow - 1][lastCol] == ch;
      }
    } break;
    case 1: {
      if (lastCol == numCols - 1) {
        return false;
      } else {
        return board[lastRow][lastCol + 1] == ch;
      }
    } break;
    case 2: {
      if (lastRow == numRows - 1) {
        return false;
      } else {
        return board[lastRow + 1][lastCol] == ch;
      }
    } break;
    case 3: {
      if (0 == lastCol) {
        return false;
      } else {
        return board[lastRow][lastCol - 1] == ch;
      }
    } break;
    default:
      return false;
    }
    return false;
  }
  bool exist(vector<vector<char>> &board, string word) {
    int numRows = board.size();
    if (0 == numRows)
      return false;
    int numCols = board[0].size();
    int len = word.length();
    if (len > numCols * numRows)
      return false;
    int strPos = 0;
    int elePos = -1;
    vector<int> eleStack;
    eleStack.reserve(len);
    int eleSize = numCols * numRows;
    int lastDir = 0; // 0 上,1 左,2 下,3 右
    while (elePos < eleSize && eleStack.size() < len) {
      if (eleStack.size() == 0) {
        bool res = false;
        for (elePos++; elePos < eleSize; elePos++) {
          int row = elePos / numCols;
          int col = elePos % numCols;
          if (board[row][col] == word[strPos]) {
            res = true;
            eleStack.emplace_back(elePos);
            strPos++;
            break;
          }
        }
        if (res == false)
          return false;
        if (eleStack.size() == len)
          return true;
      } else {
        int lasElePos = eleStack[eleStack.size() - 1];
        int lasEleRow = lasElePos / numCols;
        int lasEleCol = lasElePos % numCols;
        char ch = word[strPos];
        while (lastDir < 4) {
          if (matchChar(board, numRows, numCols, lasEleRow, lasEleCol, lastDir,
                        ch)) {
            int nextEleRow, nextEleCol;
            switch (lastDir) {
            case 0:
              nextEleCol = lasEleCol;
              nextEleRow = lasEleRow - 1;
              break;
            case 1:
              nextEleCol = lasEleCol + 1;
              nextEleRow = lasEleRow;
              break;
            case 2:
              nextEleCol = lasEleCol;
              nextEleRow = lasEleRow + 1;
              break;
            case 3:
              nextEleCol = lasEleCol - 1;
              nextEleRow = lasEleRow;
              break;
            }
            int nextElsPos = nextEleRow * numCols + nextEleCol;
            if (find(eleStack.begin(), eleStack.end(), nextElsPos) ==
                eleStack.end()) {
              eleStack.emplace_back(nextElsPos);
              strPos++;
              break;
            } else {
              lastDir++;
            }
          } else {
            lastDir++;
          }
        }
        if (4 == lastDir) {
          //当前字母找不到合适的下一个结点
          int curElePos = eleStack[eleStack.size() - 1];
          eleStack.pop_back();
          strPos--;
          if (eleStack.size() == 0) {
            lastDir = 0;
            continue;
          } else {
            int lastElePos = eleStack[eleStack.size() - 1];
            lastDir = getLastDir(numCols, lastElePos, curElePos) + 1;
          }
        } else {
          if (eleStack.size() == len)
            return true;
          else {
            lastDir = 0;
          }
        }
      }
    }
    return false;
  }
};