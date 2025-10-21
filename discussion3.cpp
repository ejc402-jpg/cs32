// Worksheet 

/*
1. (10 min) Write a function cmpr that takes in a linked list and an array and returns the largest index up to which the two are identical. 
  The function should return -1 if no values match starting from the beginning.
  The header of your function is given as:
    int cmpr(Node* head, int* arr, int arr_size)
  Assume the following declaration of Node:
    struct Node {
      int data;
      Node* next;
    };
  Examples:
    // head -> 1 -> 2 -> 3 -> 5 -> 6
    int a[6] = {1, 2, 3, 4, 5, 6};
    cout << cmpr(head, a, 6); // Should print 2
    int b[7] = {1, 2, 3, 5, 6, 7, 5};
    cout << cmpr(head, b, 7); // Should print 4
    int c[3] = {5, 1, 2};
    cout << cmpr(head, c, 3); // Should print -1
    int d[3] = {1, 2, 3};
    cout << cmpr(head, d, 3); // Should print 2
*/
int cmpr(Node* head, int* arr, int arr_size){
  int index = 0;
  while(head && index < arr_size){
    if(head->data != arr[index]) return (index == 0) ? -1 : index - 1;
    index++;
    head = head->next;
  }
  return index - 1; 
}

/*
2. (10 min) Given two linked lists where every node represents a character in a word.
Write a function compare() that works similarly to strcmp(), i.e., it returns 0 if both
strings are the same, a positive integer if the first linked list is lexicographically1
greater, and a negative integer if the second string is lexicographically greater.
The header of your function is given as:
  int compare(Node* list1, Node* list2)
Assume the following declaration of Node:
  struct Node {
    char c;
    Node* next;
  };
Example:
  If list1 = a -> n -> t
    list2 = a -> r -> k
  then compare(list1, list2) < 0
  
  If list1 = b -> e -> a -> n -> s
    list2 = b -> e -> a -> n
  then compare(list1, list2) > 0
*/
int compare(Node* list1, Node* list2) {
  while(list1 && list2){
    if(list1->c > list2->c) return 1;
    else if(list1->c < list2->c) return -1;
    list1 = list1->next;
    list2 = list2->next;
  }
  if(list1 || list2) return (list1) ? 1 : -1;
  else return 0;
}

/*
3. (10 min) The following is a class definition for a linked list, called LL, and for a node,
called Node. Class LL contains a single member variable - a pointer to the head of a
singly linked list. Struct Node contains an integer value, and a node pointer, next, that
points to the next node in the linked list. Your task is to implement a copy
constructor for LL. The copy constructor should create a new linked list with the
same number of nodes and same values.
Note: This is not a complete class implementation, but it doesn’t affect the problem.
*/

class LL {
  public:
    LL() { head = nullptr; }
    LL(const LL& other){
      if(!other.head) head = nullptr;
      else{
        head = new Node;
        head->val = other.head->val;
        Node* thisCurrent = head;
        Node* otherCurrent = other.head;
        while(otherCurrent->next){
          thisCurrent->next = new Node;
          thisCurrent->next>val = otherCurrrent->next->val;
          thisCurrent->next->next = nullptr;
        }
        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
      } 
    }
    int findNthFromLast(int n);
  private:
    struct Node {
      int val;
      Node* next;
    };
    Node* head;
};
int LL::findNthFromLast(int n){
  for(int i = 0; i < n; i++){
    if(p == nullptr) return -1;
    p = p->next;
  }
  if(!p) return -1;
  Node* newCurrent = head;
  while(p->next){
    p = p->next;
    newCurrent = newCurrent->next;
  }
  return newCurrent->val;
}

/*
4. (15 min) Using the same class LL from the last problem, write a function
findNthFromLast that returns the value of the Node that is n Nodes before the last
Node in the linked list. Consider the last Node to be 0 Nodes before the last Node,
the second-to-last Node to be 1 Node before the last Node, etc.
int LL::findNthFromLast(int n);
// findNthFromLast(2) should return 4 when given the following linked list:
// head -> 1 -> 2 -> 3 -> 4 -> 5 -> 6
If the nth from the last Node does not exist, findNthFromLast should return -1. You
may assume all values that are actually stored in the list are nonnegative.
*/

// solution to 4 implemented into 3

struct Node {
  int val;
  Node* next;
};
class LinkedList {
  public:
    void rotateLeft(int n){
      Node* newHead = nullptr;
      Node* current = head;
      if(n <= 0 || !head->next) return;
      for(int i = 0; i < n; i++){
        if(!current->next) current = head;
        else current = current->next;
      }
      Node* stopPoint = current;
      newHead->val = current->val;
      newHead->next = nullptr;
      (while current->next){
        newHead->next = current->next;
        newHead->next->val = current->next->val;
        newHead->next->next = nullptr;
        newHead = newHead->next;
      }
      while(head != stopPoint){
        newHead
      }
    }
  private:
    Node* head;
};
