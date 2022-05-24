class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int st = 0, ls = people.size() -1;
        int ans = 0;
        
        sort(people.begin(), people.end());
        
        while(st <= ls){
            if(st == ls) return ans+1;
            else if(people[st] + people[ls] <= limit){
                st++; ls--;
                ans++;
            }
            else{
                ls--;
                ans++;
            }
            
        }
        
        return ans;
    }
};