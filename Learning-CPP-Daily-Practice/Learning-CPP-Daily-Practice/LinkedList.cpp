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
