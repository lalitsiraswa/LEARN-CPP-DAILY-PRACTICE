#include<iostream>
using namespace std;

//-------------------------------------------//-------------------------------------------//
// 162. Find Peak Element
int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) {
        return 0;
    }
    int peakIndex = 0;
    for(int i = 0; i < n; i++){
        if(i == 0){
            if(nums[i] > nums[i + 1]){
                peakIndex = i;
                break;
            }
        }
        else if(i == n - 1){
            if(nums[i] > nums[i - 1]){
                peakIndex = i;
                break;
            }
        }
        else if(nums[i] > nums[i - 1] && nums[i] > nums[i + 1]){
            peakIndex = i;
            break;
        }
    }
    return peakIndex;
}

//-------------------------------------------//
int findPeakElementTwoPointer(vector<int>& nums) {
    int n = nums.size();
    // A single element is always a peak.
    if (n == 1) {
        return 0;
    }
    int peakIndex = 0;
    int leftPtr = 0, rightPtr = n - 1;
    while (leftPtr <= rightPtr) {
        // Check whether the leftmost element is a peak.
        if (leftPtr == 0) {
            if (nums[leftPtr] > nums[leftPtr + 1]) {
                return leftPtr;
            }
        }
        // Check whether the rightmost element is a peak.
        if (rightPtr == n - 1) {
            if (nums[rightPtr] > nums[rightPtr - 1]) {
                return rightPtr;
            }
        }
        // Check whether the element at leftPtr is a peak.
        if (leftPtr != 0 &&
            nums[leftPtr] > nums[leftPtr - 1] &&
            nums[leftPtr] > nums[leftPtr + 1]) {
            return leftPtr;
        }
        // Check whether the element at rightPtr is a peak.
        if (rightPtr != n - 1 &&
            nums[rightPtr] > nums[rightPtr - 1] &&
            nums[rightPtr] > nums[rightPtr + 1]) {
            return rightPtr;
        }
        leftPtr++;
        rightPtr--;
    }
    return peakIndex;
}

//-------------------------------------------//
int findPeakElementBinarySearch(vector<int>& nums) {
    int n = nums.size(); // Size of array.
    // Edge cases:
    if (n == 1)
        return 0;
    if (nums[0] > nums[1])
        return 0;
    if (nums[n - 1] > nums[n - 2])
        return n - 1;
    int low = 1, high = n - 2;
    while (low <= high)
    {
        int middle = low + (high - low) / 2;
        // If arr[mid] is the peak:
        if (nums[middle - 1] < nums[middle] && nums[middle] > nums[middle + 1])
            return middle;
        // If we are in the left:
        else if (nums[middle] > nums[middle - 1])
            low = middle + 1;
        // If we are in the right:
        else if (nums[middle] > nums[middle + 1])
            high = middle - 1;
        // We can move either left ot right
        // nums[middle] is a common point:
        else
        {
            low = middle + 1;
            // high = middle - 1;
        }
    }
    return -1;
}

//int main(){
//    vector<int> nums = {1, 2, 1};
//    cout << findPeakElementTwoPointer(nums) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 153. Find Minimum in Rotated Sorted Array
int findMin(vector<int>& nums) {
    int n = nums.size();
    // search space is already sorted
    // then arr[0] will always be
    // the minimum in that search space:
    if(nums[0] < nums[n - 1]){
        return nums[0];
    }
    int minimum = INT_MAX;
    int low = 0, high = n - 1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        minimum = min(minimum, nums[mid]);
        // Minimum is in the right half.
        // if left part is sorted:
        if(nums[0] <= nums[mid]){
            // Eliminate left half:
            low = mid + 1;
        }
        // Minimum may be in the left half.
        // if right part is sorted:
        else{
            // Eliminate right half:
            high = mid - 1;
        }
    }
    return minimum;
}

//-------------------------------------------//
int findMin01(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    int minimum = INT_MAX;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        // search space is already sorted
        // then arr[low] will always be
        // the minimum in that search space:
        if (nums[low] <= nums[high])
        {
            minimum = min(minimum, nums[low]);
            break;
        }
        // if left part is sorted:
        if (nums[low] <= nums[mid])
        {
            // keep the minimum:
            minimum = min(minimum, nums[low]);
            // Eliminate left half:
            low = mid + 1;
        }
        else
        { // if right part is sorted:
            // keep the minimum:
            minimum = min(minimum, nums[mid]);
            // Eliminate right half:
            high = mid - 1;
        }
    }
    return minimum;
}

//int main(){
//    vector<int> nums = {4,5,6,7,0,1,2};
//    cout << findMin01(nums) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 33. Search in Rotated Sorted Array
int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        // Check if the left half is sorted.
        if (nums[left] <= nums[mid]) {
            // Check if target lies within the sorted left half.
            if (nums[left] <= target && target <= nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Otherwise, check the sorted right half.
        else if (nums[mid] <= nums[right]) {
            // Check if target lies within the sorted right half.
            if (nums[mid] <= target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1; // Target not found.
}

//int main(){
//    vector<int> nums = {7, 8, 9, 1, 2, 3, 4, 5, 6};
//    cout << search(nums, 1) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 81. Search in Rotated Sorted Array II
// Dry Run
// [3, 1, 2, 3, 3, 3, 3] target = 2
// [1, 0, 1, 1, 1] target = 0
bool search2(vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    while(low <= high){
        // Skip duplicates at both ends to identify the sorted half.
        while(low < high && nums[low] == nums[low + 1]){
            low += 1;
        }
        while(low < high && nums[high] == nums[high - 1]){
            high -= 1;
        }
        int mid = low + (high - low) / 2;

        if(nums[mid] == target){
            return true;
        }
        // Check if the left half is sorted.
        if(nums[low] <= nums[mid]){
            if(nums[low] <= target && target <= nums[mid]){
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        // Otherwise, check the sorted right half.
        else if(nums[mid] <= nums[high]){
            if(nums[mid] <= target && target <= nums[high]){
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
    }
    return false;
}

//-------------------------------------------//
bool search2Tuf(vector<int>& nums, int target) {
    int n = nums.size(); // size of the array.
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int middle = low + (high - low) / 2;
        // Check if the middle element is the target.
        if (nums[middle] == target)
            return true;
        // Edge case:
        // If all three values are equal, we cannot identify the sorted half.
        if (nums[low] == nums[middle] && nums[middle] == nums[high])
        {
            low = low + 1;
            high = high - 1;
            continue;
        }
        // Check if the left half is sorted.
        if (nums[low] <= nums[middle])
        {
            // Check if the target lies within the sorted left half.
            if (nums[low] <= target && target <= nums[middle])
            {
                // element exists:
                high = middle - 1;
            }
            else
            {
                // element does not exist:
                low = middle + 1;
            }
        }
        // Otherwise, the right half is sorted.
        else
        {
            // Check if the target lies within the sorted right half.
            if (nums[middle] <= target && target <= nums[high])
            {
                // element exists:
                low = middle + 1;
            }
            else
            {
                // element does not exist:
                high = middle - 1;
            }
        }
    }
    return false; // Target not found.
}

//int main(){
//    vector<int> nums = {1, 0, 1, 1, 1};
//    cout << search2Tuf(nums, 0) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 540. Single Element in a Sorted Array
int singleNonDuplicate(vector<int>& nums) {
    int n = nums.size();
    int i = 0;
    while(i < n - 1 && nums[i] == nums[i + 1]){
        i += 2;
    }
    return nums[i];
}

//-------------------------------------------//
int singleNonDuplicate01(vector<int>& nums) {
    int n = nums.size();
    int left = 0, right = n - 1;
    while(left <= right){
        if(left < n - 1 && nums[left] != nums[left + 1]){
            return nums[left];
        }
        if(right > 0 && nums[right] != nums[right - 1]){
            return nums[right];
        }
        left += 2;
        right -= 2;
    }
    return nums[0];
}

//-------------------------------------------//
int singleNonDuplicate02(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> frequency;
    for(auto item : nums){
        frequency[item]++;
    }
    unordered_map<int, int>::iterator itr;
    for(itr = frequency.begin(); itr != frequency.end(); itr++){
        if(itr->second == 1){
            return itr->first;
        }
    }
    return nums[0];
}

//-------------------------------------------//
int singleNonDuplicateBinarySearch(vector<int>& nums) {
    int n = nums.size();
    // EDGE CASES:
    if (n == 1)
    {
        return nums[0];
    }
    if (nums[0] != nums[1])
    {
        return nums[0];
    }
    if (nums[n - 1] != nums[n - 2])
    {
        return nums[n - 1];
    }
    int low = 1;
    int high = n - 2;
    int singleElement;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1])
        {
            singleElement = nums[mid];
            break;
        }
        // EVEN INDEX:
        if (mid % 2 == 0)
        {
            if (nums[mid] == nums[mid + 1])
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        // ODD INDEX:
        else
        {
            if (nums[mid] == nums[mid - 1])
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
    }
    return singleElement;
}

//-------------------------------------------//
int singleNonDuplicateXOR(vector<int>& nums) {
    // Start with the first element.
    int singleElement = nums[0];
    for(int i = 1; i < nums.size(); i++){
        // XOR the current element with the result so far.
        // If an element appears twice, both occurrences cancel out:
        // x ^ x = 0.
        // XOR with 0 keeps the other element unchanged:
        // x ^ 0 = x.
        singleElement ^= nums[i];
    }
    // All duplicate pairs cancel out, leaving only the
    // element that appears once.
    return singleElement;
}


//int main(){
//    vector<int> nums = {3,3,7,7,10,11,11};
//    cout << singleNonDuplicateXOR(nums) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 74. Search a 2D Matrix
// Restrictions Failed:
// The solution uses a linear scan over the rows, resulting in O(m * log n) time complexity instead of the required O(log(m * n)).
bool binarySearch(vector<int> &nums, int target){
    int low = 0, high = nums.size() - 1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(nums[mid] == target){
            return true;
        }
        // Target is greater, so search the right half.
        else if(nums[mid] < target){
            low = mid + 1;
        }
        // Target is smaller, so search the left half.
        else{
            high = mid - 1;
        }
    }
    return false; // Target not found.
}

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    for(int row = 0; row < m; row++){
        // Skip rows where the target is outside the row's value range.
        if(matrix[row][0] <= target && target <= matrix[row][n - 1]){
            // Search the selected row using binary search.
            if(binarySearch(matrix[row], target)){
                return true;
            }
        }
    }
    return false; // Target not found in any row.
}

//-------------------------------------------//
// Restrictions Failed:
// The implementation uses linear scans and nested loops resulting in O(m + n) and O(m * n) time complexity.
bool searchMatrix01(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int firstRow = 0, firstColumn = 0;
    int lastRow = m - 1, lastColumn = n - 1;
    while(lastRow >= 0 && matrix[lastRow][firstColumn] > target){
        lastRow--;
    }
    while(lastColumn >= 0 && matrix[firstRow][lastColumn] > target){
        lastColumn--;
    }
    for(int row = 0; row <= lastRow; row++){
        for(int column = 0; column <= lastColumn; column++){
            if(matrix[row][column] == target){
                return true;
            }
        }
    }
    return false;
}

//-------------------------------------------//
bool searchMatrixTUF(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    // Treat the 2D matrix as a single sorted 1D array.
    int low = 0, high = (m * n) - 1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        // Convert the 1D index into 2D row and column indices.
        int row = mid / n;
        int column = mid % n;
        if(matrix[row][column] == target){
            return true;
        }
        // Target is greater, so search the right half.
        else if(matrix[row][column] < target){
            low = mid + 1;
        }
        // Target is smaller, so search the left half.
        else{
            high = mid - 1;
        }
    }
    return false; // Target not found.
}

//-------------------------------------------//
// Restrictions Failed
// The implementation uses a linear scan to find the row, resulting in O(m + log n) time complexity.
bool searchMatrix02(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int targetRow = 0;
    // Find the row whose first and last elements contain the target's range.
    while(targetRow < m){
        if(matrix[targetRow][0] <= target && target <= matrix[targetRow][n - 1]){
            break;
        }
        targetRow++;
    }
    // No row can contain the target.
    if(targetRow == m){
        return false;
    }
    // Apply binary search within the selected row.
    int low = 0, high = n - 1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(matrix[targetRow][mid] == target){
            return true;
        }
        // Target is greater, so search the right half.
        else if(matrix[targetRow][mid] < target){
            low = mid + 1;
        }
        // Target is smaller, so search the left half.
        else{
            high = mid - 1;
        }
    }
    return false; // Target not found.
}

//int main(){
//    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
//    cout << searchMatrix02(matrix, 3) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 240. Search a 2D Matrix II
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    int firstRow = 0, firstColumn = 0;
    int lastRow = m - 1, lastColumn = n - 1;
    // Exclude bottom rows whose first element is greater than target.
    while(lastRow >= 0 && matrix[lastRow][firstColumn] > target){
        lastRow--;
    }
    // Exclude rightmost columns whose first-row element is greater than target.
    while(lastColumn >= 0 && matrix[firstRow][lastColumn] > target){
        lastColumn--;
    }
    // No valid search area remains.
    if(lastRow < 0 || lastColumn < 0){
        return false;
    }
    // Search the remaining rows and columns for the target.
    for(int i = 0; i <= lastRow; i++){
        for(int j = 0; j <= lastColumn; j++){
            if(matrix[i][j] == target){
                return true;
            }
        }
    }
    return false;
}
//-------------------------------------------//
bool binarySearch201(vector<int> &nums, int target){
    int low = 0, high = nums.size() - 1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(nums[mid] == target){
            return true;
        }
        // Target is smaller, so search the left half.
        if(target < nums[mid]){
            high = mid - 1;
        }
        // Otherwise, search the right half.
        else{
            low = mid + 1;
        }
    }
    return false; // Target not found.
}

bool searchMatrix2TUF01(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    for(int row = 0; row < m; row++){
        // Search the selected row using binary search.
        if(binarySearch201(matrix[row], target)){
            return true;
        }
    }
    return false; // Target not found in any row.
}

bool searchMatrix2TUF02(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    for(int row = 0; row < m; row++){
        // Skip rows where the target is outside the row's value range.
        if(matrix[row][0] <= target && target <= matrix[row][n - 1]){
            // Search the selected row using binary search.
            if(binarySearch201(matrix[row], target)){
                return true;
            }
        }
    }
    return false; // Target not found in any row.
}
//-------------------------------------------//
// This will not work for this problem
bool searchMatrixTUF01(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int low = 0, high = (m * n) - 1;
    while(low <= high){
        int mid = low + (high - low) / 2;
        int row = mid / n;
        int column = mid % n;
        if(matrix[row][column] == target){
            return true;
        }
        else if(matrix[row][column] < target){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return false;
}

//-------------------------------------------//
bool searchMatrixTufPreferred01(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    // Start from the top-right corner.
    int row = 0, column = n - 1;
    while(row <= m - 1 && column >= 0){
        if(matrix[row][column] == target){
            return true;
        }
        // Current element is smaller, so move down to find larger values.
        else if(matrix[row][column] < target){
            row++;
        }
        // Current element is larger, so move left to find smaller values.
        else{
            column--;
        }
    }
    return false; // Target not found.
}

//-------------------------------------------//
bool searchMatrixTufPreferred02(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    // Start from the bottom-left corner.
    int row = m - 1, column = 0;
    while(row >= 0 && column < n){
        if(matrix[row][column] == target){
            return true;
        }
        // Current element is smaller, so move right to find larger values.
        else if(matrix[row][column] < target){
            column++;
        }
        // Current element is larger, so move up to find smaller values.
        else{
            row--;
        }
    }
    return false; // Target not found.
}

//int main(){
//    vector<vector<int>> matrix = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
////    vector<vector<int>> matrix = {{-5}};
//    cout << searchMatrixTufPreferred02(matrix, 5) << endl;
//    vector<int> temp = {matrix[0].begin(), matrix[0].begin() + 1};
//    for(auto item : temp){
//        cout << item << " ";
//    }
//    cout << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 1901. Find a Peak Element II
vector<int> findPeakGrid(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    for(int row = 0; row < m; row++){
        // Check whether the current row has upper and lower neighbors.
        bool up = true, down = true;
        if(row == 0){
            up = false; // No row exists above the first row.
        }
        if(row == m - 1){
            down = false; // No row exists below the last row.
        }
        for(int column = 0; column < n; column++){
            bool isPeakElement = true;
            // Check whether the current column has left and right neighbors.
            bool left = true, right = true;
            if(column == 0){
                left = false; // No column exists to the left.
            }
            if(column == n - 1){
                right = false; // No column exists to the right.
            }
            // Compare with the element above.
            if(up && mat[row][column] < mat[row - 1][column]){
                isPeakElement = false;
            }
            // Compare with the element below.
            if(down && mat[row][column] < mat[row + 1][column]){
                isPeakElement = false;
            }
            // Compare with the element on the left.
            if(left && mat[row][column] < mat[row][column - 1]){
                isPeakElement = false;
            }
            // Compare with the element on the right.
            if(right && mat[row][column] < mat[row][column + 1]){
                isPeakElement = false;
            }
            // If no neighbor is greater, the current element is a peak.
            if(isPeakElement){
                return {row, column};
            }
        }
    }
    // Fallback return; under the problem's constraints, a peak exists.
    return {-1, -1};
}

//-------------------------------------------//
vector<int> findPeakGridTuf(vector<vector<int>>& mat) {
    // Get the number of rows (m) and columns (n) in the matrix.
    int m = mat.size(), n = mat[0].size();
    // We will use binary search on the columns.
    // Initially, every column from 0 to n - 1 is a possible candidate.
    int lowColumn = 0, highColumn = n - 1;
    // Continue searching while there are columns left to check.
    while (lowColumn <= highColumn) {
        // Assume the current element is a peak until we find a larger
        // neighboring element on the left or right.
        bool isPeakElement = true;
        // Find the middle column to reduce the search space by half.
        int middleColumn = lowColumn + (highColumn - lowColumn) / 2;
        // Assume the maximum element in the middle column is in row 0.
        int maxElementRowIndex = 0;
        // Find the row containing the maximum element in the middle column.
        // Start from row 1 because row 0 is already our initial candidate.
        for (int row = 1; row < m; row++) {
            // If the current element is greater than the maximum found so far,
            // update the row index to the current row.
            if (mat[row][middleColumn] > mat[maxElementRowIndex][middleColumn]) {
                maxElementRowIndex = row;
            }
        }
        // Assume the left and right neighbors exist initially.
        // These flags help us check whether each neighbor exists
        // before accessing it, avoiding out-of-bounds access.
        bool left = true, right = true;
        // If the middle column is the first column, no left neighbor exists.
        if (middleColumn == 0) {
            left = false;
        }
        // If the middle column is the last column, no right neighbor exists.
        if (middleColumn == n - 1) {
            right = false;
        }
        // Check whether the left neighbor is greater than the current element.
        // If it is, a peak may exist in the columns to the left.
        if (left && mat[maxElementRowIndex][middleColumn - 1] > mat[maxElementRowIndex][middleColumn]) {
            // Discard the middle column and all columns to its right.
            highColumn = middleColumn - 1;
            // The current element is not a peak because its left neighbor
            // is greater than it.
            isPeakElement = false;
        }
        // If the left neighbor is not greater, check the right neighbor.
        else if (right && mat[maxElementRowIndex][middleColumn + 1] > mat[maxElementRowIndex][middleColumn]) {
            // Discard the middle column and all columns to its left.
            lowColumn = middleColumn + 1;
            // The current element is not a peak because its right neighbor
            // is greater than it.
            isPeakElement = false;
        }
        // If neither existing horizontal neighbor is greater,
        // the current element is a peak.
        //
        // We already selected the maximum element in its column,
        // so its vertical neighbors cannot be greater either.
        if (isPeakElement) {
            // Return the row index and column index of the peak.
            return {maxElementRowIndex, middleColumn};
        }
    }
    // Fallback return. Under the usual Find a Peak Element II constraints,
    // a peak exists, so the function should return before reaching this line.
    return {-1, -1};
}

//-------------------------------------------//
vector<int> findPeakGridTuf01(vector<vector<int>>& mat) {
    // Get the number of rows (m) and columns (n) in the matrix.
    int m = mat.size(), n = mat[0].size();
    // We will apply binary search on columns.
    // Initially, all columns from 0 to n - 1 are possible candidates.
    int lowColumn = 0, highColumn = n - 1;
    // Continue searching while there are columns left to check.
    while (lowColumn <= highColumn) {
        // Find the middle column of the current search range.
        int middleColumn = lowColumn + (highColumn - lowColumn) / 2;
        // Assume the maximum element in the middle column is in row 0.
        int maxElementRowIndex = 0;
        // Find the row index of the maximum element in the middle column.
        // Start from row 1 because row 0 is already our initial candidate.
        for (int row = 1; row < m; row++) {
            // If the current element is greater than the maximum found so far,
            // update the row index to the current row.
            if (mat[row][middleColumn] > mat[maxElementRowIndex][middleColumn]) {
                maxElementRowIndex = row;
            }
        }
        // Get the element immediately to the left of the maximum element.
        // If the middle column is the first column, no left neighbor exists.
        // Use INT_MIN as a placeholder so the missing neighbor cannot be
        // greater than the current element.
        int leftElement = (middleColumn - 1) >= 0 ? mat[maxElementRowIndex][middleColumn - 1] : INT_MIN;
        // Get the element immediately to the right of the maximum element.
        // If the middle column is the last column, no right neighbor exists.
        // Use INT_MIN as a placeholder for the missing neighbor.
        int rightElement = (middleColumn + 1) < n ? mat[maxElementRowIndex][middleColumn + 1] : INT_MIN;
        // Check whether the current element is greater than both
        // its left and right neighbors.
        //
        // It is already the maximum element in its column, so its vertical
        // neighbors cannot be greater than it either.
        if (leftElement < mat[maxElementRowIndex][middleColumn] && mat[maxElementRowIndex][middleColumn] > rightElement) {
            // We found a peak element.
            // Return its row index and column index.
            return {maxElementRowIndex, middleColumn};
        }
        // If the left neighbor is greater than the current element,
        // a peak can be found by searching the columns to the left.
        if (leftElement > mat[maxElementRowIndex][middleColumn]) {
            // Discard the middle column and all columns to its right.
            highColumn = middleColumn - 1;
        }
        else {
            // Otherwise, the right neighbor is greater than the current
            // element, so continue searching the columns to the right.
            // Discard the middle column and all columns to its left.
            lowColumn = middleColumn + 1;
        }
    }
    // Return {-1, -1} if no peak is found.
    // Under the usual problem constraints, a peak is guaranteed to exist.
    return {-1, -1};
}


//int main(){
////    vector<vector<int>> mat = {{4, 2, 5, 1, 4, 5}, {2, 9, 3, 2, 3, 2}, {1, 7, 6, 0, 1, 3}, {3, 6, 2, 3, 7, 2}};
//    vector<vector<int>> mat = {{1,2,3,4,5,6,7,8},{2,3,4,5,6,7,8,9},{3,4,5,6,7,8,9,10},{4,5,6,7,8,9,10,11}};
//    vector<int> result = findPeakGridTuf01(mat);
//    cout << result[0] << ", " << result[1] << endl;
//    vector<vector<int>> vect(2, vector<int>(3, 5));
//    for(int i = 0; i < vect.size(); i++){
//        for(int j = 0; j < vect[i].size(); j++){
//            cout << vect[i][j] << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// Nth Root of M - GFG
int nthRoot(int n, int m) {
    // If m is 0, its Nth root is 0.
    if (m == 0) {
        return 0;
    }
    // If m is 1, its Nth root is 1.
    if (m == 1) {
        return 1;
    }
    // Check possible root values starting from 2.
    // We only need to check values up to m / n.
    bool isPowerGreaterThanM = false;
    for (int possibleRoot = 2; possibleRoot <= m / n; possibleRoot++) {
        // Start with 1 to calculate possibleRoot raised to the power n.
        int powerResult = 1;
        // Multiply possibleRoot by itself n times.
        for (int exponent = 1; exponent <= n; exponent++) {
            powerResult *= possibleRoot;
            // If the result exceeds m, this root is too large.
            // Stop calculating its power.
            if (powerResult > m) {
                isPowerGreaterThanM = true;
                break;
            }
        }
        // Since larger possible roots will also produce powers greater
        // than m, stop checking further roots.
        if (isPowerGreaterThanM) {
            break;
        }
        // If the calculated power equals m, we found the exact Nth root.
        if (powerResult == m) {
            return possibleRoot;
        }
    }
    // No exact integer Nth root was found.
    return -1;
}

//-------------------------------------------//
int nthRootBinarySearch(int n, int m) {
    // If m is 0, its Nth root is 0.
    if (m == 0) {
        return 0;
    }
    // If m is 1, its Nth root is 1.
    if (m == 1) {
        return 1;
    }
    // Set the search range for the possible integer root.
    int low = 2, high = m / n;
    // Continue searching while the range is not empty.
    while (low <= high) {
        // Find the middle value to check as a possible Nth root.
        int possibleRoot = low + (high - low) / 2;
        // Start with 1 to calculate possibleRoot raised to the power n.
        int powerResult = 1;
        // Multiply possibleRoot by itself n times.
        for (int exponent = 1; exponent <= n; exponent++) {
            powerResult *= possibleRoot;
            // If the calculated power exceeds m, stop multiplying.
            // There is no need to calculate the remaining multiplications.
            if (powerResult > m) {
                break;
            }
        }
        // If possibleRoot raised to the power n equals m,
        // we have found the exact integer Nth root.
        if (powerResult == m) {
            return possibleRoot;
        }
        // If the calculated power is greater than m,
        // the possible root is too large.
        // Search the smaller values.
        else if (powerResult > m) {
            high = possibleRoot - 1;
        }
        // If the calculated power is smaller than m,
        // the possible root is too small.
        // Search the larger values.
        else {
            low = possibleRoot + 1;
        }
    }
    // No exact integer Nth root exists.
    return -1;
}

//int main(){
//    cout << nthRoot(2, 25) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 875. Koko Eating Bananas
// Time Limit Exceeded
int minEatingSpeed(vector<int>& piles, int h) {
    // Get the total number of piles.
    int numberOfPiles = piles.size();
    // Store the maximum number of bananas in any pile.
    // This is the maximum possible eating speed we need to check.
    int maximumPileSize = INT_MIN;
    // Store the minimum eating speed that allows us to finish
    // all the bananas within h hours.
    int minimumEatingSpeed = INT_MAX;
    // Find the largest pile because eating at this speed
    // allows us to finish any pile in at most one hour.
    for (int pileIndex = 0; pileIndex < numberOfPiles; pileIndex++) {
        maximumPileSize = max(maximumPileSize, piles[pileIndex]);
    }
    // Try every possible eating speed, starting from 1
    // up to the size of the largest pile.
    for (int eatingSpeed = 1; eatingSpeed <= maximumPileSize; eatingSpeed++) {
        // Track the total number of hours needed at this eating speed.
        // Use long long to reduce the risk of integer overflow.
        long long totalHoursRequired = 0;
        // Calculate how many hours are needed to finish each pile.
        for (int pileIndex = 0; pileIndex < numberOfPiles; pileIndex++) {
            // Count the complete hours needed to eat this pile.
            totalHoursRequired += piles[pileIndex] / eatingSpeed;
            // If bananas remain after complete hours, one additional
            // hour is needed to finish the remaining bananas.
            if (piles[pileIndex] % eatingSpeed != 0) {
                totalHoursRequired += 1;
            }
        }
        // If all piles can be finished within h hours,
        // this eating speed is valid.
        if (totalHoursRequired <= h) {
            // Since we are checking speeds in increasing order,
            // the first valid speed is the minimum eating speed.
            minimumEatingSpeed = eatingSpeed;
            // Stop searching because we have found the answer.
            break;
        }
    }
    // Return the minimum eating speed that satisfies the time limit.
    return minimumEatingSpeed;
}

//-------------------------------------------//
int minEatingSpeedBinarySearch(vector<int>& piles, int h) {
    // Get the total number of banana piles.
    int numberOfPiles = piles.size();
    // Store the size of the largest pile.
    // Eating at this speed allows Koko to finish each pile in at most one hour.
    int maximumPileSize = INT_MIN;
    // Store the minimum valid eating speed found so far.
    int minimumEatingSpeed = INT_MAX;
    // Find the largest pile to determine the upper limit of the search range.
    for (int pileIndex = 0; pileIndex < numberOfPiles; pileIndex++) {
        maximumPileSize = max(maximumPileSize, piles[pileIndex]);
    }
    // The minimum possible eating speed is 1 banana per hour.
    // The maximum possible eating speed is the size of the largest pile.
    int low = 1, high = maximumPileSize;
    // Use binary search to find the minimum valid eating speed.
    while (low <= high) {
        // Find the middle eating speed of the current search range.
        int eatingSpeed = low + (high - low) / 2;
        // Track the total hours needed to finish all the banana piles
        // at the current eating speed.
        long long totalRequiredHours = 0;
        // Calculate the time required to finish each pile.
        for (int pileIndex = 0; pileIndex < numberOfPiles; pileIndex++) {
            // Count the complete hours needed to eat this pile.
            totalRequiredHours += piles[pileIndex] / eatingSpeed;
            // If some bananas remain after complete hours,
            // one additional hour is needed to finish the pile.
            if (piles[pileIndex] % eatingSpeed != 0) {
                totalRequiredHours += 1;
            }
        }
        // If Koko can finish all piles within the given time limit,
        // the current eating speed is valid.
        if (totalRequiredHours <= h) {
            // Save the current speed as a possible minimum answer.
            minimumEatingSpeed = min(minimumEatingSpeed, eatingSpeed);
            // Try a smaller eating speed to see if it also works.
            high = eatingSpeed - 1;
        }
        else {
            // The current speed is too slow because Koko needs
            // more than h hours. Search for a higher eating speed.
            low = eatingSpeed + 1;
        }
    }
    // Return the minimum eating speed that allows Koko to finish on time.
    return minimumEatingSpeed;
}

//int main(){
////    vector<int> piles = {3, 6, 7, 11};
////    vector<int> piles = {312884470};
//    vector<int> piles = {30, 11, 23, 4, 20};
//    cout << minEatingSpeedBinarySearch(piles, 5) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
