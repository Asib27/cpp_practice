#ifndef __MY_STACK__
#define __MY_STACK__

template<typename E>
class MyStack
{
private:
    /* data */
    MyStack(MyStack &m){}
    MyStack& operator=(MyStack &m){}

public:
    MyStack(/* args */){

    }

    virtual void clear() = 0;
    virtual void push(E item) = 0;
    virtual E pop() = 0;
    virtual int length() = 0; 
    virtual const E& topValue() = 0;
    virtual void setDirection(int direction) = 0;

    virtual ~MyStack(){}
};

#endif