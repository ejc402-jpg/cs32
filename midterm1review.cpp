// Linked Lists, Classes, Dynamic Memory, Copy Constructor & Assignment Operator, Pointer Arithmetic

// Problem 1 - Linked List Method Implementation (TODO: implement addToList, the destructor, and reverse methods)

#include <iostream>
using namespace std;
class LinkedList{
  public:
    LinkedList: head(nullptr){}
    ~LinkedList(){
      Node* temp = nullptr;
      while(head){
        temp = head;
        head = head->next; // we store the memory we want to delete in temp first so we can properly move forward to the next node
        delete temp; // preventing the risk of losing access to the current node’s memory before you can free it.
      }
    }
    void addToList(int value){
      Node* newNode = new Node;
      newNode->num = value;
      newNode->next = nullptr;
      if(!head) head = newNode;
      Node* current = head; 
      while(current->next) current = current->next;
      current->next = newNode;
    }
    void reverse(){
      Node* prev = nullptr; // three pointers approach
      Node* curr = head;
      while(curr){
        Node* next = curr->next; // allows us to keep progressing forward
        curr->next = prev; // assigns the next of node to the opposite direction
        prev = curr;
        curr = next; // stops when curr goes beyond the linked list, leaving prev to point to the last node which becomes the new head
      }
      head = prev;
    }
    void output();
  private:
    struct Node{
      int num; 
      Node* next;
    };
    Node* head;
};

void LinkedList::output(){
  Node* ptr = head;
  std::cout << "The elements in the list are: ";
  while(ptr){
    std::cout << ptr->num << " ";
    ptr = ptr->next;
  }
  cout << endl;
}


int main(){
  LinkedList list; 
  for(int i = 0; i < 10; i++){
    list.addToList(i); 
    list.output();
    list.reverse();
    list.output();
  }
}

/*
Linked List Traversals 
  every time you iterate through the nodes of a linked list, this is called a traversal 
  in the previous example, we showed a traversal that printed each item (output) 
    but traversals can be generalized and used for many tasks 
  Adding To Front of List Challenge
    1. allocate a new node
    2. give the value in the node
    3. make the new node's next point to the head
    4. make the new node the new head
*/
class LinkedList{
private:
  struct Node{
    string value;
    Node* next;
  };
public: 
  void add_front(string v){
    Node *nn; 
    nn = new Node;
    nn->value = v;
    nn->next = head;
    head = nn;
  }
  void add_rear(string v){
    Node* newNode = new Node;
    newNode->value = v;
    newNode->next = nullptr;
    if(!head) {
      head = newNode;
      return;
    }
    Node* current = head;
    while(current->next) current = current->next;
    current->next = newNode;
  }
};
/*
  Adding To Rear of the List
    more complex, break it up into pieces
      1. write a helper method to determine if the node is the last node in the list
      2. write another helper method to accept a pointer to some node and adds a new node right after it
      3. then, write the actual method to add an item to the rear of the list
*/
bool isLastNode(Node *n){
  return(n->next) ? false : true;
}
void insertAfter(Node *p, string v){
  Node* tail = new Node;
  tail->value = v;
  tail->next = p->next;
  p->next = tail;
}
// given a linked list is guaranteed to have at least one item, fill in the blanks to add a new value to the rear of a list
/*
    1. traverse the list until our traversal pointer points at the last node
    2. insert the new node after the current last node
  Problem #1.4
    suppose we add a new member function called findNthFromLast() to find the N-th node from 
    the end of the list, where N being 1 means the last node, N being 2 the second-to-last, etc.
    use the reverse member function to complete the implementation of findNthFromLast() member function
    If the list has at least N node, then assign to the variable value the number that is stored in that node and return true;
    otherwise, leave the variable value unchanged and return false
    dont forget to call the reverse function to restore the linked list to the original state
*/
bool LinkedList::findNthFromLast(int N, int &value){
  reverse();
  Node*ptr = head; 
  int n = 0;
  while(ptr){
    n++;
    if(n == N){
      value = ptr->num;
      reverse();
      return true;
    }
    ptr = ptr->next; // simple logic but requires two reversals
  }
  reverse();
  return false;
}
/*
  Problem #1.5 
    there is a more efficient way to achieve the result in Problem #1.4 without linked list reversals
    scan first to count the total numebr of items in the linked list
    the second time we scan the list, we know how many items there are and the Nth node from the end of the list can be easily calculated
*/
bool LinkedList::findNthFromLast(int N, int &value){
  if(N <= 0) return false;
  Node* ptr = head;
  int i, M = 0;
  while(ptr){
    M++; 
    ptr = ptr->next;
  }
  if(N > M) return false;
  for(i = 1, ptr = head; i < (M-N+1); i++){
    ptr = ptr->next;
  }
  value = ptr->num;
  return true;
}

STOPPED AT PAGE 32
