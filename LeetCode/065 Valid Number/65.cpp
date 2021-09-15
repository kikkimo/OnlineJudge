class Solution {
public:
  bool isInteger(string &s) {
    int len = s.length();
    if (len == 0)
      return false;
    if (1 == len) {
      return '0' <= s[0] && s[0] <= '9';
    }
    int pos = (s[0] == '+' || s[0] == '-') ? 1 : 0;
    for (int i = pos; i < len; ++i) {
      char ch = s[i];
      if (ch < '0' || ch > '9')
        return false;
    }
    return true;
  }
  bool isDecimalNumber(string &s) {
    int len = s.length();
    if (len == 0)
      return false;
    if (1 == len) {
      return '0' <= s[0] && s[0] <= '9';
    }
    if (s == "+." || s == "-.") {
      return false;
    }
    int pos = (s[0] == '+' || s[0] == '-') ? 1 : 0;
    int dot = 0;
    for (int i = pos; i < len; ++i) {
      char ch = s[i];
      if (ch == '.') {
        dot++;
        if (dot >= 2)
          return false;
        continue;
      }
      if (ch < '0' || ch > '9')
        return false;
    }
    return true;
  }
  bool isNumber(string s) {
    int len = s.length();
    if (0 == len)
      return false;
    if (isDecimalNumber(s) || isInteger(s)) {
      return true;
    } else {
      auto pos_e = s.find('e');
      auto pos_E = s.find('E');
      if (pos_e != std::string::npos && pos_E != std::string::npos) {
        return false;
      } else if (pos_e != std::string::npos) {
        auto prefix = s.substr(0, pos_e);
        auto suffix = s.substr(pos_e + 1, len - pos_e - 1);
        return isDecimalNumber(prefix) && isInteger(suffix);
      } else if (pos_E != std::string::npos) {
        auto prefix = s.substr(0, pos_E);
        auto suffix = s.substr(pos_E + 1, len - pos_E - 1);
        return isDecimalNumber(prefix) && isInteger(suffix);
      } else {
        return false;
      }
    }
  }
};