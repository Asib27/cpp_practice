class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int cnt = 0;
        for(auto &i: s){
            if(i == '(') cnt++;
            if(i == ')'){
                if(cnt == 0) i = '#';
                else cnt--;
            }
        }
        
        cnt = 0;
        for(int i = s.length()-1; i >= 0; i--){
            if(s[i] == ')') cnt++;
            if(s[i] == '('){
                if(cnt == 0) s[i] = '#';
                else cnt--;
            }
        }
        
        string ans;
        for(auto i: s){
            if(i != '#') ans += i;
        }
        return ans;
    }
};