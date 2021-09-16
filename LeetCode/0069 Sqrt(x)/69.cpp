class Solution {
public:
  int mySqrt(int x) {
    if (x <= 1) {
      return x;
    }
    // f(n) = n^2 - x = 0
    // n = n_0 - f(n_0)/ f'(n_0)  = n_0 - (n_0 * n_0 - x) / n_0 / 2
    long n0 = x / 2;
    while (n0 * n0 > x) {
      n0 = (n0 + x / n0) / 2;
    }
    return n0;
  }
};