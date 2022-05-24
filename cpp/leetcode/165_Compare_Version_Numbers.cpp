class Solution {
    int parse(string st, int s, int e){
        int ans = 0;
        for(int i = s; i < e; i++){
            ans =  ans * 10 + st[i] - '0';
        }
        return ans;
    }
    
    int nextDot(string st, int i){
        for(; i < st.size(); i++ ){
            if(st[i] == '.') return i;
        }
        return st.size();
    }
public:
    int compareVersion(string version1, string version2) {
        int s1, s2, e1, e2;
        s1 = s2 = 0;
        e1 = nextDot(version1, 0);
        e2 = nextDot(version2, 0);
        
        while(s1 < version1.size() || s2 < version2.size()){
            int one = parse(version1, s1, e1);
            int two = parse(version2, s2, e2);
            
            if(one != two) return (one - two) / abs(one-two);
            else{
                s1 = e1 + 1;
                s2 = e2 + 1;
                e1 = nextDot(version1, s1);
                e2 = nextDot(version2, s2);   
            }
        }
        
        return 0;
    }
};