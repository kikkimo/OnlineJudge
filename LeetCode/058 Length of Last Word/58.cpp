class Solution {
public:
  int lengthOfLastWord(string s) {
    int len = s.length();
    int lastWordLength = 0;
    bool flag = false;
    for (int i = len - 1; i >= 0; --i) {
      if (flag == false && s[i] == ' ')
        continue;
      if (s[i] != ' ' && flag == false) {
        lastWordLength++;
        flag = true;
        continue;
      }
      if (s[i] != ' ' && flag) {
        lastWordLength++;
        continue;
      }
      if (s[i] == ' ' && flag) {
        break;
      }
    }
    return lastWordLength;
  }
};