#include <iostream>
using namespace std;

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

int main(){
    string s = "aBc";
    vector<string> result = letterCasePermutation(s);
    for(auto item : result){
        cout << item << endl;
    }
    return 0;
}
