#include <iostream>
using namespace std;

// -------------------------------------------------- Print N-bit binary numbers having more 1’s than or equal to 0’s for any prefix --------------------------------------------------

void NBitBinary(int n, int onesCount, int zerosCount, string &bitBinary, vector<string> &bitBinaries) {
    if(n == 0){
        bitBinaries.push_back(bitBinary);
        return;
    }
    bitBinary.push_back('1');
    NBitBinary(n - 1, onesCount + 1, zerosCount, bitBinary, bitBinaries);
    bitBinary.pop_back();
    if(onesCount > zerosCount){
        bitBinary.push_back('0');
        NBitBinary(n - 1, onesCount, zerosCount + 1, bitBinary, bitBinaries);
        bitBinary.pop_back();
    }
}

vector<string> NBitBinary(int n) {
    vector<string> bitBinaries;
    string bitBinary;
    int onesCount = 0;
    int zerosCount = 0;
    NBitBinary(n, onesCount, zerosCount, bitBinary, bitBinaries);
    for(auto item : bitBinaries){
        cout << item << endl;
    }
    return bitBinaries;
}

int main(){
    NBitBinary(3);
    return 0;
}
