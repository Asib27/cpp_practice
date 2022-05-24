class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<int> memo(101, 0);

        //updating how many people born or died on a year information on memo         
        for(auto &i: logs){
            memo[i[0] - 1950] ++;
            memo[i[1] - 1950] --;
        }
        
        //finding the max year population
        int mx = 0;
        int mx_idx = 0;
        int cur = 0;
        for(int i = 0; i < memo.size(); i++){
            cur += memo[i];
            if(cur > mx){
                mx = cur;
                mx_idx = i;
            }
        }
        
        return mx_idx + 1950;
    }
};