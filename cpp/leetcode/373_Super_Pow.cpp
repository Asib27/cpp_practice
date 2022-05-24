class Solution {
public:
    int superPow(int a, vector<int>& b) {
        int pow = 0;
        for(auto x: b) pow = (10 * pow + x) % 1140;
        
        int ans = 1, t = a % 1337;
        
        while(pow){
            if(pow % 2)
                ans = t * ans % 1337;
            
            t = t * t % 1337;
            pow /= 2;
        }
        
        return ans;
    }
};