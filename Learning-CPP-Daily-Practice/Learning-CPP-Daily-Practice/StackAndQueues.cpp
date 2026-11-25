#include<iostream>
using namespace std;

//----------------------------------------------//----------------------------------------------//
// Monotonic-Stack: Storing elements in specific order
// Next Greater Element
// Function to find the Next Greater Element for every array element.
vector<int> nextGreaterElementMonotonicStack(vector<int>& numbers) {
    // Stack maintains elements in decreasing order from bottom to top.
    // It stores values that can potentially be the next greater element.
    stack<int> decreasingStack;
    // Store the total number of elements in the input array.
    int arraySize = numbers.size();
    // Initialize the result array to store the Next Greater Element.
    vector<int> nextGreaterElements(arraySize);
    // Traverse the array from right to left.
    // This ensures that elements to the right are processed first.
    for (int currentIndex = arraySize - 1; currentIndex >= 0; currentIndex--) {
        // Remove all elements smaller than or equal to the current element.
        // These elements cannot be the Next Greater Element
        // for the current element.
        while (!decreasingStack.empty() && decreasingStack.top() <= numbers[currentIndex]) {
            decreasingStack.pop();
        }
        // If the stack is not empty, its top contains
        // the nearest greater element on the right.
        if (!decreasingStack.empty()) {
            nextGreaterElements[currentIndex] = decreasingStack.top();
        }
        else {
            // No greater element exists on the right.
            nextGreaterElements[currentIndex] = -1;
        }
        // Push the current element into the stack.
        // It may be the Next Greater Element for an element on its left.
        decreasingStack.push(numbers[currentIndex]);
    }
    // Return the array containing the Next Greater Elements.
    return nextGreaterElements;
}

//int main() {
//    // Input array.
//    vector<int> numbers = {4, 12, 5, 3, 1, 2, 5, 3, 1, 2, 4, 6};
//    // Calculate the Next Greater Element for every array element.
//    vector<int> nextGreaterElements = nextGreaterElementMonotonicStack(numbers);
//    // Print the result.
//    for (int element : nextGreaterElements) {
//        cout << element << ", ";
//    }
//    return 0;
//}

//----------------------------------------------//
// 496. Next Greater Element I
// Brute Force Approach
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    // Stores the next greater element for each element in nums1.
    vector<int> nextGreaterElements;
    // Iterate through every element of nums1.
    for (int nums1Index = 0; nums1Index < nums1.size(); nums1Index++) {
        // Current element for which we need to find the next greater element.
        int targetElement = nums1[nums1Index];
        // Indicates whether the target element has been found in nums2.
        // 0 = Not found, 1 = Found.
        int targetFound = 0;
        // Search for the target element in nums2.
        for (int nums2Index = 0; nums2Index < nums2.size(); nums2Index++) {
            // Check whether the current element in nums2 matches the target.
            if (nums2[nums2Index] == targetElement) {
                // Mark the target element as found.
                targetFound = 1;
                // Skip the current iteration because we need to find
                // a greater element AFTER the target element.
                continue;
            }
            // Once the target is found, look for the first element
            // that is greater than the target element.
            if (targetFound && nums2[nums2Index] > targetElement) {
                // Store the next greater element.
                nextGreaterElements.push_back(nums2[nums2Index]);
                // Stop searching because we need the first greater element.
                break;
            }
        }
        // If no next greater element was added for the current target,
        // insert -1.
        if (nums1Index + 1 != nextGreaterElements.size()) {
            nextGreaterElements.push_back(-1);
        }
    }
    // Return the next greater elements corresponding to nums1.
    return nextGreaterElements;
}

//----------------------------------------------//
// 496. Next Greater Element I
vector<int> nextGreaterElement01(vector<int>& nums1, vector<int>& nums2) {
    // Stores the next greater element for each element in nums2.
    vector<int> result;
    // Maintains elements in decreasing order (from bottom to top).
    // Helps us efficiently find the next greater element.
    stack<int> decreasingStack;
    // Maps each element of nums2 to its next greater element.
    // If no greater element exists, we store -1.
    unordered_map<int, int> nextGreaterMap;
    // PHASE 1: Find the next greater element for every element in nums2.
    // Traverse nums2 from right to left because we need to find
    // the next greater element on the right side of each element.
    for (int currentIndex = nums2.size() - 1; currentIndex >= 0; currentIndex--) {
        // Remove all elements that are smaller than or equal to
        // the current element because they cannot be its next greater element.
        while (!decreasingStack.empty() && decreasingStack.top() <= nums2[currentIndex]) {
            decreasingStack.pop();
        }
        // If the stack is not empty, its top element is the
        // nearest greater element on the right side.
        if (!decreasingStack.empty()) {
            nextGreaterMap.insert(pair<int, int>{nums2[currentIndex], decreasingStack.top()});
        }
        // If the stack is empty, no greater element exists on the right.
        else {
            nextGreaterMap.insert(pair<int, int>{nums2[currentIndex], -1});
        }
        // Push the current element into the stack so that it can
        // act as a potential next greater element for elements
        // appearing before it in nums2.
        decreasingStack.push(nums2[currentIndex]);
    }
    // PHASE 2: Build the result for nums1 using the map.
    // Each element in nums1 is guaranteed to exist in nums2.
    for (int currentIndex = 0; currentIndex < nums1.size(); currentIndex++) {
        // Look up the precomputed next greater element of the
        // current nums1 element and add it to the result.
        result.push_back(nextGreaterMap[nums1[currentIndex]]);
    }
    // Return the next greater elements corresponding to nums1.
    return result;
}

//int main(){
//    vector<int> nums1 = {4, 1, 2};
//    vector<int> nums2 = {1, 3, 4, 2};
//    vector<int> result = nextGreaterElement01(nums1, nums2);
//    for(auto element : result){
//        cout << element << ", ";
//    }
//    return 0;
//}

//----------------------------------------------//----------------------------------------------//
