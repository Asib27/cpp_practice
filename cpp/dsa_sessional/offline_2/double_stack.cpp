#include<iostream>

class DoubleStack{
    int* array;
    int capacity;
    int top_up;
    int top_down;

    template<typename T>
    void copyArray(T arr[], int start, int end, T dest[], int dest_start=0){
        for(int i = start; i != end; i++){
            dest[i-start + dest_start] = arr[i];
        }
    }

    ensureCpacity(int required){
        if(capacity < required){
            int *new_array = new int[required];
            copyArray(array, 0, capacity, new_array);

            delete[] array;
            array = new_array;
        }
    }

    void init(){
        top_up = 0;
        top_down = capacity - 1;
    }

public:
    DoubleStack(int cap=20) 
        : capacity(cap)
    {
        array = new int[cap];
        init();
    }

    DoubleStack(DoubleStack &ds)
        : capacity(ds.capacity)
    {
        array = new int[capacity];
        copyArray(ds.array, 0, ds.capacity, this->array);
        init();
    }

    DoubleStack& operator=(DoubleStack &ds){
        this->capacity = ds.capacity;
        this->array = new int[ds.capacity];
        copyArray(ds.array, 0, ds.capacity, this->array);
        init();

        return *this;
    }

    void push(int dir, int toPush){
        if(top_up > top_down)
            throw "Stack Overflow";

        if(dir == 1){
            array[top_up++] = toPush;
        }
        else if(dir == -1){
            array[top_down--] = toPush;
        }
        else{
            throw "Invalid Operand value: dir ";
        }
    }

    int pop(int dir){
        if(dir == 1){
            if(top_up == 0) throw "Stack Underflow";
            return array[--top_up];
        }
        else if(dir == -1){
            if(top_down == capacity - 1) throw "Stack Underflow";
            return array[++top_down];
        }
        else{
            throw "Invalid Operand value: dir ";
        }
    }

    int top(int dir){
        if(dir == 1){
            return array[top_up-1];
        }
        else if(dir == -1){
            return array[top_down + 1];
        }
        else{
            throw "Invalid Operand value: dir ";
        }
    }

    int size(int dir){
        if(dir == 1) return top_up;
        else if(dir == -1) return capacity - top_down - 1;
        else{
            throw "Invalid Operand value: dir ";
        }
    }

    friend std::ostream& operator<< (std::ostream &os, DoubleStack& ds){
        for(int i = 0; i < ds.top_up; i++){
            os << ds.array[i] << " ";
        }
        os << "Stack top ";

        for(int i = ds.capacity-1; i > ds.top_down; i--){
            os << ds.array[i] << " ";
        }
        os << "Stack top ";

        return os;
    }

    virtual ~DoubleStack(){
        delete[] array;
    }
};

int main(){
    DoubleStack ds;
    ds.push(1, 10);
    ds.push(1, 20);
    ds.push(-1, 100);
    ds.push(-1, 90);

    std::cout << ds << ds.size(1) << ds.size(-1) << std::endl;

    ds.pop(1);
    ds.pop(-1);

    std::cout << ds << std::endl;
}