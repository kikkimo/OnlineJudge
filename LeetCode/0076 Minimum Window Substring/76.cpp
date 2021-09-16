class Solution {
public:
  bool checkMap(const std::unordered_map<char, int> &map) {
    for (auto iter = map.begin(); iter != map.end(); ++iter) {
      if (iter->second > 0) {
        return false;
      }
    }
    return true;
  }
  string minWindow(string s, string t) {
    int lenS = s.length();
    int lenT = t.length();
    if (lenS < lenT || 0 == lenS || 0 == lenT)
      return "";
    std::unordered_map<char, int> map;
    for (int i = 0; i < lenT; ++i) {
      char ch = t[i];
      if (map.count(ch)) {
        map[ch]++;
      } else {
        map[ch] = 1;
      }
    }
    int left = 0, right = 0;
    bool findMatch = false;
    int minLength = lenS + 1;
    int subStringL = -1, subStringR = -1;
    string res{};
    while (left < lenS && right < lenS) {
      do {
        char ch = s[right];
        if (!map.count(ch)) {
          right++;
          continue;
        } else {
          map[ch]--;
          findMatch = checkMap(map);
          if (!findMatch)
            right++;
        }
      } while (!findMatch && right < lenS);
      if (!findMatch)
        break;
      do {
        char ch = s[left];
        left++;
        if (!map.count(ch)) {
          continue;
        } else {
          map[ch]++;
          findMatch = checkMap(map);
        }
      } while (findMatch && left < lenS);
      if (!findMatch) {
        int subLen = right - left + 2;
        if (subLen <= minLength) {
          minLength = subLen;
          subStringL = left - 1;
          subStringR = right;
        }
        right++;
      }
    }
    if (subStringL != -1 && subStringR != -1) {
      res = s.substr(subStringL, subStringR - subStringL + 1);
    }
    return res;
  }
};