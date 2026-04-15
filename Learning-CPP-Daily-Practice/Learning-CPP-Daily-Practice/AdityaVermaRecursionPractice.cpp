#include <iostream>
using namespace std;

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

int main(){
    string input = "ABC";
    string output = "";
    stringPermutationWithSpaces(input, output);
    return 0;
}
