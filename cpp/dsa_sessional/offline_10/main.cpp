#include<iostream>
#include<vector>
#include<utility>
#include<tuple>
#include<algorithm>
#include<set>
#include<queue>
#include<iomanip>

using namespace std;

double prims_mst(int nodes, vector<pair<int, double>> graph[], vector<pair<int, int>> &mst_edge){
    set<int> st;
    priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>, greater<tuple<double, int, int>>> pq;

    for(auto i: graph[0]){
        pq.push(make_tuple(i.second, 0, i.first));
    }

    st.insert(0);

    double sum = 0;
    while (st.size() < nodes){
        int a, b;
        double w;
        tie(w, a, b) = pq.top();
        pq.pop();

        if(st.count(a) && st.count(b)) continue;
        else{
            int ne = st.count(a)? b: a;
            sum += w;
            st.insert(ne);
            mst_edge.push_back({a, b});

            for(auto i: graph[ne]){
               pq.push(make_tuple(i.second, ne, i.first));
            }
        }
    }    
    return sum;
}

class DisjoinSets
{
private:
    vector<int> parents;
public:
    DisjoinSets(int no_of_sets): parents(no_of_sets){
        for(int i = 0; i < no_of_sets; i++){
            parents[i] = i;
        }
    }

    int find(int node){
        int p = parents[node];
        if(p == node) return p;
        return parents[node] = find(p);
    }

    void union_set(int n1, int n2){
        int p1 = find(n1);
        int p2 = find(n2);

        parents[p1] = p2;
    }
};

double kruskals_mst(int nodes, vector<tuple<double, int, int>> edges, vector<pair<int, int>> &mst_edge){
    sort(edges.begin(), edges.end());
    DisjoinSets sets(nodes);

    int added = 0;
    double sum = 0.0;

    for(auto &i: edges){
        double w; int a, b;
        tie(w, a, b) = i;

        if(sets.find(a) != sets.find(b)){
            mst_edge.push_back({a, b});
            sets.union_set(a, b);
            sum += w;
            added++;

            if(added == nodes-1) break;
        }
    }

    return sum;
}

void print(vector<pair<int, int>> &v){
    cout << '{';
    for(int i = 0; i < v.size(); i++){
        cout << '(' << v[i].first << "," << v[i].second << ")" ;
        if(i != v.size() -1)
            cout << ',';
    }
    cout << '}';
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<pair<int, double>> graph[n];
    vector<tuple<double, int, int>> edges;
    for(int i = 0; i < m; i++){
        int a, b;
        double w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});

        edges.push_back(make_tuple(w, a, b));
    }

    vector<pair<int, int>> edge_kruskal;
    double weight_kruskal = kruskals_mst(n, edges, edge_kruskal);
    vector<pair<int, int>> edge_prim;
    double weight_prim = prims_mst(n, graph, edge_prim);
    
    cout << "Cost of the minimum spanning tree : "  << weight_kruskal << endl;
    cout << "List of edges selected by Prim's: ";
    print(edge_prim);
    cout << endl;
    cout << "List of edges selected by Kruskal's: ";
    print(edge_kruskal);
    cout << endl;
}