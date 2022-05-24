#include "MyStack.cpp"

template<typename E>
class ArrayStack : public MyStack<E>
{
private:
    /* data */
    E* array;
    int top;
    int capacity;

    bool isDouble = false;

    enum Direction{
        TOP_TO_BOTTOM = -1, BOTTOM_TO_TOP = 1
    };
    Direction dir;

    template<typename T>
    void copyArray(T arr[], int start, int end, T dest[], int dest_start=0){
        for(int i = start; i != end; i++){
            dest[i-start + dest_start] = arr[i];
        }
    }

    void ensureCapacity(int required){
        if(capacity < required){
            E *new_array = new E[capacity * 2];

            if(dir == TOP_TO_BOTTOM){
                copyArray(array, 0, capacity, new_array, capacity);
                top += capacity;
            }
            else{
                copyArray(array, 0, capacity, new_array);
            }

            capacity *= 2;
            delete[] array;
            std::cout << "#1" << std::endl;
            array = new_array;
        }
    }
public:
    ArrayStack(int size = 10){
        array = new E[size];
        top = 0;
        dir = BOTTOM_TO_TOP;
        capacity = size;

        isDouble = false;
    }

    ArrayStack(E *arr, int size, int direction){
        array = arr;
        capacity = size;
        top = 0;
        dir = BOTTOM_TO_TOP;
        setDirection(direction);
        isDouble = true;
    }

    virtual void clear(){
        if(dir == TOP_TO_BOTTOM){
            top = capacity-1;
        }
        else if(dir == BOTTOM_TO_TOP){
            top = 0;
        }
        else{
            std::cerr << "Some Enum const is not considered " << dir << std::endl;
        }
    }

    void push(E item){
        ensureCapacity(length() + 1);
        if(dir == TOP_TO_BOTTOM){
            array[top--] =item;
        }
        else if(dir == BOTTOM_TO_TOP){
            array[top++] =item;
        }
        else{
            std::cerr << "Some Enum const is not considered " << dir << std::endl;
        }
    }

    E pop(){
        if(this->length() == 0){
            throw "stack underflow";
        }

        if(dir == TOP_TO_BOTTOM){
            return array[++top];
        }
        else if(dir == BOTTOM_TO_TOP){
            return array[--top];
        }
        else{
            std::cerr << "Some Enum const is not considered " << dir << std::endl;
            throw std::runtime_error("Some Enum const is not considered ");
        }
    }

    int length(){
        if(dir == TOP_TO_BOTTOM){
            return capacity - top -1;
        }
        else if(dir == BOTTOM_TO_TOP){
            return top;
        }
        else{
            std::cerr << "Some Enum const is not considered " << dir << std::endl;
            return -1;
        }
    }

    const E& topValue(){
        return array[top - dir];
    }

    void setDirection(int direction){
        if(length() != 0){
            throw std::runtime_error("Cannot change direction in non empty stack");
        }
        if(direction == 1){
            dir = BOTTOM_TO_TOP;
            top = 0;
        }
        else if(direction == -1){
            dir = TOP_TO_BOTTOM;
            top = capacity -1;
        }
        else{
            throw std::runtime_error("Invalid value of parameter direction");
        }
    }

    ~ArrayStack(){
        if(!isDouble)
            delete[] array;
    }

    friend std::ostream& operator<< (std::ostream &os, ArrayStack<E> &ds){
        if(ds.dir == BOTTOM_TO_TOP){
            for(int i = 0; i < ds.top; i++){
                os << ds.array[i] << " ";
            }
            os << "Stack top ";
        }

        else if(ds.dir == TOP_TO_BOTTOM){
            for(int i = ds.capacity-1; i > ds.top; i--){
                os << ds.array[i] << " ";
            }
            os << "Stack top ";
        }

        else{
            std::cerr << "Some Enum const is not considered " << ds.dir << std::endl;            
        }

        // os << "\n";
        // for(int i = 0; i < ds.capacity; i++){
        //     os << ds.array[i] << " ";
        // }
        

        return os;
    }
};
