#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

/* assumption: 
* it is a simple graph 
* nodes name are 0 based int
*/

class Graph
{
private:
    vector<vector<int>> adj_list;
    int no_node;
    int no_edge;
    bool is_directed;
public:
    Graph(int nodes, bool directed=false)
        : adj_list(nodes) , no_node(nodes),
          is_directed(directed)
    {
        
    }

    Graph(int nodes, int edges, istream &is , bool directed=false)
        : Graph(nodes, directed)
    {
        no_edge = edges;
        read_graph(is);
    }

    Graph& read_graph(istream &is){
        int from, to;
        for(int i = 0; i < no_edge; i++){
            is >> from >> to;

            adj_list[from].push_back(to);
            if(!is_directed){
                adj_list[to].push_back(from);
            }
        }

        return *this;
    }

    Graph& setEdgeList(int node, vector<int> &edge_list){
        no_edge += edge_list.size() - adj_list[node].size();
        adj_list[node] = edge_list;
        return *this;
    }

    vector<int>& getEdgeList(int node){
        return adj_list[node];
    }

    vector<int>& operator[](int node){
        return adj_list[node];
    }

    int getNoNode(){
        return no_node;
    }

    Graph transposeGraph() const{
        Graph g(no_node);

        for(int i = 0; i < no_node; i++){
            vector<bool> edge_present(no_node, false);

            for(auto j: adj_list[i]){
                edge_present[j] = true;
            }
            edge_present[i] = true; // so that self edge does not appear

            for(int j = 0; j < no_node; j++){
                if(!edge_present[j])
                    g.adj_list[i].push_back(j);
            }
        }

        return g;
    }

    friend ostream & operator<<(ostream &os, const Graph &g){
        os << "Node -> Edges" << endl;
        for(int i = 0; i < g.no_node; i++){
            os << i << " -> " ;
            for(auto j : g.adj_list[i]){
                os << j << " ";
            }
            os << endl;
        }

        return os;
    }
};

/* returns bfs tree */
Graph bfs(Graph &graph, int src_node){
    stack<int> st;
    vector<bool> seen(graph.getNoNode(), false);
    Graph bfs_tree(graph.getNoNode());

    st.push(src_node);
    seen[src_node] = true;
    
    while (!st.empty()){
        int cur = st.top(); st.pop();

        for(auto edge: graph[cur]){
            if(seen[edge]) continue;

            st.push(edge);
            seen[edge] = true;
            bfs_tree[cur].push_back(edge);
        }
    }

    return bfs_tree;
}

/* returns dfs tree */
Graph dfs(Graph &graph, int src_node){
    queue<int> qu;
    vector<bool> seen(graph.getNoNode(), false);
    Graph dfs_tree(graph.getNoNode());

    qu.push(src_node);
    seen[src_node] = true;
    
    while (!qu.empty()){
        int cur = qu.front(); qu.pop();

        for(auto edge: graph[cur]){
            if(seen[edge]) continue;

            qu.push(edge);
            seen[edge] = true;
            dfs_tree[cur].push_back(edge);
        }
    }

    return dfs_tree;
}


int main(){
    int n, e;
    cin >> n >> e;
    Graph g(n, e, cin, true);
    
    cout << g << endl << g.transposeGraph() << endl;

    cout << bfs(g, 0) << endl;
    cout << dfs(g, 0) << endl;
}