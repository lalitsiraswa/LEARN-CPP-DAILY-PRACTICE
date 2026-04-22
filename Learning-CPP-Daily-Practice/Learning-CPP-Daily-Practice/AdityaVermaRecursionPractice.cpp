#include <iostream>
using namespace std;

// -------------------------------------------------- Josephus Problem | Game of Death in a circle | Execution in Circle --------------------------------------------------
void josephus(int index, vector<int> vect, int k, int &ans) {
    if(vect.size() == 1){
        ans = vect[0];
        return;
    }
    index = (index + k) % vect.size();
    vect.erase(vect.begin() + index);
    josephus(index, vect, k, ans);
}
int josephus(int n, int k) {
    vector<int> vect; // Person Arrays
    for(int i = 1; i <= n; i++){
        vect.push_back(i);
    }
    k = k - 1;
    int index = 0; // Sward for killing the target person
    int ans = -1; // To store the number of the last person
    josephus(index, vect, k, ans);
    return ans;
}

int main(){
//    cout << josephus(40, 7) << endl;
    cout << josephus(10, 4) << endl;
    return 0;
}
