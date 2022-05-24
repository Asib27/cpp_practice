#include "MyQueue.cpp"

template <typename E>
class Node{
    public:

    E data;
    Node<E> *next;
    Node<E> *prev;

    Node(){
        next = nullptr;
        prev = nullptr;
    }

    Node(E d){
        data = d;
        next = nullptr;
        prev = nullptr;
    }

    Node(E d, Node<E> *p, Node<E> *n){
        data = d;
        next = n;
        prev = p;
    }
};

template<typename E>
class LinkedListQueue : public MyQueue<E>
{
private:
    Node<E> *head;
    Node<E> *tail;
    int len;
public:
    LinkedListQueue(){
        head = new Node<E>();
        tail = new Node<E>();
        len = 0;

        head->next = tail;
        tail->prev = head;
    }

    virtual void clear(){
        while(this->length() != 0){
            this->dequeue();
        }
    }

    virtual void enqueue(E item){
        /*
        before: head .... other tail
        after : head other new tail
        */

        Node<E> *new_item = new Node<E>(item, tail->prev, tail);
        tail->prev->next = new_item;
        tail->prev = new_item;

        len++;

        //std::cout << *this;
    }


    virtual E dequeue(){
        if(length() == 0){
            throw std::runtime_error("Dequeue on empty queue");
        }
        /*
        before: head toDelete other ......... tail
        after : head other tail
        */
       Node<E> *toDelete = head->next;
       head->next = toDelete->next;
       toDelete->next->prev = head;

       E val = toDelete->data;
       delete toDelete;

       len--;

       return val;
    }


    virtual int length(){
        return len;
    }

    virtual E frontValue(){
        if(length() == 0){
            throw std::runtime_error("No Front value exists on empty queue");
        }
        return head->next->data;
    }

    virtual E rearValue() {
        if(length() == 0){
            throw std::runtime_error("No rear value exists on empty queue");
        }
        return tail->prev->data;
    }

    virtual E leaveQueue(){
        if(length() == 0){
            throw std::runtime_error("No rear value exists on empty queue");
        }

        /*
        before: head ....... other toDelete  tail
        after : head other tail
        */

       Node<E> *toDelete = tail->prev;
       toDelete->prev->next = tail;
       tail->prev = toDelete->prev;

       E val = toDelete->data;
       delete toDelete;

       len--;

       return val;
    }

    ~LinkedListQueue(){
        this->clear();
        delete head;
        delete tail;
    };

    
    // friend std::ostream& operator<<(std::ostream &os, LinkedListQueue<E> &l){
    //     os << "<";

    //     for(Node<E> *cur = l.head->next; cur != l.tail; cur = cur->next){
    //         os << cur->data << " ";
    //     }

    //     os << ">";


    //     return os;
    // }
};