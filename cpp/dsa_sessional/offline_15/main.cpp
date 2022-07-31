#include <iostream>
#include <fstream>
using namespace std;

enum Color {red=1, black=0};

struct Node
{
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(int key): key(key) {}
    Node(int key, Color c): key(key) , color(c){}
    Node() = default;

    static Node* getModifiableNIL(){
        return new Node(0, Color::black);
    }

    friend ostream& operator<<(ostream &os, const Node &n){
        os << "{ "
           << "key : " << n.key << " ; "
           << "color : " << (n.color==red? "red": "black") << " ; "
           << "left : " << (n.left==nullptr? 0: n.left->key) << " ; "
           << "right : " << (n.right==nullptr? 0: n.right->key) << " ; "
           << "parent : " << (n.parent==nullptr? 0: n.parent->key) << " ; "
           << " }";

        return os;
    }
};

class RBTree
{
private:
    Node* NIL;
    Node* _root;

    void _left_rotate(Node * x){
        /* 
        *      x            left           y
        *    a    y         ==>          x   c
        *       b   c       rotate     a   b 
        */

        auto y = x->right;

        x->right = y->left;
        if(y->left != NIL){
            y->left->parent = x;
        }

        y->parent = x->parent;

        if(x->parent == NIL || x->parent == nullptr) _root = y;
        else if(x->parent->left == x) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void _right_rotate(Node * y){
        /* 
        *      x            right          y
        *    a    y         <==          x   c
        *       b   c       rotate     a   b 
        */

        auto x = y->left;

        y->left = x->right;
        if(x->right != NIL){
            x->right->parent = y;
        }

        x->parent = y->parent;

        if(y->parent == NIL || y->parent == nullptr) _root = y;
        else if(y->parent->left == y) y->parent->left = x;
        else y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

    void _insert_fixup(Node * z){
        while (z->parent->color == Color::red)
        {
            if(z->parent == z->parent->parent->left){
                auto y = z->parent->parent->right;
                if(y->color == Color::red){
                    z->parent->color = y->color = Color::black;
                    z->parent->parent->color = Color::red;
                    z = z->parent->parent;
                }
                else{ 
                    if (z == z->parent->right){
                        z = z->parent;
                        _left_rotate(z);
                    }   
                    z->parent->color = Color::black;
                    z->parent->parent->color = Color::red;
                    _right_rotate(z->parent->parent);
                }
            }
            else{
                auto y = z->parent->parent->left;
                if(y->color == Color::red){
                    z->parent->color = y->color = Color::black;
                    z->parent->parent->color = Color::red;
                    z = z->parent->parent;
                }
                else{
                    if (z == z->parent->left){
                        z = z->parent;
                        _right_rotate(z);
                    }   

                    z->parent->color = Color::black;
                    z->parent->parent->color = Color::red;
                    _left_rotate(z->parent->parent);
                }
            }
        }
        
        _root->color = Color::black;
    }

    void _free_helper(Node* n){
        if(n == nullptr || n == NIL) return ;
        _free_helper(n->left);
        _free_helper(n->right);
        delete n;
    }

    void _transplant(Node* u, Node* v){
        if(u->parent == NIL || u->parent == nullptr) _root = v;
        else if( u->parent->left == u) u->parent->left = v;
        else u->parent->right = v;

        v->parent = u->parent;
    }

    Node * _minimum(Node* z) const{
        if(z == NIL) return z;
        while(z->left != NIL)
            z = z->left;
        return z;
    }

    void _delete_fixup(Node* x){
        while (x != _root && x->color == Color::black){
            if(x == x->parent->left){
                auto w = x->parent->right;

                if(w->color == Color::red){
                    w->color = Color::black;
                    x->parent->color = Color::red;
                    _left_rotate(x->parent);
                    w = x->parent->right;
                }

                if(w->left->color == Color::black && 
                    w->right->color == Color::black
                ){
                    w->color = Color::red;
                    x = x->parent;
                }
                else{
                    if(w->right->color == Color::black){
                        w->left->color = Color::black;
                        w->color = Color::red;
                        _right_rotate(w);
                        w = x->parent->right;
                    }
                    
                    w->color = x->parent->color;
                    x->parent->color = Color::black;
                    w->right->color = Color::black;
                    _left_rotate(x->parent);
                    x = _root;
                } 
            }
            else{
                auto w = x->parent->left;

                if(w->color == Color::red){
                    w->color = Color::black;
                    x->parent->color = Color::red;
                    _right_rotate(x->parent);
                    w = x->parent->left;
                }

                if(w->right->color == Color::black && 
                    w->left->color == Color::black
                ){
                    w->color = Color::red;
                    x = x->parent;
                }
                else{
                    if(w->left->color == Color::black){
                        w->right->color = Color::black;
                        w->color = Color::red;
                        _left_rotate(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = Color::black;
                    w->left->color = Color::black;
                    _right_rotate(x->parent);
                    x = _root;
                } 
                
            }
        }

        x->color = Color::black;
    }

    Node* _search_helper(int key, Node* rt) const {
        if(rt == nullptr || rt == NIL) return nullptr;

        if(rt->key == key) return rt;
        else if(rt->key > key) return _search_helper(key, rt->left);
        else return _search_helper(key, rt->right);
    }

    int _countLessThanHelper(Node* rt, int key) const{
        if(rt == nullptr || rt == NIL) return 0;

        int cnt = _countLessThanHelper(rt->left, key);
        if(rt->key < key) cnt++;
        cnt += _countLessThanHelper(rt->right, key);

        return cnt;
    }
    
public:
    RBTree(/* args */);
    ~RBTree();

    void insert(Node * z){
        Node* y = nullptr;
        auto x = _root;

        z->parent = nullptr;

        while (x != NIL)
        {
            y = x;
            if(z->key < x->key)
                x = x->left;
            else x = x->right;    
        }
        z->parent = y;
        if(y == NIL || y == nullptr) _root = z;
        else if(z->key < y->key) y->left = z;
        else y->right = z;

        z->left = z->right = NIL;
        z->color = Color::red;

        if(z->parent == NIL || z->parent == nullptr) {
            z->color = Color::black;
            return ;
        }
        if(z->parent->parent == NIL){
            return ;
        }

        _insert_fixup(z);

    }

    void erase(Node * z){
        auto y = z;
        auto x = NIL;
        Color origColor = y->color;

        if(z->left == NIL){
            x = z->right;
            _transplant(z, z->right);
        }
        else if(z->right == NIL){
            x = z->left;
            _transplant(z, z->left);
        }
        else{
            y = _minimum(z->right);
            origColor = y->color;
            x = y->right;

            if(y->parent == z) x->parent = y;
            else{
                _transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            _transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        // delete z;
        if(origColor == Color::black){
            _delete_fixup(x);
        }
    }

    void rbTransplant(Node* u, Node* v){
        _transplant(u, v);
    }


    Node* search(int val) const{
        return _search_helper(val, _root);
    }

    int count(Node* rt){
        if(rt == nullptr || rt == NIL) return 0;
        return 1 + count(rt->left) + count(rt->right);
    }

    int countLessthan(int key) const{
        return _countLessThanHelper(_root, key);
    }
};

RBTree::RBTree(/* args */)
{
    NIL = new Node(0, Color::black);
    NIL->left = NIL->right = nullptr;
    _root = NIL;
}

RBTree::~RBTree()
{
    _free_helper(_root);
    delete NIL;
}

class RBtreeWrapper
{
private:
    RBTree tree;
public:
    int length;
    RBtreeWrapper(/* args */);
    ~RBtreeWrapper();

    int insert(int key){
        length++;
        auto t = tree.search(key);
        if(t != nullptr) return 0;

        Node* n = new Node(key);
        tree.insert(n);
        return 1;
    }

    int erase(int key){
        length--;
        auto t = tree.search(key);

        if(t == nullptr) return 0;

        tree.erase(t);
        delete t;
        return 1;
    }

    bool search(int key){
        return tree.search(key) != nullptr;
    }

    int countLessthan(int x){
        return tree.countLessthan(x);
    }
};

RBtreeWrapper::RBtreeWrapper(/* args */)
{
    length = 0;
}

RBtreeWrapper::~RBtreeWrapper()
{
}


int main(int argc, char const *argv[])
{
    ifstream fin("input.txt");

    int n;
    fin >> n;
    cout << n << endl;

    RBtreeWrapper tree;

    while (n--)
    {
        int e, x, res;
        fin >> e >> x;

        switch(e){
            case 0: //terminate 
                res = tree.erase(x);
                break;
            case 1: //initiate
                res = tree.insert(x);
                break;
            case 2: //search
                res = tree.search(x);
                break;
            case 3: // no of programs
                res = tree.countLessthan(x);
                break;
            default:
                cerr << "wrong input of e" << endl;
                break;
        }

        cout << e << " " << x << " " << res << endl;
    }

}
