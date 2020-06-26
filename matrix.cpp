#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

class Matrix
{
public:
    Matrix(){
        rows = 0;
        cols = 0;
    }
    Matrix(int new_rows, int new_cols){
        Reset(new_rows, new_cols);
    }
    void Reset(int new_rows, int new_cols){
        if (new_rows < 0 || new_cols < 0)
            throw out_of_range("invalid numbers");
        rows = new_rows;
        cols = new_cols;
        matrix.assign(new_rows, vector<int>(new_cols));
    }
    int At(int str_num, int col_num) const{
        if (str_num >= rows || col_num >= cols || str_num < 0 || col_num < 0)
            throw out_of_range("wrong numbers");
        return matrix[str_num][col_num];
    }
    int& At(int str_num, int col_num){
        if (str_num >= rows || col_num >= cols || str_num < 0 || col_num < 0)
            throw out_of_range("wrong numbers");
        return matrix[str_num][col_num];
    }
    int GetNumRows() const{
        return rows;
    }
    int GetNumColumns() const{
        return cols;
    }
private:
    int rows, cols;
    vector<vector<int>> matrix;
};
// оператор >> черзе at

istream& operator>>(istream& stream, Matrix& matrix){
    int first, second;
    stream >> first >> second;
    matrix.Reset(first, second);
    for (int i = 0; i < first; i++){
        for (int j = 0; j < second; j++)
        stream >> matrix.At(i, j);
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix){
    int rows = matrix.GetNumRows();
    int cols = matrix.GetNumColumns();
    stream << rows << ' ' << cols;
    if (rows != 0 || cols != 0)
        stream << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            stream << matrix.At(i, j);
            if (cols - 1 != j)
                stream << ' ';
        }
        if (rows - 1 != i)
            stream << endl;
    }
    return stream;
}

bool operator== (const Matrix& lhs, const Matrix& rhs){
    if (rhs.GetNumRows() != lhs.GetNumRows() || rhs.GetNumColumns() != lhs.GetNumColumns())
        if (!((rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0) && (lhs.GetNumRows() == 0 || lhs.GetNumColumns() == 0)))
            return false;
    int rows = rhs.GetNumRows();
    int cols = rhs.GetNumColumns();
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (rhs.At(i, j) != lhs.At(i, j))
                return false;
    return true;
}

Matrix operator+ (const Matrix& lhs, const Matrix& rhs){
    int rows = rhs.GetNumRows();
    int cols = rhs.GetNumColumns();
    if (rhs.GetNumRows() != lhs.GetNumRows() || rhs.GetNumColumns() != lhs.GetNumColumns())
    {
        if ((rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0) && (lhs.GetNumRows() == 0 || lhs.GetNumColumns() == 0))
        {
            rows = 0;
            cols = 0;
        }
        else
            throw invalid_argument("different size's");
    }
    Matrix res;
    res.Reset(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
    return res;
}

int main() {
  Matrix one(0, 0);
  Matrix two(0, 5);
//   stringstream input("3 5\n6 4 -1 9 8\n12 1 2 9 -5\n-4 0 12 8 6\n\n3 5\n5 1 0 -8 23\n14 5 -6 6 9\n8 0 5 4 1");
//   input >> one >> two;
    // cout << (one == two) << endl;
//   one.Reset(1, 1);
  cout << boolalpha << (one == two) << '\n';
  return 0;
}