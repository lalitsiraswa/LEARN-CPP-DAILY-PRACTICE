#include <iostream>
using namespace std;

// -------------------------------------------------- String Subsets --------------------------------------------------
void subSets(string ip, string op) {
    if(ip.empty()){
        cout << op << endl;
        return;
    }
    string op1 = op;
    string op2 = op;
    op2.push_back(ip[0]);
    ip.erase(ip.begin());
    subSets(ip, op1);
    subSets(ip, op2);
    return;
}

int main(){
    string ip = "abc";
    string op = "";
    subSets(ip, op);
    return 0;
}
