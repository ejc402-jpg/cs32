/*
CS 32 — Midterm Exam 2
Overall Topics Summary
1. Inheritance
  base vs. derived classes
  constructor/destructor order
  override rules, including const
  signature matching
2. Polymorphism
  Base* pointing to Derived
  virtual functions
  dynamic dispatch
  slicing when passed by value
3. Virtual Functions & Virtual Destructors
  virtual needed for polymorphic delete
  derived->base destructor order
  consequences of non-virtual destructor
4. Operator Overloading
  operators = functions
  comparison operator rules
  const correctness
  used in set/sort
5. Templates (Functions & Classes)
  function templates
  class templates
  out-of-class definitions need template<typename T>
6. Sorting Algorithms
• Selection Sort
  O(n^2) --> not stable
• Insertion Sort
  O(n) best, O(n^2) worst, stable
• Bubble Sort
  O(n) best, O(n^2) worst, stable
7. Sorting Stability (Stable vs Unstable)
  stable keeps equal order
  insertion and bubble stable
  selection not stable
8. Big-O Complexity for Sorting Algorithms
  nested loops --> O(n^2) 
  linear loops --> O(n)
  halving --> O(log n) with base 2
  sorting complexities
9. Trees (nodes, children, height)
• Binary Trees
• Binary Search Trees (BSTs) --> specialized type of binary tree where left/right subtrees have smaller/larger values
  search path left/right
  insert rules
  delete cases: 0/1/2 children
• Tree Traversals (preorder, inorder, postorder)
  Root Left Right
  Left Root Right
  Left Right Root
• Recursive Tree Operations
• Node Struct Design (int val, Node* left, Node* right, etc.) 
• Insertion / Search / Delete
• Complexity of Tree Operations
  balanced BST --> O(log n) 
  unbalance BST --> O(n) 
  skewed tree behaves like list 
*/

// Problem 1

class Character {
public:
Character(int health) : health_(health) {}
void takeDamage(int amount) {
health_ -= amount;
if (health_ < 0) health_ = 0;
}
int getHealth() const {
return health_;
}
private:
int health_;
void regenerate() {
health_ += 10;
}
};

class Wizard : public Character {
public:
Wizard(int health) : Character(health) {}
void castHealSpell() {
regenerate(); }
}

int main() {
Wizard w(50);
w.takeDamage(30);
w.castHealSpell();
cout << w.getHealth() << endl;
return 0;
}

/*
  regenerate method is private and is not accessible anywhere publicly
    fix: make void regenerate() a protected member to be accessed within the object
Inheritance: Reuse 
  every public method in the base class is publicly reused/exposed in the derived class as if it were defind there
  can be used as normal in the program and derived class can cleanly call them as well
  note: no matter the access modifier, derived classes cannot access private members of base classes
  but public members that can access those private members can be reusable in the derived class!
    if you want to expose a private base class member to its derived class(es) but still hide it from unrelated classes/functions...
      use the protected keyword!
      note: never put member variables in the protected keyword (bad practice, revealing structure) 
*/

// Problem 2.1 Please fill in the following blanks to complete the implementations of printReverse() and printReverseHelper() to print the list elements in reverse order recursively

#include <iostream> 
using namespace std;

class LinkedList{
public: 
LinkedList(): head(nullptr){} 
~LinkedList();
void append(int value);
void print() const;
void printReverse() const;
void reverse(); 
int sum() const;
private:
struct Node{
  int num;
  Node* next;
};
Node* head;
void printReverseHelper(const Node* p) const; 
Node* reverseHelper(Node* current, Node* previous);
int sumHelper(const Node* p) const;
void removeNodes(Node* p);
};

void LinkedList::printReverse() const{
  printReverseHelper(head);
  cout << std::endl;
}
void LinkedList::printReverseHelper(const Node* p) const{
  if(p == nullptr) return;
  printReverseHelper(p->next);
  std::cout << p->num << " ";
}

// 2.2 implement reverse() to recursively reverse linked list

void LinkedList::reverse(){
  head = reverseHelper(head, nullptr);
} 
LinkedList::Node* LinkedList::reverseHelper(Node* current, Node* previous){
  if(current == nullptr) return previous;
  Node* last_node = reverseHelper(current->next, current);
  current->next = previous;
  return last_node;
}
LinkedList::~LinkedList(){
    removeNodes(head);
}

// 2.3 fill int he followingblanks to complete implementation of sumHelper() to consume the sume of the values of the list recursively

int LinkedList::sum() const{
  return sumHelper(head);
}
int LinkedList::sumHelper(const Node* p) const{
  if(p == nullptr) return 0;
  return p->num + sumHelper(p->next);
}

// 2.4 complete implementation of removeNodes() to correctly implement in the destructor properly

LinkedList::~LinkedList(){
  removeNodes(head);
}

void LinkedList::removeNodes(Node* p){
  if (p == nullptr) return;
  removeNodes(p->next);
  delete p; // this order is extremely important to avoid dereferencing a deleted pointer
} 

// 3. fill in the missing blanks and code blocks so that the output of the program is 

class Base{
public: 
Base (string nm) : name (nm) {}
string getName() const {return name;}
virtual void printName() const {std::cout << "Base " << name << endl;}
private:
string name;
};
class Derived : public Base {
public: 
Derived (string nm) : Base (nm){}
virtual void printName() {cout << "Derived Doctor " << getName(); << endl;}
};
void printAll (const vector<Base*>& vec){
  for (int i = 0; i < vec.size(); i++){
    vec[i]->printName();
  }
}
int main(){
  vector<Base*> v;
  v.push_back(new Base("Homer Simpson"));
  v.push_back(new Derived("Beverly Crusher"));
  v.push_back(new Derived("Who"));
  printAll(v);
  for(int i = 0; i < 3; i++){
    delete v[i];
  }
} // NOTE: pay attention to the printName() const in the base class, meaning there are different functions!
/*
Inheritance: Specialization/Overriding
  in addition to adding entirely new functions and variables to a derived class..
  you can also override or specialize existing functions from the base class in your derived class(es)
    virtual keyword says you intend to override the function in derived classes
    function must have same name, parameters, return type, const to be valid
    keyword optional in derived, as with override, but base class MUST HAVE!
*/

// 3. fill in the missing blanks and code blocks below so that the output of the program is:
  // Base Homer Simpson, Derived Dctor beverly Crusher, Derived Doctor Who
  // uhhhhh either add const to derived method or remove const from base method

/*
Defining an iterator (figurative pointer)
  write the container type followed by two colons, followed by the word iterator and then a variable name
  ex. vector<string>::iterator it2;
  ex. list<float>::iterator it3;
Using an Iterator
  point your iterator to the first item, simply use the begin() method
  once the iterator points at a value, use the * oeprator to dereference it to access value
    move up and down with ++ or --
  also has an end() method which points to an allocation of memory directly after the last item in the container
    why? because loops would miss the last item of end() pointed to the last item
*/
int main(){
  vector<int> vec;
  vec.push_back(1234);
  vec.push_back(2);
  vec.push_back(65);
  vector<int>::iterator it = vec.end();
  vec--;
  std::cout << *it;
  // OR
  vector<int>::iterator it = vec.begin();
  while(it != vec.end()){
    std::cout << *it;
    it++;
  }
}
