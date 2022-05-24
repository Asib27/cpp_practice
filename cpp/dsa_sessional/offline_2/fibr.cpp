#include<iostream>
#include<stack>

using std::stack;

int findRecur(int n){
    if(n == 1) return 1;
    else return findRecur(n/2) + findRecur((n+1)/2) + n;
}

int findRecur_stack(int n){
    
    stack<int> st ;
    st.push(n);

    int sum = 0;
    while(! st.empty()){
        int val = st.top();
        st.pop();

        if(val == 1) sum += 1;
        else{
            st.push(val/2);
            st.push((val + 1)/2);
            sum += val;
        }
    }

    return sum;
}

int fibr(int n){
    if(n == 0) return 0;
    else if(n == 1) return 1;
    else return fibr(n-1) + fibr(n-2);
}

int fibr_stack(int n){
    stack<int> st ;
    st.push(n);

    int sum = 0;
    while(! st.empty()){
        int val = st.top();
        st.pop();

        if(val == 0) sum +=  0;
        else if(val == 1) sum += 1;
        else{
            st.push(val-1);
            st.push(val-2);
        }
    }

    return sum;
}

int main(){
    std::cout << findRecur(100) << " " << findRecur_stack(100) << std::endl;
}