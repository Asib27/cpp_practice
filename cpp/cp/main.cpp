#include <bits/stdc++.h>

using namespace std;

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V> &x) {
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}

template <typename T>
void __print(const T &x) {
    int f = 0;
    cerr << '{';
    for (auto &i : x) cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}

void _print() { cerr << "]\n"; }//one

template <typename T, typename... V>
void _print(T t, V... v) { //one
    __print(t);
    if (sizeof...(v)) cerr << ", ";
    _print(v...); //one
}

#define debug(x...) \
    cerr << "[" << #x << "] = ["; \
    _print(x) //one
// add a newline at the end

#define endl "\n"

typedef long long ll;
#define M_PI 3.14159265358979323846

void solve() {
    long double x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    long double d = hypot(x1-x2, y1-y2);
    if(d < r1 + r2){
        long double a = r1*r1, b = r2*r2;
        long double x = (a-b+d*d)/2/d;
        long double y = sqrt(a - x*x);

        if(d < abs(r1-r2)){
            cout << setprecision(8) << M_PI * min(a, b) << endl;
        }
        else{
            long double ans = a * acos(x/r1) + b * acos(x/r2) 
            - y * (x + sqrt(b-a + x*x));
            cout << setprecision(8) <<ans << endl;
        }
    }
    else{
        cout << 0.0 << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int t; cin >> t;
    // for (int tc = 1; tc <= t; tc++) {
        // cout << "Case " << tc << ": ";
        solve();
    //}
}