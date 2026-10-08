#include<iostream>
#include<unordered_set>
using namespace std;

//-------------------------------------------//-------------------------------------------//
// 1. Two Sum
vector<int> twoSum01(vector<int>& nums, int target) {
    unordered_map<int, int> visited;
    for(int i = 0; i < nums.size(); i++){
        int required = target - nums[i];
        if(visited.count(required)){
            return {i, visited[required]};
        }
        visited[nums[i]] = i;
    }
    return {};
}

//int main(){
//    vector<int> nums = {1, 3, 5, -7, 6, -3};
//    vector<int> result = twoSum01(nums, 0);
//    cout << result[0] << ", " << result[1] << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 128. Longest Consecutive Sequence
// Time Limit Exceeded
int longestConsecutiveQuickSortFindPivot(vector<int> &nums, int low, int high){
    int pivot = nums[low];
    int left = low;
    int right = high;
    while(left < right){
        while(nums[left] <= pivot && left < high){
            left++;
        }
        while(nums[right] > pivot && right > low){
            right--;
        }
        if(left < right){
            swap(nums[left], nums[right]);
        }
    }
    swap(nums[low], nums[right]);
    return right;
}
void longestConsecutiveQuickSort(vector<int> &nums, int low, int high){
    if(low >= high){
        return;
    }
    int pivotIndex = longestConsecutiveQuickSortFindPivot(nums, low, high);
    longestConsecutiveQuickSort(nums, low, pivotIndex - 1);
    longestConsecutiveQuickSort(nums, pivotIndex + 1, high);
}

int longestConsecutive(vector<int>& nums) {
    if(nums.size() == 0){
        return 0;
    }
    int n = nums.size();
    longestConsecutiveQuickSort(nums, 0, n - 1);
    int ans = 1;
    int currentAns = 1;
    for(int i = 0; i < n - 1; i++){
        if(nums[i + 1] == nums[i]){
            continue;
        }
        if(nums[i + 1] == nums[i] + 1){
            currentAns += 1;
        }
        else{
            currentAns = 1;
        }
        ans = max(currentAns, ans);
    }
    return ans;
}
//-------------------------------------------//
int longestConsecutive01(vector<int>& nums) {
    // Hash map used as a set of numbers.
    //
    // The key = number from the array
    // The value = index where it appeared
    //
    // We don't actually need the index.
    // We only use the map to quickly check:
    // "Does this number exist?"
    unordered_map<int, int> visited;
    // Stores the length of the longest
    // consecutive sequence found so far.
    int longestConsecutiveSequenceCount = 0;
    int n = nums.size();
    // Store all numbers in the hash map.
    //
    // Duplicate numbers will simply overwrite
    // the previous value, which is fine because
    // we only care whether the number exists.
    for (int i = 0; i < n; i++) {
        visited[nums[i]] = i;
    }
    // Iterate through every UNIQUE number in the map.
    //
    // item.first  -> the number
    // item.second -> its stored value (index)
    for (auto item : visited) {
        // Get the actual number.
        int target = item.first;
        // We only start counting if 'target' is the
        // FIRST number of a consecutive sequence.
        //
        // For example:
        //
        // [1, 2, 3, 4]
        //
        // 1 -> start counting because 0 doesn't exist.
        // 2 -> skip because 1 exists.
        // 3 -> skip because 2 exists.
        // 4 -> skip because 3 exists.
        //
        // This prevents us from checking the same
        // sequence multiple times.
        if (!visited.count(target - 1)) {
            // Length of the current consecutive sequence.
            int currentConsecutiveSequenceCount = 0;
            // Start from 'target' and keep looking
            // for the next consecutive number.
            //
            // Example:
            //
            // target = 1
            //
            // 1 -> 2 -> 3 -> 4 -> 5
            while (visited.count(target)) {
                currentConsecutiveSequenceCount++;
                // Move to the next consecutive number.
                target++;
            }
            // Update the longest sequence found so far.
            longestConsecutiveSequenceCount = max(longestConsecutiveSequenceCount, currentConsecutiveSequenceCount);
        }
    }
    return longestConsecutiveSequenceCount;
}

//-------------------------------------------//
int longestConsecutive02(vector<int>& nums) {
    // Hash map used to quickly check whether
    // a particular number exists in the array.
    //
    // Key   -> number
    // Value -> index where the number appeared
    //
    // We don't actually use the index.
    // We only care whether a number exists.
    unordered_map<int, int> visited;
    // Stores the length of the longest
    // consecutive sequence found so far.
    int longestConsecutiveSequenceCount = 0;
    int n = nums.size();
    // Store all numbers in the hash map.
    //
    // Duplicate values will overwrite the previous
    // value, which is fine because we only care
    // about whether the number exists.
    for (int i = 0; i < n; i++) {
        visited[nums[i]] = i;
    }
    // Iterate through every UNIQUE number in the map.
    for (auto item : visited) {
        // item.first contains the actual number.
        int target = item.first;
        // Since we are moving BACKWARD using target--,
        // we want to start from the LARGEST number
        // in a consecutive sequence.
        //
        // Example:
        //
        // [1, 2, 3, 4]
        //
        // 1 -> skip because 2 exists.
        // 2 -> skip because 3 exists.
        // 3 -> skip because 4 exists.
        // 4 -> start because 5 does not exist.
        //
        // Therefore, we check target + 1.
        if (!visited.count(target + 1)) {
            // Stores the length of the current
            // consecutive sequence.
            int currentConsecutiveSequenceCount = 0;
            // Move backward through the consecutive numbers.
            //
            // Example:
            //
            // target = 4
            //
            // 4 -> 3 -> 2 -> 1
            while (visited.count(target)) {
                currentConsecutiveSequenceCount++;
                // Look for the previous consecutive number.
                target--;
            }

            // Update the longest sequence if
            // the current sequence is longer.
            longestConsecutiveSequenceCount = max(longestConsecutiveSequenceCount, currentConsecutiveSequenceCount);
        }
    }
    return longestConsecutiveSequenceCount;
}

//-------------------------------------------//
// Time Limit Exceeded
int longestConsecutiveBrute(vector<int> &nums){
    int n = nums.size();
    int longestConsecutiveSequenceCount = 0;
    for(int i = 0; i < n; i++){
        int currentConsecutiveSequenceCount = 0;
        int target = nums[i];
        int j = 0;
        while(j < n){
            if(nums[j] == target){
                currentConsecutiveSequenceCount++;
                target++;
                j = 0;
            }
            else{
                j++;
            }
        }
        longestConsecutiveSequenceCount = max(longestConsecutiveSequenceCount, currentConsecutiveSequenceCount);
    }
    return longestConsecutiveSequenceCount;
}
//-------------------------------------------//
int longestConsecutiveUsingSet(vector<int> &nums) {
    // Store every number in a set.
    // unordered_set automatically removes duplicates.
    unordered_set<int> unorderedSet;
    for (auto item : nums) {
        unorderedSet.insert(item);
    }
    int longestConsecutiveSequenceCount = 0;
    // Iterate through every unique number.
    for (auto item : unorderedSet) {
        int target = item;
        int currentConsecutiveSequenceCount = 0;
        // Start counting only if this is the FIRST number
        // of a consecutive sequence.
        //
        // Example:
        // For [1, 2, 3, 4]
        //
        // 1 -> 0 does not exist -> START
        // 2 -> 1 exists       -> SKIP
        // 3 -> 2 exists       -> SKIP
        // 4 -> 3 exists       -> SKIP
        if (unorderedSet.find(target - 1) == unorderedSet.end()) {
            // We found the beginning of a sequence.
            // Keep moving forward while the next number exists.
            while (unorderedSet.find(target) != unorderedSet.end()) {
                currentConsecutiveSequenceCount++;
                target++;
            }
            // Keep track of the longest sequence found so far.
            longestConsecutiveSequenceCount = max(longestConsecutiveSequenceCount, currentConsecutiveSequenceCount);
        }
    }
    return longestConsecutiveSequenceCount;
}

//int main(){
////    vector<int> nums = {100, 4, 200, 1, 3, 2};
//    vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
////    vector<int> nums = {0, -1};
////    cout << longestConsecutive(nums) << endl;
//    cout << longestConsecutiveUsingSet(nums) << endl;
//    for(auto item : nums){
//        cout << item << " ";
//    }
//    cout << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// Longest Subarray with Sum K - GFG
int longestSubarray(vector<int>& arr, int k) {
    int n = arr.size();
    int longestSubarrayLength = 0;
    for(int i = 0; i < n; i++){
        int currentSubarrayLength = 0;
        int total = 0;
        for(int j = i; j < n; j++){
            total += arr[j];
            currentSubarrayLength++;
            if(total == k){
                longestSubarrayLength = max(longestSubarrayLength, currentSubarrayLength);
            }
        }
    }
    return longestSubarrayLength;
}

//-------------------------------------------//
// Longest Subarray with Sum K - [Containing +VE And -VE Integers]
// Longest Subarray with Sum K
// Works when array contains +ve, -ve, and 0
int longestSubarray01(vector<int>& arr, int k) {
    int n = arr.size();
    // Stores:
    // prefix sum -> first index where this prefix sum occurred
    //
    // We store the FIRST occurrence because an earlier index
    // gives us the longest possible subarray.
    unordered_map<int, int> prefixSumMap;
    int longestSubarrayLength = 0;
    // Sum of elements from index 0 to current index
    int prefixSum = 0;
    for (int i = 0; i < n; i++) {
        // Add current element to prefix sum
        prefixSum += arr[i];
        // --------------------------------------------------
        // Case 1:
        // Subarray starts from index 0
        // --------------------------------------------------
        //
        // If prefixSum == k:
        //
        // arr[0] + arr[1] + ... + arr[i] = k
        //
        // Therefore, subarray [0 ... i] has sum k.
        //
        // Its length is i + 1.
        if (prefixSum == k) {
            longestSubarrayLength = i + 1;
        }
        else {
            // --------------------------------------------------
            // Case 2:
            // Subarray starts somewhere after index 0
            // --------------------------------------------------
            //
            // Suppose:
            //
            // prefixSum = sum[0 ... i]
            //
            // We want some earlier prefix sum such that:
            //
            // prefixSum - earlierPrefixSum = k
            //
            // Therefore:
            //
            // earlierPrefixSum = prefixSum - k
            int remaining = prefixSum - k;
            // Check whether this required prefix sum
            // appeared earlier.
            if (prefixSumMap.find(remaining) != prefixSumMap.end()) {
                // Suppose the required prefix sum occurred earlier at index j.
                //
                // prefixSum = sum[0 ... i]
                // remaining/earlierPrefixSum = sum[0 ... j]
                //
                // Therefore:
                // sum[0 ... i] - sum[0 ... j] = k
                //
                // The common part sum[0 ... j] cancels out,
                // leaving:
                //
                // sum[j+1 ... i] = k
                //
                // So the subarray is from j+1 to i.
                // Length = i - j
                int length = i - prefixSumMap[remaining];
                longestSubarrayLength = max(longestSubarrayLength, length);
            }
        }
        // --------------------------------------------------
        // Store the FIRST occurrence of prefixSum
        // --------------------------------------------------
        //
        // Why only the first occurrence?
        //
        // Example:
        //
        // prefixSum = 5 occurs at index 2
        // prefixSum = 5 occurs again at index 5
        //
        // If we need this prefix sum later at index 10:
        //
        // Using index 2 -> length = 10 - 2 = 8
        // Using index 5 -> length = 10 - 5 = 5
        //
        // Earlier index gives longer subarray.
        //
        // Therefore, never overwrite the first occurrence.
        if (prefixSumMap.find(prefixSum) == prefixSumMap.end()) {
            prefixSumMap[prefixSum] = i;
        }
    }
    return longestSubarrayLength;
}

//-------------------------------------------//
// Longest Subarray with Sum K - [Containing Only +VE Integers]
int longestSubarray02(vector<int>& arr, int k) {
    int n = arr.size();
    // 'left' and 'right' represent the current window.
    //
    // Example:
    // left              right
    //   ↓                  ↓
    // [  2   1   3   2   1 ]
    //   └──── window ─────┘
    int left = 0;
    int right = 0;
    // Stores the maximum length of a subarray
    // whose sum is exactly equal to k.
    int longestSubarrayLength = 0;
    // Stores the sum of elements inside
    // the current window [left ... right].
    int totalSum = 0;
    while (right < n) {
        // Expand the window by adding the element
        // at the 'right' pointer.
        totalSum += arr[right];
        // If the sum becomes greater than k,
        // the current window is too large.
        //
        // Since all elements are POSITIVE,
        // removing an element from the left will
        // definitely decrease the sum.
        while (totalSum > k) {
            // Remove the leftmost element
            // from the current window.
            totalSum -= arr[left];
            // Move left forward to shrink the window.
            left++;
        }
        // At this point:
        //
        // totalSum <= k
        //
        // If totalSum == k, then the current window
        // [left ... right] is a valid subarray.
        if (totalSum == k) {
            // Length of subarray [left ... right]:
            //
            // right - left + 1
            int currentLength = (right - left) + 1;
            // Keep the longest valid subarray found so far.
            longestSubarrayLength = max(longestSubarrayLength, currentLength);
        }
        // Move right forward to expand the window
        // in the next iteration.
        right++;
    }
    return longestSubarrayLength;
}

//int main(){
//    vector<int> arr = {10, 5, 2, 7, 1, -10};
////    vector<int> arr = {1, 2, 3, 1, 1, 1, 1, 4, 2, 3};
//    cout << longestSubarray02(arr, 15) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 560. Subarray Sum Equals K
int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    int subarrayCount = 0;
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = i; j < n; j++){
            sum += nums[j];
            if(sum == k){
                subarrayCount++;
            }
        }
    }
    return subarrayCount;
}
    
//-------------------------------------------//
// Subarray Sum Equals K
//
// Works with positive, negative, and zero values.
//
// Approach:
// Prefix Sum + Hash Map
int subarraySumTuf(vector<int>& nums, int k) {
    int n = nums.size();
    // Stores:
    // prefix sum -> how many times that prefix sum has appeared
    //
    // We store the frequency because the same prefix sum
    // can appear multiple times, and each occurrence can
    // represent a different valid subarray.
    unordered_map<int, int> prefixSumMap;
    int subarrayCount = 0;
    // Sum of elements from index 0 to the current index.
    int prefixSum = 0;
    for (int i = 0; i < n; i++) {
        // Add the current element to the prefix sum.
        prefixSum += nums[i];
        // --------------------------------------------------
        // Check if the subarray [0 ... i] has sum K.
        // --------------------------------------------------
        //
        // If prefixSum == k:
        //
        // nums[0] + nums[1] + ... + nums[i] = k
        //
        // So [0 ... i] is one valid subarray.
        //
        // This is an INDEPENDENT check.
        // Do NOT use else here because the next check
        // can also find another valid subarray at the
        // same index.
        if (prefixSum == k) {
            subarrayCount++;
        }
        // --------------------------------------------------
        // Check if there are previous prefix sums that
        // can form another subarray with sum K.
        // --------------------------------------------------
        //
        // We know:
        //
        // currentPrefixSum - previousPrefixSum = K
        //
        // Therefore:
        //
        // previousPrefixSum = currentPrefixSum - K
        //
        // So we look for:
        //
        // prefixSum - k
        int remaining = prefixSum - k;
        // If 'remaining' appeared before, then each occurrence
        // gives us one subarray ending at index i with sum K.
        //
        // We add the frequency because the same prefix sum
        // may have appeared multiple times.
        subarrayCount += prefixSumMap[remaining];
        // Store the current prefix sum for future elements.
        //
        // If this prefix sum already exists, increase its
        // frequency.
        prefixSumMap[prefixSum]++;
    }
    return subarrayCount;
}

//int main(){
////    vector<int> nums = {1, 1, 1};
////    vector<int> nums = {1, -1, 0};
//    vector<int> nums = {1, 2, 3, -3, 1, 1, 1, 4, 2, -3};
//    cout << subarraySumTuf(nums, 3) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
