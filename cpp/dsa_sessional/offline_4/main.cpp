#include<iostream>
#include<fstream>
#include "bst.cpp"
using namespace std;

class Test{
    istream& os;
    BinarySearchTree<int> *adt;

    int runtest(int command, int param){
        int ans = -1;
        
        switch (command)
        {
        
        default:
            
            break;
        }

        return ans;
    }

    void print(BinarySearchTree<int> *bst){
        bst->print();
    }

    public:
    Test(istream &o, BinarySearchTree<int> *ds): os(o){
        adt = ds;
    }

    void startTest(){
        char command;
        
        while(os >> command && command != 0){
            try{
                if(command == '0') break;

                if(command == 'T'){
                    string s;
                    os >> s;

                    if(s == "Pre") adt->preorder();
                    else if(s == "In") adt->inorder();
                    else if(s == "Post") adt->postorder();
                }
                else{
                    if(command == 'F'){
                        int param;
                        os >> param;

                        cout << (adt->find(param)? "True": "False");
                    }
                    else if(command == 'I'){
                        int param;
                        os >> param;

                        adt->insert(param);
                        print(adt);
                    }
                    else if(command == 'D'){
                        int param;
                        os >> param;

                        if(adt->find(param)){
                            adt->remove(param);
                            adt->print();
                        }
                        else{
                            cout << "Invalid Operation";
                        }
                    }
                }

                cout << endl;
            }catch(runtime_error &ex){
                cout << ex.what() << endl;
            }
        }
    }
};

int main(){
    ifstream fin("input.txt", ios::in);
    //fin.open;

    if(!fin){
        cout << "file cannot be opened" << endl;
        return 1;
    }

    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    Test test(fin, bst);
    test.startTest();
    fin.close();
}

