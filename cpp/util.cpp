
int evaluate(vector<char> tokens){
    stack<char> sta;
    vector<char> op;

    for(auto i: tokens){
        if( i == '4')
            op.push_back(i);
        else if(i == '+' || i == '-'){
            while(!sta.empty()){
                op.push_back(sta.top());
                sta.pop();
            }
            sta.push(i);
        }
        else{
            while(!sta.empty() && !(sta.top() == '+' || sta.top() == '-') ){
                op.push_back(sta.top());
                sta.pop();
            }
            sta.push(i);
        }
    }

    while(!sta.empty()){
        op.push_back(sta.top());
        sta.pop();
    }
    //print(op);

    stack<int> st;
    for(auto i: op){
        if(i == '4') st.push(4);
        else if(i == '+'){
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();
            st.push(a + b);
        }
        else if(i == '-'){
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();
            st.push(b - a);
        }
        else if(i == '*'){
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();
            st.push(a * b);
        }
        else if(i == '/'){
            int a = st.top(); st.pop();
            int b = st.top(); st.pop();
            st.push(b / a);
        }
    }

    return st.top();
}

class n_base_number
{
private:
    /* data */
    int n;
    int digit;
    vector<int> dig;
public:
    n_base_number(int base, int digit): dig(digit, 0){
        n = base;
        this->digit = digit;
    }

    bool next(){
        for(int i = digit-1; i >= 0; i--){
            dig[i]++;
            if(dig[i] == n){
                dig[i] = 0;
            }
            else
                return true;
        }

        //cout << "here" << endl;
        return false;
    }

    vector<int>& getDig(){
        return dig;
    }

};

double distance(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2)  + (y1-y2)*(y1-y2));
}


bool isBase(string num, int base){
    if(base == 1){
        return all_of(num.begin(), num.end(), [](char i){return i == '1';});
    }

    return all_of(num.begin(), num.end(), [&](char i){
        if(base < 10) return i >= '0' && i < '0' + base ;

        return isdigit(i) || (i >= 'a' && i < 'a' + base - 10);
    });
}

int toDecimal(string num, int base){
    if(base == 1) return num.size();

    int ans = 0;
    for(auto ch : num){
        if(isdigit(ch)) ans = ans * base + ch - '0';
        else ans = ans * base + ch - 'a' + 10;
    }

    return ans;
}


int find(vi v, int to_find, int start){
    for(int i = start; i < v.size(); i++){
        if(v[i] >= to_find)
            return i;
        else if(v[i] > to_find)
            return i-1;
    }

    return v.size();
}


int find_not_matched(vector<bool> v, int to_find, int start){
    for(int i = start; i < v.size(); i++){
        if(v[i] != to_find)
            return i;
    }

    return v.size();
}
