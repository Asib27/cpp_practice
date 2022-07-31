#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

class Heap{
private:
    int *arr;
    int capacity, sz;

    int root(){ return 1;}
    int parent(int i) {return i >> 1;}
    int left(int i) {return i << 1;}
    int right(int i) {return i << 1 | 1;}
    bool isLeaf(int i) {return left(i) > sz;}

    void down_heapify(int i){
        while(!isLeaf(i)){
            int mn = i;
            if(arr[mn] > arr[left(i)]) mn = left(i);
            if(arr[mn] > arr[right(i)]) mn = right(i);

            if(i != mn){
                swap(arr[i], arr[mn]);
                i = mn;
            }
            else break;
        }
    }

    void up_heapify(int i){
        while(i > root()){
            if(arr[i] > arr[parent(i)]){
                std::swap(arr[i], arr[parent(i)]);
                i = parent(i);
            }
            else break; 
        }
    }

public:
    Heap(int size){
        capacity = size;
        sz = 0;
        arr = new int[size + 1];
    }

    void insert(int val){
        arr[++sz] = val;
        up_heapify(sz);
        //print();
    }

    int deleteKey(){
        int mx = arr[root()];
        arr[root()] = arr[sz--];
        down_heapify(root());

        //print();
        return mx;
    }

    int getMax(){
        return arr[root()];
    }

    int size(){
        return sz;
    }

    void print(){
        std::cout << sz << " -> " ;
        for(int i = 1; i <= sz; i++)
        std::cout << arr[i] << " ";
        std::cout << std::endl;
    }

    ~Heap(){
        delete[] arr;
    }
};
