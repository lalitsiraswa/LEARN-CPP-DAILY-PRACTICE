#include<iostream>
using namespace std;

void selectionSort(vector<int>& nums) {
    int n = nums.size();
    // Put the smallest element at the 1st position,
    // then the next smallest at the 2nd position,
    // and continue until the array is sorted.
    for (int i = 0; i < n - 1; i++) {
        // Assume the current position 'i' contains
        // the smallest element in the unsorted part.
        int minValueIndex = i;
        // Search for the smallest element in the
        // remaining unsorted part of the array.
        for (int j = i + 1; j < n; j++) {
            // If we find a smaller element, remember its index.
            if (nums[j] <= nums[minValueIndex]) {
                minValueIndex = j;
            }
        }
        // Put the smallest element at position 'i'.
        swap(nums[i], nums[minValueIndex]);
    }
}

//----------------------------------------------//----------------------------------------------//
void bubbleSort(vector<int>& nums) {
    int n = nums.size();
    // Perform multiple passes over the array.
    // After each pass, the largest unsorted element
    // moves to its correct position at the end.
    for (int i = 0; i < n - 1; i++) {
        // Assume the array is already sorted.
        // If we perform any swap, we know it wasn't sorted.
        int isAlreadySorted = 1;
        // Compare adjacent elements.
        // The last 'i' elements are already sorted,
        // so we don't need to check them again.
        for (int j = 0; j < (n - 1) - i; j++) {
            // If the left element is greater than the right,
            // they are in the wrong order.
            if (nums[j] > nums[j + 1]) {
                // Swap the two elements to put them
                // in the correct order.
                swap(nums[j], nums[j + 1]);
                // A swap happened, so the array was not
                // already sorted before this pass.
                isAlreadySorted = 0;
            }
        }
        // Print the number of passes completed.
        cout << "RUNNER : " << i + 1 << endl;
        // If no swap happened during this entire pass,
        // the array is already sorted, so we can stop early.
        if (isAlreadySorted) {
            break;
        }
    }
}

//----------------------------------------------//----------------------------------------------//
// Takes an element and places it in its correct position.
void insertionSort(vector<int>& nums) {
    int n = nums.size();
    // Start from the 2nd element because the 1st element
    // is considered already sorted.
    for (int i = 1; i < n; i++) {
        // Start from the current element and move it
        // towards the left until it reaches its correct position.
        int j = i;
        // Compare the current element with the element before it.
        // If the current element is smaller, move it one position left.
        while (j > 0 && nums[j] < nums[j - 1]) {
            // Swap the elements because they are in the wrong order.
            swap(nums[j], nums[j - 1]);
            // Move one position to the left.
            j--;
        }
        cout << "RUNNER : " << i << endl;
    }
}

//----------------------------------------------//----------------------------------------------//
// Merge two already sorted halves:
//
// Left half  = [low ... mid]
// Right half = [mid+1 ... high]
//
// Example:
// [2, 5, 8] + [1, 3, 7]
//          ↓
// [1, 2, 3, 5, 7, 8]
void merge(vector<int>& arr, int low, int mid, int high) {
    // Temporary array where we will build
    // the sorted result of both halves.
    vector<int> temp;
    // Pointer for the left half.
    int left = low;
    // Pointer for the right half.
    int right = mid + 1;
    // Compare elements from both halves.
    // Pick the smaller element and put it into temp.
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            // Left element is smaller,
            // so add it to the sorted result.
            temp.push_back(arr[left]);
            // Move to the next element in the left half.
            left++;
        }
        else {
            // Right element is smaller,
            // so add it to the sorted result.
            temp.push_back(arr[right]);
            // Move to the next element in the right half.
            right++;
        }
    }
    // If some elements are still left in the left half,
    // add them to temp.
    //
    // We don't need to compare them because the remaining
    // elements are already sorted.
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }
    // If some elements are still left in the right half,
    // add them to temp.
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }
    // Copy the sorted elements from temp back into
    // the original array.
    //
    // temp starts at index 0, but arr starts at index 'low',
    // therefore we use (i - low).
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

// Merge Sort works in 3 steps:
// 1. Divide the array into two halves.
// 2. Recursively sort both halves.
// 3. Merge the two sorted halves.
void mergeSortHelper(vector<int>& arr, int low, int high) {
    // Base case:
    // If there is only one element (or no element),
    // it is already sorted.
    if (low >= high) {
        return;
    }
    // Find the middle index so that we can divide
    // the array into two halves.
    int mid = (low + high) / 2;
    // Sort the left half.
    mergeSortHelper(arr, low, mid);
    // Sort the right half.
    mergeSortHelper(arr, mid + 1, high);
    // Both halves are now sorted.
    // Merge them into one sorted section.
    merge(arr, low, mid, high);
}

// Main function to perform Merge Sort.
void mergeSort(vector<int>& nums) {
    // Find the size of the array.
    int n = nums.size();
    // Start Merge Sort on the entire array.
    // low  = 0
    // high = n - 1
    mergeSortHelper(nums, 0, n - 1);
}

int main(){
    vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
//    selectionSort(nums);
//    bubbleSort(nums);
//    insertionSor t(nums);
    mergeSort(nums);
    for(auto item : nums){
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
