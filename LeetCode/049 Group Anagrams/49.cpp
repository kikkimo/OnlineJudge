class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        vector<vector<string>> res;
        int size = strs.size();
        if (0 == size) {
            return res;
        }
        if (1 == size) {
            res.push_back(strs);
            return res;
        }
        std::unordered_map<string, int> strMap;
        for (const auto &str : strs) {
            string tempStr = str;
            std::sort(tempStr.begin(), tempStr.end());
            if (strMap.find(tempStr) == strMap.end()) {
                vector<string> temp;
                temp.emplace_back(str);
                res.emplace_back(temp);
                strMap[ tempStr ] = res.size() - 1;
            } else {
                res[ strMap[ tempStr ] ].emplace_back(str);
            }
        }
        return res;
    }
};