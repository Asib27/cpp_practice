#include<iostream>

using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node<T> *left;
    Node<T> *right;

    Node(){
        left = nullptr;
        right = nullptr;
    }

    Node(T d){
        data = d;
        left = nullptr;
        right = nullptr;
    }

    Node(T d, Node<T> *l, Node<T> *r){
        data = d;
        left = l;
        right = r;
    }

    bool isLeaf(){
        return left == nullptr && right == nullptr;
    }
};

template <typename E>
class BinarySearchTree{
    Node<E> *root;

    Node<E>* insert_helper(Node<E> *root, E item){
        if(root == nullptr){
            root = new Node<E>(item);
        }
        else{
            if(item < root->data)
                root->left = insert_helper(root->left, item);
            else{
                root->right = insert_helper(root->right, item);
            }
        }

        return root;
    }

    bool find_helper(Node<E> *rt, E item){
        if(!rt){
            return false;
        }
        else if(rt->data == item){
            return true;
        }
        else{
            if(item < rt->data)
                return find_helper(rt->left, item);
            else{
                return find_helper(rt->right, item);
            }
        }
    }

    Node<E>* delete_helper(Node<E> *root, E item){
        if(root == nullptr)
            return nullptr;
        
        if(root->data == item){
            return delete_node(root);
        }
        else if(root->data < item){
            root->right = delete_helper(root->right, item);
        }
        else{
            root->left = delete_helper(root->left, item);
        }

        return root;
    }

    Node<E>* delete_node(Node<E> *root){
        if(root == nullptr)
            return nullptr;
        else if(root->isLeaf()){
            delete root;
            return nullptr;
        }

        else if(root->left != nullptr && root->right != nullptr){
            return delete_two_node2(root);
        }
        else if(root->left != nullptr){
            Node<E> *t = root->left;
            delete root;
            return t;
        }
        else{
            Node<E> *t = root->right;
            delete root;
            return t;
        }

        return root;
    }

    Node<E>* delete_two_node(Node<E> *root){
        Node<E> *minNode = find_min(root->right);

        E data = minNode->data;
        root->right = delete_helper(root->right, minNode->data);

        Node<E> *newNode = new Node<E>(data, root->left, root->right);
        delete root;
        return newNode;
    }

    Node<E>* find_min(Node<E> *root){
        if(root == nullptr)
            return root;
        
        while(root->left)
            root = root->left;
        return root;
    }

    Node<E>* delete_two_node2(Node<E> *root){
        Node<E> *minNode = find_max(root->left);

        E data = minNode->data;
        root->left = delete_helper(root->left, minNode->data);

        Node<E> *newNode = new Node<E>(data, root->left, root->right);
        delete root;
        return newNode;
    }

    Node<E>* find_max(Node<E> *root){
        if(root == nullptr)
            return root;
        
        while(root->right)
            root = root->right;
        return root;
    }

    void print_helper(Node<E> *root){
        if(root == nullptr)
            return ;

        using std::cout;
        cout << root->data;

        if(root->isLeaf())
            return ;
        
        cout << "(" ;
        print_helper(root->left);
        cout << ")";

        cout << "(" ;
        print_helper(root->right);
        cout << ")";
    }

    void preorder_helper(Node<E> *root){
        if(root){
            std::cout << root->data << " ";
            preorder_helper(root->left);
            preorder_helper(root->right);
        }
    }

    void inorder_helper(Node<E> *root){
        if(root){
            inorder_helper(root->left);
            std::cout << root->data << " ";
            inorder_helper(root->right);
        }
    }

    void postorder_helper(Node<E> *root){
        if(root){
            postorder_helper(root->left);
            postorder_helper(root->right);
            std::cout << root->data << " ";
        }
    }

public:
    BinarySearchTree(){
        root = nullptr;
    }

    BinarySearchTree(E item){
        root = new Node<E>(item);
    }

    void insert(E item){
        root = insert_helper(root, item);
    }

    bool find(E item){
        return find_helper(root, item);
    }

    void remove(E item){
        root = delete_helper(root, item);
    }

    void print(){
        print_helper(root);
    }

    void preorder(){
        preorder_helper(root);
    }

    void inorder(){
        inorder_helper(root);
    }

    void postorder(){
        postorder_helper(root);
    }
};
