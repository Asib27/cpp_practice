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

void relax(WeightedEdge edge, vector<int>& distance, vector<int>& parent, vector<int>& no_edges){
    int a, b, w;
    tie(w, a, b) = edge;

    if(distance[a] + w < distance[b] ){
        distance[b] = distance[a] + w;
        parent[b] = a;
        no_edges[b] = no_edges[a] + 1;
    }
    if(distance[a] + w == distance[b]  && no_edges[a] + 1 < no_edges[b]){
        parent[b] = a;
        no_edges[b] = no_edges[a] + 1;
    }
}

vector<int> bellman_ford(int nodes, const vector<WeightedEdge> &edges, int src){
    vector<int> distance(nodes, INT_MAX), parent(nodes, -1), no_edges(nodes, INT_MAX);
    distance[src] = 0;
    no_edges[src] = 0;

    //creating shortest path tree
    for(int i = 0; i < nodes-1; i++){
        for(auto &j: edges){
            int a, b, w;
            tie(w, a, b) = j;

            if(distance[a] != INT_MAX && distance[a] + w < distance[b] ){
                distance[b] = distance[a] + w;
                parent[b] = a;
                no_edges[b] = no_edges[a] + 1;
            }
            if(distance[a] != INT_MAX && distance[a] + w == distance[b]  && no_edges[a] + 1 < no_edges[b]){
                parent[b] = a;
                no_edges[b] = no_edges[a] + 1;
            }

        }
    }

    return no_edges;
}


int main(){
    int n, m;
    cin >> n >> m;

    vector<WeightedEdge> edges;
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;

        edges.push_back(make_tuple(w, a, b));
        edges.push_back(make_tuple(w, b, a));
    }

    int s;
    cin >> s;

    auto dest = bellman_ford(n, edges, s);
    print(dest);
}
