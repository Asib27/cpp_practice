class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int idx1 = 0, idx2 = 0;
        stack<int> st;
        
        while(idx2 < popped.size()){
            if(!st.empty() && st.top() == popped[idx2]){
                st.pop();
                idx2++;
            }
            else if(idx1 < pushed.size()){
                st.push(pushed[idx1]);
                idx1++;
            }
            else{
                return false;
            }
        }
        
        return true;
    }
};