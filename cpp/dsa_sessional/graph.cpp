#include<iostream>
#include<vector>

class Graph
{
private:
    vector<vector<int>> adj_list;
public:
    Graph(int nodes, int edges, bool directed=true)
        : adj_list(nodes, vector<int>(edges, 0))
    {
        
    }

    Graph(int nodes, int edges, istream &is , bool directed=true)
        : adj_list(nodes, vector<int>(edges, 0))
    {
        
    }
    ~Graph();
};


int main(){

}