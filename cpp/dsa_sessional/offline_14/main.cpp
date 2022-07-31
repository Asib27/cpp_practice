#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <cmath>
#include <climits>
#include <queue>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node
{
    int key;
    int degree;
    bool mark;
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Node* child;

    Node(int key): key(key){};
    Node(int key, int data): key(key), data(data){};

    friend ostream& operator<<(ostream& os, const Node &n){
        os << "{ " 
           << "key: " << n.key << " ; "
           << "degree: " << n.degree << "; "
           << "mark: " << n.mark << "; "
           << "data: " << n.data << "; "
           << "left: " << (n.left == nullptr? -1: n.left->data) << "; "
           << "right: " << (n.right == nullptr? -1: n.right->data) << "; "
           << "parent: " << (n.parent == nullptr? -1: n.parent->data) << "; "
           << "child: " << (n.child == nullptr? -1: n.child->data) << "; "
           << " }";

        return os;
    }
};

class FibonacciHeap
{
private:
    Node* _mn;
    int _length;

    /**
     * @brief inserts a node to rootlist after given node
     * 
     * @param after 
     * @param toInsert 
     */
    void _insertTORootListAfterNode(Node *after, Node *toInsert){
        if(after->right == after){
            //after ----> after toInsert
            toInsert->right = toInsert->left = after;
            after->right = after->left = toInsert;
            return ;
        }
        // after next
        // after toInsert next
        toInsert->left = after;
        toInsert->right = after->right;

        toInsert->left->right = toInsert;
        toInsert->right->left = toInsert;
    }

    /**
     * @brief removes the given node from rootlist
     * but it still contains reference to its neighbours
     * 
     * @param toDelete 
     * @return Node* 
     */
    Node* _removeNodeFromRootList(Node *toDelete){
        auto left = toDelete->left;

        if(toDelete == left) // only one child left
            left = nullptr;
        else if(toDelete->right == toDelete->left){ // only two child left
            // cld left ---> left
            left->left = left;
            left->right = left;
        }
        else{ // if at least three child is there
            // left cld right
            // left right
            toDelete->left->right = toDelete->right;
            toDelete->right->left  = toDelete->left;
        }

        toDelete->parent = nullptr;
        return left;
    }

    /**
     * @brief inserts all child node of parent node to same rootlist
     * the parent exists
     * 
     * @param parent 
     */
    void _insertChildOfNodeToRootList(Node* parent){
        for(auto cld = parent->child; cld != nullptr;){
            auto left = _removeNodeFromRootList(cld);
            _insertTORootListAfterNode(parent, cld);
            cld = left;
        }
    }

    /**
     * @brief inserts a new child at root list after insertAt
     * 
     * @param insertAt 
     * @param toInsert 
     * @return Node* insertAt node is changed in the function call
     * so it is recommanded to assign to the return value;
     */
    Node* _insertNewChildAtRootList(Node* insertAt, Node* toInsert){
        if(insertAt == nullptr){
            insertAt = toInsert;
            insertAt->right = toInsert;
            insertAt->left  = toInsert;
        }
        else{
            _insertTORootListAfterNode(insertAt, toInsert);
        }

        return insertAt;
    }
    
    /**
     * @brief links child a children of parent and performs
     * associated links
     * 
     * @param parent 
     * @param child 
     * @return Node* 
     */
    Node* _fibHeapLink(Node* parent, Node* child){
        _removeNodeFromRootList(child);

        child->parent = parent;
        parent->child = _insertNewChildAtRootList(parent->child, child);

        child->mark = false;
        parent->degree ++;

        return parent;
    }

    /**
     * @brief consolidates the fibonacchi heap
     * 
     */
    void _consolidate(){
        vector<Node *> roots;
        roots.push_back(_mn);
        for(auto cur = _mn->right; cur != _mn ;cur = cur->right){
            roots.push_back(cur);
        }

        int upper_bound = log2(_length) + 2;
        vector<Node *> array(upper_bound, nullptr);
        for(auto cur : roots){
            auto z = cur;
            int d = cur->degree;
            while(array[d] != nullptr){
                auto y = array[d];

                if(z->key <= y->key) z = _fibHeapLink(z, y);
                else z = _fibHeapLink(y, z);

                array[d] = nullptr;

                d++;
            }

            array[d] = z;
        }

        _mn = nullptr;
        for(auto node: array){
            if(node == nullptr) continue;

            _mn = _insertNewChildAtRootList(_mn, node);
            if(_mn->key > node->key){
                _mn = node;
            }
        }
        
    }

    void _cut(Node* parent, Node* node){
        parent->child = _removeNodeFromRootList(node);
        if(parent->child)
            parent->child->parent = parent;
        parent->degree--;

        _insertTORootListAfterNode(_mn, node);
        node->parent = nullptr;
        node->mark = false;
    }

    void _cascadingCut(Node* parent){
        auto grandP = parent->parent;
        if(grandP != nullptr){
            if(parent->mark == false) parent->mark = true;
            else {
                _cut(grandP, parent);
                _cascadingCut(grandP);
            }
        }
    }

    void _printHelper(ostream& os, Node *n, int tab){
        if(n == nullptr) return ;

        for(int i = 0; i < tab; i++) cout << "\t";
        os << *n << endl;
        _printHelper(os, n->child, tab+1);
        
        for(auto cur = n->right; cur != n; cur = cur->right){
            for(int i = 0; i < tab; i++) cout << "\t";
            os << *cur << endl;
            _printHelper(os, cur->child, tab+1);
        }
    }

public:
    FibonacciHeap(/* args */);
    ~FibonacciHeap();

    void insert(Node *toInsert){
        toInsert->degree = 0;
        toInsert->mark = false;
        toInsert->parent = nullptr;
        toInsert->child = nullptr;

        _mn = _insertNewChildAtRootList(_mn, toInsert);
        if(_mn->key > toInsert->key){
            _mn = toInsert;
        }
        
        _length++;
    }

    void unionHeap(FibonacciHeap &heap){

    }

    void pop(){
        if(_mn != nullptr){
            _insertChildOfNodeToRootList(_mn);
            _removeNodeFromRootList(_mn);
            
            if(_mn->left == _mn){
                _mn = nullptr;
            }else{
                _mn = _mn->right;
                _consolidate();
            }

            _length--;
        }
    }

    Node* top(){
        return _mn;
    }

    int length(){
        return _length;
    }

    void decreaseKey(Node* node, int k){
        if(node->key <= k) {
            cerr << "node->key <= k" << endl;;
            return ;
        }

        node->key = k;
        auto parent = node->parent;
        if(parent != nullptr && node->key < parent->key){
            _cut(parent, node);
            _cascadingCut(parent);
        }

        if(node->key < _mn->key){
            _mn = node;
        }
    }

    

    friend ostream& operator<<(ostream& os, FibonacciHeap &f){
        os << "====================================================" << endl;

        if(f._mn == nullptr) os << "null" << endl;
        cout << "length : " << f._length << endl;

        f._printHelper(os, f._mn, 0);

        os << "====================================================" << endl;
        return os;
    }
};

FibonacciHeap::FibonacciHeap(/* args */)
{
    _mn = nullptr;
    _length = 0;
}

FibonacciHeap::~FibonacciHeap()
{
}

typedef vector<vector<pair<int, int>>> WeightedGraph;
typedef tuple<int, int, int> WeightedEdge;

int djaskatraWithBinaryHeap(int src, int dest, const WeightedGraph &graph, int &pathLength){
    int nodes = graph.size();
    vector<int> distance(nodes, INT_MAX), path(nodes, 0);
    distance[src] = 0;
    path[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,src});

    while(!pq.empty()){
        auto t = pq.top(); pq.pop();
        int cur = t.second;

        for(auto &i: graph[cur]){
            //pair represented diffrantly in graph and priority_queue
            int next = i.first, edgeWeight =  i.second; 
            
            if(distance[cur] + edgeWeight < distance[next]){
                distance[next] = distance[cur] + edgeWeight;
                path[next] = path[cur]+1;
                pq.push({distance[next], next});
            }
        }
    }

    pathLength = path[dest];
    return distance[dest];
}


int djaskatraWithFibonacciHeap(int src, int dest, const WeightedGraph &graph, int &pathLength){
    // initialization
    int n = graph.size();

    vector<Node *> nodes(n);
    vector<bool> visited(n, false);
    vector<int> path(n, 0);
    FibonacciHeap fh;
    for(int i = 0; i < n; i++){
        nodes[i] = new Node(INT_MAX, i);
        fh.insert(nodes[i]);
    }

    fh.decreaseKey(nodes[src], 0);
    visited[src] = true;
    path[src] = 0;

    //cout << fh << endl;

    while(fh.length()){
        auto mn = fh.top(); fh.pop();

        if(mn->data == dest){ 
            pathLength = path[dest];        
            int ans = nodes[dest]->key;

            for(int i = 0; i < n; i++){
                delete nodes[i];
            }
            return ans;
        }

        visited[mn->data] = true;
        for(auto i: graph[mn->data]){
            auto node = nodes[i.first];
            int weight = i.second;

            if(!visited[node->data] && mn->key + weight < node->key){
                fh.decreaseKey(node, mn->key + weight);
                path[node->data] = path[mn->data] + 1;
            }
        }

        //cout << fh << endl;
    }

    pathLength = path[dest];
    int ans = nodes[dest]->key;

    for(int i = 0; i < n; i++){
        delete nodes[i];
    }

    return ans;
}

void tester(){
    FibonacciHeap fh;
    string inp1;
    int inp2;

    map<int, Node *> mp;
    for(int i = 1; i <= 10; i++){
        mp[i] =  new Node(2, i);
        fh.insert(mp[i]);
    }
    cout << fh << endl;

    while(cin >> inp1 >> inp2 && inp1 != "q"){
        if(inp1 == "a"){
            mp[inp2] =  new Node(inp2);
            fh.insert(mp[inp2]);
        }

        if(inp1 == "p"){
            fh.pop();
        }

        if(inp1 == "d"){
            int n; cin >> n;
            fh.decreaseKey(mp[inp2], n);
        }

        cout << fh << endl;
        for(int i = 1; i <= 10; i++){
            cout << i << " " << *mp[i] << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    //tester();
    ifstream file1("heap1.txt");
    ifstream file2("heap2.txt");

    if(!file1.is_open() || !file2.is_open()){
        cerr << "File1 or File2 cannot be opened" << endl;
        return 1;
    }

    int n, m;
    file1 >> n >> m;

    WeightedGraph graph(n);
    for(int i = 0; i < m; i++){
        int a, b, w;
        file1 >> a >> b >> w;

        graph[a].push_back({b,w});
        graph[b].push_back({a,w});
    }

    int t;
    file2 >> t;

    while (t--){
        int u,v;
        file2 >> u >> v;

        int ansB, ansF, pathLengthB, pathLengthF;

        auto startF = high_resolution_clock::now();
        ansF = djaskatraWithFibonacciHeap(u, v, graph, pathLengthF);
        auto endF = high_resolution_clock::now();
        auto durF = duration_cast<microseconds>(endF-startF);

        auto startB = high_resolution_clock::now();
        ansB = djaskatraWithBinaryHeap(u, v, graph, pathLengthB);
        auto endB = high_resolution_clock::now();
        auto durB = duration_cast<microseconds>(endB-startB);

        cout << pathLengthF << " " << ansF << " " << durB.count() 
             << " " << durF.count() << endl;
    }
}