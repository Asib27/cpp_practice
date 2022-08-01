#include<iostream>
#include<string>
#include<functional>
#include<ctime>
#include<chrono>

using namespace std;
using namespace std::chrono;

unsigned long djb2_hash(const string &s){
    unsigned long hash = 5381;
    for(auto i: s){
        hash = (hash << 5) + hash + i;
    }

    return hash;
}

unsigned int RSHash(string str)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;

   for (auto i: str)
   {
      hash = hash * a + i;
      a    = a * b;
   }

   return hash;
}

class RandomStringGenerator
{
private:
    const unsigned long seed;

public:
    RandomStringGenerator(unsigned long seed = (unsigned)time(0))
        : seed(seed){
        srand(seed);
    }

    string getNext(){
        int str_length = 7;

        string ans;
        for(int i = 0; i < str_length; i++){
            char c = rand() % 26 + 'a';
            ans.push_back(c);
        }

        return ans;
    }
};

class Linear_prob{
    function<unsigned long(string)> _hash;

public:
    Linear_prob(function<int(string)> hash) 
        : _hash(hash){

    }

    unsigned long operator()(string s, unsigned long i){
        return (_hash(s) + i);
    }
};

class Quardatic_prob{
    function<unsigned long(string)> _hash;
    unsigned long _c1;
    unsigned long _c2;

public:
    Quardatic_prob(function<int(string)> hash ,
                    unsigned long c1, unsigned long c2) 
        : _hash(hash), _c1(c1), _c2(c2)
    {

    }

    unsigned long operator()(string s, unsigned long i){
        return (_hash(s) + i*i*_c2 + i*_c1);
    }
};

class Double_Hash{
    function<unsigned long(string)> _hash1;
    function<unsigned long(string)> _hash2;
    unsigned long _m;
public:
    Double_Hash(function<unsigned long(string)> hash1, 
                function<unsigned long(string)> hash2,
                unsigned long m
                )
                : _hash1(hash1), _hash2(hash2), _m(m)
    {

    }

    unsigned long operator()(string s, unsigned long i){
        auto t = _hash2(s);
        if(t % _m != 0)
            return (_hash1(s) + i* _hash2(s) ) % _m;
        else return (_hash1(s) + i* _hash2(s) + i ) % _m;
    }
};

class LinkedList
{
private:
    struct Node
    {
        string key;
        int value;
        Node* next;
        Node* prev;

        Node(string key, int value, Node* prev, Node* next)
            : key(key), value(value), next(next), prev(prev)
        {

        }
    };

    typedef Node* Nodeptr;

    Nodeptr _root;
    Nodeptr _last;
    int _length;
    
    Nodeptr _search_helper(string key){
        auto cur = _root->next;
        while(cur != _last){
            if(cur->key == key) return cur;
            cur = cur->next;
        }

        return cur;
    }
public:
    LinkedList(/* args */){
        _root = new Node("", -1, nullptr, nullptr);
        _last = new Node("", -1, _root, nullptr);
        _root->next = _last;
        _length = 0;
    }

    bool insert(string key, int value){
        auto t = _search_helper(key);
        if(t != _last) return false;

        _length++;
        auto node = new Node(key, value, t->prev, t);
        t->prev->next = node;
        t->prev = node;
        return true;
    }

    int search(string key){
        auto t = _search_helper(key);
        return t->value;
    }

    bool erase(string key){
        auto t = _search_helper(key);
        if(t == _last) return false;

        _length--;
        t->prev->next = t->next;
        t->next->prev = t->prev;
        delete t;
        return true;
    }

    int length(){
        return _length;
    }

    friend ostream& operator<<(ostream &os, const LinkedList &l){
        auto cur = l._root->next;
        cout << "[ start : " ;
        while(cur != l._last){
            cout << "{ " << cur->key << "," << cur->value << " } ";
            cur = cur->next;
        }
        cout << " : end ]" ;

        return os;
    }

    ~LinkedList(){
        auto cur = _root->next;
        while(cur != _last){
            auto t = cur->next;
            delete cur;
            cur = t;
        }

        delete _root;
        delete _last;
    }
};

class HashTableSeparateChaining{
    function<unsigned long(string)> _hash;
    LinkedList *table;
    const int _size;

    inline int getHash(string key){
        return _hash(key) % _size;
    }
public:
    HashTableSeparateChaining(function<unsigned long(string)> hash
        , int length
    ) : _hash(hash), _size(length)
    {
        table = new LinkedList[_size];
    }

    bool insert(string key, int value){
        auto t = getHash(key);
        return table[t].insert(key, value);
    }

    int search(string key){
        auto t = getHash(key);
        return table[t].search(key);
    }

    bool erase(string key){
        auto t = getHash(key);
        return table[t].erase(key);
    }

    double getAvgProbs(){
        int cnt = 0, total = 0;
        for(int i = 0; i < _size; i++){
            if(table[i].length()){
                cnt ++;
                total += table[i].length();
            }
        }

        return (double)total / cnt;
    }

    friend ostream& operator<<(ostream &os, 
        const HashTableSeparateChaining &tbl){
        for(int i = 0; i < tbl._size; i++){
            os << tbl.table[i] << endl;
        }

        return os;
    }

    ~HashTableSeparateChaining(){
        delete[] table;
    }
};

class HashTableProbing{
    const string DELETED = "!";
    const string NIL = "-";

    function<unsigned long(string, int)> _hash;
    pair<string, int> *table;
    const int _size;

    int noOfProbs, noOfSearch;

    inline int getHash(string key, int i){
        return _hash(key, i) % _size;
    }

    int _searchHelper(string key){
        for(int i = 0; i < _size; i++){
            auto t = getHash(key, i);
            if(table[t].first == key)
                return t;
            else if(table[t].first == NIL)
                return _size;
        }

        return _size;
    }

public:
    HashTableProbing(function<unsigned long(string, int)> hash, int length)
        : _hash(hash), _size(length)
    {
        table = new pair<string, int> [_size];
        for(int i = 0; i < _size; i++){
            table[i].first = NIL;
        }

        noOfProbs = 0;
        noOfSearch = 0;
    }

    bool insert(string key, int value){
        auto idx = _searchHelper(key);
        if(idx != _size) return false;

        for(int i = 0;i < _size; i++){
            auto t = getHash(key, i);
            // cout << ">>> " << i << endl;
            // cout << key << " " << t << endl;
            if(table[t].first == DELETED || 
                table[t].first ==  NIL) 
            {
                table[t] = {key, value};
                return true;
            }
        }

        return false;
    }

    int search(string key){
        noOfSearch++;
        for(int i = 0; i < _size; i++){
            auto t = getHash(key, i);
            if(table[t].first == key)
                return table[t].second;
            else if(table[t].first == NIL)
                return -1;
            noOfProbs++;
        }

        return -1;
    }

    bool erase(string key){
        for(int i = 0; i < _size; i++){
            auto t = getHash(key, i);
            if(table[t].first == key){
                table[t].first = DELETED;
                return true;
            }
            else if(table[t].first == NIL) 
                return false;
        }

        return false;
    }

    void resetProbCount(){
        noOfProbs = 0;
        noOfSearch = 0;
    }

    double getAvgProbs(){
        return (double) noOfProbs / noOfSearch;
    }

    friend ostream& operator<<(ostream &os, const HashTableProbing &h){
        for(int i = 0; i < h._size; i++){
            os << "{ " << h.table[i].first << "," << h.table[i].second << "} ";
        }

        os << endl;
        return os;
    }

    ~HashTableProbing(){
        delete[] table;
    }
};

vector<int> getRandomArray(int range, int size){
    vector<int> array(size);
    for(auto &i: array) i = rand() % range;
    return array;
}

pair<unsigned long, unsigned long> getReport(int size, double loadFactor){
    int occupied = size * loadFactor;
    int searchAfterDelete = occupied*.1;

    HashTableSeparateChaining table(djb2_hash, size);

    RandomStringGenerator generator(27);
    vector<string> keys(occupied);
    for(auto &i: keys){
        i = generator.getNext();
    }

    /* insert into table */
    for(int i = 0; i < keys.size(); i++){
        table.insert(keys[i], i);
    }

    /* search into table */
    vector<int> search_key_index = getRandomArray(occupied, occupied*.1);

    auto startTime = high_resolution_clock::now();
    for(auto i: search_key_index){
        table.search(keys[i]);
    }

    auto endTime = high_resolution_clock::now();
    auto search_time1 = duration_cast<microseconds>(endTime-startTime);

    /* delete from table */
    vector<int> delete_key_index = getRandomArray(occupied, searchAfterDelete);
    for(int i = 0; i < keys.size(); i++){
        table.erase(keys[i]);
    }

    /* search into table */
    vector<int> key_index_deleted = getRandomArray(delete_key_index.size(), searchAfterDelete/2);
    vector<int> key_index_not_deleted = getRandomArray(keys.size(), searchAfterDelete/2);

    startTime = high_resolution_clock::now();
    for(auto i: key_index_deleted){
        table.search(keys[delete_key_index[i]]);
    }
    for(auto i: key_index_not_deleted){
        table.search(keys[i]);
    }

    endTime = high_resolution_clock::now();
    auto search_time2 = duration_cast<microseconds>(endTime-startTime);

    return {search_time1.count(), search_time2.count()};
}

void generateReportChaining(int size){
    cout << "Performance of separate chaining in various load factors" << endl;
    cout << "========================================================" << endl;
    cout << endl;
    cout << "load factor: before delation, after delation" << endl;
    for(double load_factor = .4; load_factor < .9; load_factor += .1){
        auto t = getReport(size, load_factor);
        cout << load_factor << " : " << t.first << " , " << t.second << endl;
    }
    cout << endl;
}

void getReport(int size, double loadFactor, HashTableProbing &table){
    int occupied = size * loadFactor;
    int searchAfterDelete = occupied*.1;

    RandomStringGenerator generator(27);
    vector<string> keys(occupied);
    for(auto &i: keys){
        i = generator.getNext();
    }

    /* insert into table */
    for(int i = 0; i < keys.size(); i++){
        table.insert(keys[i], i);
    }

    /* search into table */
    vector<int> search_key_index = getRandomArray(occupied, occupied*.1);

    auto startTime = high_resolution_clock::now();
    for(auto i: search_key_index){
        table.search(keys[i]);
    }

    auto endTime = high_resolution_clock::now();
    auto search_time1 = duration_cast<microseconds>(endTime-startTime);
    auto avg_prob1 = table.getAvgProbs();

    /* delete from table */
    vector<int> delete_key_index = getRandomArray(occupied, searchAfterDelete);
    for(int i = 0; i < keys.size(); i++){
        table.erase(keys[i]);
    }

    /* search into table */
    table.resetProbCount();
    vector<int> key_index_deleted = getRandomArray(delete_key_index.size(), searchAfterDelete/2);
    vector<int> key_index_not_deleted = getRandomArray(keys.size(), searchAfterDelete/2);

    startTime = high_resolution_clock::now();
    for(auto i: key_index_deleted){
        table.search(keys[delete_key_index[i]]);
    }
    for(auto i: key_index_not_deleted){
        table.search(keys[i]);
    }

    endTime = high_resolution_clock::now();
    auto search_time2 = duration_cast<microseconds>(endTime-startTime);
    auto avg_prob2 = table.getAvgProbs();
    
    cout << loadFactor << " : " << search_time1.count() << " , " 
         << search_time2.count() << " ; "
         << avg_prob1 << " , " << avg_prob2
         << endl;
}

void generateReportChaining(int size, HashTableProbing &table, string name){
    cout << "Performance of " << name << " in various load factors" << endl;
    cout << "========================================================" << endl;
    cout << endl;
    for(double load_factor = .4; load_factor < .9; load_factor += .1){
        getReport(size, load_factor, table);
    }
    cout << endl;
}

int main(){
    int size = 1000;
    generateReportChaining(size);

    Linear_prob linear(djb2_hash);
    HashTableProbing mp_linear(linear, size);
    generateReportChaining(size, mp_linear, "linear probing");

    Quardatic_prob quar(djb2_hash, 1, 1);
    HashTableProbing mp_quar(quar, size);
    generateReportChaining(size, mp_quar, "quardatic probing");

    Double_Hash double_hash(djb2_hash, RSHash, size);
    HashTableProbing mp_double(double_hash, size);
    generateReportChaining(size, mp_double, "double hashing");
}