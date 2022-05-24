#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Graph{
private:
    vector<vector<int>> graph;
    int vertex ;
public:
    Graph(int ver): graph(ver+1), vertex(ver){

    }

    void addEdge(pair<int, int> edge){
        graph[edge.first].push_back(edge.second);
    }

    void addEdge(vector<pair<int, int>> edges){
        for(auto &edge: edges){
            addEdge(edge);
        }
    }

    vector<int> getEdge(int node){
        return graph[node];
    }

    int getNoVertex(){
        return vertex;
    }

    static vector<pair<int, int>> inputEdge(std::istream &is, int n, bool directed=false){
        vector<pair<int, int>> edges;
        int x , y;

        for(int i = 0; i < n; i++){
            is >> x >> y;

            edges.push_back({x,y});
            if(!directed){
                edges.push_back({y,x});
            }
        }

        return edges;
    }
};

#endif