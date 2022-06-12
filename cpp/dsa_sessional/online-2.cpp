#include<iostream>
#include<vector>
#include<utility>
#include<tuple>
#include<algorithm>
#include<set>
#include<queue>
#include<iomanip>
#include<stack>

using namespace std;

bool inV(vector<pair<int, int>> removed, int cur, int next){
    for(auto &i: removed){
        int edge1 = i.first;
        int edge2 = i.second;
        if((next == edge2 && cur == edge1) || (next == edge1 && cur == edge2)){
            return true;
        }
    }

    return false;
}

int dfs(vector<vector<pair<int, double>>> &graph, vector<pair<int, int>> removed){
    stack<int> st;
    vector<bool> seen(graph.size(), false);

    st.push(0);
    seen[0] = true;

    while(!st.empty()){
        int cur  = st.top(); st.pop();

        //cout << cur << endl;
        for(auto &nei: graph[cur]){
            int next = nei.first;

            if(inV(removed, cur, next) || seen[next]){
                continue;
            }

            //cout << cur << " " << next << endl;
            seen[next] = true;
            st.push(next);
        }
    }

    /*
    for(auto i: seen) cout << i << " ";
    cout << endl;
    */
    return accumulate(seen.begin(), seen.end(), 0);
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, double>>> graph(n);
    vector<tuple<double, int, int>> edges;
    for(int i = 0; i < m; i++){
        int a, b;
        double w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});

        edges.push_back(make_tuple(w, a, b));
    }

    sort(edges.rbegin(), edges.rend());
    /*
    for(auto i: edges){
        double w;
        int a, b;
        tie(w, a, b) = i;
        cout << w << " " << a << " " << b << endl;
    }
    */

    vector<pair<int, int>> mst_edge, removed;
    double weight = 0;
    for(auto &i: edges){
        double w;
        int a, b;
        tie(w, a, b) = i;

        removed.push_back({a, b});
        if(dfs(graph, removed) != n){
            mst_edge.push_back({a, b});
            weight += w;
            removed.pop_back();
        }
    }

    cout << "Edges in mst\n";
    for(auto i: mst_edge){
        cout << "(" << i.first << "," << i.second << ")" << endl;
    }
    cout << "Total weight of MST is " << weight << endl;
}
