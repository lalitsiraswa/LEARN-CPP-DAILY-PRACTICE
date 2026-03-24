#include <iostream>
using namespace std;

// -------------------------------------------------- Reverse Stack Using Recusrion --------------------------------------------------
void insertAtBottom(stack<int> &st, int element){
    if(st.size() == 0){
        st.push(element);
        return;
    }
    int topElement = st.top();
    st.pop();
    insertAtBottom(st, element);
    st.push(topElement);
}

void reverseStack(stack<int> &st){
    if(st.size() == 1){
        return;
    }
    int topElement = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, topElement);
}

int main(){
    stack<int> st;
    st.push(5);
    st.push(4);
    st.push(3);
    st.push(2);
    st.push(1);
    reverseStack(st);
    while(!st.empty()){
        cout << st.top() << endl;
        st.pop();
    }
    return 0;
}
