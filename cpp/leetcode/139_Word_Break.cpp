class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        
        unordered_set<string> st(wordDict.begin(), wordDict.end());
        vector<int> dp(n, false);
        
        for(int i = 0; i < n; i++){
            for(int j = i; j >= 0; j--){
                if(st.count(s.substr(j, i-j+1))){
                    if(j == 0) dp[i] = true;
                    else if(dp[j-1]) dp[i] = dp[j-1];
                    
                }
            }
        }
        
        return dp[n-1];
    }
};