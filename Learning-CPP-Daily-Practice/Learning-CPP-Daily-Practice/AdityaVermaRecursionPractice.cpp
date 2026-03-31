#include <iostream>
using namespace std;

// -------------------------------------------------- 779. K-th Symbol in Grammar --------------------------------------------------
int kthGrammar(int n, int k) {
    if(n == 1 && k == 1){
        return 0;
    }
    int length = pow(2, n - 1);
    int mid = length / 2;
    if(k <= mid){
        return kthGrammar(n - 1, k);
    }
    // else if (k > mid)
    return !(kthGrammar(n - 1, k - mid));
}

int main(){
    cout << kthGrammar(4, 3) << endl;
    return 0;
}
