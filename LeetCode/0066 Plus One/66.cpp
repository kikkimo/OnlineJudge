class Solution {
public:
  vector<int> plusOne(vector<int> &digits) {
    int size = digits.size();
    vector<int> res(size);
    if (0 == size) {
      return res;
    }
    bool carry = false;
    for (int i = size - 1; i >= 0; --i) {
      if (i == size - 1) {
        auto temp = digits[i] + 1;
        if (temp >= 10) {
          temp -= 10;
          carry = true;
        }
        res[i] = temp;
      } else {
        auto temp = digits[i];
        if (carry) {
          temp++;
        }
        if (temp >= 10) {
          temp -= 10;
          carry = true;
        } else {
          carry = false;
        }
        res[i] = temp;
      }
    }
    if (carry) {
      res.insert(res.begin(), 1);
    }
    return res;
  }
};