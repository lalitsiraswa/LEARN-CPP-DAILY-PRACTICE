#include<iostream>
#include<set>
using namespace std;

// 73. Set Matrix Zeroes
void setZeroesSpaceOptimized(vector<vector<int>>& matrix) {
    __SIZE_TYPE__ rowCount = matrix.size();
    __SIZE_TYPE__ columnCount = matrix[0].size();
    // int row[rowCount] = {0}; --> matrix[..][0]
    // int col[columnCount] = {0}; --> matrix[0][..]
    int col0 = 1;
    // step: 1: Traverse the matrix amd
    // mark 1st row & col accordingly:
    for (int row = 0; row < rowCount; row++)
    {
        for (int column = 0; column < columnCount; column++)
        {
            if (matrix[row][column] == 0)
            {
                // mark i-th row
                matrix[row][0] = 0;
                // mark j-th column
                if (column != 0)
                    matrix[0][column] = 0;
                else
                    col0 = 0;
            }
        }
    }

    // Step 2: Mark with 0 from (1, 1) to (rowCount-1, columnCount-1):
    for (int row = 1; row < rowCount; row++)
    {
        for (int column = 1; column < columnCount; column++)
        {
            if (matrix[row][column] != 0)
            {
                // check for row & column
                if (matrix[row][0] == 0 || matrix[0][column] == 0)
                    matrix[row][column] = 0;
            }
        }
    }
    // Step 3: Finally mark the 1st row and then 1st column:
    if (matrix[0][0] == 0)
    {
        for (int column = 0; column < columnCount; column++)
        {
            matrix[0][column] = 0;
        }
    }
    if (col0 == 0)
    {
        for (int row = 0; row < rowCount; row++)
        {
            matrix[row][0] = 0;
        }
    }
}
//-------------------------------------------
void setZeroes(vector<vector<int>>& matrix) {
    __SIZE_TYPE__ rowCount = matrix.size();
    __SIZE_TYPE__ columnCount = matrix[0].size();
    vector<int> isRowZero;
    vector<int> isColumnZero;
    for (int row = 0; row < rowCount; row++)
    {
        for (int col = 0; col < columnCount; col++)
        {
            if (matrix[row][col] == 0)
            {
                isRowZero.push_back(row);
                isColumnZero.push_back(col);
            }
        }
    }
    for (int row : isRowZero)
    {
        for (int col = 0; col < columnCount; col++)
        {
            matrix[row][col] = 0;
        }
    }
    for (int col : isColumnZero)
    {
        for (int row = 0; row < rowCount; row++)
        {
            matrix[row][col] = 0;
        }
    }
}

//int main(){
//    vector<vector<int>> matrix = {{0,1,2,0},
//                                  {3,4,5,2},
//                                  {1,3,1,5}};
//    for(vector row : matrix){
//        for(int num : row){
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//    setZeroesSpaceOptimized(matrix);
//    for(vector row : matrix){
//        for(int num : row){
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//

// 118. Pascal's Triangle
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> pascalTriangle;
    for(int row = 0; row < numRows; row++){
        vector<int> singleRow;
        for(int column = 0; column <= row; column++){
            if(column == 0 || column == row){
                singleRow.push_back(1);
            }
            else{
                singleRow.push_back(pascalTriangle[row-1][column-1] + pascalTriangle[row-1][column]);
            }
        }
        pascalTriangle.push_back(singleRow);
    }
    return pascalTriangle;
}

//int main(){
//    int numRows = 6;
//    vector<vector<int>> pascalTriangle = generate(numRows);
//    for(vector row : pascalTriangle){
//        for(int num : row){
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------
long long nCr(int n, int r){
    long long result = 1;
    for(int i = 0; i < r; i++){
        result = result * (n - i);
        result = result / (i + 1);
    }
    return result;
}

vector<int> generateRow(int row){
    vector<int> resultRow;
    long long result = 1;
    resultRow.push_back(result);
    for(int column = 0; column < row; column++){
        result = result * (row - column);
        result = result / (column + 1);
        resultRow.push_back(result);
    }
    return resultRow;
}

vector<vector<int>> generatePascalTriangle(int numRows) {
    vector<vector<int>> pascalTriangle;
    for(int row = 0; row < numRows; row++){
        pascalTriangle.push_back(generateRow(row));
    }
    return pascalTriangle;
}
//int main(){
////    vector<int> resultRow = generateRow(3);
////    for(int item : resultRow){
////        cout << item << " ";
////    }
////    cout << endl;
//    
//    vector<vector<int>> pascalTriangle = generatePascalTriangle(6);
//    for(vector<int> row : pascalTriangle){
//        for(int item : row){
//            cout << item << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 31. Next Permutation
void nextPermutation(vector<int>& nums) {
    int n = nums.size();

    // Step 1:
    // Start from the second-last element and move from RIGHT to LEFT.
    // We are looking for the first position where:
    //
    //      nums[i] < nums[i + 1]
    //
    // This position is called the "pivot".
    int pivotIndex = n - 2;

    while (pivotIndex >= 0 &&
           nums[pivotIndex] >= nums[pivotIndex + 1]) {

        pivotIndex--;
    }

    // Step 2:
    // If we could not find a pivot, the entire array is in descending order.
    //
    // Example:
    //      [3, 2, 1]
    //
    // This is already the LARGEST permutation.
    // Therefore, the next permutation is the SMALLEST permutation.
    //
    // So simply reverse the entire array:
    //      [3, 2, 1] -> [1, 2, 3]
    if (pivotIndex == -1) {
        reverse(nums.begin(), nums.end());
        return;
    }

    // Step 3:
    // We found the pivot.
    //
    // Now we need to find the smallest number that is GREATER
    // than the pivot.
    //
    // Start from the RIGHT because the elements after the pivot
    // are in descending order.
    //
    // Example:
    //      [1, 3, 5, 4, 2]
    //          ^
    //        pivot = 3
    //
    // Elements after pivot: [5, 4, 2]
    //
    // Starting from the right:
    //      2 > 3 ? No
    //      4 > 3 ? Yes -> choose 4
    int targetIndex = n - 1;

    while (nums[targetIndex] <= nums[pivotIndex]) {
        targetIndex--;
    }

    // Step 4:
    // Swap the pivot with the next larger element.
    //
    // Example:
    //      [1, 3, 5, 4, 2]
    //          ^     ^
    //          3 <-> 4
    //
    // Result:
    //      [1, 4, 5, 3, 2]
    swap(nums[pivotIndex], nums[targetIndex]);

    // Step 5:
    // Everything after the pivot is currently in DESCENDING order.
    //
    // We need the SMALLEST possible arrangement after the pivot
    // to make this the immediate next permutation.
    //
    // Therefore, reverse the suffix.
    //
    // Example:
    //      [1, 4, 5, 3, 2]
    //             -------
    //             suffix
    //
    //      [5, 3, 2] -> [2, 3, 5]
    //
    // Final:
    //      [1, 4, 2, 3, 5]
    reverse(nums.begin() + pivotIndex + 1, nums.end());
}

//int main(){
////    vector<int> nums = {3, 2, 1};
//    vector<int> nums = {1, 5, 1};
//    nextPermutation(nums);
//    for(int item : nums){
//        cout << item;
//    }
//    cout << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 53. Maximum Subarray
// Time Limit Exceeded
int maxSubArrayBruteForce(vector<int>& nums) {
    int maxSum = INT_MIN;
    int n = nums.size();
    for(int i = 0; i < n; i++){
        int totalSum = 0;
        for(int j = i; j < n; j++){
            totalSum += nums[j];
            maxSum = max(totalSum, maxSum);
        }
    }
    return maxSum;
}

int maxSubArray(vector<int>& nums) {
    int maxSum = INT_MIN;
    int totalSum = 0;
    int n = nums.size();
    for(int i = 0; i < n; i++){
        totalSum += nums[i];
        if(nums[i] > totalSum){
            totalSum = nums[i];
        }
        maxSum = max(maxSum, totalSum);
    }
    return maxSum;
}

int maxSubArrayTuf(vector<int>& nums) {
    int maxSum = INT_MIN;
    int totalSum = 0;
    int n = nums.size();
    for(int i = 0; i < n; i++){
        totalSum += nums[i];
        if(totalSum > maxSum){
            maxSum = totalSum;
        }
        if(totalSum < 0){
            totalSum = 0;
        }
    }
    return maxSum;
}

// Print subarray with maximum subarray sum (extended version of above problem)
void printMaxSubArray(vector<int>& nums) {
    int startIndex = 0;
    int endIndex = 0;
    int maxSum = INT_MIN;
    int totalSum = 0;
    int start = 0;
    for (int i = 0; i < nums.size(); i++) {
        totalSum += nums[i];
        if (nums[i] > totalSum) {
            totalSum = nums[i];
            start = i;
        }
        if (totalSum > maxSum) {
            maxSum = totalSum;
            startIndex = start;
            endIndex = i;
        }
    }
    for (int i = startIndex; i <= endIndex; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

void printMaxSubArrayTuf(vector<int>& nums) {
    int startIndex = 0;
    int endIndex = 0;
    int maxSum = INT_MIN;
    int totalSum = 0;
    int n = nums.size();
    int start = 0;
    for(int i = 0; i < n; i++){
        if(totalSum == 0){
            start = i;
        }
        totalSum += nums[i];
        if(totalSum > maxSum){
            maxSum = totalSum;
            startIndex = start;
            endIndex = i;
        }
        if(totalSum <= 0){
            totalSum = 0;
        }
    }
    for (int i = startIndex; i <= endIndex; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}
//int main(){
////    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
//    vector<int> nums = {5, -5, 4, -1, 3, -7, 2, 1};
//    cout << maxSubArrayBruteForce(nums) << endl;
//    cout << maxSubArray(nums) << endl;
//    cout << maxSubArrayTuf(nums) << endl;
//    printMaxSubArray(nums);
//    printMaxSubArrayTuf(nums);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 121. Best Time to Buy and Sell Stock
// Time Limit Exceeded
int maxProfit(vector<int>& prices) {
    int maxProfit = INT_MIN;
    int n = prices.size();
    for(int i = 0; i < n; i++){
        int currProfit = INT_MIN;
        for(int j = i + 1; j < n; j++){
            if(prices[j] > prices[i]){
                currProfit = prices[j] - prices[i];
                maxProfit = max(currProfit, maxProfit);
            }
        }
    }
    return maxProfit == INT_MIN ? 0 : maxProfit;
}

int maxProfitOptimize(vector<int>& prices) {
    int maxProfit = 0;
    int n = prices.size();
    int buyingPrice = prices[0];
    int sellingPrice = prices[0];
    for(int i = 1; i < n; i++){
        if(prices[i] < buyingPrice){
            buyingPrice = prices[i];
            sellingPrice = prices[i];
        }
        if(prices[i] > sellingPrice){
            sellingPrice = prices[i];
        }
        maxProfit = max(maxProfit, sellingPrice - buyingPrice);
    }
    return maxProfit;
}

int maxProfitTuf(vector<int>& prices) {
    int maxProfit = 0;
    int minPrice = prices[0];
    for (int i = 1; i < prices.size(); i++)
    {
        int currProfit = prices[i] - minPrice;
        maxProfit = max(maxProfit, currProfit);
        minPrice = min(minPrice, prices[i]);
    }
    return maxProfit;
}

//int main(){
//    vector<int> prices = {7, 1, 5, 3, 6, 4};
//    cout << maxProfit(prices) << endl;
//    cout << maxProfitOptimize(prices) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 169. Majority Element
int majorityElement(vector<int>& nums) {
    int n = nums.size();
    int result = 0;
    unordered_map<int, int> frequency;
    for(int item : nums){
        frequency[item]++;
    }
    for(auto it = frequency.begin(); it != frequency.end(); it++){
        if(it->second > n/2){
            result = it->first;
            break;
        }
    }
    return result;
}

int majorityElement2(vector<int>& nums) {
    int candidate;
    int votes = 0;
    for(int i = 0; i < nums.size(); i++){
        if(votes == 0){
            candidate = nums[i];
        }
        if(nums[i] == candidate){
            votes++;
        }
        else{
            votes--;
        }
    }
    int count = 0;
    for(auto item : nums){
        if(candidate == item){
            count++;
        }
    }
    return count > nums.size()/2 ? candidate : -1;
}

//int main(){
//    vector<int> nums = {3, 2, 3};
//    cout << majorityElement(nums) << endl;
//    cout << majorityElement2(nums) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 229. Majority Element II
vector<int> majorityElement11(vector<int>& nums) {
    int n = nums.size();
    vector<int> result;
    unordered_map<int, int> frequencies;
    for(auto item : nums){
        frequencies[item]++;
    }
    for(auto it = frequencies.begin(); it != frequencies.end(); it++){
        if(it->second > n/3){
            result.push_back(it->first);
        }
    }
    return result;
}

vector<int> majorityElement112(vector<int>& nums) {
    int candidate1;
    int candidate2;
    int vote1 = 0;
    int vote2 = 0;
    for(int i = 0; i < nums.size(); i++){
        if(vote1 == 0 && nums[i] != candidate2){
            candidate1 = nums[i];
        }
        if(vote2 == 0 && nums[i] != candidate1){
            candidate2 = nums[i];
        }
        if(nums[i] == candidate1){
            vote1++;
        }
        else if(nums[i] == candidate2){
            vote2++;
        }
        else{
            vote1--;
            vote2--;
        }
    }
    vector<int> result;
    int n = nums.size();
    int count1 = 0;
    int count2 = 0;
    for(int i = 0; i < n; i++){
        if(candidate1 == nums[i]){
            count1++;
        }
        if(candidate2 == nums[i]){
            count2++;
        }
    }
    if(count1 > n/3){
        result.push_back(candidate1);
    }
    if(count2 > n/3 && candidate1 != candidate2){
        result.push_back(candidate2);
    }
    return result;
}

//int main(){
//    vector<int> nums = {0, 0, 0};
////    vector<int> nums = {2, 2, 1, 2, 1, 1, 3, 3};
//    vector<int> result = majorityElement112(nums);
//    for(auto item : result){
//        cout << item << " ";
//    }
//    cout << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 152. Maximum Product Subarray
int maxProduct(vector<int>& nums) {
    int maximumProduct = INT_MIN;
    int currentProduct = 1;
    int n = nums.size();
    vector<int> prefixProduct(n);
    vector<int> suffixProduct(n);
    for(int i = 0; i < n; i++){
        currentProduct *= nums[i];
        prefixProduct[i] = currentProduct;
        if(currentProduct == 0){
            currentProduct = 1;
        }
    }
    currentProduct = 1;
    for(int i = n - 1; i >= 0; i--){
        currentProduct *= nums[i];
        suffixProduct[i] = currentProduct;
        if(currentProduct == 0){
            currentProduct = 1;
        }
    }
    for(int i = 0; i < n; i++){
        maximumProduct = max(maximumProduct, max(prefixProduct[i], suffixProduct[i]));
    }
    return maximumProduct;
}

int maxProduct2(vector<int>& nums) {
    int maximumProduct = INT_MIN;
    int currentProduct = 1;
    int n = nums.size();
    vector<int> helper(n);
    for(int i = n - 1; i >= 0; i--){
        currentProduct *= nums[i];
        helper[i] = currentProduct;
        if(currentProduct == 0){
            currentProduct = 1;
        }
    }
    currentProduct = 1;
    for(int i = 0; i < n; i++){
        currentProduct *= nums[i];
        maximumProduct = max(max(currentProduct, helper[i]), maximumProduct);
        if(currentProduct == 0){
            currentProduct = 1;
        }
    }
    return maximumProduct;
}

int maxProduct3(vector<int>& nums) {
    int maximumProduct = INT_MIN;
    int prefixMaxProduct = 1;
    int suffixMaxProduct = 1;
    int n = nums.size();
    for(int i = 0; i < n; i++){
        prefixMaxProduct *= nums[i];
        suffixMaxProduct *= nums[n - i - 1];
        maximumProduct = max(maximumProduct, max(prefixMaxProduct, suffixMaxProduct));
        if(prefixMaxProduct == 0){
            prefixMaxProduct = 1;
        }
        if(suffixMaxProduct == 0){
            suffixMaxProduct = 1;
        }
    }
    return maximumProduct;
}

//int main(){
////    vector<int> nums = {2, 3, 0, 4};
//    vector<int> nums = {-3, 0, 1, -2};
//    cout << maxProduct3(nums) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 75. Sort Colors
void sortColors(vector<int>& nums) {
    int n = nums.size();
    int left = 0;
    int right = n - 1;
    int index = 0;
    while(index <= right){
        if(nums[index] == 0){
            swap(nums[index], nums[left]);
            left++;
            index++;
        }
        else if(nums[index] == 2){
            swap(nums[index], nums[right]);
            right--;
        }
        else if(nums[index] == 1){
            index++;
        }
    }
}

//int main(){
//    vector<int> nums = {2, 0, 2, 1, 1, 0};
//    sortColors(nums);
//    for(auto item : nums){
//        cout << item << " ";
//    }
//    cout << endl;
//    
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 1. Two Sum
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> ump;
    unordered_map<int, int>::iterator itr;
    int n = nums.size();
    for(int i = 0; i < n; i++){
        itr = ump.find(target - nums[i]);
        if(itr != ump.end()){
            nums.clear();
            nums.push_back(itr->second);
            nums.push_back(i);
            break;
        }
        else
            ump[nums[i]] = i;
    }
    return nums;
}

//int main(){
//    vector<int> nums = {3,3};
//    vector<int> result = twoSum(nums, 6);
//    cout << result[0] << ", " << result[1] << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 15. 3Sum
// TLE
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    set<vector<int>> st;
    int n = nums.size();
    for(int i = 0; i < n; i++){
        if(i != 0 && nums[i] == nums[i - 1]){
            continue;
        }
        for(int j = i + 1; j < n; j++){
            for(int k = j + 1; k < n; k++){
                if(nums[i] + nums[j] + nums[k] == 0){
                    vector<int> triplet = {nums[i], nums[j], nums[k]};
                    st.insert(triplet);
//                    vector<vector<int>>::iterator itr = find(result.begin(), result.end(), triplet);
//                    if(itr == result.end()){
//                        result.push_back(triplet);
//                    }
                }
            }
        }
    }
    return {st.begin(), st.end()};
}

vector<vector<int>> threeSum2(vector<int>& nums) {
    sort(nums.begin() , nums.end());     //Sorted Array
    if(nums.size() < 3){                // Base Case 1
        return {};
    }
    if(nums[0] > 0){                    // Base Case 2
        return {};
    }
    unordered_map<int , int> hashMap;
    for(int i = 0 ; i < nums.size() ; ++i){     //Hashing of Indices
        hashMap[nums[i]] = i;
    }
    vector<vector<int>> answer;
    for(int i = 0 ; i < nums.size() - 2 ; ++i){     //Traversing the array to fix the number.
        if(nums[i] > 0){     //If number fixed is +ve, stop there because we can't make it zero by searching after it.
            break;
        }
        for(int j = i + 1 ; j < nums.size() ; ++j){     //Fixing another number after first number
            int required = -1*(nums[i] + nums[j]);    //To make sum 0, we would require the -ve sum of both fixed numbers.
            if(hashMap.count(required) && hashMap.find(required)->second > j){ //If it exists in hashmap and its last occurrence index > 2nd fixed index, we found our triplet.
                answer.push_back({nums[i] , nums[j] , required});
            }
            j = hashMap.find(nums[j])->second; //Update j to last occurence of 2nd fixed number to avoid duplicate triplets.
        }
        i = hashMap.find(nums[i])->second;     //Update i to last occurence of 1st fixed number to avoid duplicate triplets.
    }
    return answer;  //Return answer vector.
}

vector<vector<int>> threeSum3(vector<int>& nums) {
    int n = nums.size();
    if (n < 3)
        return {{}};
    unordered_map<int, int> numsTracker;
    sort(nums.begin(), nums.end());
    set<vector<int>> result;
    for (int index = 0; index < n; index++)
        numsTracker[nums[index]] = index;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int requiredValue = -1 * (nums[i] + nums[j]);
            if (numsTracker[requiredValue] > j)
            {
                result.insert({nums[i], nums[j], requiredValue});
            }
        }
    }
    return {result.begin(), result.end()};
}

vector<vector<int>> threeSum4(vector<int>& nums) {
    sort(nums.begin() , nums.end());    //Sorted Array
    if(nums.size() < 3){    //Base case 1
        return {};
    }
    if(nums[0] > 0){        //Base case 2
        return {};
    }
    vector<vector<int>> answer;
    for(int i = 0 ; i < nums.size() ; ++i){     //Traversing the array to fix the number.
        if(nums[i] > 0){     //If number fixed is +ve, stop there because we can't make it zero by searching after it.
            break;
        }
        if(i > 0 && nums[i] == nums[i - 1]){    //If number is getting repeated, ignore the lower loop and continue.
            continue;
        }
        int low = i + 1 , high = nums.size() - 1;   //Make two pointers high and low, and initialize sum as 0.
        int sum = 0;
        while(low < high){                          //Search between two pointers, just similiar to binary search.
            sum = nums[i] + nums[low] + nums[high];
            if(sum > 0){   //If sum is +ve, means, we need more -ve numbers to make it 0, decreament high (high--).
                high--;
            } else if(sum < 0){ //If sum is -ve, means, we need more +ve numbers to make it 0, increament low (low++).
                low++;
            } else {
                answer.push_back({nums[i] , nums[low] , nums[high]});  //we have found the required triplet, push it in answer vector
                int last_low_occurence = nums[low] , last_high_occurence = nums[high];  //Now again, to avoid duplicate triplets, we have to navigate to last occurences of num[low] and num[high] respectively
                while(low < high && nums[low] == last_low_occurence){   // Update the low and high with last occurences of low and high.
                    low++;
                }
                while(low < high && nums[high] == last_high_occurence){
                    high--;
                }
            }
        }
    }
    return answer;      //Return the answer vector.
}

//int main(){
////    vector<int> nums = {-1, 0, 1, 2, -1, -4};
//    vector<int> nums = {-2, -2, -2, -1, -1, -1, 0, 0, 0, 2, 2, 2, 2};
//    vector<vector<int>> result = threeSum4(nums);
//    for(vector<int> item : result){
//        cout << item[0] << ", " << item[1] << ", " << item[2] << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 88. Merge Sorted Array
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> ans;
    int mIndex = 0;
    int nIndex = 0;
    // Merge while both arrays have elements
    while (mIndex < m && nIndex < n) {
        if (nums1[mIndex] <= nums2[nIndex]) {
            ans.push_back(nums1[mIndex]);
            mIndex++;
        }
        else {
            ans.push_back(nums2[nIndex]);
            nIndex++;
        }
    }
    // Remaining elements from nums1
    while (mIndex < m) {
        ans.push_back(nums1[mIndex]);
        mIndex++;
    }
    // Remaining elements from nums2
    while (nIndex < n) {
        ans.push_back(nums2[nIndex]);
        nIndex++;
    }
    nums1 = ans;
}

void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    // index -> position where we will place the next largest element
    // nums1 has total size m + n
    int index = (m + n) - 1;
    // mIndex -> last valid element of nums1
    // We ignore the extra 0s at the end of nums1
    int mIndex = m - 1;
    // nIndex -> last element of nums2
    int nIndex = n - 1;
    // Compare elements from the end of both arrays.
    // We start from the back so that we don't overwrite
    // the valid elements already present in nums1.
    while (mIndex >= 0 && nIndex >= 0) {
        // If the current element of nums1 is larger,
        // put it at the current 'index' position.
        if (nums1[mIndex] >= nums2[nIndex]) {
            nums1[index] = nums1[mIndex];
            // Move to the previous element in nums1
            mIndex--;
        }
        else {
            // nums2 element is larger,
            // so put it at the current 'index' position.
            nums1[index] = nums2[nIndex];
            // Move to the previous element in nums2
            nIndex--;
        }
        // Move to the previous empty position in nums1
        index--;
    }
    // If some elements of nums2 are still remaining,
    // copy them into nums1.
    //
    // We don't need to copy remaining nums1 elements
    // because they are already in their correct positions.
    while (nIndex >= 0) {
        nums1[index] = nums2[nIndex];
        nIndex--;
        index--;
    }
}

//int main(){
//    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
//    vector<int> nums2 = {2, 5, 6};
//    merge2(nums1, 3, nums2, 3);
//    for(auto item : nums1){
//        cout << item << " ";
//    }
//    cout << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 42. Trapping Rain Water
int trap(vector<int>& height) {
    // Number of bars
    int n = height.size();
    // prefixMaxCapacity[i] stores the maximum height
    // of a bar from index 0 to i.
    //
    // Example:
    // height = [4, 2, 0, 3]
    // prefix = [4, 4, 4, 4]
    vector<int> prefixMaxCapacity(n);
    // suffixMaxCapacity[i] stores the maximum height
    // of a bar from index i to n - 1.
    //
    // Example:
    // height = [4, 2, 0, 3]
    // suffix = [4, 3, 3, 3]
    vector<int> suffixMaxCapacity(n);
    // For the first element, there is no bar on its left.
    // So the maximum height from the left up to index 0
    // is simply height[0].
    prefixMaxCapacity[0] = height[0];
    // Similarly, for the last element, there is no bar
    // on its right.
    suffixMaxCapacity[n - 1] = height[n - 1];
    // Build prefix maximum and suffix maximum arrays.
    //
    // prefixMaxCapacity:
    // Find the tallest bar from the LEFT up to current index.
    //
    // suffixMaxCapacity:
    // Find the tallest bar from the RIGHT starting from
    // the current index.
    for (int index = 1; index < n; index++) {
        // Maximum height on the left side including
        // the current index.
        prefixMaxCapacity[index] = max(height[index], prefixMaxCapacity[index - 1]);
        // Maximum height on the right side including
        // the current index.
        //
        // n - index - 1 moves from right to left.
        suffixMaxCapacity[n - index - 1] =
            max(
                height[n - index - 1],
                suffixMaxCapacity[n - index]
            );
    }
    // Stores the total amount of water trapped.
    int maxWaterTrap = 0;
    // Calculate the water trapped at every index.
    for (int i = 0; i < n; i++) {
        // The amount of water that can be stored at index i
        // depends on the shorter of:
        //
        // 1. Tallest bar on the left
        // 2. Tallest bar on the right
        //
        // Water level = min(leftMax, rightMax)
        //
        // Water trapped = water level - current bar height
        maxWaterTrap += min(prefixMaxCapacity[i], suffixMaxCapacity[i]) - height[i];
    }
    // Return the total amount of trapped water.
    return maxWaterTrap;
}

int trap2(vector<int>& height) {
    // Number of bars
    int n = height.size();
    // suffixMaxCapacity[i] stores the maximum height
    // from index i to the end of the array.
    //
    // Example:
    // height = [4, 2, 0, 3]
    //
    // suffixMaxCapacity = [4, 3, 3, 3]
    vector<int> suffixMaxCapacity(n);
    // For the last element, the maximum height
    // from itself to the end is simply height[n - 1].
    suffixMaxCapacity[n - 1] = height[n - 1];
    // Build the suffix maximum array from RIGHT to LEFT.
    //
    // At every index i:
    // suffixMaxCapacity[i] =
    // max(current height, maximum height on the right)
    for (int i = n - 2; i >= 0; i--) {
        suffixMaxCapacity[i] = max(height[i], suffixMaxCapacity[i + 1]);
    }
    // Stores the total amount of trapped water.
    int maxWaterTrap = 0;
    // Instead of creating a prefix maximum array,
    // we maintain the maximum height seen so far
    // using a single variable.
    int prefixMaxCapacity = 0;
    // Traverse the array from LEFT to RIGHT.
    for (int i = 0; i < n; i++) {
        // Update the maximum height seen from the LEFT.
        //
        // prefixMaxCapacity represents:
        // tallest bar from index 0 to i.
        prefixMaxCapacity = max(prefixMaxCapacity, height[i]);
        // Water level at index i is determined by
        // the shorter of the tallest bar on the left
        // and the tallest bar on the right.
        //
        // Water trapped =
        // min(leftMax, rightMax) - currentHeight
        maxWaterTrap += min(prefixMaxCapacity, suffixMaxCapacity[i]) - height[i];
    }
    // Return the total amount of trapped water.
    return maxWaterTrap;
}

int trap3(vector<int>& height) {
    // Number of bars.
    int n = height.size();
    // Stores the total amount of trapped water.
    int waterTrapped = 0;
    // Two pointers:
    // leftPointer starts from the LEFT side.
    // rightPointer starts from the RIGHT side.
    int leftPointer = 0, rightPointer = n - 1;
    // leftMax stores the tallest bar seen so far
    // from the LEFT side.
    //
    // rightMax stores the tallest bar seen so far
    // from the RIGHT side.
    int leftMax = 0, rightMax = 0;
    // Process the array from BOTH ends.
    //
    // We continue until the two pointers meet.
    while (leftPointer <= rightPointer)
    {
        // If the current LEFT bar is smaller than
        // or equal to the current RIGHT bar,
        // process the LEFT side.
        //
        // Why?
        // Because the LEFT side is the limiting side here.
        //
        // The water level at leftPointer is guaranteed
        // to be determined by leftMax.
        if (height[leftPointer] <= height[rightPointer])
        {
            // If the current bar is taller than or equal
            // to all bars seen so far from the LEFT,
            // it becomes the new leftMax.
            //
            // Example:
            // leftMax = 4
            // height[leftPointer] = 6
            //
            // New leftMax = 6
            if (leftMax <= height[leftPointer]){
                leftMax = height[leftPointer];
            }
            // Otherwise, leftMax is taller than the
            // current bar.
            //
            // Therefore, water can be trapped above
            // the current bar.
            //
            // Water trapped =
            // leftMax - currentHeight
            else{
                waterTrapped += leftMax - height[leftPointer];
            }
            // Move the LEFT pointer towards the center.
            leftPointer++;
        }
        else
        {
            // Otherwise, the current RIGHT bar is smaller
            // than the current LEFT bar.
            //
            // So we process the RIGHT side.
            //
            // The RIGHT side is the limiting side here.
            // The water level can safely be determined
            // using rightMax.
            
            // If the current bar is taller than or equal
            // to all bars seen so far from the RIGHT,
            // it becomes the new rightMax.
            //
            // Example:
            // rightMax = 3
            // height[rightPointer] = 5
            //
            // New rightMax = 5
            if (rightMax <= height[rightPointer]){
                rightMax = height[rightPointer];
            }
            // Otherwise, rightMax is taller than the
            // current bar.
            //
            // Therefore, water can be trapped above
            // the current bar.
            //
            // Water trapped =
            // rightMax - currentHeight
            else{
                waterTrapped += rightMax - height[rightPointer];
            }
            // Move the RIGHT pointer towards the center.
            rightPointer--;
        }
    }
    // Return the total amount of trapped water.
    return waterTrapped;
}

//int main(){
////    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
//    vector<int> height = {4, 2, 0, 3, 2, 5};
//    cout << trap3(height) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
int inversionCountTLE(vector<int> &arr) {
    int n = arr.size();
    int count = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(arr[i] > arr[j]){
                count++;
            }
        }
    }
    return count;
}

// Merge two sorted halves and count the inversions between them.
//
// Left half  = [low ... mid]
// Right half = [mid+1 ... high]
//
// Both halves are already sorted because of Merge Sort.
int inversionCountMergeHelper(vector<int> &arr, int low, int mid, int high) {
    // Pointer for the left sorted half
    int left = low;
    // Pointer for the right sorted half
    int right = mid + 1;
    // Stores the number of inversions found
    // between the left and right halves.
    int count = 0;
    // Temporary array used to store the merged sorted elements
    vector<int> temp;
    // Compare elements from both sorted halves
    while (left <= mid && right <= high) {
        // If left element is smaller or equal,
        // there is no inversion.
        //
        // Example:
        // left = 2, right = 5
        // 2 <= 5 → no inversion
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            // arr[left] > arr[right]
            //
            // Since the LEFT half is already sorted,
            // every element from 'left' to 'mid'
            // will also be greater than arr[right].
            //
            // Example:
            //
            // Left:  [2, 5, 8]
            //          ↑
            //        left
            //
            // Right: [3]
            //
            // 5 > 3
            // 8 > 3
            //
            // So there are 2 inversions.
            //
            // Number of elements from left to mid:
            // mid - left + 1
            count += (mid - left) + 1;
            // Put the smaller right-side element
            // into the temporary array.
            temp.push_back(arr[right]);
            right++;
        }
    }
    // If some elements are still left in the left half,
    // add them to temp.
    //
    // They are already sorted, so no more comparisons
    // or inversions need to be counted here.
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
    // Copy the sorted elements from temp
    // back into the original array.
    //
    // temp[0] belongs to arr[low]
    // temp[1] belongs to arr[low + 1]
    // ...
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
    // Return the number of inversions found
    // between these two halves.
    return count;
}


// Recursively divide the array and count inversions.
int inversionCountMergeSortHelper(vector<int> &arr, int low, int high) {
    // If there is only one element (or no element),
    // it is already sorted and cannot contain an inversion.
    if (low >= high) {
        return 0;
    }
    // Find the middle point.
    int mid = (low + high) / 2;
    // Stores the total number of inversions
    // found in this portion of the array.
    int count = 0;
    // Count inversions inside the LEFT half.
    count += inversionCountMergeSortHelper(arr, low, mid);
    // Count inversions inside the RIGHT half.
    count += inversionCountMergeSortHelper(arr, mid + 1, high);
    // Merge both sorted halves and count
    // inversions that exist BETWEEN the two halves.
    count += inversionCountMergeHelper(arr, low, mid, high);
    // Return total inversions for this portion.
    return count;
}


// Main function to count inversions in the array.
int inversionCount(vector<int> &arr) {
    int n = arr.size();
    // Start Merge Sort from the entire array.
    //
    // The recursive function will:
    // 1. Divide the array
    // 2. Count inversions in the left half
    // 3. Count inversions in the right half
    // 4. Count inversions while merging
    int count = inversionCountMergeSortHelper(arr, 0, n - 1);
    return count;
}

//int main(){
//    vector<int> arr = {5, 3, 2, 4, 1};
//    cout << inversionCount(arr) << endl << endl;
//    for(auto item : arr){
//        cout << item << " ";
//    }
//    cout << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//

