#include<iostream>
using namespace std;

//----------------------------------------------//----------------------------------------------//
// 1. Next Greater Element (NGE)
vector<int> nextGreaterElement(vector<int>& nums) {
    // Maintains elements in decreasing order.
    stack<int> decreasingStack;
    // Store the size of the input array.
    int arraySize = nums.size();
    // Initialize all positions with -1.
    // -1 means no next greater element exists.
    vector<int> nextGreaterElements(arraySize, -1);
    // Traverse from right to left to find greater elements
    // on the right side of each current element.
    for (int currentIndex = arraySize - 1; currentIndex >= 0; currentIndex--) {
        // Remove all elements smaller than or equal to
        // the current element.
        while (!decreasingStack.empty() && decreasingStack.top() <= nums[currentIndex]) {
            decreasingStack.pop();
        }
        // The stack top is the nearest greater element
        // on the right side, if the stack is not empty.
        if (!decreasingStack.empty()) {
            nextGreaterElements[currentIndex] = decreasingStack.top();
        }
        // Push the current element for future comparisons.
        decreasingStack.push(nums[currentIndex]);
    }
    return nextGreaterElements;
}

//----------------------------------------------//
// 2. Next Smaller Element (NSE)
vector<int> nextSmallerElement(vector<int>& nums) {
    // Maintains elements in increasing order.
    stack<int> increasingStack;
    // Store the size of the input array.
    int arraySize = nums.size();
    // Initialize all positions with -1.
    vector<int> nextSmallerElements(arraySize, -1);
    // Traverse from right to left to find smaller elements
    // on the right side of each current element.
    for (int currentIndex = arraySize - 1; currentIndex >= 0; currentIndex--) {
        // Remove all elements greater than or equal to
        // the current element.
        while (!increasingStack.empty() && increasingStack.top() >= nums[currentIndex]) {
            increasingStack.pop();
        }
        // The stack top is the nearest smaller element
        // on the right side, if the stack is not empty.
        if (!increasingStack.empty()) {
            nextSmallerElements[currentIndex] = increasingStack.top();
        }
        // Push the current element for future comparisons.
        increasingStack.push(nums[currentIndex]);
    }
    return nextSmallerElements;
}
//----------------------------------------------//
// 3. Previous Smaller Element (PSE)
vector<int> previousSmallerElement(vector<int>& nums) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Initialize all positions with -1.
    vector<int> previousSmallerElements(arraySize, -1);
    // Maintains elements in increasing order.
    stack<int> increasingStack;
    // Traverse from left to right to find smaller elements
    // on the left side of each current element.
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Remove all elements greater than or equal to
        // the current element.
        while (!increasingStack.empty() && increasingStack.top() >= nums[currentIndex]) {
            increasingStack.pop();
        }
        // The stack top is the nearest smaller element
        // on the left side, if the stack is not empty.
        if (!increasingStack.empty()) {
            previousSmallerElements[currentIndex] = increasingStack.top();
        }
        // Push the current element for future comparisons.
        increasingStack.push(nums[currentIndex]);
    }
    return previousSmallerElements;
}
//----------------------------------------------//
// 4. Previous Greater Element (PGE)
vector<int> previousGreaterElement(vector<int>& nums) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Initialize all positions with -1.
    vector<int> previousGreaterElements(arraySize, -1);
    // Maintains elements in decreasing order.
    stack<int> decreasingStack;
    // Traverse from left to right to find greater elements
    // on the left side of each current element.
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Remove all elements smaller than or equal to
        // the current element.
        while (!decreasingStack.empty() && decreasingStack.top() <= nums[currentIndex]) {
            decreasingStack.pop();
        }
        // The stack top is the nearest greater element
        // on the left side, if the stack is not empty.
        if (!decreasingStack.empty()) {
            previousGreaterElements[currentIndex] = decreasingStack.top();
        }
        // Push the current element for future comparisons.
        decreasingStack.push(nums[currentIndex]);
    }
    return previousGreaterElements;
}

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
// 503. Next Greater Element II
vector<int> nextGreaterElements(vector<int>& nums) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Initialize the result array with -1.
    // -1 indicates that no next greater element has been found.
    vector<int> result(arraySize, -1);
    // PHASE 1: Find the next greater element for each array element.
    // Traverse every element of the array.
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Start searching from the next element.
        // Continue for at most arraySize - 1 elements.
        // This allows us to circularly traverse the array.
        for (int nextIndex = currentIndex + 1; nextIndex < currentIndex + arraySize; nextIndex++) {
            // Use modulo (%) to wrap around to the beginning
            // when nextIndex reaches the end of the array.
            //
            // Example:
            // nums = {1, 2, 3}
            // If nextIndex = 3, then 3 % 3 = 0.
            // So, we access nums[0].
            int circularIndex = nextIndex % arraySize;
            // Check whether the current element is smaller
            // than the element found during circular traversal.
            if (nums[circularIndex] > nums[currentIndex]) {
                // Store the first greater element found.
                // Since we are traversing from left to right,
                // this is the next greater element.
                result[currentIndex] = nums[circularIndex];
                // Stop searching because we have found
                // the next greater element for this position.
                break;
            }
        }
    }
    // Return the next greater element for every array position.
    return result;
}

//----------------------------------------------//
vector<int> nextGreaterElements01(vector<int>& nums) {
    // Maintains elements in decreasing order (from bottom to top).
    // Helps us efficiently find the next greater element.
    stack<int> decreasingStack;
    // Store the size of the input array.
    int arraySize = nums.size();
    // Initialize the result array with -1.
    // -1 indicates that no next greater element has been found.
    vector<int> result(arraySize, -1);
    // PHASE 1: Push all array elements into the stack.
    // Traverse the array from right to left.
    //
    // This initial traversal simulates the circular nature
    // of the array by making elements from the end available
    // while searching for greater elements.
    for (int currentIndex = arraySize - 1; currentIndex >= 0; currentIndex--) {
        decreasingStack.push(nums[currentIndex]);
    }
    // PHASE 2: Find the next greater element for every position.
    // Traverse the array again from right to left.
    for (int currentIndex = arraySize - 1; currentIndex >= 0; currentIndex--) {
        // Remove all elements that are smaller than or equal to
        // the current element because they cannot be its next
        // greater element.
        while (!decreasingStack.empty() && decreasingStack.top() <= nums[currentIndex]) {
            decreasingStack.pop();
        }
        // If the stack is not empty, its top element is the
        // next greater element for the current position.
        if (!decreasingStack.empty()) {
            result[currentIndex] = decreasingStack.top();
        }
        // Push the current element into the stack so that it
        // can be considered as a potential next greater element
        // for the elements appearing before it.
        decreasingStack.push(nums[currentIndex]);
    }
    // Return the next greater element for every array position.
    return result;
}

//----------------------------------------------//
vector<int> nextGreaterElements02(vector<int>& nums) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Initialize the result array with -1.
    // -1 indicates that no next greater element has been found.
    vector<int> result(arraySize, -1);
    // Maintains potential next greater elements in a decreasing stack.
    stack<int> decreasingStack;
    // PHASE 1: Traverse the array twice from right to left.
    //
    // We traverse 2 * arraySize elements to simulate circular traversal.
    // The second traversal allows elements at the beginning of the array
    // to act as potential next greater elements for elements near the end.
    for (int currentIndex = (arraySize * 2) - 1; currentIndex >= 0; currentIndex--) {
        // Use modulo (%) to get the actual array index.
        // This ensures that indices wrap around to the beginning
        // when currentIndex exceeds the last valid array index.
        //
        // Example:
        // nums = {1, 2, 3}
        // currentIndex = 4
        // circularIndex = 4 % 3 = 1
        // Therefore, we access nums[1].
        int circularIndex = currentIndex % arraySize;
        // Remove all elements that are smaller than or equal to
        // the current element.
        //
        // These elements cannot be the next greater element because:
        // 1. They are smaller than or equal to the current element.
        // 2. The current element is closer to the elements being processed.
        while (!decreasingStack.empty() && decreasingStack.top() <= nums[circularIndex]) {
            decreasingStack.pop();
        }
        // Only update the result during the second traversal
        // of the array (currentIndex < arraySize).
        //
        // During the first traversal, we only prepare the stack
        // with potential next greater elements.
        if (currentIndex < arraySize && !decreasingStack.empty()) {
            result[circularIndex] = decreasingStack.top();
        }
        // Push the current element into the stack so that it can
        // act as a potential next greater element for elements
        // appearing before it in the circular traversal.
        decreasingStack.push(nums[circularIndex]);
    }
    // Return the next greater element for every array position.
    return result;
}

//int main(){
//    vector<int> nums = {2, 6, 9, 8, 7, 5, 3, 1, 4};
//    vector<int> result = nextGreaterElements02(nums);
//    for(auto element : result){
//        cout << element << ", ";
//    }
//    return 0;
//}

//----------------------------------------------//----------------------------------------------//
// 901. Online Stock Span
// previousDaysFrequency.insert(pair<int, int>{price, daysCount}); vs previousDaysFrequency[price] = daysCount;

// previousDaysFrequency.insert(pair<int, int>{price, daysCount});
// Inserts a new key-value pair if the key does not exist.
// If the key already exists, it does not update or overwrite the existing value.
// The existing value remains unchanged.

// previousDaysFrequency[price] = daysCount;
// Inserts a new key-value pair if the key does not exist.
// If the key already exists, it updates/overwrites the existing value.

// 901. Online Stock Span
class StockSpanner {
public:
    // Stores stock prices in decreasing order.
    // Each element represents a previous stock price.
    stack<int> decreasingStack;
    // Stores the stock span associated with each stock price.
    // Key   = Stock price
    // Value = Number of consecutive days for which this price
    //         is greater than or equal to previous prices.
    unordered_map<int, int> priceSpanMap;
    // Constructor
    StockSpanner() {}
    int next(int price) {
        // Every stock price has a minimum span of 1,
        // because the current day itself is always included.
        int currentSpan = 1;
        // Remove all previous stock prices that are smaller than
        // or equal to the current price.
        //
        // Their spans can be combined with the current span because
        // the current price is greater than or equal to them.
        while (!decreasingStack.empty() && decreasingStack.top() <= price) {
            // Add the span of the previous stock price.
            // This allows us to skip multiple previous days at once.
            currentSpan += priceSpanMap[decreasingStack.top()];
            // Reset the previous price's span because its contribution
            // has already been included in the current span.
            priceSpanMap[decreasingStack.top()] = 0;
            // Remove the previous stock price from the stack.
            decreasingStack.pop();
        }
        // Push the current stock price into the stack.
        // It becomes a potential previous greater price
        // for future stock prices.
        decreasingStack.push(price);
        // Store the calculated span for the current stock price.
        priceSpanMap[price] = currentSpan;
        // Return the number of consecutive days for which
        // the stock price was less than or equal to today's price.
        return currentSpan;
    }
};

//int main(){
//    StockSpanner stockSpanner = StockSpanner();
//    vector<int> prices = {51, 35, 75, 20, 71, 38, 17, 38, 21, 47};
//    for(auto price : prices){
//        cout << stockSpanner.next(price) << " ";
//    }
//    return 0;
//}

//----------------------------------------------//----------------------------------------------//
// 907. Sum of Subarray Minimums
// Time Limit Exceeded
// const int MOD = 1e9 + 7;
// const int MOD = 1000000007;
// Brute Force Approach - Time Limit Exceeded
int sumSubarrayMins(vector<int>& nums) {
    // Define modulo to prevent the result from exceeding integer limits.
    const int MOD = 1000000007;
    // Store the size of the input array.
    int arraySize = nums.size();
    // Stores the sum of minimum elements of all possible subarrays.
    long long subarraysMinimumSum = 0;
    // PHASE 1: Consider every element as the starting point
    // of a subarray.
    for (int startIndex = 0; startIndex < arraySize; startIndex++) {
        // Initially, the current element itself is the minimum.
        // This represents a subarray containing only one element.
        int currentSubarrayMinimum = nums[startIndex];
        // Add the minimum of the single-element subarray.
        subarraysMinimumSum += currentSubarrayMinimum;
        // PHASE 2: Extend the subarray by moving the ending index.
        for (int endIndex = startIndex + 1; endIndex < arraySize; endIndex++) {
            // Update the minimum element of the current subarray.
            // Compare the previous minimum with the newly added element.
            currentSubarrayMinimum = min(currentSubarrayMinimum, nums[endIndex]);
            // Add the minimum of the current subarray to the total sum.
            subarraysMinimumSum += currentSubarrayMinimum;
        }
    }
    // Return the final sum modulo 10^9 + 7.
    return subarraysMinimumSum % MOD;
}

//----------------------------------------------//
// Helper function to find the index of the Next Smaller Element (NSE)
// for every element in the array.
//
// NSE[i] stores the index of the first element to the right of i
// that is smaller than nums[i].
//
// If no smaller element exists, NSE[i] stores n.
vector<int> nextSmallerElementHelper(vector<int>& nums) {
    // Monotonic increasing stack storing array indices.
    stack<int> increasingStack;
    int arraySize = nums.size();
    // Initially, assume no smaller element exists on the right.
    vector<int> nextSmallerIndices(arraySize, arraySize);
    // Traverse from right to left to find the next smaller element.
    for (int currentIndex = arraySize - 1; currentIndex >= 0; currentIndex--) {
        // Remove all elements that are greater than the current element.
        // They cannot be the next smaller element for the current index.
        while (!increasingStack.empty() && nums[increasingStack.top()] > nums[currentIndex]) {
            increasingStack.pop();
        }
        // If the stack is not empty, its top contains the index
        // of the next smaller element.
        if (!increasingStack.empty()) {
            nextSmallerIndices[currentIndex] = increasingStack.top();
        }
        // Push the current index for processing future elements.
        increasingStack.push(currentIndex);
    }
    return nextSmallerIndices;
}

// Helper function to find the index of the Previous Smaller Element (PSE)
// for every element in the array.
//
// PSE[i] stores the index of the first element to the left of i
// that is smaller than nums[i].
//
// If no smaller element exists, PSE[i] stores -1.
vector<int> previousSmallerElementHelper(vector<int>& nums) {
    int arraySize = nums.size();
    // Initially, assume no smaller element exists on the left.
    vector<int> previousSmallerIndices(arraySize, -1);
    // Monotonic increasing stack storing array indices.
    stack<int> increasingStack;
    // Traverse from left to right to find the previous smaller element.
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Remove elements that are greater than or equal to the current element.
        // They cannot be the previous smaller element for the current index.
        while (!increasingStack.empty() && nums[increasingStack.top()] >= nums[currentIndex]) {
            increasingStack.pop();
        }
        // If the stack is not empty, its top contains the index
        // of the previous smaller element.
        if (!increasingStack.empty()) {
            previousSmallerIndices[currentIndex] = increasingStack.top();
        }
        // Push the current index for processing future elements.
        increasingStack.push(currentIndex);
    }
    return previousSmallerIndices;
}

// Function to calculate the sum of minimum elements
// of all possible subarrays.
// left * right tells us HOW MANY subarrays have the current element as their minimum.
// nums[i] tells us WHAT VALUE that minimum contributes.
// Multiplying both gives us the TOTAL CONTRIBUTION of that element.
// Contribution = left * right * nums[i]
int sumSubarrayMins01(vector<int>& nums) {
    // Find the index of the Next Smaller Element for every element.
    vector<int> nextSmallerIndices = nextSmallerElementHelper(nums);
    for(auto item : nextSmallerIndices){
        cout << item << " ";
    }
    cout << endl;
    // Find the index of the Previous Smaller Element for every element.
    vector<int> previousSmallerIndices = previousSmallerElementHelper(nums);
    for(auto item : previousSmallerIndices){
        cout << item << " ";
    }
    cout << endl;
    int arraySize = nums.size();
    // Modulo value to prevent integer overflow in the final result.
    int mod = 1e9 + 7;
    int sumOfSubarrayMinimums = 0;
    // Calculate the contribution of every element to the final answer.
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Number of possible starting positions for subarrays
        // in which the current element can be the minimum.
        int leftSubarrayCount = currentIndex - previousSmallerIndices[currentIndex];
        // Number of possible ending positions for subarrays
        // in which the current element can be the minimum.
        int rightSubarrayCount = nextSmallerIndices[currentIndex] - currentIndex;
        // Total number of subarrays in which the current element
        // contributes as the minimum element.
        long long subarrayFrequency = leftSubarrayCount * rightSubarrayCount * 1LL;
        // Contribution of the current element to the final answer.
        int currentContribution = (subarrayFrequency * nums[currentIndex] * 1LL) % mod;
        // Add the current contribution to the final sum.
        sumOfSubarrayMinimums = (sumOfSubarrayMinimums + currentContribution) % mod;
    }
    return sumOfSubarrayMinimums;
}

//int main(){
//    vector<int> nums = {1, 4, 6, 7, 3, 7, 8, 1};
//    for(auto item : nums){
//        cout << item << " ";
//    }
//    cout << endl;
//    cout << sumSubarrayMins01(nums);
//    
//    return 0;
//}

//----------------------------------------------//----------------------------------------------//
// 2104. Sum of Subarray Ranges
long long subArrayRanges(vector<int>& nums) {
    int arraySize = nums.size();
    // Stores the sum of ranges of all possible subarrays.
    long long totalSubarrayRanges = 0;
    // Generate all possible subarrays by fixing the starting index.
    for (int startIndex = 0; startIndex < arraySize; startIndex++) {
        // Initially, the current element is both the minimum and maximum.
        int minimumElement = nums[startIndex];
        int maximumElement = nums[startIndex];
        // For a subarray containing only one element,
        // maximum - minimum = 0.
        totalSubarrayRanges += (maximumElement - minimumElement);
        // Expand the subarray by moving the ending index.
        for (int endIndex = startIndex + 1; endIndex < arraySize; endIndex++) {
            // Update the minimum element in the current subarray.
            minimumElement = min(minimumElement, nums[endIndex]);
            // Update the maximum element in the current subarray.
            maximumElement = max(maximumElement, nums[endIndex]);
            // Range of the current subarray = Maximum - Minimum.
            totalSubarrayRanges += (maximumElement - minimumElement);
        }
    }
    return totalSubarrayRanges;
}

//----------------------------------------------//
// Helper function to find the Previous Smaller Element (PSE).
// Returns the index of the nearest smaller element on the left.
// If no smaller element exists, stores -1.
vector<int> findPreviousSmallerElement(vector<int>& nums) {
    int arraySize = nums.size();
    // Stores the index of the previous smaller element for every index.
    vector<int> previousSmallerIndices(arraySize, -1);
    // Monotonic increasing stack storing array indices.
    stack<int> increasingStack;
    // Traverse from left to right.
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Remove elements greater than or equal to the current element.
        // They cannot be the previous strictly smaller element.
        while (!increasingStack.empty() && nums[increasingStack.top()] >= nums[currentIndex]) {
            increasingStack.pop();
        }
        // The stack top contains the index of the previous smaller element.
        if (!increasingStack.empty()) {
            previousSmallerIndices[currentIndex] = increasingStack.top();
        }
        // Push the current index for future elements.
        increasingStack.push(currentIndex);
    }
    return previousSmallerIndices;
}

// Helper function to find the Next Smaller Element (NSE).
// Returns the index of the nearest smaller element on the right.
// If no smaller element exists, stores arraySize.
vector<int> findNextSmallerElement(vector<int>& nums) {
    // Monotonic increasing stack storing array indices.
    stack<int> increasingStack;
    int arraySize = nums.size();
    // Stores the index of the next smaller element for every index.
    vector<int> nextSmallerIndices(arraySize, arraySize);
    // Traverse from right to left.
    for (int currentIndex = arraySize - 1; currentIndex >= 0; currentIndex--) {
        // Remove elements strictly greater than the current element.
        // They cannot be the next smaller or equal element.
        while (!increasingStack.empty() && nums[increasingStack.top()] > nums[currentIndex]) {
            increasingStack.pop();
        }
        // The stack top contains the index of the next smaller or equal element.
        if (!increasingStack.empty()) {
            nextSmallerIndices[currentIndex] = increasingStack.top();
        }
        // Push the current index for future elements.
        increasingStack.push(currentIndex);
    }
    return nextSmallerIndices;
}

// Helper function to find the Previous Greater Element (PGE).
// Returns the index of the nearest greater element on the left.
// If no greater element exists, stores -1.
vector<int> findPreviousGreaterElement(vector<int>& nums) {
    int arraySize = nums.size();
    // Stores the index of the previous greater element for every index.
    vector<int> previousGreaterIndices(arraySize, -1);
    // Monotonic decreasing stack storing array indices.
    stack<int> decreasingStack;
    // Traverse from left to right.
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Remove elements smaller than or equal to the current element.
        // They cannot be the previous strictly greater element.
        while (!decreasingStack.empty() && nums[decreasingStack.top()] <= nums[currentIndex]) {
            decreasingStack.pop();
        }
        // The stack top contains the index of the previous greater element.
        if (!decreasingStack.empty()) {
            previousGreaterIndices[currentIndex] = decreasingStack.top();
        }
        // Push the current index for future elements.
        decreasingStack.push(currentIndex);
    }
    return previousGreaterIndices;
}

// Helper function to find the Next Greater Element (NGE).
// Returns the index of the nearest greater element on the right.
// If no greater element exists, stores arraySize.
vector<int> findNextGreaterElement(vector<int>& nums) {
    // Monotonic decreasing stack storing array indices.
    stack<int> decreasingStack;
    int arraySize = nums.size();
    // Stores the index of the next greater element for every index.
    vector<int> nextGreaterIndices(arraySize, arraySize);
    // Traverse from right to left.
    for (int currentIndex = arraySize - 1; currentIndex >= 0; currentIndex--) {
        // Remove elements strictly smaller than the current element.
        // They cannot be the next greater or equal element.
        while (!decreasingStack.empty() && nums[decreasingStack.top()] < nums[currentIndex]) {
            decreasingStack.pop();
        }
        // The stack top contains the index of the next greater or equal element.
        if (!decreasingStack.empty()) {
            nextGreaterIndices[currentIndex] = decreasingStack.top();
        }
        // Push the current index for future elements.
        decreasingStack.push(currentIndex);
    }
    return nextGreaterIndices;
}

// 2104. Sum of Subarray Ranges
//
// Sum of Subarray Ranges = Sum of Subarray Maximums - Sum of Subarray Minimums
long long subArrayRanges01(vector<int>& nums) {
    // Find the Next Smaller Element for every array element.
    vector<int> nextSmallerIndices = findNextSmallerElement(nums);
    // Find the Previous Smaller Element for every array element.
    vector<int> previousSmallerIndices = findPreviousSmallerElement(nums);
    // Find the Next Greater Element for every array element.
    vector<int> nextGreaterIndices = findNextGreaterElement(nums);
    // Find the Previous Greater Element for every array element.
    vector<int> previousGreaterIndices = findPreviousGreaterElement(nums);
    int arraySize = nums.size();
    // PHASE 1: Calculate the sum of minimum elements
    // of all possible subarrays.
    long long sumOfSubarrayMinimums = 0;
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Number of possible starting positions for subarrays
        // where the current element is the minimum.
        long long leftSubarrayCount = currentIndex - previousSmallerIndices[currentIndex];
        // Number of possible ending positions for subarrays
        // where the current element is the minimum.
        long long rightSubarrayCount = nextSmallerIndices[currentIndex] - currentIndex;
        // Total number of subarrays where nums[currentIndex]
        // contributes as the minimum element.
        long long subarrayFrequency = leftSubarrayCount * rightSubarrayCount;
        // Calculate the total contribution of the current element.
        // Contribution = Frequency * Element Value.
        long long currentContribution = subarrayFrequency * nums[currentIndex];
        // Add the current element's contribution to the minimum sum.
        sumOfSubarrayMinimums += currentContribution;
    }
    // PHASE 2: Calculate the sum of maximum elements
    // of all possible subarrays.
    long long sumOfSubarrayMaximums = 0;
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Number of possible starting positions for subarrays
        // where the current element is the maximum.
        long long leftSubarrayCount = currentIndex - previousGreaterIndices[currentIndex];
        // Number of possible ending positions for subarrays
        // where the current element is the maximum.
        long long rightSubarrayCount = nextGreaterIndices[currentIndex] - currentIndex;
        // Total number of subarrays where nums[currentIndex]
        // contributes as the maximum element.
        long long subarrayFrequency = leftSubarrayCount * rightSubarrayCount;
        // Calculate the total contribution of the current element.
        // Contribution = Frequency * Element Value.
        long long currentContribution = subarrayFrequency * nums[currentIndex];
        // Add the current element's contribution to the maximum sum.
        sumOfSubarrayMaximums += currentContribution;
    }
    // PHASE 3: Calculate the sum of all subarray ranges.
    //
    // Range of a subarray = Maximum - Minimum.
    //
    // Therefore:
    // Sum of Subarray Ranges = Sum of Maximums - Sum of Minimums.
    return sumOfSubarrayMaximums - sumOfSubarrayMinimums;
}

//int main(){
//    vector<int> nums = {1, 4, 6, 7, 3, 7, 8, 1};
//    cout << subArrayRanges(nums) << endl;
//    return 0;
//}

//----------------------------------------------//----------------------------------------------//
