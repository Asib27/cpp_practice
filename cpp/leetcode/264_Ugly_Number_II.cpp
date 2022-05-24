class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        dp[0] = 1;
        int two = 0, three = 0, five = 0;
        
        for(int i = 1; i < n; i++){
            int tw = 2 * dp[two], th = 3 * dp[three], f = 5 * dp[five];
            
            dp[i] = min({tw, th, f});
            if(dp[i] == tw){
                two++;
            }
            if(dp[i] == th){
                three++;
            }
            if(dp[i] == f){
                five++;
            }
        }
        
        //for(auto i: dp) cout << i << " ";
        return dp[n-1];
    }
};