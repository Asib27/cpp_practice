#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Node
{
    int key;
    int degree;
    bool mark;
    Node* left;
    Node* right;
    Node* parent;
    Node* child;

    Node(int key): key(key){};

    friend ostream& operator<<(ostream& os, const Node &n){
        os << "{ " 
           << "key: " << n.key << " ; "
           << "degree: " << n.degree << "; "
           << "mark: " << n.degree << "; "
           << "left: " << (n.left == nullptr? -1: n.left->key) << "; "
           << "right: " << (n.right == nullptr? -1: n.right->key) << "; "
           << "parent: " << (n.parent == nullptr? -1: n.parent->key) << "; "
           << "child: " << (n.child == nullptr? -1: n.child->key) << "; "
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
     * ok
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
     * ok
     * @param insertAt 
     * @param toInsert 
     * return Node* insertAt node is changed in the function call
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

    int _findMaxDegree(){
        return 0;
    }

    /**
     * @brief consolidates the fibonacchi heap
     * 
     */
    void _consolidate(){
        int mxDegree = 0;
        _mn->left->right = nullptr;
        for(auto cur = _mn; cur != nullptr ;cur = cur->right){
            mxDegree = max(mxDegree, cur->degree);
        }

        vector<Node *> array(mxDegree+2, nullptr);
        for(auto cur = _mn; cur != nullptr ;cur = cur->right){
            auto z = cur;
            int d = cur->degree;
            while(array[d] != nullptr){
                auto y = array[d];

                if(cur->key < y->key) z = _fibHeapLink(cur, y);
                else z = _fibHeapLink(y, cur);

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

    void decreaseKey(Node* node, int k){
        if(node->key > k) {
            cerr << "node->key > k" << endl;;
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

int main(int argc, char const *argv[])
{
    FibonacciHeap fh;
    string inp1;
    int inp2;

    map<int, Node *> mp;
    for(int i = 1; i <= 3; i++){
        mp[i] =  new Node(i);
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

        if(inp1 == "r"){
            if(mp.count(inp2)){
                auto t = _removeNodeFromRootList(mp[inp2]);
                cout << *t << endl;
                cout << *mp[inp2] << endl;
            }
        }

        cout << fh << endl;
    }
}