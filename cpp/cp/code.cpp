#include <bits/stdc++.h>
#include<iostream>
#include<vector>

using namespace std;

const double pi = 3.14159265358979323846;
// #define rep(i, a, b) for(int i = a; i < (b); ++i)
// #define trav(a, x) for(auto& a : x)
// #define all(x) x.begin(), x.end()
// #define sz(x) (int)(x).size()

// typedef long long ll;
// typedef pair<int, int> pii;
// typedef vector<int> vi;

// const long long mod = 1000000007;

// int find(vi v, int to_find, int start){
//     for(int i = start; i < v.size(); i++){
//         if(v[i] >= to_find)
//             return i;
//     }

//     return v.size();
// }


// int find_not_matched(vector<bool> v, int to_find, int start){
//     for(int i = start; i < v.size(); i++){
//         if(v[i] != to_find)
//             return i;
//     }

//     return v.size();
// }

void print(vector<int> v){
    for(auto i : v) cout << i << " ";
    cout << endl;
}

// map<int, map<int, long long>> mp;

// long long solve(vector<vector<int>> &v, int index, int start){
//     if(index >= v.size()) return 0;
//     if(mp[index].count(start)) return mp[index][start];
//     int mn = v[index][0], mx = v[index].back();

//     if(start < mn){
//         long long low = mx-start + mx - mn + solve(v, index+1, mn);
//         long long high = mx-start + solve(v, index+1, mx);
//         return mp[index][start] = min(low, high);
//     }
//     else if(start > mx){
//         long long low = start - mn  + solve(v, index+1, mn);
//         long long high = start - mn + mx - mn + solve(v, index+1, mx);
//         return mp[index][start] = min(low, high);
//     }
//     else{
//         long long low = mx-start + mx - mn  + solve(v, index+1, mn);
//         long long high = start - mn + mx - mn + solve(v, index+1, mx);
//         return mp[index][start] = min(low, high);
//     }
// }

int main(){
    int T, C;
    cin >> T;
    C=T;
    

    while(T--){
        int n;
        string s;
        cin >> n >> s;

        bool up = false, low= false, dig = false, spe = false;
        for(auto i: s){
            if(isupper(i)) up = true;
            else if(islower(i)) low = true;
            else if(isdigit(i)) dig = true;
            else if(i == '#' || i == '@' || i == '*' || i == '&') spe = true;
        }

        if(!up) s.append(1, 'A');
        if(!low) s.append(1, 'a');
        if(!dig) s.append(1, '1');
        if(!spe) s.append(1, '*');
        n += !up + !low + !dig + !spe;

        if(n < 7) s.append(7-n, 'a');

        cout << "Case #" << C-T << ": ";
        cout << s << endl;
    }
}