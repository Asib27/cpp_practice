#include<iostream>
#include<cmath>
#include <vector>

using namespace std;

int solve(int n){
    int ans  = 0;
    while(n){
        int s = sqrt(n);
        n -= s*s;
        //cout << s << " " << n<< endl;
        ans++;
    }

    return ans;
}

bool is_pf_sq(int n){
    int t = sqrt(n);
    return t*t == n;
}

int main(){
    int n;
    cin >> n;

    vector<int> dp(n+1, INT_MAX);
    dp[0] = 0;
    dp[1] = 1;

    for(int i = 2; i <= n; i++){
        if(is_pf_sq(i))
            dp[i] = 1;
        else{
            for(int j = 0; j <= i/2; j++){
                dp[i] = min(dp[i], dp[j] + dp[i-j]);
            }
        }
    }

    cout << dp[n] << endl;
}