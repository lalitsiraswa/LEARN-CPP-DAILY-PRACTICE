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

//-------------------------------------------//-------------------------------------------//

// 118. Pascal's Triangle
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> pascalTriangle;
    for(int row = 0; row < numRows; row++){
        vector<int> singleRow;
        for(int column = 0; column <= row; column++){
            if(column == 0 || column == row){
                singleRow.push_back(1);
            }
            else{
                singleRow.push_back(pascalTriangle[row-1][column-1] + pascalTriangle[row-1][column]);
            }
        }
        pascalTriangle.push_back(singleRow);
    }
    return pascalTriangle;
}

//int main(){
//    int numRows = 6;
//    vector<vector<int>> pascalTriangle = generate(numRows);
//    for(vector row : pascalTriangle){
//        for(int num : row){
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------
long long nCr(int n, int r){
    long long result = 1;
    for(int i = 0; i < r; i++){
        result = result * (n - i);
        result = result / (i + 1);
    }
    return result;
}

vector<int> generateRow(int row){
    vector<int> resultRow;
    long long result = 1;
    resultRow.push_back(result);
    for(int column = 0; column < row; column++){
        result = result * (row - column);
        result = result / (column + 1);
        resultRow.push_back(result);
    }
    return resultRow;
}

vector<vector<int>> generatePascalTriangle(int numRows) {
    vector<vector<int>> pascalTriangle;
    for(int row = 0; row < numRows; row++){
        pascalTriangle.push_back(generateRow(row));
    }
    return pascalTriangle;
}
//int main(){
////    vector<int> resultRow = generateRow(3);
////    for(int item : resultRow){
////        cout << item << " ";
////    }
////    cout << endl;
//    
//    vector<vector<int>> pascalTriangle = generatePascalTriangle(6);
//    for(vector<int> row : pascalTriangle){
//        for(int item : row){
//            cout << item << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 31. Next Permutation
void nextPermutation(vector<int>& nums) {
    int n = nums.size();

    // Step 1:
    // Start from the second-last element and move from RIGHT to LEFT.
    // We are looking for the first position where:
    //
    //      nums[i] < nums[i + 1]
    //
    // This position is called the "pivot".
    int pivotIndex = n - 2;

    while (pivotIndex >= 0 &&
           nums[pivotIndex] >= nums[pivotIndex + 1]) {

        pivotIndex--;
    }

    // Step 2:
    // If we could not find a pivot, the entire array is in descending order.
    //
    // Example:
    //      [3, 2, 1]
    //
    // This is already the LARGEST permutation.
    // Therefore, the next permutation is the SMALLEST permutation.
    //
    // So simply reverse the entire array:
    //      [3, 2, 1] -> [1, 2, 3]
    if (pivotIndex == -1) {
        reverse(nums.begin(), nums.end());
        return;
    }

    // Step 3:
    // We found the pivot.
    //
    // Now we need to find the smallest number that is GREATER
    // than the pivot.
    //
    // Start from the RIGHT because the elements after the pivot
    // are in descending order.
    //
    // Example:
    //      [1, 3, 5, 4, 2]
    //          ^
    //        pivot = 3
    //
    // Elements after pivot: [5, 4, 2]
    //
    // Starting from the right:
    //      2 > 3 ? No
    //      4 > 3 ? Yes -> choose 4
    int targetIndex = n - 1;

    while (nums[targetIndex] <= nums[pivotIndex]) {
        targetIndex--;
    }

    // Step 4:
    // Swap the pivot with the next larger element.
    //
    // Example:
    //      [1, 3, 5, 4, 2]
    //          ^     ^
    //          3 <-> 4
    //
    // Result:
    //      [1, 4, 5, 3, 2]
    swap(nums[pivotIndex], nums[targetIndex]);

    // Step 5:
    // Everything after the pivot is currently in DESCENDING order.
    //
    // We need the SMALLEST possible arrangement after the pivot
    // to make this the immediate next permutation.
    //
    // Therefore, reverse the suffix.
    //
    // Example:
    //      [1, 4, 5, 3, 2]
    //             -------
    //             suffix
    //
    //      [5, 3, 2] -> [2, 3, 5]
    //
    // Final:
    //      [1, 4, 2, 3, 5]
    reverse(nums.begin() + pivotIndex + 1, nums.end());
}

//int main(){
////    vector<int> nums = {3, 2, 1};
//    vector<int> nums = {1, 5, 1};
//    nextPermutation(nums);
//    for(int item : nums){
//        cout << item;
//    }
//    cout << endl;
//    return 0;
//}
