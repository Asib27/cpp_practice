#include<iostream>
#include<vector>

using namespace std;

vector<int> cache(200001);

long long merge(vector<int> &v, int s, int m, int en){
    int pt1 = s, pt2 = m;
    long long in = 0;
    int idx = 0;

    //cout << "#1" << endl;
    while(pt1 < m && pt2 < en){
        //cout << v[pt1] << " " << v[pt2] << " ";
        if(v[pt1] <= v[pt2]){
            //cout << "No " << in << endl;
            cache[idx++] = v[pt1++];
        }
        else{
            cache[idx++] = v[pt2++];
            in += m - pt1;
            //cout << "Yes " << in << endl;
        }
    }

    //cout << "#2" << endl;
    while(pt1 < m){
        cache[idx++] = v[pt1++];
    }
    while(pt2 < en){
        cache[idx++] = v[pt2++];
    }

    //cout << "#3" << endl;
    for(int i = s; i < en; i++){
        v[i] = cache[i-s];
    }

    return in;
}

long long inversion_count(vector<int> &v, int st, int en){
    if(st >= en-1) return 0;
    int mid = st + (en-st)/2;
    

    long long in = inversion_count(v, st, mid);
    in += inversion_count(v, mid, en);

    in += merge(v, st, mid, en);

    //cout <<st << " " << en << " " << mid << " " << in << endl;
    return in;
}

int main(){
    // vector<int> a({2,3,1, 6,8});
    // cout << merge(a, 0, 2, 5) << endl; 

    int T;
    cin >> T;

    while(T--){
        int n;
        cin >> n;
        vector<int> v(n);
        for(auto &i: v) cin >> i;
        

        long long in = inversion_count(v, 0, n);
        cout << in << endl;
    }
}