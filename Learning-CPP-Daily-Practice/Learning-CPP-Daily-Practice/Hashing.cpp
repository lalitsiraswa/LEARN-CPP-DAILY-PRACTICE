#include<iostream>
using namespace std;

//-------------------------------------------//-------------------------------------------//
vector<int> twoSum01(vector<int>& nums, int target) {
    unordered_map<int, int> visited;
    for(int i = 0; i < nums.size(); i++){
        int required = target - nums[i];
        if(visited.count(required)){
            return {i, visited[required]};
        }
        visited[nums[i]] = i;
    }
    return {};
}

//int main(){
//    vector<int> nums = {1, 3, 5, -7, 6, -3};
//    vector<int> result = twoSum01(nums, 0);
//    cout << result[0] << ", " << result[1] << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
