#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>

using namespace std;

template <typename T>
class LazyObject
{
private:
    T obj;
    bool _assigned;
public:
    LazyObject(){
        _assigned = false;
    }

    LazyObject(T obj): obj(obj){
        _assigned = true;
    }

    bool isAssigned(){
        return _assigned;
    }
    
    void setObject(T obj){
        this->obj = obj;
        _assigned = true;
    }

    T getObject(){
        return obj;
    }
};


class BandMatrixHelper
{
private:
    vector<vector<int>> matrix;
    int n , fixed_row, fixed_col, order;
    int band;

    typedef vector<vector<int>> Matrix;

    /**
     * @brief calculates the unfixed band of the matrix
     * 
     * @return int 
     * max band value
     */
    int calculate_unfixed_band(){
        vector<int> col_sum(n, 0);
        int mx = 0;
        for(int i = fixed_row; i < n; i++){
            int cnt = 0;
            for(int j = fixed_col; j < n; j++){
                cnt += matrix[i][j];
                col_sum[j] += matrix[i][j];
            }
            mx = max(mx, cnt);
        }

        mx = max(mx, *max_element(col_sum.begin(), col_sum.end()));
        // cout << "unfixed : " << mx << endl;
        return (mx+1)/2;
    }

    int calculate_band_helper(vector<int> temp, int diag){
        int left = 0;
        while(left < diag && temp[left] != 1){
            left++;
        }

        int right = temp.size()-1;
        while(right > diag && temp[right] != 1){
            right--;
        }

        int mx = 1;
        mx = max(mx, diag-left+1);
        mx = max(mx, right-diag+1);

        return mx;
    }

    int calculate_fixed_band(){
        vector<int> temp(n);
        int mx = 0;

        //  for row
        for(int i = 0; i < fixed_row; i++){
            copy(matrix[i].begin(), matrix[i].end(), temp.begin());

            //compacting unfixed part
            int cnt = 0;
            for(int j = fixed_col; j < n; j++){
                cnt += matrix[i][j];
            }

            for(int j = fixed_col; j < n; j++, cnt--){
                if(cnt > 0) temp[j] = 1;
                else temp[j] = 0;
            }

            // cout << i << " " << mx << endl;
            mx = max(mx, calculate_band_helper(temp, i));
        }

        // for column
        for(int j = 0; j < fixed_col; j++){
            for(int i = 0; i < n; i++){
                temp[i] = matrix[i][j];
            }

            //compacting unfixed part
            int cnt = 0;
            for(int i = fixed_row; i < n; i++){
                cnt += matrix[i][j];
            }

            for(int i = fixed_row; i < n; i++, cnt--){
                if(cnt > 0) temp[i] = 1;
                else temp[i] = 0;
            }

            // cout << i << " " << mx << endl;
            mx = max(mx, calculate_band_helper(temp, j));
        }

        // cout << "fixed : " << mx << endl;
        return mx;
    }

    Matrix columnShuffle(const Matrix &src, int col){
        // copy the fixed cols
        int n = src.size();
        Matrix dest(n, vector<int>(n));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < fixed_col; j++){
                dest[i][j] = src[i][j];
            }
        }

        //copy new fixed col 
        for(int i = 0; i < n; i++){
            dest[i][fixed_col] = src[i][col];
        }

        //copy rest of the columns
        for(int j = fixed_col+1, k = fixed_col; j < n; j++, k++){
            for(int i = 0; i < n; i++){
                if(k == col) k++;
                dest[i][j] = src[i][k];
            }   
        }

        return dest;
    }

    Matrix rowShuffle(const Matrix &src, int row){
        int n = src.size();
        Matrix dest(n, vector<int>(n));

        // copy the fixed rows
        for(int i = 0;  i < fixed_row; i++){
            copy(src[i].begin(), src[i].end(), dest[i].begin());
        }

        //copy newly fixed row
        copy(src[row].begin(), src[row].end(), dest[fixed_row].begin());

        //copy other rows
        for(int i = fixed_row+1, k = fixed_row; i < n; i++, k++){
            if(k == row) k++;
            copy(src[k].begin(), src[k].end(), dest[i].begin());
        }

        return dest;
    }

public:
    BandMatrixHelper(): band(INT_MAX), order(-1), n(INT_MAX), fixed_row(INT_MAX), fixed_col(INT_MAX){
        
    }

    BandMatrixHelper(vector<vector<int>> matrix, int fixed_row, int fixed_col, int order)
        : matrix(matrix), fixed_row(fixed_row), fixed_col(fixed_col), n(matrix.size()), order(order)
    {
        band = max(calculate_unfixed_band(), calculate_fixed_band());
    }


    vector<BandMatrixHelper> getNext(){
        vector<BandMatrixHelper> nextMat;

        if(fixed_row == fixed_col){
            if(fixed_row == n) return nextMat;

            nextMat.push_back(BandMatrixHelper(matrix, fixed_row, fixed_col+1, 0));
            for(int i = fixed_col+1; i < n; i++){
                Matrix mat = columnShuffle(matrix, i);
                BandMatrixHelper t(mat, fixed_row, fixed_col+1, nextMat.size());
                nextMat.push_back(t);
            }
        }
        else{
            nextMat.push_back(BandMatrixHelper(matrix, fixed_row+1, fixed_col, 0));
            for(int i = fixed_row+1; i < n; i++){
                Matrix mat = rowShuffle(matrix, i);
                BandMatrixHelper t(mat, fixed_row+1, fixed_col, nextMat.size());
                nextMat.push_back(t);
            }
        }

        return nextMat;
    }

    friend bool operator<(BandMatrixHelper a, BandMatrixHelper b){
        if(a.band != b.band) return a.band > b.band;
        else return a.order < b.order;
    }

    // bool operator=(const BandMatrixHelper &b){
    //     this->band = b.band;
    //     this->fixed_col = b.fixed_col;
    //     this->fixed_row = b.fixed_row;
    //     this->matrix = b.matrix;
    //     this->n = b.n;
    //     this->order = b.order;
    // }

    friend ostream& operator<<(ostream &os, const BandMatrixHelper& b){
        os << "{" << endl;
        os << "Fixed : " << b.fixed_row << " " << b.fixed_col << endl;
        os << "Band : " << b.band << endl;
        os << "Order : " << b.order << endl;
        for(int i = 0; i < b.n; i++){
            for(int j = 0; j < b.n; j++){
                os << b.matrix[i][j];
            }
            os << endl;
        }
        os << "}" << endl;
        return os;
    }
};


int main(){
    int n;
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    for(auto &i: matrix){
        for(auto &j: i){
            char a; cin >> a;
            j = (a=='X');
        }
    }

    // for(int i = 0; i < n; i++){
    //     BandMatrixHelper a(matrix, i, i);
    //     cout << a << endl;

    //     BandMatrixHelper b(matrix, i, i+1);
    //     cout << b << endl;
    // }

    BandMatrixHelper a(matrix, 0, 0, 1);
    cout << a << endl;
    auto z = a.getNext();

    priority_queue<BandMatrixHelper> pq;
    
    for(auto i: z){
        cout << i << endl;
        pq.push(i);
    }

    cout << pq.top() << endl;
}