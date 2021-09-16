class Solution {
public:
  string addBinary(string a, string b) {
    int lenA = a.length();
    int lenB = b.length();
    if (0 == lenA || 0 == lenB) {
      return string();
    }
    int len = max(lenA, lenB) + 1;
    string res(len, '0');
    bool carry = false;
    for (int i = 0; i < len; ++i) {
      auto idxA = lenA - i - 1;
      auto idxB = lenB - i - 1;
      char chA = idxA >= 0 ? a[idxA] : '0';
      char chB = idxB >= 0 ? b[idxB] : '0';
      char ch;
      if (carry) {
        if (chA == '1' && chB == '1') {
          ch = '1';
          carry = true;
        } else if (chA == '0' && chB == '0') {
          ch = '1';
          carry = false;
        } else {
          ch = '0';
          carry = true;
        }
      } else {
        if (chA == '1' && chB == '1') {
          ch = '0';
          carry = true;
        } else if (chA == '0' && chB == '0') {
          ch = '0';
          carry = false;
        } else {
          ch = '1';
          carry = false;
        }
      }
      res[len - i - 1] = ch;
    }
    int pos = -1;
    for (int i = 0; i < len; ++i) {
      if (res[i] != '0') {
        pos = i;
        break;
      }
    }
    if (-1 == pos) {
      return "0";
    } else
      return res.substr(pos, len - pos);
  }
};