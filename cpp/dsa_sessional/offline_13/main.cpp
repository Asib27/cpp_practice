#include<iostream>
#include<vector>
#include<tuple>
#include<utility>
#include<climits>
#include<queue>
#include<algorithm>
#include<set>
#include<sstream>

using namespace std;

typedef tuple<int, int, int> WeightedEdge;
typedef vector<vector<pair<int, int>>> WeightedGraph;
typedef vector<vector<int>> Matrix;
typedef vector<vector<int>> Graph;


void print(Matrix &m){
    for(auto &i: m){
        for(auto j: i)
            if(j != INT_MAX)
                cout << j << " ";
            else
                cout << "INF ";
        cout << endl;
    }
}

void print(WeightedGraph graph){
    for(int i = 0; i < graph.size(); i++){
        cout << i  << " -> ";
        for(auto j: graph[i]){
            cout << j.first << " " << j.second << " ** ";
        }
        cout << endl;
    }
}

int find_weight(vector<pair<int, int>> v, int dest){
    for(auto i: v){
        if(i.first == dest) return i.second;
    }
    return 0;
}


Matrix list_to_matrix(const WeightedGraph &graph){
    int n = graph.size();
    Matrix w(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(auto &j: graph[i]){
            w[i][j.first] = j.second;
        }
    }

    return w;
}

Graph weighted_to_adjlist(const WeightedGraph &graph){
    Graph g(graph.size());

    for(int i = 0; i < graph.size(); i++){
        for(auto j: graph[i]) {
            g[i].push_back(j.first);
            g[j.first].push_back(i);
        }
    }

    return g;
}


WeightedGraph createGraph(int idx, int nodes, const vector<int> &win, const vector<int> &left,
                            const Matrix &against
                            )
{
    WeightedGraph graph(nodes+2); // nodes + s + t = nodes + 2 
    /* index maps to nodes in following way 
        s -> 0 , t -> 1, 2- nodes+2 team nodes, later vertices represents game nodes
    */
    
    // adding directed edge of weight win_idx + leftr_idx - win_i to sink vertex
    for(int i = 0; i < nodes; i++){
        graph[i+2].push_back({1, win[idx] + left[idx] - win[i]});

        // if neg edge exist, then eliminated
        if(win[idx] + left[idx] - win[i] < 0){
            graph.clear();
            return graph;
        }
    }

    //adding s vertices to match nodes and connecting match nodes to team nodes
    int vertice_no = nodes+2;
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < i; j++){
            if(i == idx || j == idx /*|| against[i][j] == 0*/) continue;

            graph[0].push_back({vertice_no, against[i][j]});
            graph.push_back(vector<pair<int, int>>());

            graph[vertice_no].push_back({i+2, INT_MAX}); // team 0 has node no 2
            graph[vertice_no].push_back({j+2, INT_MAX});

            vertice_no++;
        }
    }

    return graph;
}

bool bfs(const Graph &graph, const Matrix &weights, int src, int dest, vector<int> &path){
    int n = graph.size();
    vector<int> parents(n, -1);

    queue<int> qu;
    qu.push(src);
    parents[src] = -2;

    while(!qu.empty()){ 
        int cur = qu.front(); qu.pop();

        for(auto i: graph[cur]){
            if(weights[cur][i] && parents[i] == -1){
                parents[i] = cur;
                qu.push(i);
            }
        }
    }

    path.clear();
    for(int i = dest; i != -2; i = parents[i]){
        path.push_back(i);
    }
    reverse(path.begin(), path.end());

    return parents[dest] != -1;
}

bool edmond_carp(WeightedGraph graph, int src, int sink, set<int> &min_cut){
    Matrix capacity = list_to_matrix(graph);
    Graph adj = weighted_to_adjlist(graph);

    vector<int> path;

    while(bfs(adj, capacity, src, sink, path)){
        int mn = INT_MAX;
        for(int i = 1; i < path.size(); i++){
            int cur = path[i], prev = path[i-1];
            mn = min(capacity[prev][cur], mn);
        }

        for(int i = 1; i < path.size(); i++){
            int cur = path[i], prev = path[i-1];

            capacity[prev][cur] -= mn;
            capacity[cur][prev] += mn;
        }
    }
    
    for(int i = adj[src][0]; i < capacity[src].size(); i++){
        if(capacity[src][i] != 0){
            for(auto n: adj[i]) min_cut.insert(n-2);
        }
    }
    if(min_cut.count(src-2)) min_cut.erase(src-2);
    return !min_cut.size();
}

string cause_of_elimination(set<int> st,const Matrix &against,const vector<int> &wins){
    vector<int> eliminated;
    int win = 0, left = 0;

    for(auto i: st) {
        eliminated.push_back(i);
        win += wins[i];
    }

    for(int i = 0; i < eliminated.size(); i++){
        for(int j = 0; j < i; j++){
            left += against[eliminated[i]][eliminated[j]];
        }
    }

    stringstream ss;
    ss << "have won a total of " << win << " games.\n" <<
               "They play each other " << left << " times.\n" <<
               "So on average, each of the teams wins " << 
               win+left<< " / " <<st.size() << " = " << double(win+left) / st.size() << 
               " games.\n";
    return ss.str();
}

void print_result(int idx,const vector<int> &win, const vector<int>& left, 
                    const Matrix &against, const vector<string> &names, set<int> st){

    cout << "They can win at most " << win[idx] << " + " << left[idx]
                        << " = " << win[idx] + left[idx] << " games." << endl;

    for(auto i: st){
        cout << names[i] << " ";
    }
    cout << cause_of_elimination(st, against, win) << endl;
}

int main(){
    int n;
    cin >> n;

    Matrix against(n, vector<int>(n, 0));
    vector<string> names(n);
    vector<int> win(n), loss(n), left(n);
    for(int i = 0; i < n; i++){
        cin >> names[i] >> win[i] >> loss[i] >> left[i];

        for(auto &j: against[i]){
            cin >> j;
        }
    }

    int s = 0,  t = 1;

    for(int i = 0; i < n; i++){
        auto g = createGraph(i, n, win, left, against);
        set<int> st;

        if(!g.size() || !edmond_carp(g, s, t, st)){
            cout << names[i] << " is eliminated" << endl;
            if(!g.size()){
                for(int j = 0; j < n; j++){
                    if(j == i) continue;

                    if(win[i]+left[i] < win[j]) st.insert(j);

                }
            }

            print_result(i, win, left, against, names, st);
        }
    }
    
}