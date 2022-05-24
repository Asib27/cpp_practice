#include "MyQueue.cpp"

template <typename E>
class ArrayQueue : public MyQueue<E>
{
private:
    /* data */
    E* array;
    int front;
    int rear;
    int capacity;

    void copy_array(E dest[]){
        int temp_rear = 0;
        while(this->length() != 0){
            temp_rear++;
            dest[temp_rear] = this->dequeue();
        }

        rear = temp_rear;
        front = 1;
    }

    void ensureCapacity(int req){
        if(capacity - 1 < req){
            E *new_array = new E[2 * capacity - 1];
            copy_array(new_array);

            delete[] array;
            array = new_array;
            capacity *= 2;
        }
    }
public:
    ArrayQueue(int size=10){
        capacity = size + 1;

        rear = 0;
        front = 1;

        array = new E[capacity];
    };

    ArrayQueue(E* arr, int size){
        capacity = size;

        rear = 0;
        front = 1;

        array = arr;//new E[capacity];
    };

    virtual void clear(){
        rear = 0;
        front = 1;
    }

    virtual void enqueue(E item){
        ensureCapacity(this->length() + 1);
        rear = (rear+1) % capacity;
        array[rear] = item;
    }

    virtual E dequeue(){
        if(this->length() == 0){
            throw std::runtime_error("Dequeue on empty queue");
        }

        E it = array[front];
        front = (front+1) % capacity;

        return it;
    }

    virtual int length() {
        return ( rear + capacity - front + 1) % capacity; 
    }
    virtual E frontValue(){
        return array[front];
    }
    virtual E rearValue(){
        return array[rear];
    }
    virtual E leaveQueue() {
        if(this->length() == 0){
            throw std::runtime_error("Leave queue on empty queue");
        }

        E it = array[rear];
        rear = (rear - 1 + capacity) % capacity;

        return it;
    }

    ~ArrayQueue(){
        delete[] array;
    }
};