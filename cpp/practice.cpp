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

int main()
{
    cout << "Hello world" << endl;

    return 0;
}