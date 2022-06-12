#include<iostream>
#include<vector>
#include<tuple>
#include<utility>
#include<climits>

using namespace std;

typedef tuple<int, int, int> WeightedEdge;
typedef vector<vector<pair<int, int>>> WeightedGraph;
typedef vector<vector<int>> Matrix;


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

void multiply(const Matrix &mat1, const Matrix &mat2, Matrix &ans){
    for(int i = 0; i < mat1.size(); i++){
        for(int j = 0; j < mat2[0].size(); j++){
            ans[i][j] = INT_MAX;
            for(int k = 0; k < mat2.size(); k++){
                if(mat1[i][k] != INT_MAX && mat2[k][j] != INT_MAX)
                    ans[i][j] = min(ans[i][j], mat1[i][k] + mat2[k][j]);
            }
        }
    }

    //print(ans);
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

Matrix all_pair_shortest_path(const WeightedGraph &graph){
    int n = graph.size();
    Matrix temp(n, vector<int>(n));
    auto w = list_to_matrix(graph);

    for(int i = 1; i < n-1; i*=2){
        //copying vectors
        for(int j = 0; j < n; j++) for(int k = 0; k < n; k++) temp[j][k] = w[j][k];
        multiply(temp, temp, w);
    }

    return w;
}

Matrix FLoyd_Warshall(WeightedGraph &graph){
    int n = graph.size();
    Matrix temp(n, vector<int>(n));
    auto w = list_to_matrix(graph);

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(w[i][k] != INT_MAX && w[k][j] != INT_MAX)
                    w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
            }
        }
    }

    return w;
}

int main(){
    int n, m;
    cin >> n >> m;

    WeightedGraph graph(n);
    vector<WeightedEdge> edges;
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;

        a--; b--;

        graph[a].push_back({b,w});
        //graph[b].push_back({a,w});

        edges.push_back(make_tuple(w, a, b));
    }

    auto dis1 = all_pair_shortest_path(graph);
    cout << "Shortest distance matrix" << endl;
    print(dis1);
    
    auto dis2 = FLoyd_Warshall(graph);
    cout << "Shortest distance matrix" << endl;
    print(dis2);
    
}