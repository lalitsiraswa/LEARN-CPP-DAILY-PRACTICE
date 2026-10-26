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

int main(){
//    string s = "abcabcbb";
//    string s = "ccbbcc";
//    string s = "abcabcbbdefghijklmno";
    string s = "cadbzabcd";
    cout << lengthOfLongestSubstring03(s) << endl;
    return 0;
}

//-------------------------------------------//-------------------------------------------//
