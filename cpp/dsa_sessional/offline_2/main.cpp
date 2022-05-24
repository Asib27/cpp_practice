#include<iostream>
#include "arrayStack.cpp"
#include "LinkedListStack.cpp"

using namespace std;

class Test{
    istream& os;
    MyStack<int> *adt;

    int runtest(int command, int param){
        int ans = -1;
        
        switch (command)
        {
        case 1:
            adt->clear();
            break;
        case 2:
            adt->push(param);
            break;
        case 3:
            ans = adt->pop();
            break;
        case 4:
            ans = adt->length();
            break;
        case 5:
            ans = adt->topValue();
            break;
        case 6:
            adt->setDirection(param);
            break;
        default:
            
            break;
        }

        return ans;
    }

    void print(MyStack<int> *ms){
        MyStack<int> *temp = new ArrayStack<int>(ms->length());

        cout << "<";
        while(ms->length() != 0)
            temp->push(ms->pop());
        
        while(temp->length() != 0){
            int val = temp->pop();
            cout << val << " ";
            ms->push(val);
        }

        cout << "| >";
        
        delete temp;
    }

    public:
    Test(istream &o, MyStack<int> *ds): os(o){
        adt = ds;
    }

    void startTest(){
        int command, param;
        while(os >> command >> param && command != 0){
            int ans = runtest(command, param);
            cout << ans << endl;
            print(adt);
            cout << endl;
        }
    }
};

int main(){
    int arr[10];
    MyStack<int> *st = new ArrayStack<int>(arr, 10, -1);
    Test test(cin, st);
    test.startTest();

    //ArrayStack<int> as;
    // LinkedListStack<int> as;    

    // as.push(100);
    // cout << as << endl; // T 100
    // as.push(90);
    // as.push(80);
    // cout << as << endl; // T 80 90 100
    // as.pop();
    // cout << as << endl; // T 90 100
    // cout << as.topValue() << endl; // T 100
    // as.clear();
    // cout << as << endl;

    // cout << "-----------------------------------------------" << endl;

    // as.setDirection(-1);
    // as.push(70);
    // cout << as << endl;
    // as.push(60);
    // as.push(50);
    // cout << as << endl;
    // as.pop();
    // cout << as << endl;
    // cout << as.topValue() << endl;
    // as.clear();
    // cout << as << endl;

    // cout << "-----------------------------------------------" << endl;

    // cout << "-----------------------------------------------" << endl;
    // as.setDirection(1);
    // for(int i = 0; i < 30; i++){
    //     as.push(i);
    // }
    // as.push(20);
    // cout << as << endl;
    // cout << as.length() << endl;
    // as.clear();
}

