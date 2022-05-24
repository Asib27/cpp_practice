class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int mx = 0, mn = 0;
        int ans = 0;
        
        for(auto i: nums){
            if(i < 0) swap(mx, mn);
            mx = max(i, mx*i);
            mn = min(i, mn*i);
            
            ans = max(ans, mx);
        }
        
        if(ans==0) return *max_element(nums.begin(), nums.end());
        return ans;
    }
};