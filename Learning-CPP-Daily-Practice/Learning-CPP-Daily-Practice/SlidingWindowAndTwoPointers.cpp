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
