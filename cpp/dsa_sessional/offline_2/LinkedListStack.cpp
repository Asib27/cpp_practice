#include "MyStack.cpp"

template<typename E>
class Node{
public:
    E value;
    Node* next;
    Node(E val, Node* next=nullptr){
        this->value = val;
        this->next = next;
    }

    Node(){}
};


template<typename E>
class LinkedListStack: public MyStack<E>
{
private:
    /* data */
    Node<E>* top;
    int len;
public:
    LinkedListStack(/* args */)
    {
        top = nullptr;
        len = 0;
    }

    void clear(){
        while(this->length() != 0){
            this->pop();
        }
    }

    void push(E item){
        
        top =  new Node<E>(item, top);
        ++len;
    }

    E pop(){
        if(top == nullptr){
            throw "stack underflow";
        }

        Node<E> *cur =  top;
        top = top->next;

        E value =  cur->value;

        --len;
        delete cur;
        return value;
    }

    const E& topValue(){
        return top->value;
    }

    void setDirection(int direction){
    }

    int length(){
        return len;
    }

    ~LinkedListStack(){
        this->clear();
    }

    friend std::ostream& operator<< (std::ostream &os, LinkedListStack<E> &ds){
        Node<E> *cur = ds.top;

        os << "Top ";
        while(cur != nullptr){
            os << cur->value << " ";
            cur = cur->next;
        }

        return os;
    }
};
