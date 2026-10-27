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
