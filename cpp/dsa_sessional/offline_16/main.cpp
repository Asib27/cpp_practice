#include<iostream>
#include<string>
#include<functional>
#include<ctime>

using namespace std;

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
    unsigned long _m;

public:
    Linear_prob(function<int(string)> hash,unsigned long m) 
        : _hash(hash), _m(m){

    }

    unsigned long operator()(string s, unsigned long i){
        return (_hash(s) + i) % _m;
    }
};

class Quardatic_prob{
    function<unsigned long(string)> _hash;
    unsigned long _m;
    unsigned long _c1;
    unsigned long _c2;

public:
    Quardatic_prob(function<int(string)> hash,unsigned long m,
                    unsigned long c1, unsigned long c2) 
        : _hash(hash), _m(m) , _c1(c1), _c2(c2)
    {

    }

    unsigned long operator()(string s, unsigned long i){
        return (_hash(s) + i*i*_c2 + i*_c1) % _m;
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

int main(){
    // function<unsigned long(string)> hash = djb2_hash;
    // RandomStringGenerator rand(30);
    // Linear_prob linear_prob(djb2_hash, 97);
    // Quardatic_prob quad_prob(djb2_hash, 97, 1, 1);
    // Double_Hash double_hash(djb2_hash, RSHash, 97);

    // for(int i = 0; i < 10; i++){
    //     auto s = rand.getNext();
    //     cout << s << " " << hash(s) << endl;
    //     cout << linear_prob(s, 0) << " " << linear_prob(s, 1) << " "
    //         << linear_prob(s, 2) << endl;
    //     cout << quad_prob(s, 0) << " " << quad_prob(s, 1) << " "
    //         << quad_prob(s, 2) << endl;
    //     cout << double_hash(s, 0) << " " << double_hash(s, 1) << " "
    //         << double_hash(s, 2) << endl;
    // }

    // LinkedList ll;
    // cout << ll << endl;
    
    // int a,b;HashTableSeparateChaining
    // while(cin >> a >> b){
    //     int res;
    //     if(a == 1) res = ll.insert(b);
    //     else if(a == 2) res = ll.search(b);
    //     else if(a == 3) res = ll.erase(b);

    //     cout << res << endl;
    //     cout << ll << endl;
    // }
    
    RandomStringGenerator rand(30);
    HashTableSeparateChaining mp(djb2_hash, 20);

    string b;
    int a;
    while(cin >> a >> b){
        int res;
        if(a == 1){
            int c;
            cin >> c;
            res = mp.insert(b, c);  
        } 
        else if(a == 2) res = mp.search(b);
        else if(a == 3) res = mp.erase(b);

        cout << res << endl;
        cout << mp << endl;
    }
}