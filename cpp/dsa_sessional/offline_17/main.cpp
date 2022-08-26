#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class BandMatrixHelper
{
private:
    vector<vector<int>> matrix;
    const int n , fixed_row, fixed_col;
    int band;

    // typedef vector<vector<bool>> Matrix;

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

public:
    BandMatrixHelper(vector<vector<char>> matrix, int fixed_row, int fixed_col)
        : fixed_row(fixed_row), fixed_col(fixed_col), n(matrix.size())
    {
        this->matrix.assign(n, vector<int> (n));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                this->matrix[i][j] = (matrix[i][j] == 'X');
            }
        }

        band = max(calculate_unfixed_band(), calculate_fixed_band());
    }

    friend ostream& operator<<(ostream &os, const BandMatrixHelper& b){
        os << "{" << endl;
        os << "Fixed : " << b.fixed_row << " " << b.fixed_col << endl;
        os << "Band : " << b.band << endl;
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

    vector<vector<char>> matrix(n, vector<char>(n));
    for(auto &i: matrix){
        for(auto &j: i){
            cin >> j;
        }
    }

    for(int i = 0; i < n; i++){
        BandMatrixHelper a(matrix, i, i);
        cout << a << endl;

        BandMatrixHelper b(matrix, i, i+1);
        cout << b << endl;
    }
}