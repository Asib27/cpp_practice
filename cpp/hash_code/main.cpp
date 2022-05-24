#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<set>
#include<map>

using namespace std;

int main(){
    //freopen("output_B.txt", "w", stdout);

    int C;
    cin >> C;
    vector<vector<string>> like(C), dislike(C);
    for(int i = 0; i < C; i++){
        int t;
        
        cin >> t;
        like[i].resize(t);
        for(auto &i: like[i]) cin >> i;
        
        cin >> t;
        dislike[i].resize(t);
        for(auto &i: dislike[i]) cin >> i;
    }

    map<string, int> ans;
    for(auto &i: like){
        for(auto j: i)
            ans.insert(j);
    }

    cout << ans.size() << " ";
    for(auto i: ans){
        cout << i << " ";
    }
    cout << endl;
}