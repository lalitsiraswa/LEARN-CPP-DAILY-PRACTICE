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
// 141. Linked List Cycle
bool hasCycle(ListNode* head) {
    // Initialize both pointers at the head of the linked list.
    // slowNode moves one node at a time.
    // fastNode moves two nodes at a time.
    ListNode* slowNode = head;
    ListNode* fastNode = head;
    // Continue traversing as long as:
    // 1. fastNode is not nullptr.
    // 2. fastNode->next is not nullptr.
    //
    // We check both conditions because fastNode moves two steps
    // at a time, so we must ensure that both steps are valid.
    while (fastNode != nullptr && fastNode->next != nullptr) {
        // Move slowNode one step forward.
        slowNode = slowNode->next;
        // Move fastNode two steps forward.
        fastNode = fastNode->next->next;
        // If both pointers point to the same node,
        // a cycle exists in the linked list.
        //
        // In a cyclic linked list, the faster pointer will
        // eventually catch up with the slower pointer.
        if (slowNode == fastNode) {
            return true;
        }
    }
    // If fastNode reaches nullptr, there is no cycle.
    return false;
}


//int main(){
//    ListNode* head = new ListNode(1);
//    ListNode* node2 = new ListNode(2);
//    ListNode* node3 = new ListNode(3);
//    ListNode* node4 = new ListNode(4);
//    ListNode* node5 = new ListNode(5);
//    head->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    node5->next = node2;
//    cout << hasCycle(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 19. Remove Nth Node From End of List
ListNode* removeNthFromEnd(ListNode* head, int n) {
    // Tracks the number of nodes traversed in the linked list.
    int listLength = 1;
    // Both pointers initially point to the head.
    // currentNode will eventually point to the node that needs to be deleted.
    // traversalNode is used to traverse the linked list.
    ListNode* currentNode = head;
    ListNode* traversalNode = head;
    // Keeps track of the node immediately before currentNode.
    ListNode* previousNode = nullptr;
    // Move traversalNode until it reaches the last node.
    while (traversalNode->next != nullptr) {
        // Move traversalNode one step forward.
        traversalNode = traversalNode->next;
        // Increment the total number of nodes traversed.
        listLength += 1;
        // Once the number of traversed nodes becomes greater than n,
        // start moving currentNode and previousNode.
        //
        // This maintains a gap of n nodes between traversalNode
        // and currentNode.
        if (listLength > n) {
            // Move previousNode to the current position of currentNode.
            previousNode = currentNode;
            // Move currentNode one step forward.
            currentNode = currentNode->next;
        }
    }
    // If listLength equals n, the first node needs to be deleted.
    // This happens when we need to remove the Nth node from the end
    // and that node is the head itself.
    if (listLength == n) {
        // Store the current head so that we can delete it.
        ListNode* nodeToDelete = head;
        // Update head to point to the second node.
        head = head->next;
        // Delete the original head node to free its memory.
        delete nodeToDelete;
        return head;
    }
    // Skip currentNode by connecting previousNode directly
    // to the node after currentNode.
    previousNode->next = currentNode->next;
    // Delete the target node to free its memory.
    delete currentNode;
    return head;
}


//int main(){
//    ListNode* head = new ListNode(1);
//    ListNode* node2 = new ListNode(2);
//    ListNode* node3 = new ListNode(3);
//    ListNode* node4 = new ListNode(4);
//    ListNode* node5 = new ListNode(5);
//    ListNode* node6 = new ListNode(6);
//    head->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    node5->next = node6;
//    printLinkedList(head);
//    head = removeNthFromEnd(head, 5);
//    printLinkedList(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 142. Linked List Cycle II
ListNode* detectCycle(ListNode* head) {
    // Initialize both pointers at the head of the linked list.
    // slowNode moves one step at a time.
    // fastNode moves two steps at a time.
    ListNode* slowNode = head;
    ListNode* fastNode = head;
    // PHASE 1: Detect whether a cycle exists.
    //
    // Continue traversing while fastNode and its next node
    // are not nullptr.
    while (fastNode != nullptr && fastNode->next != nullptr) {
        // Move slowNode one step forward.
        slowNode = slowNode->next;
        // Move fastNode two steps forward.
        fastNode = fastNode->next->next;
        // If both pointers meet, a cycle exists.
        if (slowNode == fastNode) {
            break;
        }
    }
    // If fastNode reaches nullptr or its next node is nullptr,
    // the linked list does not contain a cycle.
    if (fastNode == nullptr || fastNode->next == nullptr) {
        return nullptr;
    }
    // PHASE 2: Find the starting node of the cycle.
    //
    // Move slowNode back to the head of the linked list.
    // Keep fastNode at the meeting point.
    slowNode = head;
    // Move both pointers one step at a time.
    // They will meet at the starting node of the cycle.
    while (slowNode != fastNode) {
        slowNode = slowNode->next;
        fastNode = fastNode->next;
    }
    // Both pointers meet at the beginning of the cycle.
    return slowNode;
}

//int main(){
//    ListNode* head = new ListNode(1);
//    ListNode* node2 = new ListNode(2);
//    ListNode* node3 = new ListNode(3);
//    ListNode* node4 = new ListNode(4);
//    ListNode* node5 = new ListNode(5);
//    head->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    node5->next = node2;
//    ListNode* startCycleNode = detectCycle(head);
//    cout << startCycleNode->value << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// Cycle Length in Linked List - GFG
int lengthOfLoop(ListNode* head) {
    // Initialize both pointers at the head of the linked list.
    // slowNode moves one step at a time.
    // fastNode moves two steps at a time.
    ListNode* slowNode = head;
    ListNode* fastNode = head;
    // Stores the total number of nodes present in the cycle.
    int cycleLength = 0;
    // PHASE 1: Detect whether a cycle exists.
    //
    // Continue traversing while fastNode and its next node
    // are not nullptr.
    while (fastNode != nullptr && fastNode->next != nullptr) {
        // Move slowNode one step forward.
        slowNode = slowNode->next;
        // Move fastNode two steps forward.
        fastNode = fastNode->next->next;
        // If both pointers meet, a cycle exists.
        if (slowNode == fastNode) {
            break;
        }
    }
    // If fastNode reaches nullptr or its next node is nullptr,
    // the linked list does not contain a cycle.
    if (fastNode == nullptr || fastNode->next == nullptr) {
        return 0;
    }
    // PHASE 2: Calculate the length of the cycle.
    //
    // Both pointers are currently at the same meeting node.
    // Keep fastNode stationary and move slowNode around the cycle
    // until it reaches the meeting node again.
    while (true) {
        // Move slowNode one step forward inside the cycle.
        slowNode = slowNode->next;
        // Count each node visited inside the cycle.
        cycleLength += 1;
        // If slowNode reaches the meeting node again,
        // one complete cycle has been traversed.
        if (slowNode == fastNode) {
            break;
        }
    }
    // Return the total number of nodes in the cycle.
    return cycleLength;
}

//int main(){
//    ListNode* head = new ListNode(1);
//    ListNode* node2 = new ListNode(2);
//    ListNode* node3 = new ListNode(3);
//    ListNode* node4 = new ListNode(4);
//    ListNode* node5 = new ListNode(5);
//    head->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    node5->next = node2;
//    cout << lengthOfLoop(head) << endl;
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 206. Reverse Linked List
ListNode* reverseList(ListNode* head) {
    // Points to the current node being processed.
    ListNode* currentNode = head;
    // Represents the head of the reversed linked list.
    // Initially nullptr because the reversed list is empty.
    ListNode* reversedHead = nullptr;
    // Keeps track of the previous node.
    // Initially nullptr because the original head
    // will become the last node after reversal.
    ListNode* previousNode = nullptr;
    // Traverse the entire linked list.
    while (currentNode != nullptr) {
        // Update reversedHead to the current node.
        // Eventually, it will point to the new head.
        reversedHead = currentNode;
        // Store the next node before changing the current
        // node's next pointer.
        currentNode = currentNode->next;
        // Reverse the link of the current node.
        // Instead of pointing to the next node,
        // it now points to the previous node.
        reversedHead->next = previousNode;
        // Move previousNode forward to the current node.
        // This node will become the previous node
        // in the next iteration.
        previousNode = reversedHead;
    }
    // Return the new head of the reversed linked list.
    return reversedHead;
}

//-------------------------------------------//
// Recursive Approach
// Recursive helper function to reverse the linked list.
ListNode* reverseListRecursiveHelper(ListNode*& currentNode, ListNode*& reversedHead, ListNode*& previousNode) {
    // BASE CASE:
    // If currentNode becomes nullptr, all nodes have been processed.
    // reversedHead now points to the new head of the reversed list.
    if (currentNode == nullptr) {
        return reversedHead;
    }
    // Update reversedHead to point to the current node.
    // Eventually, it will point to the original last node.
    reversedHead = currentNode;
    // Move currentNode to the next node.
    // We do this before reversing the current node's link
    // so that we don't lose the remaining linked list.
    currentNode = currentNode->next;
    // Reverse the link of the current node.
    // Instead of pointing to the next node,
    // it now points to the previous node.
    reversedHead->next = previousNode;
    // Move previousNode forward to the current node.
    // This node will become the previous node
    // in the next recursive call.
    previousNode = reversedHead;
    // Recursively process the remaining nodes.
    // Continue until currentNode becomes nullptr.
    return reverseListRecursiveHelper(currentNode, reversedHead, previousNode);
}

// Main function to reverse the linked list recursively.
ListNode* reverseListRecursive(ListNode* head) {
    // Points to the current node being processed.
    ListNode* currentNode = head;
    // Represents the head of the reversed linked list.
    ListNode* reversedHead = nullptr;
    // Keeps track of the previously processed node.
    ListNode* previousNode = nullptr;
    // Start the recursive reversal process.
    return reverseListRecursiveHelper(currentNode, reversedHead, previousNode);
}

//int main(){
//    ListNode* head = new ListNode(1);
//    ListNode* node2 = new ListNode(2);
//    ListNode* node3 = new ListNode(3);
//    ListNode* node4 = new ListNode(4);
//    ListNode* node5 = new ListNode(5);
//    ListNode* node6 = new ListNode(6);
//    head->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    node5->next = node6;
//    printLinkedList(head);
//    head = reverseListRecursive(head);
//    printLinkedList(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
