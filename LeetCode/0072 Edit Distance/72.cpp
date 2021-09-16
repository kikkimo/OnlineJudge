class Solution {
public:
  int minDistance(string word1, string word2) {
    int len1 = word1.length();
    int len2 = word2.length();
    if (0 == len1 && 0 == len2) {
      return 0;
    }
    if (0 == len1) {
      return len2;
    }
    if (0 == len2) {
      return len1;
    }
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
    for (int i = 1; i < len1 + 1; ++i) {
      dp[i][0] = i;
    }
    for (int i = 1; i < len2 + 1; ++i) {
      dp[0][i] = i;
    }
    for (int i = 1; i < len1 + 1; ++i) {
      for (int j = 1; j < len2 + 1; ++j) {
        auto temp1 = word1[i - 1] == word2[j - 1] ? dp[i - 1][j - 1]
                                                  : dp[i - 1][j - 1] + 1;
        auto temp2 = min(dp[i - 1][j], dp[i][j - 1]) + 1;
        dp[i][j] = min(temp1, temp2);
      }
    }
    return dp[len1][len2];
  }
};