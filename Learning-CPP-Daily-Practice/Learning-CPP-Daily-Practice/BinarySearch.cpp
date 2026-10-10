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
        if(nums[mid] >= nums[0]){
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
