#ifndef _UTIL_CPP
#define _UTIL_CPP

using namespace std;

class Dish{
    int friend_no;
    int time_pushed;
    int course_no;

public:
    Dish(){
        friend_no = -1;
        time_pushed = -1;
        course_no = -1;
    }

    Dish(int k, int t, int s){
        friend_no = k;
        time_pushed = t;
        course_no = s;
    }

    int getTime(){
        return time_pushed;
    }

    int getFriendNo(){
        return friend_no;
    }

    int getCourseNo(){
        return course_no;
    }

    friend ostream& operator<<(ostream& os,const Dish &d){
        os << "|" << d.friend_no << " " << d.time_pushed << " " 
            << d.course_no << "|";
             

        return os;
    }
};

class DirtyStackHandler{
    Dish dish;
    istream& is;
    bool hNext;

    void takeInput(){
        int n, t, s;
        is >> n >> t >> s;
        dish = Dish(n, t, s);

        if(n == 0) hNext = false;
    }

public:
    DirtyStackHandler(istream& o): is(o){
        hNext = true;
        takeInput();
    }

    Dish next(){
        Dish ans = dish;
        
        takeInput();
        return ans;
    }

    bool hasNext(int total_time){
        return hNext && total_time == dish.getTime();
    }

    bool hasNextFuture(int total_time){
        return hNext && total_time <= dish.getTime();
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


class DishCleaner{
    Dish dish;
    int time_left;

public:
    DishCleaner(){

    }

    DishCleaner(Dish d, int time){
        dish = d;
        time_left = time;
    }

    Dish getDish(){
        return dish;
    }

    int getTimeLeft(){
        return time_left;
    }

    void countDown(int time=1){
        time_left -= time;
    }

    bool isClean(){
        return time_left <= 0;
    }

    friend ostream& operator<<(ostream& os,const DishCleaner &d){
        os << d.dish << " " << d.time_left;
             

        return os;
    }
};

class CleandDish{
    Dish dish;
    int time_cleaned;

    public:
    CleandDish(){

    }

    CleandDish(Dish d, int time){
        dish = d;
        time_cleaned = time;
    }

    Dish getDish(){
        return dish;
    }

    int getTimeCleaned(){
        return time_cleaned;
    }
};


#endif