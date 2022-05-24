#include<iostream>
#include<vector>
#include<bitset>

const int MAX_INP = 10;
const int MAX_SIZE = 1024;

using namespace std;

void print(vector<vector<int>> dp){
    for(auto &i: dp){
        for(auto j: i){
            cout << j << " ";
        }

        cout << endl;
    }
}

long long find_cost(bitset<MAX_INP> mp, vector<int> costs){
    long long ans = 0;
    for(int i = 0; i < costs.size(); i++){
        ans += mp[i] * costs[i];
    }

    return ans;
}

long long find_min_cost(vector<long long> &dp, bitset<MAX_INP> mp, vector<vector<int>> &cost){
    // if(mp.count() == cost.size())
    //     return 0;

    if(dp[mp.to_ulong()] != -1)
        return dp[mp.to_ulong()];

    long long mn = LONG_LONG_MAX;

    for(int i = 0; i < cost.size(); i++){
        if(!mp[i]){
            //cout << i << " " << mp << endl;
            mp.set(i);
            auto ins_cost = find_cost(mp, cost[i]);
            mn = min(mn, ins_cost + find_min_cost(dp, mp, cost));

            mp.reset(i);
        }
    }
    

    return dp[mp.to_ulong()] = mn;
}

int main(){
    int n;
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));
    for(auto &i: cost)
        for(auto &j: i)
            cin >> j;

    int dp_size = 1<<(n);
    vector<long long> dp(dp_size, -1);
    dp.back() = 0;
    bitset<MAX_INP> mp;

    cout << find_min_cost(dp, mp, cost) << endl;
    //for(auto &i: dp) cout << i << " ";
}