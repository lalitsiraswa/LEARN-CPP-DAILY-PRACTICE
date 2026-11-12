#include<iostream>
using namespace std;

// https://leetcode.com/problems/permutations/solutions/18239/a-general-approach-to-backtracking-questions-in-java-subsets-permutations-combination-sum-palindrome-partioning/

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
// 40. Combination Sum II
void combinationSum2Helper01( int startIndex, vector<int>& candidates, vector<vector<int>>& result, vector<int>& currentCombination, int& currentSum, int& target) {
    // If the current sum equals the target,
    // we have found a valid combination.
    if(currentSum == target){
        result.push_back(currentCombination);
        return;
    }
    // If all candidates have been considered,
    // there are no more elements to explore.
    if(startIndex >= candidates.size()){
        return;
    }
    // Explore all possible candidates starting from startIndex.
    for(int currentIndex = startIndex; currentIndex < candidates.size(); currentIndex++){
        // Skip duplicate elements at the same recursion level.
        // This prevents generating duplicate combinations.
        //
        // We only skip when currentIndex is not equal to startIndex
        // because the first occurrence of a value should still be considered.
        if(currentIndex != startIndex && candidates[currentIndex] == candidates[currentIndex - 1]){
            continue;
        }
        // Since the candidates are sorted, if adding the current
        // candidate exceeds the target, there is no need to explore
        // this candidate or any subsequent candidate.
        if(currentSum + candidates[currentIndex] > target){
            break;
        }
        // Include the current candidate in the combination.
        currentSum += candidates[currentIndex];
        currentCombination.push_back(candidates[currentIndex]);
        // Move to currentIndex + 1 because each candidate
        // can be used only once.
        combinationSum2Helper01(currentIndex + 1, candidates, result, currentCombination, currentSum, target);
        // Backtracking:
        // Remove the current candidate and restore the previous sum
        // so that other possible combinations can be explored.
        currentSum -= candidates[currentIndex];
        currentCombination.pop_back();
    }
}

vector<vector<int>> combinationSum201(vector<int>& candidates, int target) {
    // Sort the candidates to:
    // 1. Handle duplicate elements efficiently.
    // 2. Stop exploring when the current sum exceeds the target.
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> result;
    vector<int> currentCombination;
    int currentSum = 0;
    // Start exploring combinations from index 0.
    combinationSum2Helper01( 0, candidates, result, currentCombination, currentSum, target);
    return result;
}

//int main(){
//    vector<int> candidates = {10,1,2,7,6,1,5};
//    vector<vector<int>> combinations = combinationSum201(candidates, 8);
////    vector<int> candidates = {2,5,2,1,2};
////    vector<vector<int>> combinations = combinationSum201(candidates, 5);
//    for(auto combination : combinations){
//        for(auto num : combination){
//            cout << num << ", ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 90. Subsets II
void subsetsWithoutDupHelper01(int startIndex, vector<int>& nums, vector<vector<int>>& result, vector<int>& currentSubset) {
    // Every subset is a valid answer, including the empty subset.
    // Therefore, add the current subset to the result at every
    // recursive call.
    result.push_back(currentSubset);
    // If all elements have been considered, stop exploring.
    if(startIndex >= nums.size()){
        return;
    }
    // Explore all possible elements starting from startIndex.
    for(int currentIndex = startIndex; currentIndex < nums.size(); currentIndex++){
        // Skip duplicate elements at the same recursion level.
        // This prevents generating duplicate subsets.
        //
        // We do not skip the first element at the current recursion
        // level because it should be considered.
        if(currentIndex != startIndex && nums[currentIndex] == nums[currentIndex - 1]){
            continue;
        }
        // Include the current element in the subset.
        currentSubset.push_back(nums[currentIndex]);
        // Recursively explore subsets using the remaining elements.
        // Move to currentIndex + 1 because each array position
        // can be selected only once.
        subsetsWithoutDupHelper01(currentIndex + 1, nums, result, currentSubset);
        // Backtracking:
        // Remove the last selected element to restore the previous
        // subset before exploring the next possible element.
        currentSubset.pop_back();
    }
}

vector<vector<int>> subsetsWithDup01(vector<int>& nums) {
    // Sort the array so that duplicate elements are adjacent.
    // This allows us to identify and skip duplicate elements.
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> currentSubset;
    // Start generating subsets from index 0.
    subsetsWithoutDupHelper01(0, nums, result, currentSubset);
    return result;
}

//int main(){
//    vector<int> nums = {1,2,2};
//    vector<vector<int>> subsets = subsetsWithDup01(nums);
//    for(auto subset : subsets){
//        for(auto num : subset){
//            cout << num << ", ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 131. Palindrome Partitioning
// Checks whether the given substring is a palindrome.
bool isSubstringPalindrome(string& substring){
    // Use two pointers:
    // low starts from the beginning.
    // high starts from the end.
    int left = 0;
    int right = substring.size() - 1;
    // Compare characters from both ends and move towards the center.
    while(left <= right){
        // If characters at both positions do not match,
        // the substring is not a palindrome.
        if(substring[left] != substring[right]){
            return false;
        }
        // Move both pointers towards the center.
        left++;
        right--;
    }
    // If all corresponding characters match,
    // the substring is a palindrome.
    return true;
}

void partitionHelper01(string& inputString, int startIndex, vector<string>& currentPartition, vector<vector<string>>& result) {
    // Base condition:
    // If startIndex reaches the end of the string,
    // we have successfully partitioned the entire string.
    //
    // Since every selected substring was checked for palindrome,
    // the current partition is a valid answer.
    if(startIndex >= inputString.size()){
        result.push_back(currentPartition);
        return;
    }
    // Build substrings starting from startIndex.
    // Each iteration extends the substring by one character.
    string currentSubstring;
    for(int currentIndex = startIndex; currentIndex < inputString.size(); currentIndex++){
        // Extend the current substring by including the character
        // at currentIndex.
        currentSubstring.push_back(inputString[currentIndex]);
        // Only consider the substring if it is a palindrome.
        if(isSubstringPalindrome(currentSubstring)){
            // Include the palindrome in the current partition.
            currentPartition.push_back(currentSubstring);
            // Recursively partition the remaining part of the string.
            // Start from the next index because the current substring
            // has already been included in the partition.
            partitionHelper01(inputString, currentIndex + 1, currentPartition, result);
            // Backtracking:
            // Remove the last selected palindrome so that we can
            // explore other possible palindrome partitions.
            currentPartition.pop_back();
        }
    }
}

vector<vector<string>> partition01(string inputString) {
    vector<vector<string>> result;
    vector<string> currentPartition;
    // Start partitioning the string from index 0.
    partitionHelper01(inputString, 0, currentPartition, result);
    return result;
}

//int main(){
//    string s = "aabaa";
////    string s = "aabb";
//    vector<vector<string>> partitions = partition01(s);
//    for(auto partition : partitions){
//        for(auto substring : partition){
//            cout << substring << ", ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 79. Word Search
bool existHelper01(int currentRow, int currentColumn, vector<vector<char>>& board, string& word, int currentIndex, vector<vector<int>>& visited) {
    // Base condition:
    // If currentIndex reaches the length of the word,
    // it means we have successfully matched every character.
    if(currentIndex >= word.size()){
        return true;
    }
    // Check whether the current position is outside the board boundaries.
    // If the position is invalid, we cannot explore further in this direction.
    if(currentRow < 0 || currentRow >= board.size() || currentColumn < 0 || currentColumn >= board[0].size()){
        return false;
    }
    // Check two conditions:
    // 1. If the current cell is already visited, we cannot use it again.
    // 2. If the current cell's character does not match the required
    //    character in the word, this path is invalid.
    if(visited[currentRow][currentColumn] || board[currentRow][currentColumn] != word[currentIndex]){
        return false;
    }
    // Mark the current cell as visited so that we do not use
    // the same cell again while searching for the remaining characters.
    visited[currentRow][currentColumn] = 1;
    // Explore all four possible directions from the current cell.
    // Move to the next character in the word (currentIndex + 1).
    // Explore the left cell.
    bool foundInLeft = existHelper01(currentRow, currentColumn - 1, board, word, currentIndex + 1, visited);
    // Explore the right cell.
    bool foundInRight = existHelper01(currentRow, currentColumn + 1, board, word, currentIndex + 1, visited);
    // Explore the cell above the current cell.
    bool foundInTop = existHelper01(currentRow - 1, currentColumn,board, word, currentIndex + 1, visited);
    // Explore the cell below the current cell.
    bool foundInBottom = existHelper01(currentRow + 1, currentColumn,board, word, currentIndex + 1, visited);
    // Backtracking:
    // Unmark the current cell so that it can be used in
    // other possible search paths.
    visited[currentRow][currentColumn] = 0;
    // If the word is found in any of the four directions,
    // return true. Otherwise, return false.
    return (foundInLeft || foundInRight || foundInTop || foundInBottom);
}

bool exist01(vector<vector<char>>& board, string word) {
    // Get the number of rows and columns in the board.
    int rowCount = board.size();
    int columnCount = board[0].size();
    // Create a visited matrix of the same dimensions as the board.
    // Initially, all cells are unvisited (0).
    vector<vector<int>> visited(rowCount,vector<int>(columnCount, 0));
    // Try starting the word search from every cell in the board.
    for(int currentRow = 0; currentRow < rowCount; currentRow++){
        for(int currentColumn = 0; currentColumn < columnCount; currentColumn++){
            // Start searching for the word from the current cell.
            // currentIndex = 0 means we are looking for the first
            // character of the word.
            if(existHelper01(currentRow, currentColumn, board, word, 0, visited)){
                return true;
            }
        }
    }
    // If no starting position produces the complete word,
    // the word does not exist in the board.
    return false;
}

//-------------------------------------------//
// WITHOUT USING ANY EXTRA SPACE
bool existHelper02(int currentRow, int currentColumn, vector<vector<char>>& board, string& word, int currentIndex) {
    // Base condition:
    // If currentIndex reaches the length of the word,
    // it means all characters have been successfully matched.
    if(currentIndex >= word.size()){
        return true;
    }
    // Check whether the current position is outside the board boundaries.
    // If the position is invalid, this search path cannot continue.
    if(currentRow < 0 || currentRow >= board.size() || currentColumn < 0 || currentColumn >= board[0].size()){
        return false;
    }
    // If the current cell does not contain the expected character,
    // this search path is invalid.
    if(board[currentRow][currentColumn] != word[currentIndex]){
        return false;
    }
    // Store the original character before modifying the board.
    // We need this character later to restore the original board.
    char originalCharacter = board[currentRow][currentColumn];
    // Mark the current cell as visited by temporarily replacing
    // its character with '.'.
    //
    // This prevents us from visiting the same cell again
    // in the current search path.
    board[currentRow][currentColumn] = '.';
    // Explore the left cell for the next character in the word.
    bool foundInLeft = existHelper02(currentRow, currentColumn - 1, board, word, currentIndex + 1);
    // If the complete word is found in the left direction,
    // return true immediately.
    if(foundInLeft){
        return true;
    }
    // Explore the right cell for the next character.
    bool foundInRight = existHelper02( currentRow, currentColumn + 1, board, word, currentIndex + 1);
    // If the complete word is found in the right direction,
    // return true immediately.
    if(foundInRight){
        return true;
    }
    // Explore the cell above the current cell.
    bool foundInTop = existHelper02(currentRow - 1, currentColumn, board, word, currentIndex + 1);
    // If the complete word is found in the top direction,
    // return true immediately.
    if(foundInTop){
        return true;
    }
    // Explore the cell below the current cell.
    bool foundInBottom = existHelper02( currentRow + 1, currentColumn, board, word, currentIndex + 1);
    // If the complete word is found in the bottom direction,
    // return true immediately.
    if(foundInBottom){
        return true;
    }
    // Backtracking:
    // None of the four directions contains the remaining word.
    // Restore the original character so that this cell can be
    // used in other possible search paths.
    board[currentRow][currentColumn] = originalCharacter;
    return false;
}

bool exist02(vector<vector<char>>& board, string word) {
    // Get the number of rows and columns in the board.
    int rowCount = board.size();
    int columnCount = board[0].size();
    // Try starting the word search from every cell in the board.
    for(int currentRow = 0; currentRow < rowCount; currentRow++){
        for(int currentColumn = 0; currentColumn < columnCount; currentColumn++){
            // Start searching from the current cell.
            // currentIndex = 0 represents the first character of the word.
            if(existHelper02(currentRow, currentColumn, board, word, 0)){
                return true;
            }
        }
    }
    // The word was not found starting from any cell.
    return false;
}

//int main(){
//    vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
////    string word = "ABCCEDF";
//    string word = "ABCB";
//    cout << exist02(board, word);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 51. N-Queens
bool isValidPosition01(int& currentRow, int& currentColumn, vector<string>& chessBoard, int& boardSize) {
    // CHECK COLUMN:
    // Check whether any queen already exists in the current column.
    // We check all rows from 0 to currentRow.
    for(int row = 0; row <= currentRow; row++){
        // If a queen already exists in this column,
        // placing another queen here would violate the column constraint.
        if(chessBoard[row][currentColumn] == 'Q'){
            return false;
        }
    }
    // CHECK MAIN DIAGONAL:
    // Check the upper-left diagonal starting from the current position.
    // This is required because queens may already exist in previous rows.
    int row = currentRow;
    int column = currentColumn;
    while(true){
        // Stop if we move outside the upper or left boundary.
        if(row < 0 || column < 0){
            break;
        }
        // If a queen exists on this diagonal,
        // the current position is invalid.
        if(chessBoard[row][column] == 'Q'){
            return false;
        }
        // Move diagonally towards the upper-left direction.
        row--;
        column--;
    }
    // LOWER-RIGHT DIAGONAL (OPTIONAL):
    // Since we are placing queens row by row, starting from top to bottom,
    // no queens have been placed in the rows below the current row.
    // Therefore, checking the lower-right diagonal is unnecessary.
    row = currentRow + 1;
    column = currentColumn + 1;
    while(true){
        // Stop if we move outside the lower or right boundary.
        if(row >= boardSize || column >= boardSize){
            break;
        }
        // If a queen exists on this diagonal,
        // the current position is invalid.
        if(chessBoard[row][column] == 'Q'){
            return false;
        }
        // Move diagonally towards the lower-right direction.
        row++;
        column++;
    }
    // CHECK ANTI-DIAGONAL
    // Check the upper-right diagonal.
    // This is required because queens may already exist in previous rows.
    row = currentRow;
    column = currentColumn;
    while(true){
        // Stop if we move outside the upper or right boundary.
        if(row < 0 || column >= boardSize){
            break;
        }
        // If a queen exists on this diagonal,
        // the current position is invalid.
        if(chessBoard[row][column] == 'Q'){
            return false;
        }
        // Move diagonally towards the upper-right direction.
        row--;
        column++;
    }
    // LOWER-LEFT DIAGONAL (OPTIONAL):
    // Since we are placing queens row by row, starting from top to bottom,
    // no queens have been placed in the rows below the current row.
    // Therefore, checking the lower-left diagonal is unnecessary.
    row = currentRow + 1;
    column = currentColumn - 1;
    while(true){
        // Stop if we move outside the lower or left boundary.
        if(row >= boardSize || column < 0){
            break;
        }
        // If a queen exists on this diagonal,
        // the current position is invalid.
        if(chessBoard[row][column] == 'Q'){
            return false;
        }
        // Move diagonally towards the lower-left direction.
        row++;
        column--;
    }
    // No queen was found in the same column or either diagonal.
    // Therefore, the current position is valid.
    return true;
}

void solveNQueensHelper01( int currentRow, int boardSize, vector<vector<string>>& result, vector<string>& chessBoard) {
    // Base condition:
    // If currentRow reaches boardSize, it means we have successfully
    // placed one queen in every row without violating any constraints.
    if(currentRow >= boardSize){
        // Store the completed chessboard configuration.
        result.push_back(chessBoard);
        return;
    }
    // Try placing a queen in every column of the current row.
    for(int currentColumn = 0; currentColumn < boardSize; currentColumn++){
        // Check whether the current position is safe for placing a queen.
        if(isValidPosition01( currentRow, currentColumn, chessBoard, boardSize)){
            // Place a queen at the current position.
            chessBoard[currentRow][currentColumn] = 'Q';
            // Recursively move to the next row to place another queen.
            solveNQueensHelper01( currentRow + 1, boardSize, result, chessBoard);
            // Backtracking:
            // Remove the queen from the current position.
            // This allows us to try placing the queen in another
            // column of the current row.
            chessBoard[currentRow][currentColumn] = '.';
        }
    }
}

vector<vector<string>> solveNQueens01(int boardSize) {
    // Create an empty chessboard with boardSize rows.
    vector<string> chessBoard(boardSize);
    // Stores all valid chessboard configurations.
    vector<vector<string>> result;
    // Create a single row containing only empty cells.
    string emptyRow(boardSize, '.');
    // Initialize every row of the chessboard with empty cells.
    fill(chessBoard.begin(), chessBoard.end(), emptyRow);
    // Start placing queens from the first row (row 0).
    solveNQueensHelper01(0, boardSize, result, chessBoard);
    return result;
}

//int main(){
//    int n = 4;
//    vector<vector<string>> result = solveNQueens01(n);
//    for(auto chessBoard : result){
//        for(auto row : chessBoard){
//            cout << row << endl;
//        }
//        cout << endl;
//    }
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 37. Sudoku Solver
bool check3x3Matrix01(int currentRow, int currentColumn, vector<vector<char>>& board, char digit) {
    // Traverse the 3x3 subgrid starting from the given row and column.
    for(int row = currentRow; row < currentRow + 3; row++){
        for(int column = currentColumn; column < currentColumn + 3; column++){
            // Check whether the digit already exists in the 3x3 subgrid.
            if(board[row][column] == digit){
                return false;
            }
        }
    }
    // The digit does not exist in the 3x3 subgrid.
    return true;
}

bool isValidNumber01(int currentRow, int currentColumn, char digit, vector<vector<char>>& board) {
    // CHECK CURRENT ROW
    for(int column = 0; column < 9; column++){
        // Check whether the digit already exists in the current row.
        if(board[currentRow][column] == digit){
            return false;
        }
    }
    // CHECK CURRENT COLUMN
    for(int row = 0; row < 9; row++){
        // Check whether the digit already exists in the current column.
        if(board[row][currentColumn] == digit){
            return false;
        }
    }
    // CHECK CORRESPONDING 3x3 SUBGRID
    // Identify which of the nine 3x3 subgrids contains the current cell.
    if(currentRow <= 2){
        if(currentColumn <= 2){
            // Top-left 3x3 subgrid.
            if(!check3x3Matrix01(0, 0, board, digit)){
                return false;
            }
        }
        else if(currentColumn <= 5){
            // Top-middle 3x3 subgrid.
            if(!check3x3Matrix01(0, 3, board, digit)){
                return false;
            }
        }
        else if(currentColumn <= 8){
            // Top-right 3x3 subgrid.
            if(!check3x3Matrix01(0, 6, board, digit)){
                return false;
            }
        }
    }
    else if(currentRow <= 5){
        if(currentColumn <= 2){
            // Middle-left 3x3 subgrid.
            if(!check3x3Matrix01(3, 0, board, digit)){
                return false;
            }
        }
        else if(currentColumn <= 5){
            // Middle-middle 3x3 subgrid.
            if(!check3x3Matrix01(3, 3, board, digit)){
                return false;
            }
        }
        else if(currentColumn <= 8){
            // Middle-right 3x3 subgrid.
            if(!check3x3Matrix01(3, 6, board, digit)){
                return false;
            }
        }
    }
    else if(currentRow <= 8){
        if(currentColumn <= 2){
            // Bottom-left 3x3 subgrid.
            if(!check3x3Matrix01(6, 0, board, digit)){
                return false;
            }
        }
        else if(currentColumn <= 5){
            // Bottom-middle 3x3 subgrid.
            if(!check3x3Matrix01(6, 3, board, digit)){
                return false;
            }
        }
        else if(currentColumn <= 8){
            // Bottom-right 3x3 subgrid.
            if(!check3x3Matrix01(6, 6, board, digit)){
                return false;
            }
        }
    }
    // The digit is valid if it does not exist in the row, column, or subgrid.
    return true;
}

// Recursive helper function to solve Sudoku using backtracking.
bool solveSudokuHelper01(int currentRow, vector<vector<char>>& board) {
    // Traverse the board starting from the current row.
    for(int row = currentRow; row < 9; row++){
        for(int column = 0; column < 9; column++){
            // Find an empty cell.
            if(board[row][column] == '.'){
                // Try placing digits from 1 to 9 in the empty cell.
                for(int number = 1; number <= 9; number++){
                    // Convert the integer into its corresponding character digit.
                    char digit = number + 48;
                    // Check whether the digit can be placed in the current cell.
                    if(isValidNumber01(row, column, digit, board)){
                        // Place the digit in the empty cell.
                        board[row][column] = digit;
                        // Recursively solve the remaining Sudoku board.
                        if(solveSudokuHelper01(row, board)){
                            return true;
                        }
                        // BACKTRACK:
                        // If the current digit does not lead to a solution,
                        // reset the cell and try the next digit.
                        board[row][column] = '.';
                    }
                }
                // No valid digit could be placed in this empty cell.
                // Return false to backtrack to the previous cell.
                return false;
            }
        }
    }
    // All cells are filled successfully. Sudoku is solved.
    return true;
}

// Main function to solve the Sudoku board.
void solveSudoku01(vector<vector<char>>& board) {
    // Start solving the Sudoku from the first row.
    solveSudokuHelper01(0, board);
}

//-------------------------------------------//
bool check3x3Matrix02(int startRow, int startColumn, vector<vector<char>>& board, char digit) {
    // Traverse the corresponding 3x3 subgrid.
    for(int row = startRow; row < startRow + 3; row++){
        for(int column = startColumn; column < startColumn + 3; column++){
            // Check whether the digit already exists.
            if(board[row][column] == digit){
                return false;
            }
        }
    }
    return true;
}


bool isValidNumber02(int currentRow, int currentColumn, char digit, vector<vector<char>>& board) {
    // CHECK CURRENT ROW
    for(int column = 0; column < 9; column++){
        if(board[currentRow][column] == digit){
            return false;
        }
    }
    // CHECK CURRENT COLUMN
    for(int row = 0; row < 9; row++){
        if(board[row][currentColumn] == digit){
            return false;
        }
    }
    // FIND STARTING POSITION OF THE 3x3 SUBGRID.
    int startRow = (currentRow / 3) * 3;
    int startColumn = (currentColumn / 3) * 3;
    // CHECK CORRESPONDING 3x3 SUBGRID.
    if(!check3x3Matrix02(startRow, startColumn, board, digit)){
        return false;
    }
    return true;
}


bool solveSudokuHelper02(int currentRow, vector<vector<char>>& board) {
    // Traverse the Sudoku board.
    for(int row = currentRow; row < 9; row++){
        for(int column = 0; column < 9; column++){
            // Find an empty cell.
            if(board[row][column] == '.'){
                // Try digits from 1 to 9.
                for(int number = 1; number <= 9; number++){
                    char digit = number + '0';
                    // Check whether the digit is valid.
                    if(isValidNumber02(row, column, digit, board)){
                        // Place the digit.
                        board[row][column] = digit;
                        // Recursively solve the remaining board.
                        if(solveSudokuHelper02(row, board)){
                            return true;
                        }
                        // BACKTRACK: Undo the previous placement.
                        board[row][column] = '.';
                    }
                }
                // No valid digit found. Backtrack.
                return false;
            }
        }
    }
    // Sudoku is solved.
    return true;
}

void solveSudoku02(vector<vector<char>>& board) {
    solveSudokuHelper02(0, board);
}

//int main(){
//    vector<vector<char>> board = {{'5','3','.','.','7','.','.','.','.'},
//                                  {'6','.','.','1','9','5','.','.','.'},
//                                  {'.','9','8','.','.','.','.','6','.'},
//                                  {'8','.','.','.','6','.','.','.','3'},
//                                  {'4','.','.','8','.','3','.','.','1'},
//                                  {'7','.','.','.','2','.','.','.','6'},
//                                  {'.','6','.','.','.','.','2','8','.'},
//                                  {'.','.','.','4','1','9','.','.','5'},
//                                  {'.','.','.','.','8','.','.','7','9'}};
//    solveSudoku02(board);
//    for(auto row : board){
//        for(auto element : row){
//            cout << element << " ";
//        }
//        cout << endl;
//    }
//    cout << endl << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
