class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        for(auto &i: nums) i = i == 0? 0: i/abs(i);
        
        int cnt = 0;
        int pro = 1;
        int mx = 0;
        
        for(auto i: nums){
            pro *= i;
            cnt++;
            if(pro == 0){
                cnt = 0;
                pro = 1;
            }
            else if(pro == 1){
                mx = max(cnt, mx);
            }
        }
        
        cnt = 0;
        pro = 1; 
        for(int i = nums.size()-1; i >= 0; i--){
            pro *= nums[i];
            cnt++;
            if(pro == 0){
                cnt = 0;
                pro = 1;
            }
            else if(pro == 1){
                mx = max(cnt, mx);
            }
        }
        
        return mx;
    }
};