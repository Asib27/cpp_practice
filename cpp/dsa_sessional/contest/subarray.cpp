#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

const int mod = 10000007;

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(auto &i: arr) cin >> i;

    long long cur_sum = 0, max_sum = INT_MIN;
    for(auto i: arr){
        cur_sum += i;
        max_sum = max(cur_sum, max_sum);
        if(cur_sum < 0) cur_sum = 0;
    }

    cout << max_sum << endl;
}