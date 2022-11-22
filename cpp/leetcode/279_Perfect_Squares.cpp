class Solution {
public:
    int numSquares(int n) {
        vector<int> ans(n+1, INT_MAX);
        
        ans[1] = 1;
        ans[0] = 0;
        for(int i = 0; i < n+1; i++){
            for(int j = 1; j*j + i < n+1; j++){
                ans[i + j*j] = min(ans[i] + 1, ans[i + j*j]);
            }
        }
        
        return ans[n];
    }
};
