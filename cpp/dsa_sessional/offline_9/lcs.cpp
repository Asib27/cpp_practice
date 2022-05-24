#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

void print(vector<vector<int>> dp){
    for(auto &i: dp){
        for(auto j: i){
            cout << j << " ";
        }

        cout << endl;
    }
}

int main(){
    string X, Y;
    cin >> X >> Y;

    int m = X.size(), n = Y.size();

    //forming dp table
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(X[i-1] == Y[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;

            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    //finding answer
    string rev_ans;
    int i = m, j = n;
    while(dp[i][j]){
        if(X[i-1] == Y[j-1]){
            rev_ans.push_back(X[i-1]);
            i--; j--;
        }
        else if(dp[i][j] == dp[i-1][j]){
            i--;
        }
        else{
            j--;
        }
    }

    string ans(rev_ans.rbegin(), rev_ans.rend());
    cout << dp[m][n] << endl; 
    cout << ans << endl ;
}