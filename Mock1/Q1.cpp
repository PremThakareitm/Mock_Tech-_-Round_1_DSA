// Write a function that reverse a singly linked list in place and return the reversed list. aditional implemente a function to detect if the linked list has a loop and remove the loop if present.
//you must handle both the reversal & cycle detection / removal in O(n) tim complexity
//constraints don't use any additional data structure like arrays or hash sets.

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* reverseList(Node* head) {
    Node *prev = nullptr, *curr = head, *next = nullptr;
    
    while (curr != nullptr) {
        next = curr->next;  
        curr->next = prev;  
        prev = curr;        
        curr = next;        
    }
    
    return prev;  
}

bool detectAndRemoveCycle(Node* head) {
    if (head == nullptr || head->next == nullptr)
        return false;
        
    Node *slow = head, *fast = head;
    bool hasCycle = false;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }

    if (hasCycle) {
        slow = head;

        if (slow == fast) {
            while (fast->next != slow) {
                fast = fast->next;
            }
        } else {
            while (slow->next != fast->next) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        

        fast->next = nullptr;
    }
    
    return hasCycle;
}

//to print the linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

// Test the implementation
int main() {
    // Test Case 1: List without cycle (1->2->3->4)
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    
    cout << "List 1 (without cycle): ";
    printList(head1);
    
    head1 = reverseList(head1);
    cout << "List 1 reversed: ";
    printList(head1);
    
    // Test Case 2: List with cycle (1->2->3->4->2)
    Node* head2 = new Node(1);
    Node* second = new Node(2);
    head2->next = second;
    head2->next->next = new Node(3);
    head2->next->next->next = new Node(4);
    head2->next->next->next->next = second;  // cycle to node 2
    
    cout << "\nList 2 (with cycle 1->2->3->4->2)" << endl;
    bool hasCycle = detectAndRemoveCycle(head2);
    cout << "Cycle " << (hasCycle ? "detected and removed" : "not found") << endl;
    cout << "List 2 after cycle removal: ";
    printList(head2);
    
    head2 = reverseList(head2);
    cout << "List 2 reversed: ";
    printList(head2);
    
    return 0;
}
