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
void bubbleSort(vector<int>& nums) {
    int n = nums.size();
    for(int i = 0; i < n - 1; i++){
        int isAlreadySorted = 1;
        for(int j = 0; j < (n - 1) - i; j++){
            if(nums[j] > nums[j + 1]){
                swap(nums[j], nums[j + 1]);
                isAlreadySorted = 0;
            }
        }
        cout << "RUNNER : " << i + 1 << endl;
        if(isAlreadySorted){
            break;
        }
    }
}

//----------------------------------------------//----------------------------------------------//
int main(){
    vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
//    selectionSort(nums);
    bubbleSort(nums);
    for(auto item : nums){
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
