#include <iostream>
using namespace std;

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

int main(){
    generateParenthesis(2);
    return 0;
}
