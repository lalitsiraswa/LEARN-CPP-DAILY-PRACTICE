#include <iostream>
using namespace std;

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
