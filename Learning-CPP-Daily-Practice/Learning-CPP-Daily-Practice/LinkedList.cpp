#include<iostream>
using namespace std;

struct ListNode{
    int value;
    ListNode *next;
    ListNode(): value(0), next(nullptr){}
    ListNode(int value): value(value), next(nullptr){}
    ListNode(int value, ListNode* next): value(value), next(next){}
};

void printLinkedList(ListNode* node){
    while(node != nullptr){
        cout << node->value << " -> ";
        node = node->next;
    }
    cout << "nullptr" << endl;
}

//-------------------------------------------//-------------------------------------------//
// 876. Middle of the Linked List
ListNode* middleNode(ListNode* head) {
    // Handle an empty linked list.
    if(head == nullptr){
        return head;
    }
    // Initialize both pointers at the head.
    ListNode* slowPointer = head;
    ListNode* fastPointer = head;
    // Move slowPointer one step and fastPointer two steps.
    while(fastPointer != nullptr && fastPointer->next != nullptr){
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
    }
    // When fastPointer reaches the end,
    // slowPointer points to the middle node.
    return slowPointer;
}


//int main(){
//    ListNode* node1 = new ListNode(1);
//    ListNode* node2 = new ListNode(2);
//    ListNode* node3 = new ListNode(3);
//    ListNode* node4 = new ListNode(4);
//    ListNode* node5 = new ListNode(5);
//    ListNode* node6 = new ListNode(6);
//    node1->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    node5->next = node6;
//    printLinkedList(node1);
//    ListNode* middleNodePointer = middleNode(node1);
//    printLinkedList(middleNodePointer);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 160. Intersection of Two Linked Lists
// Calculate the total number of nodes in the linked list.
int findLinkedListSize(ListNode* head) {
    ListNode* currentNode = head;
    int listSize = 0;
    // Traverse the linked list and count each node.
    while(currentNode != nullptr){
        listSize += 1;
        currentNode = currentNode->next;
    }
    return listSize;
}

// Move the starting pointer forward by N nodes.
ListNode* shiftStartingPointerByLengthN(ListNode* head, int n) {
    ListNode* currentNode = head;
    // Skip the first N nodes.
    while(n){
        currentNode = currentNode->next;
        n -= 1;
    }
    return currentNode;
}

// Find the intersection node of two linked lists.
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    // If either linked list is empty, intersection is not possible.
    if(headA == nullptr || headB == nullptr){
        return nullptr;
    }
    // Calculate the lengths of both linked lists.
    int listLength1 = findLinkedListSize(headA);
    int listLength2 = findLinkedListSize(headB);
    // Calculate the difference between the lengths.
    int lengthDifference = abs(listLength1 - listLength2);
    // Initialize pointers at the beginning of both linked lists.
    ListNode* pointerA = headA;
    ListNode* pointerB = headB;
    // Move the pointer of the longer linked list forward
    // so that both pointers have the same number of nodes remaining.
    if(listLength1 > listLength2){
        pointerA = shiftStartingPointerByLengthN(headA, lengthDifference);
    }
    else{
        pointerB = shiftStartingPointerByLengthN(headB, lengthDifference);
    }
    // Traverse both linked lists simultaneously.
    while(pointerA != nullptr && pointerB != nullptr){
        // Compare node addresses, not node values.
        // If addresses match, the intersection node is found.
        if(pointerA == pointerB){
            return pointerA;
        }
        pointerA = pointerA->next;
        pointerB = pointerB->next;
    }
    // No intersection node found.
    return nullptr;
}

//-------------------------------------------//
// TUF Two Pointer Switching Approach Approach
ListNode* getIntersectionNodeTuf(ListNode* headA, ListNode* headB) {
    // If either linked list is empty, intersection is not possible.
    if(headA == nullptr || headB == nullptr){
        return nullptr;
    }
    // Initialize both pointers at the beginning of their respective lists.
    ListNode* tempA = headA;
    ListNode* tempB = headB;
    while(tempA != tempB){
        // Move both pointers one node forward.
        tempA = tempA->next;
        tempB = tempB->next;
        // Check whether both pointers have reached the same node.
        if(tempA == tempB){
            return tempA;
        }
        // If pointer A reaches the end of List A, redirect it to List B.
        if(tempA == nullptr){
            tempA = headB;
        }
        // If pointer B reaches the end of List B, redirect it to List A.
        if(tempB == nullptr){
            tempB = headA;
        }
    }
    // Return the intersection node, or nullptr if no intersection exists.
    return tempA;
}

//int main(){
//    ListNode* head1 = new ListNode(4);
//    ListNode* node2 = new ListNode(1);
//    ListNode* node3 = new ListNode(8);
//    ListNode* node4 = new ListNode(4);
//    ListNode* node5 = new ListNode(5);
//    head1->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    printLinkedList(head1);
//    ListNode* head2 = new ListNode(5);
//    ListNode* node02 = new ListNode(6);
//    ListNode* node03 = new ListNode(1);
//    head2->next = node02;
//    node02->next = node03;
//    node03->next = node3;
//    printLinkedList(head2);
//    ListNode* intersectionNode = getIntersectionNodeTuf(head1, head2);
//    printLinkedList(intersectionNode);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
