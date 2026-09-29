#include<iostream>
using namespace std;

void selectionSort(vector<int>& nums) {
    int n = nums.size();
    vector<int> result;
    for(int i = 0; i < n - 1; i++){
        int minValueIndex = i;
        for(int j = i + 1; j < n; j++){
            if(nums[j] <= nums[minValueIndex]){
                minValueIndex = j;
            }
        }
        swap(nums[i], nums[minValueIndex]);
    }
}

//----------------------------------------------//----------------------------------------------//

int main(){
    vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    selectionSort(nums);
    for(auto item : nums){
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
