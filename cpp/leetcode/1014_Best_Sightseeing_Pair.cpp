class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int res = 0, mx = values[0];
        
        for(int i = 1; i < values.size(); i++){
            mx--;
            res = max(res, mx+values[i]);
            mx = max(mx, values[i]);
        }
        
        return res;
    }
};