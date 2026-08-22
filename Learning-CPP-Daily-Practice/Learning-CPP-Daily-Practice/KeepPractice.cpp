#include<iostream>
using namespace std;

// -------------------------------------------- 875. Koko Eating Bananas --------------------------------------------
int minEatingSpeedBruteForce(vector<int>& piles, int h) {
    int max_val = *max_element(piles.begin(), piles.end());
    int k = max_val;
    for(k; k >= 1; k--){
        int currHour = 0;
        for(int pile : piles){
            currHour += (pile + k - 1) / k;
//            if(pile <= k){
//                currHour++;
//            }
//            else{
//                currHour += (pile/k) + 1;
//            }
            if(currHour > h){
                k++;
                return k;
            }
        }
    }
    k++;
    return k;
}

int main(){
    vector<int> piles = {3,6,7,11};
    int h = 8;
    cout << minEatingSpeedBruteForce(piles, h) << endl;
    return 0;
}

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
