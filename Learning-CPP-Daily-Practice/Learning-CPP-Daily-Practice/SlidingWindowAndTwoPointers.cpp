#include<iostream>
using namespace std;

//-------------------------------------------//-------------------------------------------//
// 3. Longest Substring Without Repeating Characters
// Time Limit Exceeded
int lengthOfLongestSubstring(string s) {
    int stringLength = s.size();
    // Stores the maximum length of a substring
    // that contains no repeating characters.
    int maxSubstringLength = 0;
    // Try every possible starting index of a substring.
    for (int startIndex = 0; startIndex < stringLength; startIndex++) {
        // Tracks the characters encountered in the current substring.
        unordered_map<char, int> visitedCharacters;
        // Length of the current substring being examined.
        int currentSubstringLength = 0;
        // Extend the substring from startIndex toward the end of the string.
        for (int endIndex = startIndex; endIndex < stringLength; endIndex++) {
            // If this character has already been encountered,
            // the substring would contain a duplicate.
            // Stop extending this substring.
            if (visitedCharacters.count(s[endIndex])) {
                break;
            }
            // Record the character as visited.
            visitedCharacters[s[endIndex]]++;
            // Include this character in the current substring length.
            currentSubstringLength++;
            // Update the maximum length if the current substring is longer.
            maxSubstringLength = max(maxSubstringLength, currentSubstringLength);
        }
    }
    // Return the longest substring length without repeating characters.
    return maxSubstringLength;
}

//-------------------------------------------//
int lengthOfLongestSubstring01(string s) {
    int stringLength = s.size();
    // Two pointers define the current sliding window.
    int windowStart = 0;
    int windowEnd = 0;
    // Stores the maximum length of a substring without duplicate characters.
    int maxLength = 0;
    // Stores each character and the index of its most recent occurrence.
    unordered_map<char, int> lastSeenIndex;
    // Expand the window by moving windowEnd through the string.
    while (windowEnd < stringLength) {
        char currentChar = s[windowEnd];
        // Check whether the current character already exists
        // in the current window.
        if (lastSeenIndex.find(currentChar) != lastSeenIndex.end()) {
            // Get the previous index of the repeated character.
            int previousIndex = lastSeenIndex[currentChar];
            // Remove characters from the beginning of the window
            // until the previous occurrence is excluded.
            while (windowStart <= previousIndex) {
                lastSeenIndex.erase(s[windowStart]);
                windowStart++;
            }
        }
        // Add or update the current character with its latest index.
        lastSeenIndex[currentChar] = windowEnd;
        // Calculate the current window length and update the maximum.
        int currentWindowLength = windowEnd - windowStart + 1;
        maxLength = max(maxLength, currentWindowLength);
        // Expand the window by moving its ending pointer forward.
        windowEnd++;
    }
    return maxLength;
}

//-------------------------------------------//
int lengthOfLongestSubstring02(string s) {
    int stringLength = s.size();
    // Stores each character and its most recent index in the string.
    unordered_map<char, int> lastSeenIndex;
    // Starting index of the current substring (sliding window).
    int windowStart = 0;
    // Ending index of the current substring.
    // This pointer moves forward to process each character.
    int windowEnd = 0;
    // Stores the maximum length of a substring without repeating characters.
    int maxSubstringLength = 0;
    // Traverse the string using the windowEnd pointer.
    while (windowEnd < stringLength) {
        char currentChar = s[windowEnd];
        // Check whether the current character has appeared before.
        if (lastSeenIndex.find(currentChar) != lastSeenIndex.end()) {
            // Get the most recent index of the current character.
            int previousIndex = lastSeenIndex[currentChar];
            // Move the windowStart only if the previous occurrence
            // is inside the current window.
            //
            // This prevents windowStart from moving backward when
            // the previous occurrence is outside the current window.
            if (windowStart <= previousIndex) {
                windowStart = previousIndex + 1;
            }
        }
        // Record the current character's latest index.
        lastSeenIndex[currentChar] = windowEnd;
        // Move the ending pointer to the next character.
        windowEnd++;
        // Calculate the current window length.
        // Since windowEnd has already been incremented,
        // the length is windowEnd - windowStart.
        int currentWindowLength = windowEnd - windowStart;
        // Update the maximum length if the current window is longer.
        maxSubstringLength = max(maxSubstringLength, currentWindowLength);
    }
    // Return the longest substring length without repeating characters.
    return maxSubstringLength;
}

//-------------------------------------------//
int lengthOfLongestSubstring03(string s) {
    int stringLength = s.size();
    // Starting and ending indices of the current sliding window.
    int windowStart = 0;
    int windowEnd = 0;
    // Stores the maximum length of a substring without repeating characters.
    int maxSubstringLength = 0;
    // Tracks whether a character is currently present in the window.
    // 1 means the character is present; 0 means it is absent.
    unordered_map<char, int> characterPresent;
    // Expand the window by moving windowEnd through the string.
    while (windowEnd < stringLength) {
        // If the current character is already in the window,
        // shrink the window from the left until the duplicate is removed.
        while (characterPresent[s[windowEnd]] == 1) {
            // Remove the leftmost character from the current window.
            characterPresent[s[windowStart]] = 0;
            // Move the starting index forward to shrink the window.
            windowStart++;
        }
        // The current character can now be added without creating a duplicate.
        characterPresent[s[windowEnd]] = 1;
        // Calculate the current window length and update the maximum.
        int currentWindowLength = windowEnd - windowStart + 1;
        maxSubstringLength = max(maxSubstringLength, currentWindowLength);
        // Move the ending index forward to process the next character.
        windowEnd++;
    }
    // Return the length of the longest substring without repeating characters.
    return maxSubstringLength;
}

//int main(){
////    string s = "abcabcbb";
////    string s = "ccbbcc";
////    string s = "abcabcbbdefghijklmno";
//    string s = "cadbzabcd";
//    cout << lengthOfLongestSubstring03(s) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 1423. Maximum Points You Can Obtain from Cards
// Time Limit Exceeded
int maxScore(vector<int>& cardPoints, int k) {
    int totalCards = cardPoints.size();
    // Initially, select all k cards from the left side.
    int cardsFromLeft = k;
    // Initially, no cards are selected from the right side.
    int cardsFromRight = 0;
    // Stores the maximum score found among all combinations.
    int maximumScore = 0;
    // Try every possible combination:
    // k cards from the left and 0 from the right,
    // k-1 from the left and 1 from the right, and so on,
    // until 0 cards from the left and k from the right.
    while (cardsFromLeft >= 0) {
        // Calculate the score for the current combination.
        int currentScore = 0;
        // Add the points from the first cardsFromLeft cards.
        for (int leftIndex = 0; leftIndex < cardsFromLeft; leftIndex++) {
            currentScore += cardPoints[leftIndex];
        }
        // Prepare the next combination by selecting one fewer card
        // from the left.
        cardsFromLeft--;
        // Add the points from the last cardsFromRight cards.
        for (int rightIndex = totalCards - 1; rightIndex >= totalCards - cardsFromRight; rightIndex--) {
            currentScore += cardPoints[rightIndex];
        }
        // Prepare the next combination by selecting one more card
        // from the right.
        cardsFromRight++;
        // Update the maximum score if the current combination is better.
        maximumScore = max(maximumScore, currentScore);
    }
    // Return the highest score among all possible combinations.
    return maximumScore;
}


//-------------------------------------------//
int maxScore01(vector<int>& cardPoints, int k) {
    int totalCards = cardPoints.size();
    // Calculate the score by initially selecting the first k cards
    // from the left side of the array.
    int currentScore = 0;
    for (int index = 0; index < k; index++) {
        currentScore += cardPoints[index];
    }
    // If k equals to the total number of cards, we must select all cards.
    // The score calculated above is already the maximum possible score.
    if (totalCards == k) {
        return currentScore;
    }
    // Initialize the pointers for replacing cards from the left
    // with cards from the right.
    //
    // leftIndex points to the last selected card on the left.
    // rightIndex points to the last card in the array.
    int leftIndex = k - 1;
    int rightIndex = totalCards - 1;
    // Store the best score found so far.
    int maximumScore = currentScore;
    // Gradually remove cards from the left selection and add cards
    // from the right side, considering every possible combination.
    while (leftIndex >= 0) {
        // Remove the current leftmost selected card from the score.
        currentScore -= cardPoints[leftIndex];
        // Add one more card from the right end of the array.
        currentScore += cardPoints[rightIndex];
        // Move both pointers one position to the left.
        leftIndex--;
        rightIndex--;
        // Update the maximum score if this combination gives a better result.
        maximumScore = max(maximumScore, currentScore);
    }
    // Return the maximum score obtained by selecting exactly k cards
    // from the beginning and/or the end of the array.
    return maximumScore;
}

//int main(){
//    vector<int> cardPoints = {1, 2, 3, 4, 5, 6, 1};
////    vector<int> cardPoints = {1, 2, 3, 4, 5, 6};
////    vector<int> cardPoints = {5, 4, 1, 8, 7, 1, 3};
////    vector<int> cardPoints = {6, 2, 3, 4, 7, 2, 1, 7, 1}; k = 4
//    cout << maxScore(cardPoints, 3) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 1004. Max Consecutive Ones III
int longestOnes01(vector<int>& nums, int k) {
    int arraySize = nums.size();
    // Stores the maximum length of a subarray containing at most k zeros.
    int maxConsecutiveOnes = 0;
    // Try every possible starting index of a subarray.
    // Continue only if the remaining elements could produce
    // a subarray longer than the best one found so far.
    for (int startIndex = 0; startIndex < arraySize && (arraySize - startIndex) > maxConsecutiveOnes; startIndex++) {
        // Counts the number of zeros in the current subarray.
        int zeroCount = 0;
        // Extend the subarray from startIndex toward the end.
        for (int endIndex = startIndex; endIndex < arraySize; endIndex++) {
            // Count a zero because it would need to be flipped to 1.
            if (nums[endIndex] == 0) {
                zeroCount++;
            }
            // If the subarray contains more than k zeros,
            // it cannot be made entirely of ones using only k flips.
            // Stop extending this subarray.
            if (zeroCount > k) {
                break;
            }
            // The current subarray contains at most k zeros,
            // so update the maximum valid subarray length.
            int currentLength = endIndex - startIndex + 1;
            maxConsecutiveOnes = max(maxConsecutiveOnes, currentLength);
        }
    }
    // Return the longest subarray that can contain all ones
    // after flipping at most k zeros.
    return maxConsecutiveOnes;
}

//-------------------------------------------//
int longestOnes02(vector<int>& nums, int k) {
    int arraySize = nums.size();
    // Stores the maximum length of a valid window found so far.
    int maxWindowLength = 0;
    // Defines the current sliding window:
    // windowStart is the first index, and windowEnd is the index
    // of the next element to include in the window.
    int windowStart = 0;
    int windowEnd = 0;
    // Counts the number of zeros inside the current window.
    // We can flip at most k zeros to ones.
    int zeroCount = 0;
    // Move windowEnd forward to expand the window.
    while (windowEnd < arraySize && windowStart < arraySize) {
        // If the new element is zero, increment the zero count.
        if (nums[windowEnd] == 0) {
            zeroCount++;
        }
        // If the window contains more than k zeros,
        // shrink it from the left until it becomes valid.
        while (zeroCount > k) {
            // If the element being removed is zero,
            // decrement the zero count.
            if (nums[windowStart] == 0) {
                zeroCount--;
            }
            // Remove the leftmost element from the window.
            windowStart++;
        }
        // Move the ending pointer forward to include the next element.
        windowEnd++;
        // Calculate the current valid window length.
        // windowEnd is exclusive here because it was incremented above.
        int currentWindowLength = windowEnd - windowStart;
        // Update the maximum length if the current window is longer.
        maxWindowLength = max(maxWindowLength, currentWindowLength);
    }
    // Return the longest subarray that can contain all ones
    // after flipping at most k zeros.
    return maxWindowLength;
}

//-------------------------------------------//
int longestOnes03(vector<int>& nums, int k) {
    int arraySize = nums.size();
    // Stores the maximum length of a valid window found so far.
    int maxWindowLength = 0;
    // Define the boundaries of the sliding window.
    int windowStart = 0;
    int windowEnd = 0;
    // Counts the number of zeros inside the current window.
    int zeroCount = 0;
    // Traverse the array by expanding the window from the right.
    while (windowStart < arraySize && windowEnd < arraySize) {
        // Include the current element in the window.
        // If it is zero, increment the zero count.
        if (nums[windowEnd] == 0) {
            zeroCount++;
        }
        // If the window contains more than k zeros,
        // shrink it by removing one element from the left.
        if (zeroCount > k) {
            // If the element being removed is zero,
            // decrement the zero count.
            if (nums[windowStart] == 0) {
                zeroCount--;
            }
            // Move the starting boundary one position forward.
            windowStart++;
        }
        // Move the ending boundary forward.
        windowEnd++;
        // Update the maximum length only when the window
        // contains at most k zeros.
        if (zeroCount <= k) {
            int currentWindowLength = windowEnd - windowStart;
            maxWindowLength = max(maxWindowLength, currentWindowLength);
        }
    }
    // Return the longest subarray that can be converted entirely
    // into ones by flipping at most k zeros.
    return maxWindowLength;
}

//int main(){
////    vector<int> nums = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
//    vector<int> nums = {0, 0, 0, 0};
//    cout << longestOnes03(nums, 0) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 424. Longest Repeating Character Replacement
int characterReplacement01(string s, int k) {
    int stringLength = s.size();
    // Stores the length of the longest valid substring found so far.
    int maxSubstringLength = 0;
    // Try every possible starting index of a substring.
    // Continue only while the remaining characters could produce
    // a substring longer than the best result found so far.
    for (int startIndex = 0; startIndex < stringLength && maxSubstringLength < (stringLength - startIndex); startIndex++) {
        // Stores the frequency of each uppercase English letter.
        // Index 0 represents 'A', index 1 represents 'B', and so on.
        int characterFrequency[26] = {0};
        // Stores the highest frequency of any character
        // in the current substring.
        int maxFrequency = 0;
        // Extend the substring from startIndex toward the end.
        for (int endIndex = startIndex; endIndex < stringLength; endIndex++) {
            // Convert the current uppercase character into an array index
            // and increase its frequency.
            int characterIndex = s[endIndex] - 'A';
            characterFrequency[characterIndex]++;
            // Update the highest frequency among all characters
            // in the current substring.
            maxFrequency = max(maxFrequency, characterFrequency[characterIndex]);
            // Calculate the current substring length.
            int currentSubstringLength = endIndex - startIndex + 1;
            // To make every character identical, we can keep the most
            // frequent character and replace all other characters.
            //
            // Required replacements = substring length - max frequency.
            if (currentSubstringLength - maxFrequency > k) {
                // More than k replacements would be needed.
                // Extending this substring further cannot make it valid,
                // so stop checking this starting index.
                break;
            }
            // The substring is valid because it requires at most k
            // replacements. Update the longest length found so far.
            maxSubstringLength = max(maxSubstringLength, currentSubstringLength);
        }
    }
    // Return the length of the longest substring that can be made
    // to contain identical characters using at most k replacements.
    return maxSubstringLength;
}

//-------------------------------------------//
int characterReplacement02(string s, int k) {
    int stringLength = s.size();
    // Stores the length of the longest valid substring found so far.
    int maxSubstringLength = 0;
    // The sliding window starts with both pointers at index 0.
    int windowStart = 0;
    int windowEnd = 0;
    // Stores the frequency of each uppercase English letter.
    // Index 0 represents 'A', index 1 represents 'B', and so on.
    int characterFrequency[26] = {0};
    // Stores the highest character frequency in the current window.
    int maxFrequency = 0;
    // Expand the window by moving windowEnd to the right.
    while (windowEnd < stringLength) {
        // Convert the current character into an array index.
        int characterIndex = s[windowEnd] - 'A';
        // Include the current character in the window.
        characterFrequency[characterIndex]++;
        // Update the highest frequency of any character seen so far.
        maxFrequency = max(maxFrequency, characterFrequency[characterIndex]);
        // Calculate the current window length.
        int currentWindowLength = windowEnd - windowStart + 1;
        // The minimum replacements needed are:
        // window length - frequency of the most common character.
        //
        // If more than k replacements are required, shrink the window
        // from the left until it becomes valid.
        while (currentWindowLength - maxFrequency > k) {
            // Remove the character at windowStart from the window.
            int leftCharacterIndex = s[windowStart] - 'A';
            characterFrequency[leftCharacterIndex]--;
            // Recalculate the highest frequency using the updated counts.
            // This ensures maxFrequency reflects the current window.
            maxFrequency = 0;
            for (int i = 0; i < 26; i++) {
                maxFrequency = max(maxFrequency, characterFrequency[i]);
            }
            // Move the left pointer forward to shrink the window.
            windowStart++;
            // Recalculate the window length after shrinking.
            currentWindowLength = windowEnd - windowStart + 1;
        }
        // The current window is valid because it needs at most k replacements.
        maxSubstringLength = max(maxSubstringLength, currentWindowLength);
        // Expand the window by moving the right pointer forward.
        windowEnd++;
    }
    // Return the length of the longest valid substring.
    return maxSubstringLength;
}

//-------------------------------------------//
int characterReplacement03(string s, int k) {
    int stringLength = s.size();
    // Stores the length of the longest valid substring found so far.
    int maxSubstringLength = 0;
    // Pointers representing the current sliding window.
    int windowStart = 0;
    int windowEnd = 0;
    // Stores the frequency of each uppercase English letter.
    // Index 0 represents 'A', index 1 represents 'B', and so on.
    int characterFrequency[26] = {0};
    // Stores the highest character frequency encountered
    // while expanding the sliding window.
    int maxFrequency = 0;
    // Expand the window by moving windowEnd to the right.
    while (windowEnd < stringLength) {
        // Convert the current character into an array index.
        int characterIndex = s[windowEnd] - 'A';
        // Include the current character in the window.
        characterFrequency[characterIndex]++;
        // Update the highest frequency encountered so far.
        maxFrequency = max(maxFrequency, characterFrequency[characterIndex]);
        // Calculate the current window length.
        int currentWindowLength = windowEnd - windowStart + 1;
        // Minimum replacements required =
        // window length - frequency of the most common character.
        //
        // If more than k replacements are needed, shrink the window
        // by removing one character from the left.
        if (currentWindowLength - maxFrequency > k) {
            // Remove the character at windowStart from the window.
            int leftCharacterIndex = s[windowStart] - 'A';
            characterFrequency[leftCharacterIndex]--;
            // Move the left pointer forward by one position.
            windowStart++;
            // Recalculate the window length after shrinking.
            currentWindowLength = windowEnd - windowStart + 1;
        }
        // Update the maximum window length found so far.
        maxSubstringLength = max(maxSubstringLength, currentWindowLength);
        // Expand the window by moving the right pointer forward.
        windowEnd++;
    }
    // Return the longest substring length found.
    return maxSubstringLength;
}

//int main(){
//    string s = "BAABAABBBAAA";
//    cout << characterReplacement03(s, 2) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// Longest Substring with K Uniques - GFG
// Brute-force approach with outer-loop optimization
int longestKSubstr01(string &s, int k) {
    int stringLength = s.size();
    // Stores the maximum length of a substring
    // containing exactly k distinct characters.
    // -1 means no valid substring has been found yet.
    int maxSubstringLength = -1;
    // Try every possible starting index.
    // Continue only if the remaining characters could produce
    // a substring longer than the best answer found so far.
    for (int startIndex = 0; startIndex < stringLength && (stringLength - startIndex) > maxSubstringLength; startIndex++) {
        // Stores the frequency of each lowercase English letter.
        // Index 0 represents 'a', index 1 represents 'b', and so on.
        int characterFrequency[26] = {0};
        // Counts the number of distinct characters
        // in the current substring.
        int distinctCharacterCount = 0;
        // Extend the substring from startIndex toward the end.
        for (int endIndex = startIndex; endIndex < stringLength; endIndex++) {
            // Convert the current lowercase character into an array index.
            int characterIndex = s[endIndex] - 'a';
            // Increase the frequency of the current character.
            characterFrequency[characterIndex]++;
            // If its frequency becomes 1, this character has appeared
            // for the first time in the current substring.
            if (characterFrequency[characterIndex] == 1) {
                distinctCharacterCount++;
            }
            // If the substring contains more than k distinct characters,
            // extending it further cannot make it valid.
            if (distinctCharacterCount > k) {
                break;
            }
            // Calculate the current substring length.
            int currentSubstringLength = endIndex - startIndex + 1;
            // Update the answer only when the substring contains
            // exactly k distinct characters.
            if (distinctCharacterCount == k) {
                maxSubstringLength = max(maxSubstringLength, currentSubstringLength);
            }
        }
    }
    // Return the longest valid substring length.
    // Returns -1 if no substring contains exactly k distinct characters.
    return maxSubstringLength;
}

//-------------------------------------------//
// Sliding-window approach
int longestKSubstr02(string &s, int k) {
    int stringLength = s.size();
    // Stores the maximum length of a substring
    // containing exactly k distinct characters.
    // -1 means no valid substring has been found yet.
    int maxSubstringLength = -1;
    // Pointers representing the current sliding window.
    int windowStart = 0;
    int windowEnd = 0;
    // Stores the frequency of each lowercase English letter.
    // Index 0 represents 'a', index 1 represents 'b', and so on.
    int characterFrequency[26] = {0};
    // Counts the number of distinct characters in the current window.
    int distinctCharacterCount = 0;
    // Expand the window by moving windowEnd to the right.
    while (windowEnd < stringLength) {
        // Convert the current lowercase character into an array index.
        int characterIndex = s[windowEnd] - 'a';
        // Include the current character in the window.
        characterFrequency[characterIndex]++;
        // If this character appears for the first time in the window,
        // increase the number of distinct characters.
        if (characterFrequency[characterIndex] == 1) {
            distinctCharacterCount++;
        }
        // If the window contains more than k distinct characters,
        // shrink it from the left until it becomes valid.
        while (distinctCharacterCount > k) {
            // Remove the character at windowStart from the window.
            int leftCharacterIndex = s[windowStart] - 'a';
            characterFrequency[leftCharacterIndex]--;
            // If its frequency becomes zero, the character no longer
            // exists in the current window, so reduce the distinct count.
            if (characterFrequency[leftCharacterIndex] == 0) {
                distinctCharacterCount--;
            }
            // Move the left pointer forward to shrink the window.
            windowStart++;
        }
        // Calculate the current window length.
        int currentSubstringLength = windowEnd - windowStart + 1;
        // Update the answer only when the window contains
        // exactly k distinct characters.
        if (distinctCharacterCount == k) {
            maxSubstringLength = max(maxSubstringLength, currentSubstringLength);
        }
        // Expand the window by moving the right pointer forward.
        windowEnd++;
    }
    // Return the longest substring length containing exactly k
    // distinct characters, or -1 if no such substring exists.
    return maxSubstringLength;
}

//-------------------------------------------//
// Sliding-window approach using a single if condition
int longestKSubstr03(string &s, int k) {
    int stringLength = s.size();
    // Stores the maximum length of a substring
    // containing exactly k distinct characters.
    // -1 means no valid substring has been found yet.
    int maxSubstringLength = -1;
    // Pointers representing the current sliding window.
    int windowStart = 0;
    int windowEnd = 0;
    // Stores the frequency of each lowercase English letter.
    // Index 0 represents 'a', index 1 represents 'b', and so on.
    int characterFrequency[26] = {0};
    // Counts the distinct characters in the current window.
    int distinctCharacterCount = 0;
    // Expand the window by moving windowEnd to the right.
    while (windowEnd < stringLength) {
        // Convert the current lowercase character into an array index.
        int characterIndex = s[windowEnd] - 'a';
        // Include the current character in the window.
        characterFrequency[characterIndex]++;
        // If this character appears for the first time,
        // increase the distinct character count.
        if (characterFrequency[characterIndex] == 1) {
            distinctCharacterCount++;
        }
        // If the window contains more than k distinct characters,
        // remove one character from the left.
        if (distinctCharacterCount > k) {
            // Remove the leftmost character from the window.
            int leftCharacterIndex = s[windowStart] - 'a';
            characterFrequency[leftCharacterIndex]--;
            // If its frequency becomes zero, it no longer exists
            // in the window, so decrease the distinct character count.
            if (characterFrequency[leftCharacterIndex] == 0) {
                distinctCharacterCount--;
            }
            // Move the left pointer forward by one position.
            windowStart++;
        }
        // Calculate the current window length.
        int currentSubstringLength = windowEnd - windowStart + 1;
        // Update the answer only when the window contains
        // exactly k distinct characters.
        if (distinctCharacterCount == k) {
            maxSubstringLength = max(maxSubstringLength, currentSubstringLength);
        }
        // Expand the window by moving the right pointer forward.
        windowEnd++;
    }
    // Return the longest substring length containing exactly k
    // distinct characters, or -1 if no such substring exists.
    return maxSubstringLength;
}

//int main(){
//    string s = "aabacbebebe";
//    cout << longestKSubstr03(s, 3) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 76. Minimum Window Substring
// Brute-force approach (Time Limit Exceeded)
string minWindow01(string s, string t) {
    int sourceLength = s.size();
    int targetLength = t.size();
    // Stores the smallest substring of s that contains
    // all characters of t, including duplicate characters.
    string minimumWindow = "";
    // Initially, no valid window has been found.
    int minimumWindowLength = INT_MAX;
    // Try every possible starting index of a window in s.
    for (int startIndex = 0; startIndex < sourceLength; startIndex++) {
        // Stores the number of times each character is required
        // to form a valid window containing all characters of t.
        unordered_map<char, int> characterFrequency;
        // Count the frequency of every character in t.
        for (int targetIndex = 0; targetIndex < targetLength; targetIndex++) {
            characterFrequency[t[targetIndex]]++;
        }
        // Counts how many required character occurrences
        // have been matched by the current window.
        int matchedCharacterCount = 0;
        // Expand the window from startIndex toward the end of s.
        for (int endIndex = startIndex; endIndex < sourceLength; endIndex++) {
            char currentCharacter = s[endIndex];
            // If this character is required and its remaining
            // required frequency is positive, it contributes
            // to satisfying the target string.
            if (characterFrequency.find(currentCharacter) !=  characterFrequency.end() && characterFrequency[currentCharacter] > 0) {
                matchedCharacterCount++;
            }
            // Decrease the remaining frequency for this character.
            // Frequencies can become negative when the window
            // contains more occurrences than t requires.
            characterFrequency[currentCharacter]--;
            // Calculate the current window length.
            int currentWindowLength = endIndex - startIndex + 1;
            // If all characters required by t have been matched
            // and this window is smaller than the best one found,
            // save it as the new minimum window.
            if (matchedCharacterCount == targetLength && currentWindowLength < minimumWindowLength) {
                minimumWindow = s.substr(startIndex, currentWindowLength);
                minimumWindowLength = currentWindowLength;
                // Since endIndex moves from left to right,
                // this is the first valid window for this startIndex.
                // Any longer window with the same start cannot be better.
                break;
            }
        }
    }
    // Return the smallest valid window, or an empty string
    // if no window contains all characters of t.
    return minimumWindow;
}

//-------------------------------------------//
// Sliding-window approach (Memory Limit Exceeded)
string minWindow02(string s, string t) {
    int sourceLength = s.size();
    int targetLength = t.size();
    // Stores the length of the smallest valid window found so far.
    int minimumWindowLength = INT_MAX;
    // Stores the smallest valid substring found so far.
    string minimumWindow = "";
    // Pointers representing the current sliding window.
    int windowStart = 0;
    int windowEnd = 0;
    // Stores the required frequency of each character in t.
    // During window expansion and shrinking, these frequencies
    // are updated to track which characters are still required.
    unordered_map<char, int> characterFrequency;
    // Counts how many required character occurrences
    // have been matched in the current window.
    int matchedCharacterCount = 0;
    // Count the frequency of every character in the target string.
    for (int targetIndex = 0;targetIndex < targetLength; targetIndex++) {
        characterFrequency[t[targetIndex]]++;
    }
    // Expand the sliding window by moving windowEnd to the right.
    while (windowEnd < sourceLength) {
        // Get the character at the current right boundary.
        char currentCharacter = s[windowEnd];
        // If this character exists in the map and is still required,
        // count this occurrence as a match.
        if (characterFrequency.find(currentCharacter) != characterFrequency.end() && characterFrequency[currentCharacter] > 0) {
            matchedCharacterCount++;
        }
        // Decrease the remaining frequency of the current character.
        // Negative frequencies indicate extra occurrences in the window.
        characterFrequency[currentCharacter]--;
        // When all required character occurrences are matched,
        // try shrinking the window to find a smaller valid substring.
        while (matchedCharacterCount == targetLength) {
            // Calculate the current window length.
            int currentWindowLength = windowEnd - windowStart + 1;
            // If this window is smaller than the best one found,
            // save the substring and its length.
            if (minimumWindowLength > currentWindowLength) {
                minimumWindow = s.substr(windowStart,currentWindowLength);
                minimumWindowLength = currentWindowLength;
            }
            // Get the character at the current left boundary.
            currentCharacter = s[windowStart];
            // Restore its frequency because it is being removed
            // from the current window.
            characterFrequency[currentCharacter]++;
            // If this character is required again, the current window
            // no longer contains enough required character occurrences.
            if (characterFrequency[currentCharacter] > 0) {
                matchedCharacterCount--;
            }
            // Move the left boundary forward to shrink the window.
            windowStart++;
        }
        // Move the right boundary forward to expand the window.
        windowEnd++;
    }
    // Return the smallest valid substring.
    // If no valid window was found, this returns an empty string.
    return minimumWindow;
}

//-------------------------------------------//
string minWindow03(string s, string t) {
    // Store the lengths of the source and target strings.
    int sourceLength = s.size();
    int targetLength = t.size();
    // Store the length of the smallest valid window found so far.
    int minimumWindowLength = INT_MAX;
    // Store the starting index of the smallest valid window.
    // -1 means that no valid window has been found yet.
    int minimumWindowStartIndex = -1;
    // Pointers representing the current sliding window.
    int windowStart = 0, windowEnd = 0;
    // Store the required frequency of each character in the target string.
    unordered_map<char, int> characterFrequency;
    // Count how many characters from the target string have been matched.
    int matchedCharacterCount = 0;
    // Count the frequency of each character in the target string.
    for (int targetIndex = 0; targetIndex < targetLength; targetIndex++) {
        characterFrequency[t[targetIndex]]++;
    }
    // Expand the window by moving windowEnd through the source string.
    while (windowEnd < sourceLength) {
        // Get the character at the current window's ending position.
        int currentCharacter = s[windowEnd];
        // If this character is required and its remaining frequency is
        // positive, it contributes to matching a required character.
        if (characterFrequency.find(currentCharacter) != characterFrequency.end() && characterFrequency[currentCharacter] > 0) {
            matchedCharacterCount++;
        }
        // Decrease the remaining frequency of the current character.
        characterFrequency[s[windowEnd]]--;
        // When all target characters are matched, try to shrink the window.
        while (matchedCharacterCount == targetLength) {
            // Calculate the current window's length.
            int currentWindowLength = (windowEnd - windowStart) + 1;
            // Update the smallest window if the current one is shorter.
            if (minimumWindowLength > currentWindowLength) {
                minimumWindowStartIndex = windowStart;
                minimumWindowLength = currentWindowLength;
            }
            // Get the character at the starting position of the window.
            currentCharacter = s[windowStart];
            // Restore its frequency because it is leaving the window.
            characterFrequency[currentCharacter]++;
            // If its frequency becomes positive, removing it means
            // the current window no longer contains all required characters.
            if (characterFrequency[currentCharacter] > 0) {
                matchedCharacterCount--;
            }
            // Move the starting pointer forward to shrink the window.
            windowStart++;
        }
        // Expand the window by moving the ending pointer forward.
        windowEnd++;
    }
    // Return an empty string if no valid window was found.
    // Otherwise, return the smallest valid substring.
    return minimumWindowStartIndex == -1 ? "" : s.substr(minimumWindowStartIndex, minimumWindowLength);
}

//-------------------------------------------//
// Optimized sliding-window approach
string minWindow04(string s, string t) {
    int sourceLength = s.size();
    int targetLength = t.size();
    // Stores the length of the smallest valid window found so far.
    int minimumWindowLength = INT_MAX;
    // Stores the starting index of the smallest valid window.
    // -1 means that no valid window has been found yet.
    int minimumWindowStartIndex = -1;
    // Pointers representing the current sliding window.
    int windowStart = 0;
    int windowEnd = 0;
    // Stores the remaining required frequency of each character.
    // The array supports character values from 0 to 255.
    int characterFrequency[256] = {0};
    // Counts how many required character occurrences
    // have been matched in the current window.
    int matchedCharacterCount = 0;
    // Count the frequency of every character required by t.
    for (int targetIndex = 0; targetIndex < targetLength; targetIndex++) {
        characterFrequency[t[targetIndex]]++;
    }
    // Expand the window by moving windowEnd to the right.
    while (windowEnd < sourceLength) {
        // Get the character at the current right boundary.
        char currentCharacter = s[windowEnd];
        // If this character is still required, it matches
        // one of the character occurrences needed from t.
        if (characterFrequency[currentCharacter] > 0) {
            matchedCharacterCount++;
        }
        // Decrease the remaining required frequency.
        // A negative value means the window contains extra occurrences.
        characterFrequency[currentCharacter]--;
        // When all target character occurrences are matched,
        // try shrinking the window to find a smaller valid substring.
        while (matchedCharacterCount == targetLength) {
            // Calculate the current window length.
            int currentWindowLength = windowEnd - windowStart + 1;
            // If this window is smaller than the best one found,
            // save its starting index and length.
            if (currentWindowLength < minimumWindowLength) {
                minimumWindowStartIndex = windowStart;
                minimumWindowLength = currentWindowLength;
            }
            // Remove the leftmost character from the window.
            char leftCharacter = s[windowStart];
            characterFrequency[leftCharacter]++;
            // If its frequency becomes positive, the window no longer
            // contains enough occurrences of this required character.
            if (characterFrequency[leftCharacter] > 0) {
                matchedCharacterCount--;
            }
            // Move the left boundary forward to shrink the window.
            windowStart++;
        }
        // Expand the window by moving the right boundary forward.
        windowEnd++;
    }
    // If no valid window was found, return an empty string.
    // Otherwise, return the smallest valid substring.
    return minimumWindowStartIndex == -1 ? "" : s.substr(minimumWindowStartIndex, minimumWindowLength);
}

//int main(){
////    string s = "ADOBECODEBANC";
////    cout << minWindow01(s, "ABC") << endl;
////    string s = "bba";
////    cout << minWindow01(s, "ab") << endl;
//    string s = "ddaaabbca";
//    cout << minWindow03(s, "abc") << endl;
//    unordered_map<char, int> umap;
////    cout << umap['Z'] << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 1358. Number of Substrings Containing All Three Characters
int numberOfSubstrings01(string s) {
    // Store the length of the input string.
    int stringLength = s.size();
    // Store the total number of valid substrings.
    int totalSubstrings = 0;
    // Choose the starting index of each substring.
    for (int startIndex = 0; startIndex < stringLength; startIndex++) {
        // Store the frequency of 'a', 'b', and 'c'.
        // Index 0 represents 'a', 1 represents 'b', and 2 represents 'c'.
        int characterFrequency[3] = {0};
        // Count how many distinct required characters have appeared.
        int matchedCharacterCount = 0;
        // Expand the substring by moving the ending index forward.
        for (int endIndex = startIndex; endIndex < stringLength; endIndex++) {
            // Convert the character into an array index:
            // 'a' - 97 = 0, 'b' - 97 = 1, 'c' - 97 = 2.
            char characterIndex = s[endIndex] - 97;
            // Increase the frequency of the current character.
            characterFrequency[characterIndex]++;
            // If this character appears for the first time in the
            // current substring, increase the distinct character count.
            if (characterFrequency[characterIndex] == 1) {
                matchedCharacterCount++;
            }
            // If the substring contains all three characters ('a', 'b', 'c'),
            // every extension ending at a later index is also valid.
            if (matchedCharacterCount == 3) {
                // Count all valid substrings starting at startIndex
                // and ending at endIndex or any position after it.
                totalSubstrings += (stringLength - endIndex);
                // Stop because all extensions have already been counted.
                break;
            }
        }
    }
    // Return the total number of valid substrings.
    return totalSubstrings;
}

//-------------------------------------------//
int numberOfSubstrings02(string s) {
    // Store the length of the input string.
    int stringLength = s.size();
    // Store the total number of valid substrings.
    int totalSubstrings = 0;
    // Store the frequency of 'a', 'b', and 'c'.
    // Index 0 represents 'a', 1 represents 'b', and 2 represents 'c'.
    int characterFrequency[3] = {0};
    // Count how many distinct characters ('a', 'b', 'c')
    // are currently present in the sliding window.
    int matchedCharacterCount = 0;
    // Pointers representing the current sliding window.
    int windowStart = 0, windowEnd = 0;
    // Expand the window by moving windowEnd forward.
    while (windowEnd < stringLength) {
        // Convert the current character into an array index:
        // 'a' - 97 = 0, 'b' - 97 = 1, 'c' - 97 = 2.
        int characterIndex = s[windowEnd] - 97;
        // Increase the frequency of the current character.
        characterFrequency[characterIndex]++;
        // If this character appears for the first time in the window,
        // increase the count of distinct characters.
        if (characterFrequency[characterIndex] == 1) {
            matchedCharacterCount++;
        }
        // When all three characters are present, count valid substrings
        // and try to shrink the window from the left.
        while (matchedCharacterCount == 3) {
            // Every substring starting at windowStart and ending at
            // windowEnd or any later position is valid.
            totalSubstrings += stringLength - windowEnd;
            // Get the character that will leave the window.
            characterIndex = s[windowStart] - 97;
            // Decrease its frequency because windowStart is moving forward.
            characterFrequency[characterIndex]--;
            // If its frequency becomes zero, this character is no longer
            // present in the current window.
            if (characterFrequency[characterIndex] == 0) {
                matchedCharacterCount--;
            }
            // Shrink the window by moving the starting pointer forward.
            windowStart++;
        }
        // Expand the window by moving the ending pointer forward.
        windowEnd++;
    }
    // Return the total number of valid substrings.
    return totalSubstrings;
}

//-------------------------------------------//
int numberOfSubstrings03(string s) {
    // Store the length of the input string.
    int stringLength = s.size();
    // Store the last seen index of 'a', 'b', and 'c'.
    // Index 0 represents 'a', 1 represents 'b', and 2 represents 'c'.
    // Initially, -1 means the character has not been visited.
    int lastSeenIndex[3] = {-1, -1, -1};
    // Store the total number of valid substrings.
    int totalSubstrings = 0;
    // Traverse each character in the input string.
    for (int currentIndex = 0; currentIndex < stringLength; currentIndex++) {
        // Convert the current character into an array index:
        // 'a' - 97 = 0, 'b' - 97 = 1, 'c' - 97 = 2.
        int characterIndex = s[currentIndex] - 97;
        // Update the last seen index of the current character.
        lastSeenIndex[characterIndex] = currentIndex;
        // Check whether all three characters have been visited.
        if (lastSeenIndex[0] != -1 && lastSeenIndex[1] != -1 && lastSeenIndex[2] != -1) {
            // Find the smallest last-seen index among 'a', 'b', and 'c'.
            int minimumLastSeenIndex = min(lastSeenIndex[0], min(lastSeenIndex[1], lastSeenIndex[2]));
            // Every substring ending at currentIndex and starting
            // from index 0 through minimumLastSeenIndex contains
            // all three characters.
            totalSubstrings += (minimumLastSeenIndex + 1);
        }
    }
    // Return the total number of valid substrings.
    return totalSubstrings;
}

// "aaaabc" -> Dry Run -> 4
//int main(){
////    string s = "abcabc";
//    string s = "ccabcc";
//    cout << numberOfSubstrings03(s) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 560. Subarray Sum Equals K
// Brute Force Approach
int subarraySum01(vector<int>& nums, int k) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Store the total number of subarrays whose sum equals k.
    int totalSubarrays = 0;
    // Choose the starting index of each subarray.
    for (int startIndex = 0; startIndex < arraySize; startIndex++) {
        // Reset the sum for each new starting index.
        int currentSubarraySum = 0;
        // Expand the subarray by moving the ending index forward.
        for (int endIndex = startIndex; endIndex < arraySize; endIndex++) {
            // Add the current element to the subarray sum.
            currentSubarraySum += nums[endIndex];
            // Check whether the current subarray sum equals k.
            if (currentSubarraySum == k) {
                totalSubarrays++;
            }
        }
    }
    // Return the total number of subarrays whose sum equals k.
    return totalSubarrays;
}

//-------------------------------------------//
// Approach:
// Prefix Sum + Hash Map
int subarraySum02(vector<int>& nums, int k) {
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
//    vector<int> nums = {1, 2, 3, -3, 1, 1, 1, 4, 2, -3};
//    cout << subarraySum02(nums, 3) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 930. Binary Subarrays With Sum
// Brute Force Approach - Time Limit Exceeded
int numSubarraysWithSum01(vector<int>& nums, int goal) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Store the total number of subarrays whose sum equals goal.
    int totalSubarrays = 0;
    // Choose the starting index of each subarray.
    for (int startIndex = 0; startIndex < arraySize; startIndex++) {
        // Reset the sum for each new starting index.
        int currentSubarraySum = 0;
        // Expand the subarray by moving the ending index forward.
        for (int endIndex = startIndex; endIndex < arraySize; endIndex++) {
            // Add the current element to the subarray sum.
            currentSubarraySum += nums[endIndex];
            // Since the array contains only 0s and 1s,
            // the sum cannot decrease as the window expands.
            // Therefore, stop if the sum exceeds the goal.
            if (currentSubarraySum > goal) {
                break;
            }
            // If the current subarray sum equals the goal,
            // increment the count of valid subarrays.
            if (currentSubarraySum == goal) {
                totalSubarrays++;
            }
        }
    }
    // Return the total number of subarrays with the required sum.
    return totalSubarrays;
}
//-------------------------------------------//
// Prefix Sum + Unordered Map
// DRY - RUN
// nums = [1, 1, 0, 1, 0, 0, 1] , goal = 3
int numSubarraysWithSum02(vector<int>& nums, int goal) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Stores:
    // Prefix sum -> Number of times that prefix sum has appeared.
    //
    // The same prefix sum can appear multiple times.
    // Each occurrence can represent a different valid subarray.
    unordered_map<int, int> prefixSumFrequency;
    // Store the total number of valid subarrays.
    int totalSubarrays = 0;
    // Store the sum of elements from index 0 to the current index.
    int currentPrefixSum = 0;
    // Traverse the input array.
    for (int currentIndex = 0; currentIndex < arraySize; currentIndex++) {
        // Add the current element to the prefix sum.
        currentPrefixSum += nums[currentIndex];
        // --------------------------------------------------
        // Check whether the subarray [0 ... currentIndex]
        // has a sum equal to goal.
        // --------------------------------------------------
        //
        // If currentPrefixSum == goal:
        //
        // nums[0] + nums[1] + ... + nums[currentIndex] = goal
        //
        // Therefore, [0 ... currentIndex] is one valid subarray.
        //
        // This is an INDEPENDENT check.
        // Do not use else here because the next check
        // can also find another valid subarray at the same index.
        if (currentPrefixSum == goal) {
            totalSubarrays++;
        }
        // --------------------------------------------------
        // Check whether previous prefix sums can form
        // another subarray whose sum equals goal.
        // --------------------------------------------------
        //
        // We know:
        //
        // currentPrefixSum - previousPrefixSum = goal
        //
        // Therefore:
        //
        // previousPrefixSum = currentPrefixSum - goal
        //
        // So, search for currentPrefixSum - goal.
        int requiredPrefixSum = currentPrefixSum - goal;
        // If requiredPrefixSum appeared previously,
        // each occurrence represents one valid subarray
        // ending at currentIndex.
        //
        // Add its frequency because the same prefix sum
        // might have appeared multiple times.
        totalSubarrays += prefixSumFrequency[requiredPrefixSum];
        // Store the current prefix sum for future elements.
        //
        // If it already exists, increase its frequency.
        prefixSumFrequency[currentPrefixSum]++;
    }
    // Return the total number of valid subarrays.
    return totalSubarrays;
}

//-------------------------------------------//
// DRY-RUN
// nums = {1,0,0,1,1,0}
// k = 2
// Sliding Window: At Most K Technique
// Counts the number of subarrays whose sum is less than
// or equal to the given limit.
int countSubarraysWithSumLessThanOrEqualToK(
    const vector<int>& nums, int k) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Store the total number of valid subarrays.
    int totalSubarrays = 0;
    // Store the sum of elements in the current sliding window.
    int currentWindowSum = 0;
    // Starting index of the sliding window.
    int windowStart = 0;
    // A subarray sum cannot be less than or equal to a negative
    // limit because the array contains only 0s and 1s.
    if (k < 0) {
        return 0;
    }
    // Expand the sliding window by moving windowEnd forward.
    for (int windowEnd = 0; windowEnd < arraySize; windowEnd++) {
        // Add the current element to the window sum.
        currentWindowSum += nums[windowEnd];
        // Shrink the window while its sum exceeds the given limit.
        while (currentWindowSum > k) {
            // Remove the element at the starting position.
            currentWindowSum -= nums[windowStart];
            // Move the starting pointer forward.
            windowStart++;
        }
        // Every subarray ending at windowEnd and starting
        // anywhere from windowStart to windowEnd has a sum <= k.
        //
        // Number of such subarrays = windowEnd - windowStart + 1.
        totalSubarrays += (windowEnd - windowStart + 1);
    }
    // Return the total number of subarrays with sum <= k.
    return totalSubarrays;
}

// Counts the number of subarrays whose sum is exactly equal to goal.
int numSubarraysWithSum03(vector<int>& nums, int goal) {
    // Exactly(goal) = AtMost(goal) - AtMost(goal - 1).
    //
    // First function call:
    // Counts subarrays whose sum is <= goal.
    //
    // Second function call:
    // Counts subarrays whose sum is <= goal - 1.
    //
    // Subtracting both gives subarrays whose sum is exactly goal.
    return countSubarraysWithSumLessThanOrEqualToK(nums, goal)
         - countSubarraysWithSumLessThanOrEqualToK(nums, goal - 1);
}

//int main(){
////    vector<int> nums = {1,0,1,0,1};
////    cout << numSubarraysWithSum03(nums, 2) << endl;
////    vector<int> nums = {0,0,0,0,0};
////    cout << numSubarraysWithSum02(nums, 0) << endl;
//    vector<int> nums = {1,0,0,1,1,0};
//    cout << numSubarraysWithSum03(nums, 2) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 1248. Count Number of Nice Subarrays
// Brute Force Approach - Time Limit Exceeded
int numberOfSubarrays01(vector<int>& nums, int k) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Store the total number of nice subarrays.
    int totalSubarrays = 0;
    // Choose the starting index of each subarray.
    for (int startIndex = 0; startIndex < arraySize; startIndex++) {
        // Reset the odd number count for each new starting index.
        int currentOddNumberCount = 0;
        // Expand the subarray by moving the ending index forward.
        for (int endIndex = startIndex; endIndex < arraySize; endIndex++) {
            // Check whether the current element is odd.
            if (nums[endIndex] % 2 != 0) {
                currentOddNumberCount++;
            }
            // A nice subarray contains exactly k odd numbers.
            if (currentOddNumberCount == k) {
                totalSubarrays++;
            }
            // If the odd number count exceeds k, extending
            // the subarray cannot make it valid again.
            if (currentOddNumberCount > k) {
                break;
            }
        }
    }
    // Return the total number of nice subarrays.
    return totalSubarrays;
}

//-------------------------------------------//
// Sliding Window - At Most K Technique
// Counts the number of subarrays containing at most k odd numbers.
int countSubarraysWithOddCountLessThanOrEqualToK(
    vector<int>& nums, int k) {
    // Store the size of the input array.
    int arraySize = nums.size();
    // Store the total number of valid subarrays.
    int totalSubarrays = 0;
    // A negative odd-number limit is not possible.
    if (k < 0) {
        return 0;
    }
    // Starting index of the sliding window.
    int windowStart = 0;
    // Count the number of odd numbers in the current window.
    int currentOddCount = 0;
    // Expand the sliding window by moving windowEnd forward.
    for (int windowEnd = 0; windowEnd < arraySize; windowEnd++) {
        // Check whether the current element is odd.
        if (nums[windowEnd] % 2 != 0) {
            currentOddCount++;
        }
        // Shrink the window while the odd-number count
        // exceeds the allowed limit.
        while (currentOddCount > k) {
            // If the element leaving the window is odd,
            // decrease the odd-number count.
            if (nums[windowStart] % 2 != 0) {
                currentOddCount--;
            }
            // Move the starting pointer forward.
            windowStart++;
        }
        // Every subarray ending at windowEnd and starting
        // anywhere from windowStart to windowEnd contains
        // at most k odd numbers.
        //
        // Number of such subarrays = windowEnd - windowStart + 1.
        totalSubarrays += (windowEnd - windowStart + 1);
    }
    // Return the total number of subarrays containing at most k odd numbers.
    return totalSubarrays;
}

// Counts the number of nice subarrays containing exactly k odd numbers.
int numberOfSubarrays02(vector<int>& nums, int k) {
    // Exactly(k) = AtMost(k) - AtMost(k - 1).
    //
    // First call:
    // Counts subarrays containing at most k odd numbers.
    //
    // Second call:
    // Counts subarrays containing at most k - 1 odd numbers.
    //
    // Their difference gives subarrays containing exactly k odd numbers.
    return countSubarraysWithOddCountLessThanOrEqualToK(nums, k)
         - countSubarraysWithOddCountLessThanOrEqualToK(nums, k - 1);
}

//int main(){
////    vector<int> nums = {1,1,2,1,1};
////    cout << numberOfSubarrays01(nums, 3) << endl;
//    vector<int> nums = {2,2,2,1,2,2,1,2,2,2};
//    cout << numberOfSubarrays02(nums, 2) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
