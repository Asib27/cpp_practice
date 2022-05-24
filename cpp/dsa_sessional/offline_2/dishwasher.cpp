#include <iostream>

#include "MyStack.cpp"
#include "ArrayStack.cpp"
#include "LinkedListStack.cpp"
#include "Util.cpp"

using namespace std;


template <typename T> bool every(T arr[], int len, int is_equal_to);

int main(){
    int n,x;
    cin >> n >> x;

    int time_course[x];
    int order_of_finish[x];
    int idx_order = 0;
    int last_meal[x];
    for(int i= 0; i < x; i++)
        cin >> time_course[i];


    MyStack<Dish> *dirty = new LinkedListStack<Dish>();
    MyStack<CleandDish> *clean = new LinkedListStack<CleandDish>();
    Optional<DishCleaner> current;
    DirtyStackHandler input(cin);

    int total_time = 0;
    for(; dirty->length() != 0 || current.hasValue() || input.hasNextFuture(total_time); total_time++){
        //if input.hasNext()
            //push value to dirty stack
        if(input.hasNext(total_time)){
            Dish d = input.next();
            dirty->push(d);

            last_meal[d.getFriendNo()-1] = d.getCourseNo();
            if(last_meal[d.getFriendNo()-1] == n){
                order_of_finish[idx_order++] = d.getFriendNo();
            }
            //cout << d  << " " <<  dirty->length() << " " << clean->length() << " Pushed to dirty stack"<< endl;
        }
        
        
        //count down current dish
        if(current.hasValue()){
            //cout << "before "  << current.getValue().getTimeLeft(); 
            current.getValue().countDown();
            //cout << " after "  << current.getValue().getTimeLeft() << " " << current.getValue().getDish()<< endl; 
        }

        bool isNothingCleaned = !current.hasValue();

        if(! current.hasValue() || current.getValue().isClean()){
            //cout << "Entered if " << endl;
            // if clean
            if(current.hasValue()) {
                DishCleaner dc = current.getValue();
                current.setHasValue(false);
                CleandDish cd(dc.getDish(), total_time);
                clean->push(cd);
            }

            if(dirty->length() != 0){
                //cout << "Expected " << endl;

                Dish d = dirty->pop();
                DishCleaner dc(d, time_course[d.getCourseNo()-1]);
                current.setValue(dc);

                if(isNothingCleaned) current.getValue().countDown();

                //cout << current.getValue() << "popped from dirty stack  " << endl;
            }
            
            else current.setHasValue(false);
            
            //if the last dish takes 1 unit time
            if(!input.hasNextFuture(total_time) && dirty->length() == 0 && 
                current.hasValue() && current.getValue().isClean()){

                DishCleaner dc = current.getValue();
                CleandDish cd(dc.getDish(), total_time);
                clean->push(cd);
                total_time++;
                break;
            }
        }
        //if current is clean
            //push current to clean
            // pop from dirty if present
            // if not present make current optional false
        //cout << total_time << " " << dirty->length() << " " << current.hasValue() << " " << input.hasNext(total_time)
        //<< endl << "------------------------------------" << endl;
    }

    //print required time
    cout << total_time-1 << endl;

    //print time of clening from clean stack
    MyStack<CleandDish> *temp = new ArrayStack<CleandDish>();
    while(clean->length() != 0){
        temp->push(clean->pop());
    }

    bool printStart = false;
    while(temp->length() != 0){
        if(printStart){
            cout << "," <<  temp->pop().getTimeCleaned();
        }
        else{
            cout << temp->pop().getTimeCleaned();
            printStart = true;
        }
    }
    cout << endl;

    //print whether everyone eat full course
    cout << (every(last_meal, x, n)? "Y": "N") << endl;

    printStart = false;
    for(int i = 0; i < x; i++){
        if(last_meal[i] == n){
            if(printStart){
                cout << "," << i+1 ;
            }
            else{
                cout << i+1;
                printStart = true;
            }
        }
    }
}

template <typename T>
bool every(T arr[], int len, int is_equal_to){
    bool ans = true;
    for(int i = 0; i < len; i++){
        if(arr[i] != is_equal_to)
            ans = false;
    }

    return ans;
}
