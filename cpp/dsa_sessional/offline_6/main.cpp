#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include "Graph.h"

using namespace std;

void printGraph(Graph &graph){
    int x = graph.getNoVertex();
    for(int i = 0; i <= x; i++){
        for(auto j: graph.getEdge(i)){
            cout << j << " ";
        }
        
        cout << i << endl;
    }
}

int bfs(Graph &graph, int start, int dice, vector<bool> &seen, vector<int> &parent){
    int cur = start;
    int x = graph.getNoVertex();
    int step = 0;
 
    queue<int> qu;
    qu.push(cur);
    seen[cur] = true;

    while(!qu.empty()){
        int sz = qu.size();

        if(!seen[x])
            step++;
        //cout << endl;
        
        for(int i = 0; i < sz; i++){
            int top = qu.front();
            qu.pop();

            for(int j = 1; j <= dice; j++){
                cur = top + j;
                if(cur <= x && !seen[cur]){
                    seen[cur] = true;
                    parent[cur] = top;
                    //cout << cur << " ";
                    if(graph.getEdge(cur).size() != 0){
                        int t = graph.getEdge(cur)[0];

                        if(!seen[t])
                            parent[t] = cur;
                        cur = t;
                        seen[cur] = true;
                        //cout << "( " << " " << cur << " ) ";
                    }

                    qu.push(cur);
                }
            }
        }
    }

    return step;
}

bool every(vector<bool> v){
    for(int i = 1; i < v.size(); i++){
        if(!v[i]) return false;
    }

    return true;
}

int main(){
    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    while(T--){
        int n, x;
        cin >> n >> x;

        Graph graph(x);

        int l, s;
        cin >> l;
        graph.addEdge(Graph::inputEdge(cin, l, true));

        cin >> s;
        graph.addEdge(Graph::inputEdge(cin, s, true));

        vector<bool> seen(x+1, false);
        vector<int> parent(x+1, -1);

        int steps = bfs(graph, 1, n, seen, parent);

        //output answer
        vector<int> ans;
        for(int i = x; i != -1; i = parent[i]){
            ans.push_back(i);
        }

        if(*(ans.rbegin()) == 1){
            cout << steps << endl;
            for(auto it = ans.rbegin(); it != ans.rend(); it++){
                if(it != ans.rbegin())
                    cout << " -> ";
                cout << *it;
            }
            cout << endl;
        }
        else{
            cout << "-1\nNo solution" << endl;
        }

        if(every(seen)) cout << "All reachable" << endl;
        else{
            for(int i = 1; i < seen.size(); i++){
                if(!seen[i]) cout << i << " ";
            }
            cout << endl;
        }

        cout << endl;
    }
}