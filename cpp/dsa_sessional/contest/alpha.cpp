#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> v(n), ps(n+1);
    for(auto &i: v) cin >> i;
    for(int i = 0; i < n; i++){
        ps[v[i]] = i;
    }

    int step = 0;
    for(int i = 1; i < n; i++){
        if(ps[i] > ps[i+1]) step++;
    }

    cout << step+1 << endl;
}
