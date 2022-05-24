#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    int n, k, m;
    cin >> n >> m >> k;
    vector<int> de(n), av(m);
    for(auto &i:de) cin >> i;
    for(auto &i:av) cin >> i;

    sort(de.begin(), de.end());
    sort(av.begin(), av.end());

    int idx = 0;
    int ans = 0;
    for(auto i: av){
        if(idx >= n)
            break;
        while(idx < n && de[idx] - k <= i){
            if(idx < n && i <= de[idx]+k){
                ans++;
                idx++;
                break;
            }

            idx++;
        }
    }

    cout << ans << endl;
    return 0;
}