#include <iostream>
using namespace std;

// -------------------------------------------------- Print 1 - N --------------------------------------------------
void print1ToN(int n){
    if(n == 0){ // Step 3: Base Condition
        return;
    }
    print1ToN(n - 1); // Step 1: Hypothesis
    cout << n << endl; // Step 2: Induction
}

// -------------------------------------------------- factorial --------------------------------------------------
int factorial(int n){
    if(n == 1){
        return 1;
    }
    return n * factorial(n - 1);
}

// -------------------------------------------------- Sort An Array --------------------------------------------------
void insertElement(vector<int> &vect, int targetElement){
    if(vect.size() == 0 || vect[vect.size() - 1] <= targetElement){
        vect.push_back(targetElement);
        return;
    }
    int lastElement = vect[vect.size() - 1];
    vect.pop_back();
    insertElement(vect, targetElement);
    vect.push_back(lastElement);
}

void sortArray(vector<int> &vect){
    if(vect.size() == 1){
        return;
    }
    int lastElement = vect[vect.size() - 1];
    vect.pop_back();
    sortArray(vect);
    insertElement(vect, lastElement);
}

// -------------------------------------------------- Sort A Stack --------------------------------------------------
void insertElement(stack<int> &st, int targetElement){
    if(st.size() == 0 || st.top() >= targetElement){
        st.push(targetElement);
        return;
    }
    int topElement = st.top();
    st.pop();
    insertElement(st, targetElement);
    st.push(topElement);
}
void sortStack(stack<int> &st){
    if(st.size() == 0){
        return;
    }
    int topElement = st.top();
    st.pop();
    sortStack(st);
    insertElement(st, topElement);
}


int main(){
    stack<int> st;
    st.push(7);
    st.push(4);
    st.push(9);
    st.push(2);
    st.push(5);
    sortStack(st);
    while(!st.empty()){
        cout << st.top() << endl;
        st.pop();
    }
    return 0;
}
