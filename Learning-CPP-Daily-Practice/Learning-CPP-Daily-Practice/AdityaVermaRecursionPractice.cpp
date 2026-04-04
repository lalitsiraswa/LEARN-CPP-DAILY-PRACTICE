#include <iostream>
using namespace std;

// -------------------------------------------------- Tower of Hanoi --------------------------------------------------
void towerOfHanoi(int source, int destination, int helper, int plateNumber) {
    if(plateNumber == 1){
        cout << "Moving plate " << plateNumber << " from " << source << " to " << destination << endl;
        return;
    }
    towerOfHanoi(source, helper, destination, plateNumber - 1);
    cout << "Moving plate " << plateNumber << " from " << source << " to " << destination << endl;
    towerOfHanoi(helper, destination, source, plateNumber - 1);
}

int main(){
    int plateNumber = 4;
    int source = 1;
    int destination = 2;
    int helper = 3;
    towerOfHanoi(source, destination, helper, plateNumber);
    return 0;
}
