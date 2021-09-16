class Solution {
public:
  vector<string> generateSpace(int freeSpaceNum, int lineWordNum,
                               bool lastLine = false) {
    if (lineWordNum == 1) {
      string str(freeSpaceNum, ' ');
      vector<string> res;
      res.emplace_back(str);
      return res;
    }
    if (!lastLine) {
      vector<int> spaceNum(lineWordNum, 0);
      if (freeSpaceNum % (lineWordNum - 1) == 0) {
        for (int i = 0; i < lineWordNum - 1; ++i) {
          spaceNum[i] = freeSpaceNum / (lineWordNum - 1);
        }
      } else {
        auto temp = freeSpaceNum / (lineWordNum - 1);
        for (int i = 0; i < lineWordNum - 1; ++i) {
          spaceNum[i] = temp;
        }
        int remainingSpace = freeSpaceNum % (lineWordNum - 1);
        for (int i = 0; i < remainingSpace; ++i) {
          spaceNum[i]++;
        }
      }
      vector<string> res(lineWordNum);
      for (int i = 0; i < lineWordNum; ++i) {
        string str(spaceNum[i], ' ');
        res[i] = str;
      }
      return res;
    } else {
      vector<string> res(lineWordNum);
      for (int i = 0; i < lineWordNum - 1; ++i) {
        res[i] = " ";
      }
      string str(freeSpaceNum - lineWordNum + 1, ' ');
      res[lineWordNum - 1] = str;
      return res;
    }
  }

  vector<string> fullJustify(vector<string> &words, int maxWidth) {
    int numWords = words.size();
    vector<int> wordWidths(numWords);
    for (int i = 0; i < numWords; ++i) {
      wordWidths[i] = words[i].length();
    }
    vector<string> res;
    auto start = 0, end = 0;
    while (end <= numWords - 1) {
      int sumWidth = 0;
      int sumWordsWidth = 0;
      for (; end <= numWords - 1;) {
        sumWidth += wordWidths[end];
        if (sumWidth < maxWidth) {
          sumWidth += 1; //单词后面跟着一个空格
          sumWordsWidth += wordWidths[end];
          end++;
        } else if (sumWidth == maxWidth) {
          sumWordsWidth += wordWidths[end];
          end++;
          break;
        } else {
          break;
        }
      }
      int lineWordNum = end - start;
      int freeSpace = maxWidth - sumWordsWidth;
      auto lineWordsSpace =
          generateSpace(freeSpace, lineWordNum, end > numWords - 1);
      string str{};
      for (int i = start; i < end; ++i) {
        str += words[i];
        str += lineWordsSpace[i - start];
      }
      res.emplace_back(str);
      start = end;
    }
    return res;
  }
};