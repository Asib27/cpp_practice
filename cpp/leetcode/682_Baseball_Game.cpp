class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> score;
        for(auto &i: ops){
            if(i == "+"){
                score.push_back(score.back() + *(score.rbegin()+1));
            }
            else if(i == "D"){
                score.push_back(score.back() * 2);
            }
            
            else if(i == "C"){
                score.pop_back();
            }
            else{
                score.push_back(stoi(i));
            }
        }
        
        return accumulate(score.begin(), score.end(), 0);
    }
};