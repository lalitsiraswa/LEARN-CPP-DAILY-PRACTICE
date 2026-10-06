#include<iostream>
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

//int main(){
////    vector<int> nums = {100, 4, 200, 1, 3, 2};
//    vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
////    cout << longestConsecutive(nums) << endl;
//    cout << longestConsecutive02(nums) << endl;
//    for(auto item : nums){
//        cout << item << " ";
//    }
//    cout << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//

