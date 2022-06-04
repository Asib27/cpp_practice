#include<iostream>
#include<vector>
#include<tuple>
#include<climits>
#include<queue>
#include<algorithm>

using namespace std;

typedef tuple<int, int, int> WeightedEdge;
typedef vector<vector<pair<int, int>>> WeightedGraph;

void print(vector<int> &v){
    for(auto i: v){
        cout << i << " ";
    }

    cout << endl;
}

int djaskatra(int nodes, const WeightedGraph &graph, int src, int dest, vector<int> &path){
    vector<int> distance(nodes, INT_MAX), parent(nodes, -1);
    distance[src] = 0;

    priority_queue<WeightedEdge, vector<WeightedEdge>, greater<WeightedEdge>> pq;
    for(auto &i: graph[src])
        pq.push(make_tuple(i.second, src, i.first));

    for(int i = 1; i < nodes; i++){
        int a, b, w;
        tie(w, a, b) = pq.top(); pq.pop();

        distance[b] = distance[a] + w;
        parent[b] = a;
        for(auto &i: graph[b]){
            if(distance[i.first] == INT_MAX)
                pq.push(make_tuple(i.second, b, i.first));
        }
    }

    // print(distance);
    for(int i = dest; i != -1; i = parent[i])
        path.push_back(i);
    reverse(path.begin(), path.end());

    return distance[dest];
}

int bellman_ford(int nodes, const vector<WeightedEdge> &edges, int src, int dest, vector<int> &path){
    vector<int> distance(nodes, INT_MAX), parent(nodes, -1);
    distance[src] = 0;

    //creating shortest path tree
    for(int i = 0; i < nodes-1; i++){
        for(auto &j: edges){
            int a, b, w;
            tie(w, a, b) = j;

            if(distance[a] != INT_MAX && distance[a] + w < distance[b]){
                distance[b] = distance[a] + w;
                parent[b] = a;
            }
        }
    }

    // print(distance);
    // print(parent);
    //detecting negative cycle
    for(auto &j: edges){
        int a, b, w;
        tie(w, a, b) = j;

        if(distance[b] > distance[a] + w)
            return -1;
    }

    //returning ans
    for(int i = dest; i != -1; i = parent[i])
        path.push_back(i);
    reverse(path.begin(), path.end());

    return distance[dest];
}

int main(){
    int n, m;
    cin >> n >> m;

    WeightedGraph graph(n);
    vector<WeightedEdge> edges;
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;

        graph[a].push_back({b,w});

        edges.push_back(make_tuple(w, a, b));
    }

    int u,v;
    cin >> u >> v;

    bool djiskatra = true;
    if(djiskatra){
        vector<int> path;
        cout << "Shortest path cost: " << djaskatra(n, graph, u, v, path) << endl;
        for(auto i: path){
            if( i != path.back())
                cout << i << " -> ";
            else
                cout << i ;
        }
        cout << endl;
    }
    else{
        vector<int> path;
        int w = bellman_ford(n, edges, u, v, path);

        if(path.size() != 0){
            cout << "The graph does not contain a negative cycle" << endl;
            cout << "Shortest path cost: " << w << endl;
            for(auto i: path){
                if( i != path.back())
                    cout << i << " -> ";
                else
                    cout << i ;
            }
            cout << endl;
        }
        else{
            cout << "The graph contains a negative cycle" << endl;
        }
    }
}