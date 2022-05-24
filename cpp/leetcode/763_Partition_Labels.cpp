class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26] = {0};
        
        for(int i = 0; i < s.length(); i++){
            last[s[i]-'a'] = i;
        }

        
        vector<int> partition;
        for(int start = 0; start < s.length(); ){
            int f = start, l = start;
            while(f < s.length() && f <= l){
                l = max(l, last[s[f]-'a']);
                f++;
            }
            
            partition.push_back(l-start+1);
            start = f;
        }
        
        return partition;
    }
};