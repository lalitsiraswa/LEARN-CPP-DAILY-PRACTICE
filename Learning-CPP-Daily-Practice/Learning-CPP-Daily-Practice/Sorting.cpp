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
// Takes an element and place it in its right order.
void insertionSort(vector<int>& nums) {
    int n = nums.size();
    // Start from the 2nd element because the 1st element
    // is considered already sorted.
    for (int i = 1; i < n; i++) {
        // Assume the array is already sorted.
        // If we perform a swap, we know it wasn't sorted.
        int isAlreadySorted = 1;
        // Start from the current element and move it
        // towards the left until it reaches its correct position.
        int j = i;
        // Compare the current element with the element
        // immediately before it.
        //
        // If the current element is smaller, swap them.
        // Keep moving left until the correct position is found.
        while (j > 0 && nums[j] <= nums[j - 1]) {
            // Swap the elements because they are
            // in the wrong order.
            swap(nums[j], nums[j - 1]);
            // Move one position to the left and continue
            // checking for the correct position.
            j--;
            // A swap happened, so the array was not
            // already sorted.
            isAlreadySorted = 0;
        }

        // Print the number of elements processed so far.
        cout << "RUNNER : " << i << endl;
        // If no swap happened, the array is already sorted.
        // No need to continue.
        if (isAlreadySorted) {
            break;
        }
    }
}

//----------------------------------------------//----------------------------------------------//

int main(){
    vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
//    selectionSort(nums);
//    bubbleSort(nums);
//    insertionSort(nums);
    for(auto item : nums){
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
