#include <iostream>
#include "MyQueue.cpp"
#include "LinkedListQueue.cpp"
#include "ArrayQueue.cpp"

using namespace std;

class Customer{
    int entry_time;
    int service_time;

    public:
    Customer() {}

    Customer(int e, int s){
        entry_time = e;
        service_time = s;
    }

    int getRemainingServiceTime(){
        return service_time;
    }

    void count_down(){
        service_time--;
    }

    int getTime(){
        return entry_time;
    }

    int isServed(){
        return service_time <= 0;
    }

    friend ostream& operator<<(ostream &os , const Customer &c){
        os << "|" << c.entry_time << " " << c.service_time << "|";

        return os;
    }
};

template<typename T>
class Optional{
    T value;
    bool hValue;

    public:
    Optional(T val): value(val){
        hValue = true;
    }

    Optional(){
        hValue = false;
    }

    T& getValue(){
        return value;
    }

    bool hasValue(){
        return hValue;
    }

    void setHasValue(bool val){
        hValue = false;
    }

    void setValue(T val){
        value = val;
        hValue = true;
    }
};


class InputHandler{
    Customer customer;
    istream& is;
    bool hNext;

    int input_left;

    void takeInput(){
        if(input_left != 0){
            int n, t;
            is >> n >> t;
            customer = Customer(n, t);
            --input_left;
        }
        else{
            hNext = false;
        }
        
    }

public:
    InputHandler(istream& o, int n): is(o){
        input_left = n;
        hNext = true;
        takeInput();
    }

    Customer next(){
        Customer ans = customer;
        
        takeInput();
        return ans;
    }

    bool hasNext(int total_time){
        return hNext && total_time == customer.getTime();
    }

    bool hasNextFuture(int total_time){
        return hNext && total_time <= customer.getTime();
    }
};

template <typename T>
bool handleTeller(MyQueue<T> *qu, Optional<T> &teller){
    bool did_left = false;

    if(teller.hasValue()){
        teller.getValue().count_down();
    }

    if(teller.hasValue() && teller.getValue().isServed()){
        cout << teller.getValue() << "leaves teller" << endl;
        teller.setHasValue(false);
        
        did_left = true;
    }

    if(!teller.hasValue()){
        if(qu->length() != 0){
            teller.setValue(qu->dequeue());
            cout << teller.getValue() << "from qu goes to teller" << endl;
        }
        else{
            teller.setHasValue(false);
            cout << "qu empty" << endl;
        }
    }

    return did_left;
}

template <typename T>
void handleLeaveQueue(MyQueue<T> *qu1, Optional<Customer> &teller1, MyQueue<T> *qu2, Optional<Customer> &teller2){
    if(qu1->length() + teller1.hasValue() - 1 > qu2->length() + teller2.hasValue()){
        qu2->enqueue(qu1->leaveQueue());
        cout << qu2->frontValue() << "leaves q1 enters qu2" << endl;
    }
    else if(qu2->length() + teller2.hasValue() - 1 > qu1->length() + teller1.hasValue()){
        qu1->enqueue(qu2->leaveQueue());
        cout << qu1->frontValue() << "leaves q2 enters qu1" << endl;
    }
}

int main(){
    int customer_no;
    cin >> customer_no;

    InputHandler input(cin, customer_no);

    Optional<Customer> teller1, teller2;
    MyQueue<Customer> *qu1 = new LinkedListQueue<Customer>();
    MyQueue<Customer> *qu2 = new LinkedListQueue<Customer>();

    int total_time = 0;
    int last_time1 = 0, last_time2 = 0;

    while(input.hasNextFuture(total_time) || teller1.hasValue() || teller2.hasValue()
         || qu1->length() + qu2->length() > 0){

        //pushed customer to new queue
        if(input.hasNext(total_time)){
            if(qu1->length() + teller1.hasValue() < qu2->length() + teller2.hasValue()){
                qu1->enqueue(input.next());
                cout << qu1->frontValue() << "pushed to qu1" << endl;
            }
            else{
                qu2->enqueue(input.next());
                cout << qu2->frontValue() << "pushed to qu2" << endl;
            }
        }

        if(handleTeller(qu1, teller1))
            last_time1 = total_time;
        if(handleTeller(qu2, teller2))
            last_time2 = total_time;

        handleLeaveQueue(qu1, teller1, qu2, teller2); 

        cout << "total time: " << total_time << endl << "-----------------------------------\n";
        total_time++;
    }

    cout << total_time << " " << last_time1 << " " << last_time2 << endl;
    cout << "Booth 1 finishes service at t=" << last_time1 << endl;
    cout << "Booth 2 finishes service at t=" << last_time2 << endl;
}