#include <iostream>
using namespace std;

// -------------------------------------------------- Print 1 - N --------------------------------------------------
void print1ToN(int n){
    if(n == 0){ // Step 3: Base Condition
        return;
    }
    print1ToN(n - 1); // Step 1: Hypothesis
    cout << n << endl; // Step 2: Induction
}

// -------------------------------------------------- factorial --------------------------------------------------
int factorial(int n){
    if(n == 1){
        return 1;
    }
    return n * factorial(n - 1);
}

// -------------------------------------------------- Sort An Array --------------------------------------------------
void insertElement(vector<int> &vect, int targetElement){
    if(vect.size() == 0 || vect[vect.size() - 1] <= targetElement){
        vect.push_back(targetElement);
        return;
    }
    int lastElement = vect[vect.size() - 1];
    vect.pop_back();
    insertElement(vect, targetElement);
    vect.push_back(lastElement);
}

void sortArray(vector<int> &vect){
    if(vect.size() == 1){
        return;
    }
    int lastElement = vect[vect.size() - 1];
    vect.pop_back();
    sortArray(vect);
    insertElement(vect, lastElement);
}

// -------------------------------------------------- Sort A Stack --------------------------------------------------
void insertElement(stack<int> &st, int targetElement){
    if(st.size() == 0 || st.top() >= targetElement){
        st.push(targetElement);
        return;
    }
    int topElement = st.top();
    st.pop();
    insertElement(st, targetElement);
    st.push(topElement);
}
void sortStack(stack<int> &st){
    if(st.size() == 0){
        return;
    }
    int topElement = st.top();
    st.pop();
    sortStack(st);
    insertElement(st, topElement);
}

// -------------------------------------------------- Delete Middle Element From Stack --------------------------------------------------
void midDelStack(stack<int> &st, int targetIndex){
    if(targetIndex == 1){
        st.pop();
        return;
    }
    int topElement = st.top();
    st.pop();
    midDelStack(st, targetIndex - 1);
    st.push(topElement);
}

void midDelStack(stack<int> &st){
    int targetIndex = (st.size()/2) + 1;
    midDelStack(st, targetIndex);
}

// -------------------------------------------------- Reverse Stack Using Recusrion --------------------------------------------------
void insertAtBottom(stack<int> &st, int element){
    if(st.size() == 0){
        st.push(element);
        return;
    }
    int topElement = st.top();
    st.pop();
    insertAtBottom(st, element);
    st.push(topElement);
}

void reverseStack(stack<int> &st){
    if(st.size() == 1){
        return;
    }
    int topElement = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, topElement);
}

// -------------------------------------------------- 779. K-th Symbol in Grammar --------------------------------------------------
int kthGrammar(int n, int k) {
    if(n == 1 && k == 1){
        return 0;
    }
    int length = pow(2, n - 1);
    int mid = length / 2;
    if(k <= mid){
        return kthGrammar(n - 1, k);
    }
    // else if (k > mid)
    return !(kthGrammar(n - 1, k - mid));
}

// -------------------------------------------------- Tower of Hanoi --------------------------------------------------
void towerOfHanoi(int source, int destination, int helper, int plateNumber) {
    if(plateNumber == 1){
        cout << "Moving plate " << plateNumber << " from " << source << " to " << destination << endl;
        return;
    }
    towerOfHanoi(source, helper, destination, plateNumber - 1);
    cout << "Moving plate " << plateNumber << " from " << source << " to " << destination << endl;
    towerOfHanoi(helper, destination, source, plateNumber - 1);
}

// -------------------------------------------------- String Subsets --------------------------------------------------
void subSets(string ip, string op) {
    if(ip.empty()){
        cout << op << endl;
        return;
    }
    string op1 = op;
    string op2 = op;
    op2.push_back(ip[0]);
    ip.erase(ip.begin());
    subSets(ip, op1);
    subSets(ip, op2);
    return;
}

// -------------------------------------------------- 78. Subsets --------------------------------------------------
void subsets(vector<vector<int>> &result, vector<int> &subset, int index, vector<int> &nums) {
    if(index == nums.size()){
        result.push_back(subset);
        return;
    }
    // Not Pick
    subsets(result, subset, index+1, nums);
    // Pick
    subset.push_back(nums[index]);
    subsets(result, subset, index+1, nums);
    subset.pop_back();
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> subset;
    subsets(result, subset, 0, nums);
    return result;
}

// -------------------------------------------------- String permutation with spaces --------------------------------------------------
void stringPermutationWithSpaces(string input, string output) {
    if(input.empty()){
        cout << output << endl;
        return;
    }
    // First character should always without space
    if(output.empty()){
        output = input[0];
        input.erase(input.begin());
        stringPermutationWithSpaces(input, output);
    }
    else{
        // Without Space
        string op1 = output;
        op1.push_back(input[0]);
        // With Space
        string op2 = output;
        op2.push_back('_');
        op2.push_back(input[0]);
        input.erase(input.begin());
        stringPermutationWithSpaces(input, op1);
        stringPermutationWithSpaces(input, op2);
    }
}

// -------------------------------------------------- 784. Letter Case Permutation --------------------------------------------------
void stringPermutationWithCaseChange01(string input, string output, vector<string> &result) {
    if(input.empty()){
        result.push_back(output);
        return;
    }
    char ip = input[0];
    string op1 = output;
    string op2 = output;
    // Capital Character
    if(ip >= 65 && ip <= 90){
        // No case change
        op1.push_back(ip);
        // Change case
        op2.push_back(ip + 32);
        input.erase(input.begin());
        stringPermutationWithCaseChange01(input, op1, result);
        stringPermutationWithCaseChange01(input, op2, result);
    }
    // Small Character
    else if(ip >= 97 &&ip <= 122){
        // No case change
        op1.push_back(ip);
        // Change case
        op2.push_back(ip - 32);
        input.erase(input.begin());
        stringPermutationWithCaseChange01(input, op1, result);
        stringPermutationWithCaseChange01(input, op2, result);
    }
    // Numerical
    else{
        // No case change
        op1.push_back(ip);
        input.erase(input.begin());
        stringPermutationWithCaseChange01(input, op1, result);
    }
}

void stringPermutationWithCaseChange02(string input, string output, vector<string> &result) {
    if(input.empty()){
        result.push_back(output);
        return;
    }
    char ip = input[0];
    string op1 = output;
    string op2 = output;
    // Check Digit
    if(ip >= 48 && ip <= 57){
        // No case change
        op1.push_back(ip);
        input.erase(input.begin());
        stringPermutationWithCaseChange02(input, op1, result);
    }
    else {
        // Lowercase Scenario
        op1.push_back(tolower(ip));
        // Uppercase Scenario
        op2.push_back(toupper(ip));
        input.erase(input.begin());
        stringPermutationWithCaseChange02(input, op1, result);
        stringPermutationWithCaseChange02(input, op2, result);
    }
}

vector<string> letterCasePermutation(string s) {
    vector<string> result;
    string output = "";
    // stringPermutationWithCaseChange01(s, output, result);
    stringPermutationWithCaseChange02(s, output, result);
    return result;
}

// -------------------------------------------------- 22. Generate Parentheses --------------------------------------------------
void generateParenthesis(int openParenthesisCount, int closeParenthesisCount, string &temp, vector<string> &result) {
    if(openParenthesisCount == 0 && closeParenthesisCount == 0){
        result.push_back(temp);
        return;
    }
    if(openParenthesisCount != 0){
        temp.push_back('(');
        generateParenthesis(openParenthesisCount - 1, closeParenthesisCount, temp, result);
        temp.pop_back();
    }
    if(openParenthesisCount < closeParenthesisCount){
        temp.push_back(')');
        generateParenthesis(openParenthesisCount, closeParenthesisCount - 1, temp, result);
        temp.pop_back();
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    string temp;
    generateParenthesis(n, n, temp, result);
    for(auto item : result){
        cout << item << endl;
    }
    return result;
}

// -------------------------------------------------- Print N-bit binary numbers having more 1’s than or equal to 0’s for any prefix --------------------------------------------------

void NBitBinary(int n, int onesCount, int zerosCount, string &bitBinary, vector<string> &bitBinaries) {
    if(n == 0){
        bitBinaries.push_back(bitBinary);
        return;
    }
    bitBinary.push_back('1');
    NBitBinary(n - 1, onesCount + 1, zerosCount, bitBinary, bitBinaries);
    bitBinary.pop_back();
    if(onesCount > zerosCount){
        bitBinary.push_back('0');
        NBitBinary(n - 1, onesCount, zerosCount + 1, bitBinary, bitBinaries);
        bitBinary.pop_back();
    }
}

vector<string> NBitBinary(int n) {
    vector<string> bitBinaries;
    string bitBinary;
    int onesCount = 0;
    int zerosCount = 0;
    NBitBinary(n, onesCount, zerosCount, bitBinary, bitBinaries);
    for(auto item : bitBinaries){
        cout << item << endl;
    }
    return bitBinaries;
}

// -------------------------------------------------- Josephus Problem | Game of Death in a circle | Execution in Circle --------------------------------------------------
void josephus(int index, vector<int> vect, int k, int &ans) {
    if(vect.size() == 1){
        ans = vect[0];
        return;
    }
    index = (index + k) % vect.size();
    vect.erase(vect.begin() + index);
    josephus(index, vect, k, ans);
}
int josephus(int n, int k) {
    vector<int> vect; // Person Arrays
    for(int i = 1; i <= n; i++){
        vect.push_back(i);
    }
    k = k - 1;
    int index = 0; // Sward for killing the target person
    int ans = -1; // To store the number of the last person
    josephus(index, vect, k, ans);
    return ans;
}

int main(){
//    cout << josephus(40, 7) << endl;
    cout << josephus(10, 4) << endl;
    return 0;
}



