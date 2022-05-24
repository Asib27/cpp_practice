#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

template<class T>void print_with_delimiter(ostream &os, vector<T> &v, string delim=",", string end="\n"){
    os << v[0];

    for(int i = 1; i < v.size(); i++){
        os << delim <<v[i];
    }

    os << end;
}

int partition(vector<int> &arr, int start, int end, bool isRandomized){
    if(isRandomized){
        int r = rand() % (end - start) + start;
        swap(arr[end-1], arr[r]);
    }
    int x = arr[end-1];

    int i = start;
    for(int j = start; j < end-1; j++){
        if(arr[j] < x){
            swap(arr[i], arr[j]);
            ++i;
        }
    }

    swap(arr[i], arr[end-1]);
    return i;
}

void quickSortHelper(vector<int> &arr, int start, int end, bool isRandomized=true){
    if(start >= end) return ;

    int mid = partition(arr, start, end, isRandomized);
    quickSortHelper(arr, start, mid, isRandomized);
    quickSortHelper(arr, mid+1, end, isRandomized);
}

void quickSort(vector<int> &arr, int start, int end){
    quickSortHelper(arr, start, end, false);
}

void randomizedQuickSort(vector<int> &arr, int start, int end){
    quickSortHelper(arr, start, end, true);
}

void merge(vector<int> &arr, int start, int mid, int end){
    int p1 = start, p2 = mid, secP = 0;
    vector<int> sec(end-start);

    while(p1 < mid && p2 < end){
        if(arr[p1] < arr[p2]){
            sec[secP++] = arr[p1];
            p1++;
        }
        else{
            sec[secP++] = arr[p2];
            p2++;
        }
    }

    while(p1 < mid){
        sec[secP++] = arr[p1];
        p1++;
    }

    while(p2 < end){
        sec[secP++] = arr[p2];
        p2++;
    }

    for(int i = start; i < end; i++){
        arr[i] = sec[i-start];
    }
}


void mergeSort(vector<int> &arr, int start, int end){
    if(start >= end-1) return ;

    int mid = start + (end - start)/2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid, end);

    merge(arr, start, mid, end);
}

void insertionSort(vector<int> &arr, int start, int end){
    for(int i = start; i < end; i++){
        int j = i-1;
        int x = arr[i];
        while(j >= start && x < arr[j]){
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = x;
    }
}


class Timer{
    clock_t started;
    clock_t stoped;

    public:
    Timer(){
        started = clock();
        stoped = 0;
    }

    void start(){
        started = clock();
        stoped = 0;
    }

    void stop(){
        stoped = clock();
    }

    double getTime(){
        if(stoped == 0){
            stop();
        }
        return (double)(stoped - started)/ CLOCKS_PER_SEC;
    }
};


double test_helper(vector<int> v, void (*sorter)(vector<int>& v, int, int)){
    Timer t;
    t.start();
    sorter(v, 0, v.size());
    t.stop();

    return t.getTime();
}

vector<double> test(int n, int no_of_test=20){
    vector<int> v(n);
    vector<double> times(7, 0);
    

    for(int i = 0; i < no_of_test; i++){
        for(auto &i: v) i = rand();

        times[0] +=  test_helper(v, mergeSort);
        times[1] +=  test_helper(v, quickSort);
        times[2] +=  test_helper(v, randomizedQuickSort);
        times[3] +=  test_helper(v, insertionSort);
        
        
        Timer t;
        t.start();
        sort(v.begin(), v.end());
        t.stop();
        times[6] += t.getTime();

        times[4] = test_helper(v, quickSort);
        times[5] = test_helper(v, randomizedQuickSort);

        cout << i << " " << n << endl;
    }

    for(auto &i: times) i /= no_of_test;
    return times;
}


int main(){
    ofstream fout;
    fout.open("runtimes.csv");
    srand(1927429);

    fout << "Time required in ms\n";
    vector<string> sort_name = {"n", "Merge Sort", "Quicksort",  "Randomized Quicksort", "Insertion Sort",
     "Quicksort with Sorted Imput", "Randomized Quicksort with Sorted Imput", "STL sort() function"};

    print_with_delimiter(fout, sort_name);

    auto result = test(5);
    fout << 5 << ",";
    print_with_delimiter(fout, result);

    cout << 5 << " " << "done" << endl;

    for(int i = 10; i < 100000; i *= 10){
        auto result = test(i);
        fout << i << ",";
        print_with_delimiter(fout, result);

        cout << i << " " << "done" << endl;
    }
    
    fout.close();
    cout << "Completed Successfully" << endl;
}