#include <iostream>
using namespace std;

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

int main(){
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = subsets(nums);
    for (auto it = result.begin(); it != result.end(); ++it) {
        cout << "{";
        for (auto jt = it->begin(); jt != it->end(); ++jt) {
            cout << *jt;
            if (next(jt) != it->end())
                cout << ", ";
        }
        cout << "}" << endl;
    }
    return 0;
}
