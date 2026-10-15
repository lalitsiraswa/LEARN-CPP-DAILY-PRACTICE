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
