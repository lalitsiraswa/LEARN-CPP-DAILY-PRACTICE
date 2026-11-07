#include<iostream>
using namespace std;

//-------------------------------------------//-------------------------------------------//
// 78. Subsets
void generateSubsetsHelper(vector<int>& nums, vector<vector<int>>& result, int currentIndex, vector<int>& currentSubset) {
    // BASE CASE:
    // We have considered all elements in the input array.
    // The current subset is now complete, so add it to the result.
    if (currentIndex >= nums.size())
    {
        result.push_back(currentSubset);
        return;
    }
    // PICK:
    // Include the current element in the subset.
    currentSubset.push_back(nums[currentIndex]);
    // Recursively process the remaining elements
    // with the current element included.
    generateSubsetsHelper(nums, result, currentIndex + 1, currentSubset);
    // BACKTRACKING:
    // Remove the last added element to restore the previous subset.
    // This allows us to explore the possibility of not picking it.
    currentSubset.pop_back();
    // NOT-PICK:
    // Exclude the current element from the subset.
    // Recursively process the remaining elements without it.
    generateSubsetsHelper(nums, result, currentIndex + 1, currentSubset);
}

vector<vector<int>> subsets01(vector<int>& nums) {
    // Stores all the generated subsets.
    vector<vector<int>> result;
    // Temporarily stores the subset being constructed.
    vector<int> currentSubset;
    // Start generating subsets from index 0.
    generateSubsetsHelper(nums, result, 0, currentSubset);
    return result;
}

//-------------------------------------------//
// Bit Manipulation Approach
// Checks whether the bit at the given position is set (1) or not (0).
int isBitSet(int number, int bitPosition) {
    // Create a bitmask with only the bit at bitPosition set to 1.
    // Example: If bitPosition = 2,
    // bitMask = 00000100 (decimal 4).
    int bitMask = 1 << bitPosition;
    // Perform bitwise AND between the number and the bitmask.
    // If the result is not zero, the bit at bitPosition is set.
    int result = bitMask & number;
    // Return 0 if the bit is not set; otherwise, return 1.
    if (result == 0) {
        return 0;
    }
    return 1;
}

vector<vector<int>> subsets02(vector<int>& nums) {
    // Stores all the generated subsets.
    vector<vector<int>> result;
    // Number of elements in the input array.
    int numberOfElements = nums.size();
    // Every element has two choices: Pick or Not-Pick.
    // Therefore, the total number of possible subsets is 2^n.
    //
    // 1 << numberOfElements is equivalent to 2^numberOfElements.
    // Example: If numberOfElements = 3,
    // subsetCount = 1 << 3 = 8.
    int totalSubsets = 1 << numberOfElements;
    // Generate every possible subset using a bitmask.
    // Each integer from 0 to totalSubsets - 1 represents one subset.
    for (int subsetMask = 0; subsetMask < totalSubsets; subsetMask++) {
        // Stores the elements belonging to the current subset.
        vector<int> currentSubset;
        // Check every bit of the current subsetMask.
        // Each bit represents whether the corresponding array element
        // should be included in the current subset.
        for (int bitPosition = 0; bitPosition < numberOfElements; bitPosition++) {
            // If the bit at bitPosition is set (1),
            // include the corresponding array element in the subset.
            if (isBitSet(subsetMask, bitPosition) == 1) {
                currentSubset.push_back(nums[bitPosition]);
            }
        }
        // Store the completely generated subset.
        result.push_back(currentSubset);
    }
    return result;
}

//int main(){
//    vector<int> nums = {1,2,3};
////    vector<vector<int>> subsets = subsets01(nums);
//    vector<vector<int>> subsets = subsets02(nums);
//    for(auto subset : subsets){
//        cout << "{";
//        for(int i = 0; i < subset.size(); i++){
//            cout << subset[i] << ",";
//        }
//        cout << "}"<< endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 22. Generate Parentheses
void generateParenthesesHelper(int openCount, int closeCount, int totalPairs, vector<string>& result, string& currentCombination) {
    // BASE CASE:
    // If we have added all required opening and closing parentheses,
    // the current combination is complete and valid.
    if (openCount == totalPairs && closeCount == totalPairs) {
        result.push_back(currentCombination);
        return;
    }
    // ADD OPENING PARENTHESIS:
    // We can add '(' only if the number of opening parentheses
    // added so far is less than the required total pairs.
    if (openCount < totalPairs) {
        // Add an opening parenthesis to the current combination.
        currentCombination.push_back('(');
        // Recursively generate the remaining parentheses
        // after adding one opening parenthesis.
        generateParenthesesHelper(openCount + 1, closeCount, totalPairs, result, currentCombination);
        // BACKTRACKING:
        // Remove the last added '(' to restore the previous state.
        // This allows us to explore another possible combination.
        currentCombination.pop_back();
    }
    // ADD CLOSING PARENTHESIS:
    // We can add ')' only when:
    // 1. There are more opening parentheses than closing parentheses.
    // 2. We have not reached the required total closing parentheses.
    //
    // This ensures that every closing parenthesis has a matching
    // opening parenthesis before it.
    if (closeCount < openCount && closeCount < totalPairs) {
        // Add a closing parenthesis to the current combination.
        currentCombination.push_back(')');
        // Recursively generate the remaining parentheses
        // after adding one closing parenthesis.
        generateParenthesesHelper(openCount, closeCount + 1, totalPairs, result, currentCombination);
        // BACKTRACKING:
        // Remove the last added ')' to restore the previous state.
        currentCombination.pop_back();
    }
}

vector<string> generateParenthesis01(int n) {
    // Stores all valid parentheses combinations.
    vector<string> result;
    // Temporarily stores the combination being constructed.
    string currentCombination;
    // Initially, no opening or closing parentheses have been added.
    generateParenthesesHelper(0, 0, n, result, currentCombination);
    return result;
}

int main(){
    vector<string> result = generateParenthesis01(3);
    for(string str : result){
        cout << str << endl;
    }
    return 0;
}

//-------------------------------------------//-------------------------------------------//
