#ifndef _LIST_H
#define _LIST_H

template<class E>
class List
{
private:
    /* data */
public:
    List(/* args */){

    }

    /*clear all the element*/
    virtual void clear() = 0;
    /*insert element to current position*/
    virtual void insert(E item) = 0;
    /*append element to end of list*/
    virtual void append(E item) = 0;
    /*removes element from current position*/
    virtual E remove() = 0;
    
    /*returns the length of list*/
    virtual int length() = 0;
    
    /*searches list and return position if found else returns -1*/
    virtual int search(E item) = 0;

    /*makes the first element as current position*/
    virtual void moveToStart() = 0;
    /*makes the last element as current position*/
    virtual void moveToEnd() = 0;
    /*makes the previous element as current position*/
    virtual void prev() = 0;
    /*makes the next element as current position*/
    virtual void next() = 0;
    /*returns current position*/
    virtual int curPos() = 0;
    /*moves to given position*/
    virtual void moveToPos(int position) = 0;
    /*returns value in current positopn*/
    virtual int getValue() = 0;

    virtual ~List(){
        
    }
};

#endif