#include <iostream>
using namespace std;

// -------------------------------------------------- Delete Middle Element From Stack --------------------------------------------------
void midDelStack(stack<int> &st, int targetIndex){
    if(targetIndex == 1){
        st.pop();
        return;
    }
    int topElement = st.top();
    st.pop();
    midDelStack(st, targetIndex - 1);
    st.push(topElement);
}

void midDelStack(stack<int> &st){
    int targetIndex = (st.size()/2) + 1;
    midDelStack(st, targetIndex);
}

int main(){
    stack<int> st;
    st.push(5);
    st.push(4);
    st.push(3);
    st.push(2);
    st.push(1);
    midDelStack(st);
    while(!st.empty()){
        cout << st.top() << endl;
        st.pop();
    }
    return 0;
}
