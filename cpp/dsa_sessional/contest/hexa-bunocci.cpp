#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int mod = 10000007;

int main(){
    int T, C;
    cin >> T;
    C = T;

    while(T--){
        long long dp[10001] = {0};
        long long n;
        cin >> dp[0] >> dp[1] >> dp[2] >> dp[3] >> dp[4] >> dp[5] >> n;
        
        for(int i = 6; i <= n; i++){
            // long long t = 0;
            // for(int j = 1; j <= 6; j++){
            //     t = (t + dp[i-j]) %mod;
            // }
            dp[i] = (dp[i-1] + dp[i-2] + dp[i-3] + dp[i-4] + dp[i-5] + dp[i-6])%mod;
        }

        cout << "Case " << C-T << ": "<< dp[n] %mod << endl;
    }
}