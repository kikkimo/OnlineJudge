class Solution {
public:
    string multiply(string num1, string num2) {
        int l1 = num1.length();
        int l2 = num2.length();
        string res(l1 + l2, '0');
        for(int i = l1 - 1; i >= 0; i--) {
            for(int j = l2 - 1; j >= 0; j--) {
                int sum = (res[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0');
                res[i + j + 1] = sum % 10 + '0';
                res[i + j] += sum / 10;
            }
        }
        for(int i = 0; i < res.length(); i++) {
            if(res[i] != '0' || i == res.length() - 1) return res.substr(i);
        }
        return "";
    }
};