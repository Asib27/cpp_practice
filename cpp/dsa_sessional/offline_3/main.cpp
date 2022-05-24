#include<iostream>
#include "MyQueue.cpp"
#include "LinkedListQueue.cpp"
#include "ArrayQueue.cpp"

using namespace std;

class Test{
    istream& os;
    MyQueue<int> *adt;

    int runtest(int command, int param){
        int ans = -1;
        
        switch (command)
        {
        case 1:
            adt->clear();
            break;
        case 2:
            adt->enqueue(param);
            break;
        case 3:
            ans = adt->dequeue();
            break;
        case 4:
            ans = adt->length();
            break;
        case 5:
            ans = adt->frontValue();
            break;
        case 6:
            ans = adt->rearValue();
            break;
        case 7:
            ans = adt->leaveQueue();
            break;
        default:
            
            break;
        }

        return ans;
    }

    void print(MyQueue<int> *ms){
        cout << "< ";
        for(int i = 0; i < ms->length(); i++){
            cout << ms->frontValue() << " ";
            int t = ms->dequeue();
            ms->enqueue(t);
        }
        cout << ">";
    }

    public:
    Test(istream &o, MyQueue<int> *ds): os(o){
        adt = ds;
    }

    void startTest(){
        int command, param;
        while(os >> command >> param && command != 0){
            try{
                int ans = runtest(command, param);
                cout << ans << endl;
                print(adt);
                cout << endl;
            }catch(runtime_error &ex){
                cout << ex.what() << endl;
            }
        }
    }
};

int main(){
    int *a = new int[10];
    MyQueue<int> *qu = new ArrayQueue<int>(a, 10);
    Test test(cin, qu);
    test.startTest();
}

