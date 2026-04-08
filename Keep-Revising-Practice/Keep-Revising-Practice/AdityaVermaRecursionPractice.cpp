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

// -------------------------------------------------- String - Print unique subsets --------------------------------------------------
void subsets(string input, string output, vector<string> &allSubSets) {
    if(input.empty()){
        allSubSets.push_back(output);
        return;
    }
    // Not Pick
    string op1 = output;
    string op2 = output;
    // Pick
    op2.push_back(input[0]);
    input.erase(input.begin());
    subsets(input, op1, allSubSets);
    subsets(input, op2, allSubSets);
    return;
}

vector<string> findSubSets(string &input) {
    vector<string> allSubSets;
    string output = "";
    subsets(input, output, allSubSets);
    unordered_map<string, int> mp;
    vector<string> uniqueSubSets;
    for(auto set : allSubSets){
        if(mp.find(set) == mp.end()){
            mp.insert({set, 1});
            uniqueSubSets.push_back(set);
        }
    }
    for(auto set : uniqueSubSets){
        cout << set << endl;
    }
    return uniqueSubSets;
}

int main(){
    string input = "aab";
    vector<string> subsets = findSubSets(input);
    return 0;
}

