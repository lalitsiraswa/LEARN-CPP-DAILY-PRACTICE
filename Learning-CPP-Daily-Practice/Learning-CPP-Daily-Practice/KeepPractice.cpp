#include<iostream>
using namespace std;

// -------------------------------------------- Printing Number in Descending order --------------------------------------------

int findMax(vector<int> &nums, int previousMax){
    int currentMax = INT_MIN;
    __SIZE_TYPE__ n = nums.size();
    for(int i = 0; i < n; i++){
        if(nums[i] > currentMax && nums[i] < previousMax){
            currentMax = nums[i];
        }
    }
    return currentMax==INT_MIN ? nums[0] : currentMax;
}

void printNumInDescending(vector<int>& nums) {
    __SIZE_TYPE__ n = nums.size();
    int previousMax = INT_MAX;
    for(int i = 0; i < n; i++){
        previousMax = findMax(nums, previousMax);
        cout << previousMax << endl;
    }
}

//int main(){
//    vector<int> nums = {3,6,7,11};
//    printNumInDescending(nums);
//    return 0;
//}
