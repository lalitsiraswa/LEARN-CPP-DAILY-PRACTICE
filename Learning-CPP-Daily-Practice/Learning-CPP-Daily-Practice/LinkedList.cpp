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
// 21. Merge Two Sorted Lists
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    // If the first list is empty, return the second list.
    if (list1 == nullptr) {
        return list2;
    }
    // If the second list is empty, return the first list.
    if (list2 == nullptr) {
        return list1;
    }
    // Pointers used to traverse both linked lists.
    ListNode* firstNode = list1;
    ListNode* secondNode = list2;
    // Points to the first node of the merged linked list.
    ListNode* mergedHead = nullptr;
    // Points to the last node of the merged linked list.
    // Used to attach the next selected node.
    ListNode* tailNode = nullptr;
    // Compare the first nodes of both lists.
    // Select the smaller node as the head of the merged list.
    if (firstNode->value <= secondNode->value) {
        // First list contains the smaller node.
        mergedHead = firstNode;
        tailNode = firstNode;
        // Move firstNode to the next node.
        firstNode = firstNode->next;
    }
    else {
        // Second list contains the smaller node.
        mergedHead = secondNode;
        tailNode = secondNode;
        // Move secondNode to the next node.
        secondNode = secondNode->next;
    }
    // Continue merging while both lists have remaining nodes.
    while (firstNode != nullptr && secondNode != nullptr) {
        // Compare the current nodes of both lists.
        if (firstNode->value <= secondNode->value) {
            // Attach the smaller node from the first list
            // to the end of the merged list.
            tailNode->next = firstNode;
            // Move firstNode to its next node.
            firstNode = firstNode->next;
        }
        else {
            // Attach the smaller node from the second list
            // to the end of the merged list.
            tailNode->next = secondNode;
            // Move secondNode to its next node.
            secondNode = secondNode->next;
        }
        // Move tailNode forward to the newly attached node.
        tailNode = tailNode->next;
    }
    // If the first list still contains nodes,
    // attach all remaining nodes to the merged list.
    if (firstNode != nullptr) {
        tailNode->next = firstNode;
    }
    // If the second list still contains nodes,
    // attach all remaining nodes to the merged list.
    if (secondNode != nullptr) {
        tailNode->next = secondNode;
    }
    // Return the head of the merged sorted linked list.
    return mergedHead;
}

//-------------------------------------------//
// Recursive Approach
ListNode* mergeTwoListsRecursion(ListNode* firstList, ListNode* secondList) {
    // BASE CASE 1:
    // If the first list is empty, return the second list.
    // All remaining nodes from the second list are already sorted.
    if (firstList == nullptr) {
        return secondList;
    }
    // BASE CASE 2:
    // If the second list is empty, return the first list.
    // All remaining nodes from the first list are already sorted.
    if (secondList == nullptr) {
        return firstList;
    }
    // Stores the head of the merged linked list
    // returned by the current recursive call.
    ListNode* mergedHead = nullptr;
    // Compare the values of the current nodes from both lists.
    if (firstList->value <= secondList->value) {
        // The first list contains the smaller node.
        // Select it as the head of the merged list.
        mergedHead = firstList;
        // Recursively merge the remaining nodes of the first list
        // with the entire second list.
        //
        // Attach the resulting merged list to the selected node.
        mergedHead->next = mergeTwoListsRecursion(firstList->next, secondList);
    }
    else {
        // The second list contains the smaller node.
        // Select it as the head of the merged list.
        mergedHead = secondList;
        // Recursively merge the entire first list
        // with the remaining nodes of the second list.
        //
        // Attach the resulting merged list to the selected node.
        mergedHead->next = mergeTwoListsRecursion(firstList, secondList->next);
    }
    // Return the head of the merged linked list
    // created by the current recursive call.
    return mergedHead;
}

//int main(){
//    ListNode* head1 = new ListNode(1);
//    head1->next = new ListNode(2);
//    head1->next->next = new ListNode(3);
//    ListNode* head2 = new ListNode(1);
//    head2->next = new ListNode(2);
//    head2->next->next = new ListNode(3);
//    printLinkedList(head1);
//    printLinkedList(head2);
//    ListNode* mergeSortedHead = mergeTwoListsRecursion(head1, head2);
//    printLinkedList(mergeSortedHead);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// Sort Linked List of 0s, 1s and 2s - GFG
ListNode* segregate(ListNode* head) {
    // Pointer used to traverse the original linked list.
    ListNode* traversalNode = head;
    // Head pointers for the three separate linked lists.
    // Each head points to the first node containing 0, 1, or 2.
    ListNode* zeroListHead = nullptr;
    ListNode* oneListHead = nullptr;
    ListNode* twoListHead = nullptr;
    // Tail pointers for the three separate linked lists.
    // Each tail points to the last node of its respective list.
    // These pointers help us append new nodes efficiently.
    ListNode* zeroListTail = nullptr;
    ListNode* oneListTail = nullptr;
    ListNode* twoListTail = nullptr;
    // Traverse the original linked list.
    while (traversalNode != nullptr) {
        // If the current node contains 0, add it to the zero list.
        if (traversalNode->value == 0) {
            // If the zero list is empty, initialize its head and tail.
            if (zeroListHead == nullptr) {
                zeroListHead = traversalNode;
                zeroListTail = traversalNode;
            }
            else {
                // Append the current node to the end of the zero list.
                zeroListTail->next = traversalNode;
                // Update the tail to the newly added node.
                zeroListTail = zeroListTail->next;
            }
        }
        // If the current node contains 1, add it to the one list.
        else if (traversalNode->value == 1) {
            // If the one list is empty, initialize its head and tail.
            if (oneListHead == nullptr) {
                oneListHead = traversalNode;
                oneListTail = traversalNode;
            }
            else {
                // Append the current node to the end of the one list.
                oneListTail->next = traversalNode;
                // Update the tail to the newly added node.
                oneListTail = oneListTail->next;
            }
        }
        // If the current node contains 2, add it to the two list.
        else if (traversalNode->value == 2) {
            // If the two list is empty, initialize its head and tail.
            if (twoListHead == nullptr) {
                twoListHead = traversalNode;
                twoListTail = traversalNode;
            }
            else {
                // Append the current node to the end of the two list.
                twoListTail->next = traversalNode;
                // Update the tail to the newly added node.
                twoListTail = twoListTail->next;
            }
        }
        // Move to the next node in the original linked list.
        traversalNode = traversalNode->next;
    }
    // Terminate each individual list by connecting its tail to nullptr.
    // This prevents unwanted connections between the separated lists.
    if (zeroListTail != nullptr) {
        zeroListTail->next = nullptr;
    }
    if (oneListTail != nullptr) {
        oneListTail->next = nullptr;
    }
    if (twoListTail != nullptr) {
        twoListTail->next = nullptr;
    }
    // PHASE 2: Merge the three separate lists in sorted order.
    // If the zero list exists, it will be the head of the final list.
    if (zeroListHead != nullptr) {
        // If both one and two lists exist, connect all three lists.
        if (oneListHead != nullptr && twoListHead != nullptr) {
            zeroListTail->next = oneListHead;
            oneListTail->next = twoListHead;
            return zeroListHead;
        }
        // If only the one list exists, connect zero list to one list.
        else if (oneListHead != nullptr) {
            zeroListTail->next = oneListHead;
            return zeroListHead;
        }
        // If only the two list exists, connect zero list to two list.
        else if (twoListHead != nullptr) {
            zeroListTail->next = twoListHead;
            return zeroListHead;
        }
        // If only the zero list exists, return it directly.
        return zeroListHead;
    }
    // If the zero list does not exist, check whether the one list exists.
    if (oneListHead != nullptr) {
        // If the two list also exists, connect the one list to it.
        if (twoListHead != nullptr) {
            oneListTail->next = twoListHead;
        }
        // Return the one list as the head of the final list.
        return oneListHead;
    }
    // If neither zero nor one list exists,
    // return the two list as the final sorted list.
    return twoListHead;
}

//-------------------------------------------//
ListNode* segregateTUF(ListNode* head) {
    // Pointer used to traverse the original linked list.
    ListNode* currentNode = head;
    // Create three dummy nodes to maintain separate linked lists
    // for nodes containing 0, 1, and 2.
    ListNode* zeroListDummyHead = new ListNode(-1);
    ListNode* oneListDummyHead = new ListNode(-1);
    ListNode* twoListDummyHead = new ListNode(-1);
    // Tail pointers initially point to their respective dummy nodes.
    // They help us append nodes to the corresponding linked lists.
    ListNode* zeroListTail = zeroListDummyHead;
    ListNode* oneListTail = oneListDummyHead;
    ListNode* twoListTail = twoListDummyHead;
    // Traverse the original linked list and distribute each node
    // into the corresponding list based on its value.
    while (currentNode != nullptr) {
        // If the current node contains 0, append it to the zero list.
        if (currentNode->value == 0) {
            zeroListTail->next = currentNode;
            zeroListTail = zeroListTail->next;
        }
        // If the current node contains 1, append it to the one list.
        else if (currentNode->value == 1) {
            oneListTail->next = currentNode;
            oneListTail = oneListTail->next;
        }
        // If the current node contains 2, append it to the two list.
        else if (currentNode->value == 2) {
            twoListTail->next = currentNode;
            twoListTail = twoListTail->next;
        }
        // Move to the next node in the original linked list.
        currentNode = currentNode->next;
    }
    // Connect the zero list to the one list if it exists.
    // Otherwise, connect the zero list directly to the two list.
    zeroListTail->next = (oneListDummyHead->next != nullptr) ? oneListDummyHead->next : twoListDummyHead->next;
    // Connect the one list to the beginning of the two list.
    oneListTail->next = twoListDummyHead->next;
    // Mark the end of the final linked list.
    // This prevents any unwanted connections or cycles.
    twoListTail->next = nullptr;
    // Return the head of the sorted linked list,
    // skipping the dummy node.
    return zeroListDummyHead->next;
}

//int main(){
//    ListNode* head = new ListNode(1);
//    ListNode* node2 = new ListNode(2);
//    ListNode* node3 = new ListNode(0);
//    ListNode* node4 = new ListNode(1);
//    ListNode* node5 = new ListNode(2);
//    ListNode* node6 = new ListNode(0);
//    head->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    node4->next = node5;
//    node5->next = node6;
//    printLinkedList(head);
//    head = segregateTUF(head);
//    printLinkedList(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 2. Add Two Numbers
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // Pointers used to traverse both input linked lists.
    ListNode* firstListCurrent = l1;
    ListNode* secondListCurrent = l2;
    // Pointer to store the head of the newly created result linked list.
    ListNode* resultHead = nullptr;
    // Pointer used to append new nodes to the result linked list.
    ListNode* resultTail = resultHead;
    // Stores the carry generated during addition.
    int carry = 0;
    // PHASE 1: Add corresponding nodes while both lists have elements.
    while (firstListCurrent != nullptr && secondListCurrent != nullptr) {
        // Add the values of both nodes along with the previous carry.
        int sum = firstListCurrent->value + secondListCurrent->value + carry;
        // Extract the digit to be stored in the current result node.
        int digit = sum % 10;
        // Calculate the carry to be added during the next iteration.
        carry = sum / 10;
        // If the result list is empty, create its first node.
        if (resultHead == nullptr) {
            resultHead = new ListNode(digit);
            resultTail = resultHead;
        }
        // Otherwise, append the new node at the end of the result list.
        else {
            resultTail->next = new ListNode(digit);
            resultTail = resultTail->next;
        }
        // Move both input pointers to their next nodes.
        firstListCurrent = firstListCurrent->next;
        secondListCurrent = secondListCurrent->next;
    }
    // PHASE 2: Process the remaining nodes of the first list, if any.
    while (firstListCurrent != nullptr) {
        // Add the current node's value along with the previous carry.
        int sum = firstListCurrent->value + carry;
        // Extract the digit to be stored in the result list.
        int digit = sum % 10;
        // Calculate the carry for the next iteration.
        carry = sum / 10;
        // Append the newly calculated digit to the result list.
        resultTail->next = new ListNode(digit);
        resultTail = resultTail->next;
        // Move to the next node in the first list.
        firstListCurrent = firstListCurrent->next;
    }
    // PHASE 3: Process the remaining nodes of the second list, if any.
    while (secondListCurrent != nullptr) {
        // Add the current node's value along with the previous carry.
        int sum = secondListCurrent->value + carry;
        // Extract the digit to be stored in the result list.
        int digit = sum % 10;
        // Calculate the carry for the next iteration.
        carry = sum / 10;
        // Append the newly calculated digit to the result list.
        resultTail->next = new ListNode(digit);
        resultTail = resultTail->next;
        // Move to the next node in the second list.
        secondListCurrent = secondListCurrent->next;
    }
    // PHASE 4: If a carry is still remaining, append it as the final node.
    if (carry != 0) {
        resultTail->next = new ListNode(carry);
    }
    // Return the head of the newly created result linked list.
    return resultHead;
}

//-------------------------------------------//
// Helper function to calculate the length of a linked list.
int findLinkedListLength(ListNode* head) {
    // Pointer used to traverse the linked list.
    ListNode* currentNode = head;
    // Stores the total number of nodes in the linked list.
    int length = 0;
    // Traverse the linked list until the end is reached.
    while (currentNode != nullptr) {
        length++;
        // Move to the next node.
        currentNode = currentNode->next;
    }
    // Return the total number of nodes.
    return length;
}

// Helper function to add two numbers by reusing the nodes
// of the longer linked list instead of creating a new result list.
ListNode* addTwoNumbersWithoutCreatingNewNodeHelper(ListNode* longerList, ListNode* shorterList) {
    // The longer list will store the final addition result.
    ListNode* resultHead = longerList;
    // Pointer used to keep track of the previously processed node.
    // This is required to append a new node if a carry remains.
    ListNode* previousNode = longerList;
    // Stores the carry generated during addition.
    int carry = 0;
    // PHASE 1: Add corresponding nodes while the shorter list
    // still contains elements.
    while (shorterList != nullptr) {
        // Add the values of both nodes along with the previous carry.
        int sum = longerList->value + shorterList->value + carry;
        // Extract the digit to be stored in the current node.
        int digit = sum % 10;
        // Calculate the carry for the next iteration.
        carry = sum / 10;
        // Update the existing node of the longer list
        // with the calculated digit.
        longerList->value = digit;
        // Keep track of the previously processed node.
        previousNode = longerList;
        // Move both pointers to their next nodes.
        longerList = longerList->next;
        shorterList = shorterList->next;
    }

    // PHASE 2: Process the remaining nodes of the longer list.
    // Only the carry needs to be added because the shorter list
    // has already been completely traversed.
    while (longerList != nullptr) {
        // Add the current node's value along with the previous carry.
        int sum = longerList->value + carry;
        // Extract the digit to be stored in the current node.
        int digit = sum % 10;
        // Calculate the carry for the next iteration.
        carry = sum / 10;
        // Update the existing node with the calculated digit.
        longerList->value = digit;
        // Keep track of the previously processed node.
        previousNode = longerList;
        // Move to the next node in the longer list.
        longerList = longerList->next;
    }

    // PHASE 3: If a carry is still remaining after processing
    // both lists, create one additional node at the end.
    if (carry != 0) {
        previousNode->next = new ListNode(carry);
    }
    // Return the head of the modified longer linked list.
    return resultHead;
}

// Function to add two numbers without creating a completely
// new result linked list.
ListNode* addTwoNumbersWithoutCreatingNewNode(ListNode* l1, ListNode* l2) {
    // Calculate the lengths of both input linked lists.
    int firstListLength = findLinkedListLength(l1);
    int secondListLength = findLinkedListLength(l2);
    // If the first list is longer or both lists have equal lengths,
    // use the first list to store the addition result.
    if (firstListLength >= secondListLength) {
        return addTwoNumbersWithoutCreatingNewNodeHelper(l1, l2);
    }
    // Otherwise, use the second list because it has more nodes.
    return addTwoNumbersWithoutCreatingNewNodeHelper(l2, l1);
}

//int main(){
//    ListNode* head1 = new ListNode(9);
//    head1->next = new ListNode(9);
//    head1->next->next = new ListNode(9);
//    ListNode* head2 = new ListNode(9);
//    head2->next = new ListNode(9);
//    printLinkedList(head1);
//    printLinkedList(head2);
//    ListNode* head = addTwoNumbersWithoutCreatingNewNode(head1, head2);
//    printLinkedList(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 61. Rotate List
// Helper function to calculate the length of the linked list.
int rotateRightFindLengthHelper(ListNode* head) {
    // Pointer used to traverse the linked list.
    ListNode* currentNode = head;
    // Stores the total number of nodes in the linked list.
    int length = 0;
    // Traverse the linked list until the end is reached.
    while (currentNode != nullptr) {
        length++;
        // Move to the next node.
        currentNode = currentNode->next;
    }
    // Return the total number of nodes.
    return length;
}

ListNode* rotateRight(ListNode* head, int k) {
    // If the list is empty or no rotation is required,
    // return the original linked list.
    if (head == nullptr || k == 0) {
        return head;
    }
    // Calculate the total number of nodes in the linked list.
    int length = rotateRightFindLengthHelper(head);
    // Rotating the list by its length produces the original list.
    // Reduce k to avoid performing unnecessary rotations.
    k = k % length;
    // If the effective rotation count is 0, no rotation is required.
    if (k == 0) {
        return head;
    }
    // Tracks how many right rotations have been performed.
    int rotationCount = 0;
    // Perform one right rotation at a time until k rotations are completed.
    while (rotationCount < k) {
        // Pointer used to traverse the linked list.
        ListNode* currentNode = head;
        // Pointer used to keep track of the node before the last node.
        ListNode* previousNode = nullptr;
        // Traverse the linked list to find the last node.
        // previousNode will point to the second-last node.
        while (currentNode->next != nullptr) {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        // Connect the last node to the original head.
        // This makes the last node the new starting point.
        currentNode->next = head;
        // Update the head to the previous last node.
        head = currentNode;
        // Disconnect the second-last node from the new head.
        // This makes the second-last node the new tail.
        previousNode->next = nullptr;
        // Increment the rotation count after completing one rotation.
        rotationCount++;
    }
    // Return the head of the rotated linked list.
    return head;
}

//-------------------------------------------//
// Helper function to calculate the length of the linked list.
int rotateRightFindLengthHelper01(ListNode* head) {
    // Pointer used to traverse the linked list.
    ListNode* currentNode = head;
    // Stores the total number of nodes in the linked list.
    int length = 0;
    // Traverse the linked list until the end is reached.
    while (currentNode != nullptr) {
        length++;
        // Move to the next node.
        currentNode = currentNode->next;
    }
    // Return the total number of nodes.
    return length;
}

ListNode* rotateRight01(ListNode* head, int k) {
    // If the list is empty or no rotation is required,
    // return the original list.
    if (head == nullptr || k == 0) {
        return head;
    }
    // Calculate the total number of nodes in the linked list.
    int length = rotateRightFindLengthHelper(head);
    // Rotating the list by its length produces the original list.
    // Therefore, reduce k to avoid unnecessary rotations.
    k = k % length;
    // If k becomes 0, no rotation is required.
    if (k == 0) {
        return head;
    }
    // Pointer used to traverse the linked list.
    ListNode* currentNode = head;
    // Pointer used to identify the new tail of the rotated list.
    ListNode* previousNode = head;
    // Tracks the number of nodes traversed by currentNode.
    int currentListLength = 0;
    // Traverse the linked list to find the new tail.
    // The new tail will be at position (length - k - 1).
    while (currentNode->next != nullptr) {
        // Move the traversal pointer to the next node.
        currentNode = currentNode->next;
        // Update the number of nodes traversed.
        currentListLength++;
        // Once currentNode has moved more than k positions,
        // move previousNode forward as well.
        // This ensures previousNode stops at the new tail.
        if (currentListLength > k) {
            previousNode = previousNode->next;
        }
    }
    // Connect the original tail to the original head
    // to temporarily form a circular linked list.
    currentNode->next = head;
    // The node after the new tail becomes the new head.
    head = previousNode->next;
    // Break the circular linked list at the new tail.
    previousNode->next = nullptr;
    // Return the head of the rotated linked list.
    return head;
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
//    printLinkedList(head);
//    head = rotateRight(head, 3);
//    printLinkedList(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 148. Sort List
// Approach: Insertion Sort
// Time Complexity: O(N^2)
// Auxiliary Space: O(1)
ListNode* sortList(ListNode* head) {
    // Head and tail pointers of the sorted linked list.
    ListNode* sortedHead = nullptr;
    ListNode* sortedTail = nullptr;
    // Pointer used to traverse the original linked list.
    ListNode* currentNode = head;
    // Stores the next node before modifying the current node's links.
    // This ensures that we do not lose the remaining original list.
    ListNode* nextNode = nullptr;
    // Traverse the original linked list and insert each node
    // into its correct position in the sorted linked list.
    while (currentNode != nullptr) {
        // Save the next node before modifying currentNode->next.
        nextNode = currentNode->next;
        // CASE 1: The sorted linked list is currently empty.
        // Insert the first node and initialize both head and tail.
        if (sortedHead == nullptr) {
            sortedHead = currentNode;
            sortedTail = currentNode;
        }
        // CASE 2: The current node's value is smaller than or equal
        // to the first node's value in the sorted linked list.
        // Insert the current node at the beginning.
        else if (currentNode->value <= sortedHead->value) {
            // Connect the current node to the existing sorted list.
            currentNode->next = sortedHead;
            // Update the head of the sorted linked list.
            sortedHead = currentNode;
            // Restore the connection to the remaining original list.
            // This ensures that unprocessed nodes are not lost.
            sortedTail->next = nextNode;
        }
        // CASE 3: The current node's value is greater than
        // the last node's value in the sorted linked list.
        // Append the current node at the end.
        else if (currentNode->value > sortedTail->value) {
            sortedTail = currentNode;
        }
        // CASE 4: The current node belongs somewhere between
        // the head and tail of the sorted linked list.
        // Find its correct insertion position.
        else {
            // Pointer used to find the correct insertion position.
            ListNode* traversalNode = sortedHead;
            // Tracks the node immediately before traversalNode.
            ListNode* previousNode = nullptr;
            // Find the first node whose value is greater than
            // or equal to the current node's value.
            while (traversalNode != currentNode) {
                if (traversalNode->value >= currentNode->value) {
                    break;
                }
                // Move the previous pointer forward.
                previousNode = traversalNode;
                // Move to the next node in the sorted list.
                traversalNode = traversalNode->next;
            }
            // Insert the current node before traversalNode.
            currentNode->next = traversalNode;
            previousNode->next = currentNode;
            // Restore the connection to the remaining original list.
            sortedTail->next = nextNode;
        }
        // Move to the next unprocessed node in the original list.
        currentNode = nextNode;
    }
    // Return the head of the sorted linked list.
    return sortedHead;
}

//-------------------------------------------//
// Approach: Merge Sort
// Helper function to find the middle node of the linked list.
ListNode* sortListFindMiddleNodeHelper(ListNode* head) {
    // If the linked list is empty or contains only one node,
    // return the head itself.
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    // Slow pointer moves one node at a time.
    ListNode* slowPointer = head;
    // Fast pointer moves two nodes at a time.
    // Starting from head->next helps find the first middle node
    // when the linked list contains an even number of nodes.
    ListNode* fastPointer = head->next;
    // Move slowPointer one step and fastPointer two steps
    // until fastPointer reaches the end of the linked list.
    while (fastPointer != nullptr && fastPointer->next != nullptr) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
    }
    // Return the middle node, which will be the last node
    // of the left half after splitting the linked list.
    return slowPointer;
}

// Helper function to merge two sorted linked lists into one sorted list.
ListNode* mergeTwoSortedLinkedLists(ListNode* firstList, ListNode* secondList) {
    // Create a dummy node to simplify the merging process.
    // The actual merged linked list will start from dummyNode->next.
    ListNode* dummyNode = new ListNode(-1);
    // Pointer used to append nodes to the merged linked list.
    ListNode* mergedListTail = dummyNode;
    // Compare the current nodes of both lists and append
    // the smaller node to the merged linked list.
    while (firstList != nullptr && secondList != nullptr) {
        // If the first list's current value is smaller than
        // or equal to the second list's current value,
        // append the first list's node.
        if (firstList->value <= secondList->value) {
            mergedListTail->next = firstList;
            // Move the first list pointer forward.
            firstList = firstList->next;
        }
        else {
            // Otherwise, append the second list's current node.
            mergedListTail->next = secondList;
            // Move the second list pointer forward.
            secondList = secondList->next;
        }
        // Move the merged-list tail to the newly appended node.
        mergedListTail = mergedListTail->next;
    }
    // If the first list still contains nodes,
    // append all its remaining nodes to the merged list.
    if (firstList != nullptr) {
        mergedListTail->next = firstList;
    }
    // If the second list still contains nodes,
    // append all its remaining nodes to the merged list.
    if (secondList != nullptr) {
        mergedListTail->next = secondList;
    }
    // Store the actual head of the merged linked list.
    ListNode* mergedHead = dummyNode->next;
    // Delete the dummy node to avoid a memory leak.
    delete dummyNode;
    // Return the merged sorted linked list.
    return mergedHead;
}

// Main function to sort the linked list using Merge Sort.
ListNode* sortListTuf(ListNode* head) {
    // BASE CASE:
    // An empty linked list or a list containing only one node
    // is already sorted.
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    // PHASE 1: Find the middle node to divide the linked list
    // into two smaller halves.
    ListNode* middleNode = sortListFindMiddleNodeHelper(head);
    // The right half starts from the node after the middle.
    ListNode* rightHalfHead = middleNode->next;
    // Break the connection between the two halves.
    // This creates two independent linked lists.
    middleNode->next = nullptr;
    // The left half starts from the original head.
    ListNode* leftHalfHead = head;
    // PHASE 2: Recursively sort both halves.
    // Continue dividing each half until individual nodes remain.
    leftHalfHead = sortListTuf(leftHalfHead);
    rightHalfHead = sortListTuf(rightHalfHead);
    // PHASE 3: Merge the two sorted halves into one sorted list.
    return mergeTwoSortedLinkedLists(leftHalfHead, rightHalfHead);
}

//int main(){
//    ListNode* head = new ListNode(4);
//    ListNode* node2 = new ListNode(10);
//    ListNode* node3 = new ListNode(6);
//    ListNode* node4 = new ListNode(1);
//    head->next = node2;
//    node2->next = node3;
//    node3->next = node4;
//    printLinkedList(head);
//    head = sortListTuf(head);
//    printLinkedList(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 138. Copy List with Random Pointer
struct Node{
    int value;
    Node *next;
    Node *random;
    Node(): value(0), next(nullptr){}
    Node(int value): value(value), next(nullptr), random(nullptr){}
    Node(int value, Node* next): value(value), next(next), random(nullptr){}
    Node(int value, Node* next, Node* random): value(value), next(next), random(random){}
};

void printLinkedList(Node* node){
    while(node != nullptr){
        cout << "Value : " << node->value;
        if(node->random != nullptr){
            cout << " Random Value : " << node->random->value;
        }
        node = node->next;
        cout << endl;
    }
    cout << "nullptr" << endl;
}

Node* copyRandomList(Node* head) {
    // STEP 1: Create a new linked list containing copies of all nodes.
    // The next pointers will be connected in the same order as the original list.
    // Dummy node helps us build the copied list without handling
    // the first node separately.
    Node* dummyNode = new Node(-1);
    // Maintains the last node of the copied linked list.
    Node* copiedListTail = dummyNode;
    // Traverses the original linked list.
    Node* originalListCurrent = head;
    while (originalListCurrent != nullptr) {
        // Create a new node with the same value as the original node.
        copiedListTail->next = new Node(originalListCurrent->value);
        // Move the tail pointer to the newly created node.
        copiedListTail = copiedListTail->next;
        // Move to the next node in the original linked list.
        originalListCurrent = originalListCurrent->next;
    }
    // STEP 2: Assign random pointers to the copied nodes.
    // Pointer to traverse the original linked list.
    Node* originalListCurrentNode = head;
    // Pointer to traverse the copied linked list.
    Node* copiedListCurrentNode = dummyNode->next;
    while (originalListCurrentNode != nullptr && copiedListCurrentNode != nullptr) {
        // Get the node pointed to by the current original node's random pointer.
        Node* originalRandomNode = originalListCurrentNode->random;
        // CASE 1: If the original node's random pointer is nullptr,
        // the corresponding copied node's random pointer should also be nullptr.
        if (originalRandomNode == nullptr) {
            copiedListCurrentNode->random = nullptr;
        }
        else {
            // CASE 2: Find the position of the original random node
            // in the original linked list.
            // Start traversing the original list from its head.
            Node* originalListTraversal = head;
            // Stores the number of nodes between the head and random node.
            int randomNodePosition = 0;
            while (originalListTraversal != originalRandomNode) {
                randomNodePosition++;
                originalListTraversal = originalListTraversal->next;
            }
            // STEP 3: Find the corresponding copied node
            // at the same position in the copied linked list.
            // Start traversing the copied list from its head.
            Node* copiedListTraversal = dummyNode->next;
            // Move to the same position as the original random node.
            while (randomNodePosition != 0) {
                copiedListTraversal = copiedListTraversal->next;
                randomNodePosition--;
            }
            // Connect the copied node's random pointer to
            // the corresponding copied random node.
            copiedListCurrentNode->random = copiedListTraversal;
        }
        // Move both pointers to their respective next nodes.
        originalListCurrentNode = originalListCurrentNode->next;
        copiedListCurrentNode = copiedListCurrentNode->next;
    }
    // STEP 4: Return the head of the copied linked list.
    // dummyNode itself is not part of the copied list.
    return dummyNode->next;
}

//-------------------------------------------//
Node* copyRandomListUsingUnorderedMap(Node* head) {
    // STEP 1: Create a new linked list containing copies of all original nodes.
    // Dummy node helps us build the copied linked list easily.
    Node* dummyNode = new Node(-1);
    // Maintains the last node of the copied linked list.
    Node* copiedListTail = dummyNode;
    // Traverses the original linked list.
    Node* originalListCurrent = head;
    // Stores the mapping between original nodes and their corresponding copied nodes.
    // Key   = Address of the original node.
    // Value = Address of the copied node.
    unordered_map<Node*, Node*> originalToCopiedNodeMap;
    while (originalListCurrent != nullptr) {
        // Create a new node with the same value as the original node.
        Node* copiedNode = new Node(originalListCurrent->value);
        // Store the mapping between the original node and its copied node.
        originalToCopiedNodeMap.insert(pair<Node*, Node*>{originalListCurrent, copiedNode});
        // Connect the newly created node to the copied linked list.
        copiedListTail->next = copiedNode;
        // Move the tail pointer to the newly created node.
        copiedListTail = copiedListTail->next;
        // Move to the next node in the original linked list.
        originalListCurrent = originalListCurrent->next;
    }
    // STEP 2: Assign random pointers to the copied nodes.
    // Pointer to traverse the original linked list.
    Node* originalListCurrentNode = head;
    // Pointer to traverse the copied linked list.
    Node* copiedListCurrentNode = dummyNode->next;
    while (originalListCurrentNode != nullptr && copiedListCurrentNode != nullptr) {
        // Get the node pointed to by the current original node's random pointer.
        Node* originalRandomNode = originalListCurrentNode->random;
        // Find the corresponding copied node using the unordered_map.
        // If originalRandomNode is nullptr, operator[] returns a nullptr
        // because the nullptr key is not present in the map.
        copiedListCurrentNode->random = originalToCopiedNodeMap[originalRandomNode];
        // Move both pointers to their respective next nodes.
        originalListCurrentNode = originalListCurrentNode->next;
        copiedListCurrentNode = copiedListCurrentNode->next;
    }
    // STEP 3: Return the head of the copied linked list.
    // Skip the dummy node because it is not part of the actual copied list.
    return dummyNode->next;
}

//-------------------------------------------//
Node* copyRandomListTuf(Node* head) {
    // STEP 1: Insert a copied node immediately after each original node.
    //
    // Original: A -> B -> C -> nullptr
    // Updated:  A -> A' -> B -> B' -> C -> C' -> nullptr
    //
    // This allows us to find the copied node corresponding to
    // any original node using its next pointer.
    Node* originalCurrentNode = head;
    while (originalCurrentNode != nullptr) {
        // Store the next original node before modifying the next pointer.
        Node* nextOriginalNode = originalCurrentNode->next;
        // Create a copied node with the same value as the original node.
        Node* copiedNode = new Node(originalCurrentNode->value);
        // Insert the copied node immediately after the original node.
        originalCurrentNode->next = copiedNode;
        // Connect the copied node to the next original node.
        copiedNode->next = nextOriginalNode;
        // Move to the next original node.
        // Skip the copied node that was just inserted.
        originalCurrentNode = nextOriginalNode;
    }
    // STEP 2: Assign random pointers to the copied nodes.
    //
    // Since every copied node is immediately after its original node,
    // originalRandomNode->next gives us the corresponding copied node.
    originalCurrentNode = head;
    while (originalCurrentNode != nullptr) {
        // Get the random node pointed to by the current original node.
        Node* originalRandomNode = originalCurrentNode->random;
        // Get the copied node corresponding to the current original node.
        Node* copiedCurrentNode = originalCurrentNode->next;
        // CASE 1: If the original random pointer is nullptr,
        // the copied node's random pointer should also be nullptr.
        if (originalRandomNode == nullptr) {
            copiedCurrentNode->random = nullptr;
        }
        // CASE 2: If the original random pointer is not nullptr,
        // its next pointer gives us the corresponding copied node.
        else {
            copiedCurrentNode->random = originalRandomNode->next;
        }
        // Move to the next original node.
        // Skip the copied node and move two steps ahead.
        originalCurrentNode = originalCurrentNode->next->next;
    }
    // STEP 3: Separate the original and copied linked lists.
    //
    // Before separation:
    // Original: A -> A' -> B -> B' -> C -> C' -> nullptr
    //
    // After separation:
    // Original: A -> B -> C -> nullptr
    // Copied:   A' -> B' -> C' -> nullptr
    // Dummy node helps us construct the copied linked list.
    Node* dummyNode = new Node(-1);
    // Maintains the tail of the copied linked list.
    Node* copiedListTail = dummyNode;
    // Start traversing the interwoven linked list from its head.
    originalCurrentNode = head;
    while (originalCurrentNode != nullptr) {
        // Store the next original node before separating the lists.
        Node* nextOriginalNode = originalCurrentNode->next->next;
        // Connect the copied node to the copied linked list.
        copiedListTail->next = originalCurrentNode->next;
        // Restore the original node's next pointer.
        // This separates the original linked list from the copied list.
        originalCurrentNode->next = nextOriginalNode;
        // Move to the next original node.
        originalCurrentNode = nextOriginalNode;
        // Move the copied list's tail to the newly connected copied node.
        copiedListTail = copiedListTail->next;
    }
    // STEP 4: Return the head of the copied linked list.
    // Skip the dummy node because it is not part of the actual copied list.
    return dummyNode->next;
}

//int main(){
//    Node* head = new Node(7);
//    Node* node2 = new Node(13);
//    Node* node3 = new Node(11);
//    Node* node4 = new Node(10);
//    Node* node5 = new Node(1);
//    head->next = node2;
//    node2->next = node3;
//    node3->next= node4;
//    node4->next = node5;
//    head->random = nullptr;
//    node2->random = head;
//    node3->random = node5;
//    node4->random = node3;
//    node5->random = head;
//    printLinkedList(head);
//    Node* newHead = copyRandomListTuf(head);
//    printLinkedList(newHead);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// 25. Reverse Nodes in k-Group
// Helper function to reverse a linked list iteratively.
void reverseKGroupLinkListReverseHelper(ListNode* head) {
    // Pointer to traverse the linked list.
    ListNode* currentNode = head;
    // Initially, there is no previous node.
    ListNode* previousNode = nullptr;
    while (currentNode != nullptr) {
        // Store the next node before changing the current node's next pointer.
        ListNode* nextNode = currentNode->next;
        // Reverse the current node's next pointer.
        currentNode->next = previousNode;
        // Move previousNode one step forward.
        previousNode = currentNode;
        // Move currentNode to the next node.
        currentNode = nextNode;
    }
    // After reversal, previousNode points to the new head.
    // The original head pointer now points to the last node.
}

// Function to reverse the linked list in groups of k nodes.
ListNode* reverseKGroup(ListNode* head, int k) {
    // Pointer to traverse the original linked list.
    ListNode* currentNode = head;
    // Stores the head of the final reversed linked list.
    ListNode* newHead = nullptr;
    // Maintains the tail of the previously reversed group.
    ListNode* previousGroupTail = nullptr;
    while (currentNode != nullptr) {
        // STEP 1: Identify the starting and ending nodes of the current group.
        // Marks the first node of the current group.
        ListNode* groupStartNode = currentNode;
        // Initially, the first node is also the ending node.
        ListNode* groupEndNode = currentNode;
        // Counts the number of nodes in the current group.
        int groupNodeCount = 1;
        // Traverse the linked list to find exactly k nodes.
        while (groupNodeCount != k && groupEndNode->next != nullptr) {
            groupEndNode = groupEndNode->next;
            groupNodeCount++;
        }
        // STEP 2: Check whether the current group contains exactly k nodes.
        // If fewer than k nodes remain, leave them unchanged.
        // If no group has been reversed, return the original head.
        // Otherwise, return the head of the already reversed groups.
        if (groupNodeCount != k) {
            return (newHead == nullptr) ? head : newHead;
        }
        // STEP 3: Store the first node of the next group.
        // We need this pointer to reconnect the remaining linked list
        // after reversing the current group.
        ListNode* nextGroupStartNode = groupEndNode->next;
        // Disconnect the current group from the remaining linked list.
        groupEndNode->next = nullptr;
        // STEP 4: Reverse the current group.
        //
        // Before reversal:
        // groupStartNode -> ... -> groupEndNode -> nullptr
        //
        // After reversal:
        // groupEndNode -> ... -> groupStartNode -> nullptr
        //
        // groupEndNode becomes the new head of the reversed group.
        // groupStartNode becomes the new tail of the reversed group.
        reverseKGroupLinkListReverseHelper(groupStartNode);
        // STEP 5: Connect the reversed group to the final linked list.
        // If this is the first reversed group, update the final head.
        if (newHead == nullptr) {
            newHead = groupEndNode;
        }
        else {
            // Connect the previous group's tail to the current group's head.
            previousGroupTail->next = groupEndNode;
        }
        // The original starting node becomes the tail after reversal.
        previousGroupTail = groupStartNode;
        // STEP 6: Connect the current reversed group to the next group.
        previousGroupTail->next = nextGroupStartNode;
        // Move to the beginning of the next group.
        currentNode = nextGroupStartNode;
    }
    // Return the head of the completely reversed linked list.
    return newHead;
}

//int main(){
//    ListNode* head = new ListNode(1);
//    head->next = new ListNode(2);
//    head->next->next = new ListNode(3);
//    head->next->next->next = new ListNode(4);
//    head->next->next->next->next = new ListNode(5);
//    printLinkedList(head);
//    head = reverseKGroup(head, 3);
//    printLinkedList(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
// Flatten Linked List - GFG
// Structure of a linked list node.
// Time Limit Exceeded (TLE)
class DataNode {
public:
    int data;
    DataNode* next;
    DataNode* bottom;
    DataNode(int data) : data(data), next(nullptr), bottom(nullptr) {};
};

// Helper function to print the original linked list
// along with its bottom pointers.
void printLinkedListWithBottom(DataNode* head) {
    // Pointer to traverse the main linked list.
    DataNode* currentNode = head;
    while (currentNode != nullptr) {
        cout << currentNode->data << " : ";
        // Traverse the bottom linked list of the current node.
        DataNode* bottomNode = currentNode->bottom;
        while (bottomNode != nullptr) {
            cout << bottomNode->data << " -> ";
            bottomNode = bottomNode->bottom;
        }
        // Move to the next node in the main linked list.
        currentNode = currentNode->next;
        cout << endl;
    }
    cout << endl;
}

// Helper function to print the flattened linked list
// using bottom pointers.
void printFlattenLinkedListWithBottom(DataNode* head) {
    DataNode* currentNode = head;
    while (currentNode != nullptr) {
        cout << currentNode->data << " -> ";
        // Move to the next node using the bottom pointer.
        currentNode = currentNode->bottom;
    }
    cout << endl;
}

// Helper function to print the linked list using next pointers.
void printFlattenLinkedListWithNext(DataNode* head) {
    DataNode* currentNode = head;
    while (currentNode != nullptr) {
        cout << currentNode->data << " -> ";
        // Move to the next node using the next pointer.
        currentNode = currentNode->next;
    }
    cout << endl;
}

// Helper function to merge two sorted linked lists using bottom pointers.
DataNode* mergeTwoSortedList(DataNode* firstList, DataNode* secondList) {
    // Dummy node helps construct the merged list without
    // handling the first node separately.
    DataNode* dummyNode = new DataNode(-1);
    // Maintains the tail of the merged linked list.
    DataNode* mergedListTail = dummyNode;
    // Traverse both sorted linked lists simultaneously.
    while (firstList != nullptr && secondList != nullptr) {
        // If the first list has the smaller or equal value,
        // attach its current node to the merged list.
        if (firstList->data <= secondList->data) {
            mergedListTail->bottom = firstList;
            // Move to the next node in the first list.
            firstList = firstList->bottom;
        }
        else {
            // Otherwise, attach the current node from the second list.
            mergedListTail->bottom = secondList;
            // Move to the next node in the second list.
            secondList = secondList->bottom;
        }
        // Move the merged list's tail to the newly attached node.
        mergedListTail = mergedListTail->bottom;
    }
    // If nodes remain in the first list, attach them directly.
    if (firstList != nullptr) {
        mergedListTail->bottom = firstList;
    }
    // If nodes remain in the second list, attach them directly.
    if (secondList != nullptr) {
        mergedListTail->bottom = secondList;
    }
    // Return the head of the merged linked list.
    return dummyNode->bottom;
}

// Function to flatten the linked list into a single sorted linked list.
DataNode* flatten(DataNode* head) {
    // If the list is empty or contains only one main node,
    // it is already flattened.
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    // Initially, the first vertical list is considered the flattened list.
    DataNode* flattenedListHead = head;
    // Start processing from the second main node.
    DataNode* currentNode = head->next;
    // STEP 1: Merge each vertical sorted list into the flattened list.
    while (currentNode != nullptr) {
        // Store the next main list node before merging.
        // This is necessary because merging modifies bottom pointers.
        DataNode* nextMainNode = currentNode->next;
        // Merge the current flattened list with the next vertical list.
        flattenedListHead = mergeTwoSortedList(flattenedListHead, currentNode);
        // Move to the next main list node.
        currentNode = nextMainNode;
    }
    // Return the head of the flattened linked list.
    return flattenedListHead;
}

//-------------------------------------------
// Helper function to merge two sorted bottom-linked lists.
DataNode* flattenMergeTwoSortedListHelper(DataNode* firstListHead, DataNode* secondListHead) {
    // Create a temporary dummy node to simplify the merging process.
    // The actual merged list will start from dummyNode->bottom.
    DataNode* dummyNode = new DataNode(-1);
    // Maintain a pointer to the last node of the merged list.
    DataNode* mergedListTail = dummyNode;
    // Traverse both sorted lists until one of them becomes empty.
    while (firstListHead != nullptr && secondListHead != nullptr) {
        // Compare the current nodes of both lists.
        // Attach the node containing the smaller value to the merged list.
        if (firstListHead->data <= secondListHead->data) {
            // Attach the current node from the first list.
            mergedListTail->bottom = firstListHead;
            // Move the first list pointer to its next bottom node.
            firstListHead = firstListHead->bottom;
        }
        else {
            // Attach the current node from the second list.
            mergedListTail->bottom = secondListHead;
            // Move the second list pointer to its next bottom node.
            secondListHead = secondListHead->bottom;
        }
        // Move the merged list tail to the newly attached node.
        mergedListTail = mergedListTail->bottom;
    }
    // If nodes remain in the first list, attach all remaining nodes.
    // No additional comparisons are required because the list is already sorted.
    if (firstListHead != nullptr) {
        mergedListTail->bottom = firstListHead;
    }
    // If nodes remain in the second list, attach all remaining nodes.
    if (secondListHead != nullptr) {
        mergedListTail->bottom = secondListHead;
    }
    // Store the actual head of the merged sorted list.
    DataNode* mergedListHead = dummyNode->bottom;
    // Delete the temporary dummy node to avoid a memory leak.
    delete dummyNode;
    // Return the merged sorted bottom-linked list.
    return mergedListHead;
}

// Helper function to find the middle node of a bottom-linked list.
// Uses the slow and fast pointer technique.
DataNode* flattenMergeSortFindMiddleNodeHelper(DataNode* head) {
    // If the list is empty or contains only one node,
    // that node itself is considered the middle node.
    if (head == nullptr || head->bottom == nullptr) {
        return head;
    }
    // Slow pointer moves one bottom node at a time.
    DataNode* slowPointer = head;
    // Fast pointer moves two bottom nodes at a time.
    // Starting from head->bottom helps find the node before
    // the middle when the list contains an even number of nodes.
    DataNode* fastPointer = head->bottom;
    // Continue until the fast pointer reaches the end of the list.
    while (fastPointer != nullptr && fastPointer->bottom != nullptr) {
        // Move slow pointer one step forward.
        slowPointer = slowPointer->bottom;
        // Move fast pointer two steps forward.
        fastPointer = fastPointer->bottom->bottom;
    }
    // Return the middle node (or the node before the middle).
    return slowPointer;
}

// Helper function to sort a bottom-linked list using Merge Sort.
DataNode* flattenMergeSortHelper(DataNode* head) {
    // BASE CASE:
    // An empty list or a list containing only one node
    // is already sorted.
    if (head == nullptr || head->bottom == nullptr) {
        return head;
    }
    // PHASE 1: Find the middle node to divide the list into two halves.
    DataNode* middleNode = flattenMergeSortFindMiddleNodeHelper(head);
    // Store the head of the right half.
    DataNode* rightHalfHead = middleNode->bottom;
    // Disconnect the two halves by terminating the left half.
    middleNode->bottom = nullptr;
    // The left half starts from the original head.
    DataNode* leftHalfHead = head;
    // PHASE 2: Recursively sort the left half.
    leftHalfHead = flattenMergeSortHelper(leftHalfHead);
    // Recursively sort the right half.
    rightHalfHead = flattenMergeSortHelper(rightHalfHead);
    // PHASE 3: Merge both sorted halves into one sorted bottom-linked list.
    return flattenMergeTwoSortedListHelper(leftHalfHead, rightHalfHead);
}

// Main function to flatten the linked list into one sorted bottom-linked list.
DataNode* flatten01(DataNode* head) {
    // Handle an empty linked list.
    if (head == nullptr) {
        return nullptr;
    }
    // Store the head of the final flattened list.
    DataNode* flattenedListHead = head;
    // Pointer to traverse the horizontal linked list using next pointers.
    DataNode* currentHorizontalNode = head;
    // ---------------------------------------------------------
    // PHASE 1: Connect all vertical bottom lists into one list.
    // ---------------------------------------------------------
    // Traverse the horizontal linked list until the last horizontal node.
    while (currentHorizontalNode->next != nullptr) {
        // Start from the current horizontal node.
        DataNode* currentBottomNode = currentHorizontalNode;
        // Store the next horizontal node before modifying connections.
        DataNode* nextHorizontalNode = currentHorizontalNode->next;
        // Find the last node of the current vertical bottom list.
        while (currentBottomNode->bottom != nullptr) {
            currentBottomNode = currentBottomNode->bottom;
        }
        // Append the next horizontal list at the end of the current bottom list.
        currentBottomNode->bottom = nextHorizontalNode;
        // Move to the next horizontal list.
        currentHorizontalNode = nextHorizontalNode;
    }
    // ---------------------------------------------------------
    // PHASE 2: Sort the combined bottom-linked list using Merge Sort.
    // ---------------------------------------------------------
    // All vertical lists are now connected through bottom pointers.
    // Apply Merge Sort directly using bottom pointers.
    flattenedListHead = flattenMergeSortHelper(flattenedListHead);
    // Return the head of the final sorted flattened linked list.
    return flattenedListHead;
}

//int main(){
//    DataNode* head = new DataNode(5);
//    head->bottom = new DataNode(7);
//    head->bottom->bottom = new DataNode(8);
//    head->next = new DataNode(10);
//    head->next->bottom = new DataNode(20);
//    head->next->next = new DataNode(19);
//    head->next->next->bottom = new DataNode(22);
//    head->next->next->next = new DataNode(28);
//    head->next->next->next->bottom = new DataNode(40);
//    head->next->next->next->bottom->bottom = new DataNode(45);
//    printLinkedListWithBottom(head);
//    head = flatten(head);
//    printFlattenLinkedListWithBottom(head);
//    return 0;
//}

//-------------------------------------------//-------------------------------------------//
