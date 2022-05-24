//this is a problem of converting 27 base number "AB" to 
//10 base number system. 
//std no converting algorithm is used

class Solution {
public:
    int titleToNumber(string columnTitle) {
        int ans = 0;
        for(auto i: columnTitle){
            ans = ans * 26 + (i - 'A' + 1);
        }
        
        return ans;
    }
};