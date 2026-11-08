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

//int main(){
//    vector<string> result = generateParenthesis01(3);
//    for(string str : result){
//        cout << str << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 17. Letter Combinations of a Phone Number
void generateLetterCombinationsHelper(vector<string>& lettersForEachDigit, int currentIndex, string& currentCombination, vector<string>& result) {
    // BASE CASE:
    // If we have processed all the digits,
    // the current combination is complete.
    // Store it in the result and return.
    if (currentIndex >= lettersForEachDigit.size()) {
        result.push_back(currentCombination);
        return;
    }
    // Get all possible letters mapped to the current digit.
    // For example, if the current digit is '2',
    // possible letters are "abc".
    //
    // Explore each possible letter one by one.
    for (int letterIndex = 0; letterIndex < lettersForEachDigit[currentIndex].size(); letterIndex++) {
        // PICK:
        // Add the current letter to the combination.
        currentCombination.push_back(lettersForEachDigit[currentIndex][letterIndex]);
        // RECURSION:
        // Move to the next digit and generate combinations
        // using the remaining digits.
        generateLetterCombinationsHelper(lettersForEachDigit, currentIndex + 1, currentCombination, result);
        // BACKTRACKING:
        // Remove the last added letter to restore the previous state.
        // This allows us to try the next possible letter
        // for the current digit.
        currentCombination.pop_back();
    }
}

vector<string> letterCombinations01(string digits) {
    // Stores the mapping between phone digits and their corresponding letters.
    unordered_map<char, string> digitToLetters = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };
    // Stores the possible letters for each input digit.
    //
    // Example:
    // digits = "23"
    // lettersForEachDigit = {"abc", "def"}
    vector<string> lettersForEachDigit;
    // Convert every digit into its corresponding letters.
    for (int digitIndex = 0; digitIndex < digits.size(); digitIndex++) {
        // Get the letters associated with the current digit
        // and store them in the vector.
        lettersForEachDigit.push_back(digitToLetters[digits[digitIndex]]);
    }
    // Stores all generated letter combinations.
    vector<string> result;
    // Temporarily stores the combination being constructed.
    string currentCombination;
    // Start generating combinations from the first digit (index 0).
    generateLetterCombinationsHelper(lettersForEachDigit, 0, currentCombination, result);
    return result;
}

//int main(){
//    vector<string> combinations = letterCombinations01("23");
//    for(auto combination : combinations){
//        cout << combination << ", ";
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 39. Combination Sum
void combinationSumHelper01(int startIndex, vector<int>& candidates, vector<vector<int>>& combinations, vector<int>& currentCombination, int& currentSum, int target) {
    // BASE CASE:
    // If the current sum reaches the target,
    // the current combination is a valid solution.
    // Store it in the result.
    if (currentSum == target) {
        combinations.push_back(currentCombination);
        return;
    }
    // If we have processed all candidates,
    // there are no more elements to explore.
    if (startIndex >= candidates.size()) {
        return;
    }
    // Try every candidate starting from startIndex.
    //
    // We start from startIndex instead of 0 to avoid
    // generating duplicate combinations in different orders.
    for (int candidateIndex = startIndex; candidateIndex < candidates.size(); candidateIndex++) {
        // PRUNING:
        // If adding the current candidate exceeds the target,
        // skip it because all candidates are positive integers.
        if (currentSum + candidates[candidateIndex] <= target) {
            // PICK:
            // Add the current candidate to the combination.
            currentSum += candidates[candidateIndex];
            currentCombination.push_back(candidates[candidateIndex]);
            // RECURSION:
            // Pass candidateIndex instead of candidateIndex + 1.
            // This allows us to reuse the same candidate multiple times.
            //
            // Starting from candidateIndex also ensures that
            // we do not generate combinations in different orders.
            combinationSumHelper01( candidateIndex, candidates, combinations, currentCombination, currentSum, target);
            // BACKTRACKING:
            // Undo the selected candidate from the current sum.
            currentSum -= candidates[candidateIndex];
            // Remove the last selected candidate from the combination.
            // This allows us to explore the next candidate.
            currentCombination.pop_back();
        }
    }
}

vector<vector<int>> combinationSum01(vector<int>& candidates, int target) {
    // Stores all valid combinations whose sum equals the target.
    vector<vector<int>> result;
    // Temporarily stores the combination being constructed.
    vector<int> currentCombination;
    // Maintains the sum of the elements in currentCombination.
    int currentSum = 0;
    // Start exploring candidates from index 0.
    combinationSumHelper01(0, candidates, result, currentCombination, currentSum, target);
    return result;
}

//-------------------------------------------//
// 39. Combination Sum - Pick / Not-Pick Approach
void combinationSumHelper02(int currentIndex, vector<int>& candidates, vector<vector<int>>& result, vector<int>& currentCombination, int& remainingTarget) {
    // BASE CASE:
    // If the remaining target becomes 0,
    // we have found a valid combination.
    // Store the current combination and return.
    if (remainingTarget == 0) {
        result.push_back(currentCombination);
        return;
    }
    // BASE CASE:
    // If we have processed all candidates,
    // there are no more elements to explore.
    if (currentIndex >= candidates.size()) {
        return;
    }
    // PICK:
    // We can pick the current candidate only if
    // its value does not exceed the remaining target.
    if (candidates[currentIndex] <= remainingTarget) {
        // Add the current candidate to the combination.
        currentCombination.push_back(candidates[currentIndex]);
        // Reduce the remaining target by the selected candidate.
        remainingTarget -= candidates[currentIndex];
        // RECURSION:
        // Pass the same index because we are allowed
        // to reuse the current candidate multiple times.
        combinationSumHelper02( currentIndex, candidates, result, currentCombination, remainingTarget);
        // BACKTRACKING:
        // Restore the remaining target to its previous value.
        remainingTarget += candidates[currentIndex];
        // Remove the selected candidate from the combination.
        // This allows us to explore the Not-Pick decision.
        currentCombination.pop_back();
    }
    // NOT-PICK:
    // Skip the current candidate and move to the next candidate.
    // This ensures that we explore combinations without
    // including the current candidate.
    combinationSumHelper02( currentIndex + 1, candidates, result, currentCombination, remainingTarget);
}

vector<vector<int>> combinationSum02(vector<int>& candidates, int target) {
    // Stores all valid combinations.
    vector<vector<int>> result;
    // Temporarily stores the combination being constructed.
    vector<int> currentCombination;
    // Stores the remaining target that needs to be achieved.
    int remainingTarget = target;
    // Start exploring candidates from index 0.
    combinationSumHelper02(0, candidates, result, currentCombination, remainingTarget);
    return result;
}

//int main(){
//    vector<int> candidates = {2, 3, 6, 7};
//    vector<vector<int>> combinations = combinationSum02(candidates, 7);
//    for(auto combination : combinations){
//        for(auto num : combination){
//            cout << num << ", ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
