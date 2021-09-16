class Solution {
public:
  struct Ele {
    int row;
    int col;
  };
  bool isEleValid(const Ele &ele, const vector<vector<char>> &mark) {
    int n = mark.size();
    for (int i = 0; i < n; ++i) {
      if (mark[ele.row][i] || mark[i][ele.col]) {
        return false;
      }
    }
    for (int i = ele.col, j = ele.row; i >= 0 && j >= 0; --i, --j) {
      if (mark[j][i]) {
        return false;
      }
    }
    for (int i = ele.col, j = ele.row; i < n && j >= 0; ++i, --j) {
      if (mark[j][i]) {
        return false;
      }
    }
    for (int i = ele.col, j = ele.row; i >= 0 && j < n; --i, ++j) {
      if (mark[j][i]) {
        return false;
      }
    }
    for (int i = ele.col, j = ele.row; i < n && j < n; ++i, ++j) {
      if (mark[j][i]) {
        return false;
      }
    }
    return true;
  }
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    if (n == 2 || n == 3 || n <= 0) {
      return res;
    }
    if (1 == n) {
      vector<string> temp{"Q"};
      res.emplace_back(temp);
      return res;
    }
    if (4 == n) {
      vector<string> temp1{".Q..", "...Q", "Q...", "..Q."};
      res.emplace_back(temp1);
      vector<string> temp2{"..Q.", "Q...", "...Q", ".Q.."};
      res.emplace_back(temp2);
      return res;
    }
    std::stack<Ele> eleStack;
    Ele ele;
    ele.row = 0;
    ele.col = 0;
    eleStack.push(ele);
    vector<vector<char>> mark(n, vector<char>(n, 0));
    mark[ele.row][ele.col] = 1;
    bool findNextRow = true;
    while (eleStack.size()) {
      auto &eleT = eleStack.top();
      if (!findNextRow) {
        bool ok = false;
        mark[eleT.row][eleT.col] = 0;
        auto eleTN = eleT;
        eleStack.pop();
        for (int i = eleT.col + 1; i < n; ++i) {
          eleTN.col = i;
          if (isEleValid(eleTN, mark)) {
            ok = true;
            break;
          }
        }
        if (ok) {
          mark[eleTN.row][eleTN.col] = 1;
          eleStack.push(eleTN);
          findNextRow = true;
        }
        continue;
      }
      // find element in next row
      ele.row = eleT.row + 1;
      bool ok = false;
      for (int i = 0; i < n; ++i) {
        ele.col = i;
        if (isEleValid(ele, mark)) {
          ok = true;
          break;
        }
      }
      if (ok) {
        eleStack.push(ele);
        if (eleStack.size() == n) {
          vector<string> tempStr(n);
          auto eleStackBackup = eleStack;
          while (eleStackBackup.size()) {
            auto &elem = eleStackBackup.top();
            string str(n, '.');
            str.at(elem.col) = 'Q';
            tempStr[elem.row] = str;
            eleStackBackup.pop();
          }
          res.emplace_back(tempStr);
          eleStack.pop();
          findNextRow = false;
        } else {
          mark[ele.row][ele.col] = 1;
          findNextRow = true;
        }
      } else {
        findNextRow = false;
      }
    }
    return res;
  }
};