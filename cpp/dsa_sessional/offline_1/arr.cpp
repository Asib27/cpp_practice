#include "list.h"

template<class E>
class ArrayList : public List<E>
{
private:
    /* data */
    E* array; 
    int capacity;
    int cur;
    int array_length;

    void ensure_capacity(int required){
        if(capacity < required){
            E *new_array = new E[capacity * 2];
            capacity *= 2;
            copy(this->array, 0, array_length, new_array);

            delete this->array;
            this->array = new_array;
        }
    }

    void copy(E* array, int start, int last, E* dest){
        int j = 0;
        for(int i = start; i < last; i++){
            dest[j] = array[i];
            j++;
        }
    }

public:
    ArrayList(int cap=10) : capacity(cap) {
        array = new E[capacity];
        array_length = 0;
        cur = 0;
    }
    ~ArrayList(){
        delete[] array;
    }

    ArrayList(ArrayList<E> &list){
        list.array_length = this->array_length;
        list.cur = this->cur;
        list.capacity = this->capacity;
        list.array = new E[this->capacity];
        copy(this->array, 0, array_length, list.array);
    }


    /*clear all the element*/
    virtual void clear(){
        array_length = 0;
        cur = 0;
    }
    /*insert element to current position*/
    virtual void insert(E item){
        ensure_capacity(array_length + 1);

        for(int i = array_length; i > cur; i--){
            array[i] = array[i-1];
        }

        array[cur] = item;
        array_length++;
    }
    /*append element to end of list*/
    virtual void append(E item){
        array[array_length++] = item;
    }
    /*removes element from current position*/
    virtual E remove(){
        E toRemove = getValue();
        for(int i=cur; i < array_length -1; i++){
            array[i] = array[i+1];
        }

        --array_length;
        return toRemove;
    }
    
    /*returns the length of list*/
    virtual int length(){
        return array_length;
    }
    
    /*searches list and return position if found else returns -1*/
    virtual int search(E item){
        for(int i = 0; i < array_length; i++){
            if(array[i] == item)
                return i;
        }

        return -1;
    }

    /*makes the first element as current position*/
    virtual void moveToStart(){
        cur = 0;
    }
    /*makes the last element as current position*/
    virtual void moveToEnd(){
        cur = array_length;
    }
    /*makes the previous element as current position*/
    virtual void prev(){
        if(cur != 0)
            --cur;
    }
    /*makes the next element as current position*/
    virtual void next(){
        if(cur != array_length)
            ++cur;
    }
    /*returns current position*/
    virtual int curPos(){
        return cur;
    }
    /*moves to given position*/
    virtual void moveToPos(int position){
        cur = position;
    }
    /*returns value in current positopn*/
    virtual int getValue(){
        return array[cur];
    }
};

