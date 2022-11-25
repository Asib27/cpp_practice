#include <iostream>
using namespace std;

string maximum_marks (double a, double b, double c, string a_name, string b_name, string c_name)
{
    if (a>b && a>c) return a_name;
    else if (b>a && b>c) return b_name;
    else return c_name;
}

class Student
{
private:
    int id;
    double marks[4];
public:
    string name;
    Student(string myname, int myid, double mymarks[])
    { //define this constructor to take the values as input
        name = myname;
        id = myid;
        for(int i = 0; i < 4; i++)
            marks[i] = mymarks[i];
    }
    double sum()
    { //define this function to calculate and return the sum of the marks obtained
        double sum = 0;
        for(int i = 0; i < 4; i++)
            sum += marks[i];
        return sum;
    }
    void display()
    { //define this function to print the name, id, and total marks(obtained using sum()) of an object "Student"
        cout << name << " " << id << " " << sum() << endl;
    }   
};

static unsigned int SDBMHash(string str) {
	unsigned int hash = 0;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash = (str[i]) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

class SymbolInfo
{
	string _name;
	string _type;
	SymbolInfo* _next;
public:
	SymbolInfo() : _next(nullptr) {};
	SymbolInfo(string name, string type, string next=nullptr)
		: _name(name), _type(type), _next(next)
	{

	}

	string getName(){ return _name;}
	string getType(){ return _type;}
	SymbolInfo* getNext(){ return _next;}
	void setName(string name){ _name = name;}
	void setType(string type){ _type = type;} 
	void setNext(SymbolInfo* next){
		_next = next;
	}
}

/**
* If any instance of ScopeTable is destroyed it will automatically free,
* all symbolInfo it contaims
*/
class ScopeTable
{
	SymbolInfo* _table;
	int _no_of_bucket;

	
public:
	ScopeTable(int n) : _no_of_bucket(n){
		table = new SymbolInfo[n];
		for(int i = 0; i < n; i++) table[i] = nullptr;
	}

	~ScopeTable(){
		for(int i = 0; i < _no_of_bucket; i++){
			if(table[i]) delete table[i];
		}
		delete[] table;
	}
}

int main()
{
    cout << "Hello world" << endl;

    return 0;
}
