#include<iostream>
#include<vector>
#include<tuple>
#include<utility>
#include<climits>
#include<queue>
#include<algorithm>

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
    }

    //adding s vertices to match nodes and connecting match nodes to team nodes
    int vertice_no = nodes+2;
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < i; j++){
            if(i == idx || j == idx) continue;

            graph[0].push_back({vertice_no, against[i][j]});
            graph.push_back(vector<pair<int, int>>());

            graph[vertice_no].push_back({i+2, INT_MAX}); // team 0 has node no 2
            graph[vertice_no].push_back({j+2, INT_MAX});

            vertice_no++;
        }
    }

    return graph;
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

bool bfs(const WeightedGraph &graph, int src, int dest, vector<int> &path){
    int n = graph.size();
    vector<int> parents(n, -1);

    queue<int> qu;
    qu.push(src);

    while(!qu.empty() && parents[dest] == -1){ 
        int cur = qu.front(); qu.pop();

        for(auto i: graph[cur]){
            if(i.second < 0) return false;
            if(i.second != 0 && parents[i.second] == -1){
                qu.push(i.first);
                parents[i.first] = cur;
            }
            
            if(i.first == dest) break; 
        }
    }

    path.clear();
    for(int i = dest; i != -1; i = parents[i]){
        path.push_back(i);
    }
    reverse(path.begin(), path.end());

    return parents[dest] != -1;
}

int find_weight(vector<pair<int, int>> v, int dest){
    for(auto i: v){
        if(i.first == dest) return i.second;
    }
    return 0;
}


Matrix list_to_matrix(const WeightedGraph &graph){
    int n = graph.size();
    Matrix w(n, vector<int>(n, INT_MAX)), temp(n, vector<int>(n, INT_MAX));

    for(int i = 0; i < graph.size(); i++){
        for(auto &j: graph[i]){
            w[i][j.first] = j.second;
        }
    }

    for(int i = 0; i < n; i++) w[i][i] =  0;

    return w;
}

Graph weighted_to_adjlist(const WeightedGraph &graph){
    Graph g(graph.size());

    for(int i = 0; i < graph.size(); i++){
        for(auto j: graph[i]) g[i].push_back(j.first);
    }

    return g;
}

bool edmond_carp(WeightedGraph graph){
    Matrix weights = list_to_matrix(graph);
    vector<int> path;

    while(bfs(graph, 0, 1, path)){
        int mn = INT_MAX;
        for(int i = 1; i < path.size(); i++){
            int cur = path[i], prev = path[i-1];
            mn = min(find_weight(graph[prev], cur), mn);
            //cout << find_weight(graph[prev], cur) << " " << prev << " " << cur << " ** ";
        }
        //cout << mn << " " << path.size() << endl;

        for(int i = 1; i < path.size(); i++){
            int cur = path[i], prev = path[i-1];
            for(auto &j: graph[prev]){
                if(j.first == cur)
                    j.second = (j.second == INT_MAX ? INT_MAX: j.second - mn);
            } 
        }

        // cout << "---------------------------------------------------" << endl;
        // print(graph);
    }
    
    for(auto i: graph[0]){
        if(i.second != 0) return false;
    }
    return true;
}

int main(){
    int T;
    cin >> T;
    while(T--){
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

        for(int i = 0; i < n; i++){
            auto g = createGraph(i, n, win, left, against);
            if(!edmond_carp(g)){
                cout << names[i] << " is eliminated" << endl;
            }
        }

        cout << "-------------------------------------------------------------\n" << endl;
    }
}