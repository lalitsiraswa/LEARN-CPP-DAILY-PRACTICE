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
void merge(vector<int>& nums, int low, int mid, int high) {
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
        if (nums[left] <= nums[right]) {
            // Left element is smaller,
            // so add it to the sorted result.
            temp.push_back(nums[left]);
            // Move to the next element in the left half.
            left++;
        }
        else {
            // Right element is smaller,
            // so add it to the sorted result.
            temp.push_back(nums[right]);
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
        temp.push_back(nums[left]);
        left++;
    }
    // If some elements are still left in the right half,
    // add them to temp.
    while (right <= high) {
        temp.push_back(nums[right]);
        right++;
    }
    // Copy the sorted elements from temp back into
    // the original array.
    //
    // temp starts at index 0, but nums starts at index 'low',
    // therefore we use (i - low).
    for (int i = low; i <= high; i++) {
        nums[i] = temp[i - low];
    }
}

// Merge Sort works in 3 steps:
// 1. Divide the array into two halves.
// 2. Recursively sort both halves.
// 3. Merge the two sorted halves.
void mergeSortHelper(vector<int>& nums, int low, int high) {
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
    mergeSortHelper(nums, low, mid);
    // Sort the right half.
    mergeSortHelper(nums, mid + 1, high);
    // Both halves are now sorted.
    // Merge them into one sorted section.
    merge(nums, low, mid, high);
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

//----------------------------------------------//----------------------------------------------//
// Partition the array around a pivot.
//
// After partitioning:
// - All elements smaller than or equal to the pivot
//   will be on the left side.
// - All elements greater than the pivot
//   will be on the right side.
// - The pivot will be placed at its correct position.
int partition(vector<int>& nums, int low, int high) {
    // Choose a random index between low and high.
    // Random pivot helps avoid consistently bad partitions
    // for certain types of input.
//    int randomIndex = low + rand() % (high - low + 1);
    // Move the randomly selected element to the beginning.
    // We will use arr[low] as our pivot.
//    swap(nums[low], nums[randomIndex]);
    // Select the first element as the pivot.
    int pivot = nums[low];
    // i moves from left to right looking for an element
    // that is greater than the pivot.
    int i = low;
    // j moves from right to left looking for an element
    // that is smaller than or equal to the pivot.
    int j = high;
    // Continue until the two pointers cross.
    while (i < j) {
        // Move i to the right while elements are
        // already on the correct side of the pivot.
        //
        // Stop when:
        // 1. We find an element greater than the pivot, or
        // 2. i reaches the end of the current range.
        while (nums[i] <= pivot && i <= high - 1) {
            i++;
        }
        // Move j to the left while elements are
        // already on the correct side of the pivot.
        //
        // Stop when:
        // 1. We find an element smaller than or equal to the pivot, or
        // 2. j reaches the beginning of the current range.
        while (nums[j] > pivot && j >= low + 1) {
            j--;
        }
        // At this point:
        // arr[i] is greater than the pivot
        // arr[j] is smaller than or equal to the pivot
        //
        // These two elements are on the wrong sides,
        // so swap them.
        if (i < j) {
            swap(nums[i], nums[j]);
        }
    }
    // i and j have crossed.
    // j is now the correct position for the pivot.
    //
    // Move the pivot from arr[low] to arr[j].
    swap(nums[low], nums[j]);

    // Return the pivot's final position.
    return j;
}


// Helper function to recursively perform Quick Sort.
void quickSortHelper(vector<int>& nums, int low, int high) {
    // If low >= high, there is only one element
    // or no elements in this range.
    // Such a range is already sorted.
    if (low < high) {
        // Partition the array and get the pivot's
        // final/correct position.
        int pIndex = partition(nums, low, high);
        // Recursively sort the elements to the
        // left of the pivot.
        quickSortHelper(nums, low, pIndex - 1);
        // Recursively sort the elements to the
        // right of the pivot.
        quickSortHelper(nums, pIndex + 1, high);
    }
}


// Main function to perform Quick Sort.
vector<int> quickSort(vector<int>& nums) {
    // Get the size of the array.
    int n = nums.size();
    // Start Quick Sort on the entire array.
    // low  = first index
    // high = last index
    quickSortHelper(nums, 0, n - 1);
    // Return the sorted array.
    return nums;
}

int main(){
//    vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> nums = {4, 6, 2, 5, 7, 9, 1, 3};
//    selectionSort(nums);
//    bubbleSort(nums);
//    insertionSor t(nums);
//    mergeSort(nums);
    quickSort(nums);
    for(auto item : nums){
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
