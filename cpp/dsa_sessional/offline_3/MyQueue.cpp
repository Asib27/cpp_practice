#ifndef _MY_QUEUE_H_
#define _MY_QUEUE_H_

template<typename E>
class MyQueue
{
private:
    /* data */
    MyQueue(MyQueue &){};
    MyQueue& operator=(MyQueue &){};
public:
    MyQueue(/* args */){}

    virtual void clear() = 0;
    virtual void enqueue(E item) = 0;
    virtual E dequeue() = 0;
    virtual int length() = 0;
    virtual E frontValue() = 0;
    virtual E rearValue() = 0;
    virtual E leaveQueue() = 0;

    virtual ~MyQueue(){};
};


#endif