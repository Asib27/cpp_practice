#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    vector<int> price(n);
    for(auto &i: price) cin >> i;
    sort(price.rbegin(), price.rend());

    int cost = 0;
    for(int i = 0; i < n; i++){
        cost += price[i] * (i / m + 1);
    }

    cout << cost << endl;
}