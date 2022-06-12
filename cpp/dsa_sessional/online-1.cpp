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


bool checkWin(int r, int c, vector<vector<char>> &board){
    // check row
    if(board[r][0] == board[r][1] && board[r][2] == board[r][1]){
        return true;
    }
    //check column
    if(board[0][c] == board[1][c] && board[1][c] == board[2][c]){
        return true;
    }

    //check diagonal
    if(r == c){
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
            return true;
        }
    }

    if(r + c == 2){
        if(board[2][0] == board[1][1] && board[1][1] == board[0][2]){
            return true;
        }
    }

    return false;
}
/*
bool draw(vector<vector<char>> &board){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == '_') return false;
        }
    }

}
*/
/*
bool checkWin(int r, int c, vector<vector<char>> &board){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(checkWinHelp(i, j, board)) return true;
        }
    }

    return false;
}
*/

void print(vector<vector<char>> &cur){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << cur[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

bool checkSame(vector<vector<char>> cur, const vector<vector<char>> &board){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(cur[i][j] != board[i][j])
                return false;
        }
    }
    return true;
}

int dfs(vector<vector<char>> cur, const vector<vector<char>> &board, char cur_move){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(cur[i][j] != '_') continue;

            cur[i][j] = cur_move;
            auto isSame = checkSame(cur, board);
            auto isWin = checkWin(i, j, cur);

            if(isSame && isWin) return 1;
            else if(isSame) return 2;
            else if(isWin) return 3;

            int dfs_res = dfs(cur, board, (cur_move == 'X')? 'O' : 'X' );
            if(dfs_res != 3) return dfs_res;

            cur[i][j] = '_';
        }
    }

    return 3;
}

int main(){
    int T;
    cin >> T;

    while(T--){
        vector<vector<char>> des_board(3, vector<char>(3)), cur(3, vector<char>(3, '_'));
        int no_x = 0, no_o = 0;
        for(auto &i: des_board){
            for(auto &j: i){
                cin >> j;
                if(j == 'X') no_x++;
                else no_o++;
            }
        }

        cout << dfs(cur, des_board, 'X') << endl;;
    }


}
