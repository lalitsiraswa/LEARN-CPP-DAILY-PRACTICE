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
// 234. Palindrome Linked List
// Find the middle node and disconnect the first half of the linked list.
ListNode* isPalindromeFindMiddleNodeHelper(ListNode* head){
    // Handle an empty linked list.
    if(head == nullptr){
        return head;
    }
    // Initialize slow and fast pointers at the head.
    ListNode* slowPointer = head;
    ListNode* fastPointer = head;
    // Keep track of the node before the slow pointer.
    ListNode* previousNode = nullptr;
    // Move slowPointer one step and fastPointer two steps.
    while(fastPointer != nullptr && fastPointer->next != nullptr){
        previousNode = slowPointer;
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
    }
    // Disconnect the first half from the second half.
    // For a single-node list, previousNode remains nullptr.
    if(previousNode){
        previousNode->next = nullptr;
    }
    // Return the middle node, which is the starting node of the second half.
    return slowPointer;
}

// Reverse the linked list and return its new head.
ListNode* isPalindromeReverseLinkedListHelper(ListNode* head){
    ListNode* currentNode = head;
    ListNode* previousNode = nullptr;
    ListNode* newHead = nullptr;
    // Reverse the links of the linked list.
    while(currentNode != nullptr){
        // Store the current node as the new head.
        newHead = currentNode;
        // Move currentNode forward before changing its next pointer.
        currentNode = currentNode->next;
        // Reverse the link to point towards the previous node.
        newHead->next = previousNode;
        // Update previousNode for the next iteration.
        previousNode = newHead;
    }
    // Return the new head of the reversed linked list.
    return newHead;
}

// Check whether the linked list is a palindrome.
bool isPalindrome(ListNode* head){
    // An empty or single-node linked list is always a palindrome.
    if(head == nullptr || head->next == nullptr){
        return true;
    }
    // Keep the head of the first half unchanged.
    ListNode* head1 = head;
    // Find the middle node and disconnect the two halves.
    ListNode* head2 = isPalindromeFindMiddleNodeHelper(head);
    // Reverse the second half of the linked list.
    head2 = isPalindromeReverseLinkedListHelper(head2);
    printLinkedList(head1);
    printLinkedList(head2);
    // Compare both halves node by node.
    while(head1 != nullptr && head2 != nullptr){
        // If corresponding node values differ, it is not a palindrome.
        if(head1->value != head2->value){
            return false;
        }
        // Move both pointers forward.
        head1 = head1->next;
        head2 = head2->next;
    }
    // All corresponding node values match.
    return true;
}

//-------------------------------------------//
// Find the middle node and disconnect the first half of the linked list.
ListNode* isPalindromeFindMiddleNodeHelper01(ListNode* head){
    // Handle an empty linked list.
    if(head == nullptr){
        return head;
    }
    // Initialize slow and fast pointers at the head.
    ListNode* slowPointer = head;
    ListNode* fastPointer = head;
    // Move slowPointer one step and fastPointer two steps.
    while(fastPointer != nullptr && fastPointer->next != nullptr){
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
    }
    // Return the middle node, which is the starting node of the second half.
    return slowPointer;
}

// Reverse the linked list and return its new head.
ListNode* isPalindromeReverseLinkedListHelper01(ListNode* head){
    ListNode* currentNode = head;
    ListNode* previousNode = nullptr;
    ListNode* newHead = nullptr;
    // Reverse the links of the linked list.
    while(currentNode != nullptr){
        // Store the current node as the new head.
        newHead = currentNode;
        // Move currentNode forward before changing its next pointer.
        currentNode = currentNode->next;
        // Reverse the link to point towards the previous node.
        newHead->next = previousNode;
        // Update previousNode for the next iteration.
        previousNode = newHead;
    }
    // Return the new head of the reversed linked list.
    return newHead;
}

// Check whether the linked list is a palindrome.
bool isPalindrome01(ListNode* head){
    // An empty or single-node linked list is always a palindrome.
    if(head == nullptr || head->next == nullptr){
        return true;
    }
    // Keep the head of the first half unchanged.
    ListNode* head1 = head;
    // Find the middle node and disconnect the two halves.
    ListNode* head2 = isPalindromeFindMiddleNodeHelper01(head);
    // Reverse the second half of the linked list.
    head2 = isPalindromeReverseLinkedListHelper01(head2);
    printLinkedList(head1);
    printLinkedList(head2);
    // Compare both halves node by node.
    while(head1 != nullptr && head2 != nullptr){
        // If corresponding node values differ, it is not a palindrome.
        if(head1->value != head2->value){
            return false;
        }
        // Move both pointers forward.
        head1 = head1->next;
        head2 = head2->next;
    }
    // All corresponding node values match.
    return true;
}

//int main(){
//    ListNode* head = new ListNode(1);
//    ListNode* node2 = new ListNode(2);
//    ListNode* node3 = new ListNode(3);
//    ListNode* node4 = new ListNode(3);
//    ListNode* node5 = new ListNode(2);
//    ListNode* node6 = new ListNode(1);
//    head->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    node5->next = node6;
////    printLinkedList(head);
//    cout << isPalindrome01(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
