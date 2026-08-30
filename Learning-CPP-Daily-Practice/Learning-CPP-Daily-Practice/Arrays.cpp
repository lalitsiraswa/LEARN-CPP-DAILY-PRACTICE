#include<iostream>
using namespace std;

// 73. Set Matrix Zeroes
void setZeroesSpaceOptimized(vector<vector<int>>& matrix) {
    __SIZE_TYPE__ rowCount = matrix.size();
    __SIZE_TYPE__ columnCount = matrix[0].size();
    // int row[rowCount] = {0}; --> matrix[..][0]
    // int col[columnCount] = {0}; --> matrix[0][..]
    int col0 = 1;
    // step: 1: Traverse the matrix amd
    // mark 1st row & col accordingly:
    for (int row = 0; row < rowCount; row++)
    {
        for (int column = 0; column < columnCount; column++)
        {
            if (matrix[row][column] == 0)
            {
                // mark i-th row
                matrix[row][0] = 0;
                // mark j-th column
                if (column != 0)
                    matrix[0][column] = 0;
                else
                    col0 = 0;
            }
        }
    }

    // Step 2: Mark with 0 from (1, 1) to (rowCount-1, columnCount-1):
    for (int row = 1; row < rowCount; row++)
    {
        for (int column = 1; column < columnCount; column++)
        {
            if (matrix[row][column] != 0)
            {
                // check for row & column
                if (matrix[row][0] == 0 || matrix[0][column] == 0)
                    matrix[row][column] = 0;
            }
        }
    }
    // Step 3: Finally mark the 1st row and then 1st column:
    if (matrix[0][0] == 0)
    {
        for (int column = 0; column < columnCount; column++)
        {
            matrix[0][column] = 0;
        }
    }
    if (col0 == 0)
    {
        for (int row = 0; row < rowCount; row++)
        {
            matrix[row][0] = 0;
        }
    }
}
//-------------------------------------------
void setZeroes(vector<vector<int>>& matrix) {
    __SIZE_TYPE__ rowCount = matrix.size();
    __SIZE_TYPE__ columnCount = matrix[0].size();
    vector<int> isRowZero;
    vector<int> isColumnZero;
    for (int row = 0; row < rowCount; row++)
    {
        for (int col = 0; col < columnCount; col++)
        {
            if (matrix[row][col] == 0)
            {
                isRowZero.push_back(row);
                isColumnZero.push_back(col);
            }
        }
    }
    for (int row : isRowZero)
    {
        for (int col = 0; col < columnCount; col++)
        {
            matrix[row][col] = 0;
        }
    }
    for (int col : isColumnZero)
    {
        for (int row = 0; row < rowCount; row++)
        {
            matrix[row][col] = 0;
        }
    }
}

//int main(){
//    vector<vector<int>> matrix = {{0,1,2,0},
//                                  {3,4,5,2},
//                                  {1,3,1,5}};
//    for(vector row : matrix){
//        for(int num : row){
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//    setZeroesSpaceOptimized(matrix);
//    for(vector row : matrix){
//        for(int num : row){
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}
