class Solution {
public:
    bool isMatch(string s, string p) {
        int lenS = s.length();
        int lenP = p.length();
        if(0 == lenS && 0 == lenP)
            return true;
        if(0 == lenS)
        {
            for(int i = 0 ; i < lenP; ++i)
            {
                if(p[i] != '*')
                    return false;
            }
            return true;
        }
        if(0 == lenP)
            return false;
        vector<vector<char>> dp(lenS + 1,vector<char>(lenP + 1,0)); 
        dp[0][0] = 1;
        for(int i = 1; i <= lenP; ++i)
        {
            if(1 == i)
                dp[0][i] = p[0] == '*';
            else{
                dp[0][i] = dp[0][i-1] && p[i-1]== '*';
            }
        }
        for(int i = 1 ; i <= lenP; ++i)
        {
            for(int j = 1; j <= lenS; ++j)
            {
                if(dp[j-1][i-1])
                {
                    dp[j][i] = (s[j-1] == p[i-1] || p[i-1] == '?' || p[i-1] == '*');
                } else if(dp[j][i-1] || dp[j-1][i]) {
                    dp[j][i] = p[i-1] == '*';
                }
            }
        }
        return dp[lenS][lenP];
    }
};