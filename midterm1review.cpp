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
  for(i = 1, ptr = head; i < (M-N+1); i++){ // move forward (M-N) steps to get N-th to last element
    ptr = ptr->next;
  }
  value = ptr->num;
  return true;
}

// Problem #2 Please complete the missing blocks of codes below to make the program generate the following output
/*
1 + 2i
6 + 7i
6 + 7i
6 + 7i
*/
#include <iostream>
using namespace std;
class Complex{
private:
  double r, i;
public:
  Complex() : r(0), i(0) {}
  Complex(int c_r, int c_i) : r(c_r), i(c_i) {}
  void output(){
    cout << r << "+" << i << "i" << endl;
  }
  Complex& operator=(const Complex& other){ // this was unnecessary however
    r = other.r; // no dynamically allocated memory, so compiler-generated copy is safe
    i = other.i;
  }
};
int main(){
  Complex a, b;
  a = Complex(1, 2); a.output();
  b = Complex (6, 7); b.output();
  a = b;
  a.output();
  b.output();
  return 0;
}

// Problem 3 - The implementation below will crash because it's missing a copy constructor and an assignment operator
// currently, Class Triangle dynamically allocated of Points 
// default copy causes shallow copy --> multiple deletes on the same pointer
// must define copy constructro and assignment operator for deep copy
// rule of three
#include <iostream>
using namespace std;
class Triangle {
public:
  Triangle() {
    p = new Point[3];
  }
  Triangle(int x1,int y1,int x2, int y2,int x3,int y3) {
    p = new Point[3];
    p[0].x = x1; p[0].y = y1;
    p[1].x = x2; p[1].y = y2;
    p[2].x = x3; p[2].y = y3;
  }
  Triangle(const Triangle& other){
    p = new Point[3];
    p[0].x = other[0].x; p[0].y = other[0].y;
    p[1].x = other[1].x; p[1].y = other[1].y;
    p[2].x = other[2].x; p[2].y = other[2].y;
  }
Triangle& operator=(const Triangle& other){
  if(&other = this) return *this;
  delete[] p;
  p = new Point[3];
  p[0].x = other[0].x; p[0].y = other[0].y;
  p[1].x = other[1].x; p[1].y = other[1].y;
  p[2].x = other[2].x; p[2].y = other[2].y;
  return *this;
}
  Triangle::~Triangle() { delete [] p; }
private:
  struct Point {
    int x,y;
    Point(int px=0,int py=0): x(px), y(py) { }
  };
  Point *p;
};
int main() {
  Triangle *array[3]; // dynamically allocated array of three triangles (each triangle points to a point)
  array[0] = new Triangle(1,1,1,3,3,1);
  array[1] = new Triangle(2,2,2,6,6,2);
  array[2] = new Triangle(3,3,3,9,9,3);
  Triangle c2 = *array[0];
  c2 = *array[1];
  for(int i=0;i<3;i++) delete array[i];
}

/*
Rule of Three Summary
  if a class manages dynamic memory, you must define all three
    1. destructor - free allocated memory
      delete pointers within array first or just delete the array or whatever pointers
    2. copy constructor - deep copy during creation
    3. assignment operator - deep copy during assignment
      delete pointers within array first or just delete the array or whatever pointers
      check if (&src = this) and return *this at the end 
*/

// Pointer Arithmetic Review

#include <iostream> 
using namespace std;
int main(){
  int nums[] = {10, 20, 30, 40, 50};
  int *p = nums;

  std::cout << *(p+2) << endl;
  std::cout << *p + 2 << endl;
  std::cout << *(nums+4) - *(p+1) << endl;

  return 0;
}

// 30 12 30

#include <iostream> 
using namespace std;

int main(){
  int arr[5] = {5, 10, 15, 20, 25};
  // supposed address respectively are 1000, 1004, 1008, 1012, 1016
  int *p = arr;
  int *q = p + 3;

  std::cout << (q-p) << endl;
  std::cout << (p+2) << endl;
  std::cout << *(q-1) << endl;
}

// 3, 1008, 15
// pointer minus pointer gives number of elements between them, not byte difference
