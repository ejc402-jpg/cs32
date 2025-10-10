// Overview: Resource Management pt. 2, Basic Linked Lists (insertion, deletion, destruction, traversal), Advanced Linked Lists (tail pointers, doubly-linked lists)

/*
Assignment Operators
  we learned how to create copy constructors to create a new object from an existing one
  but what about changing and existing object's value to another existing object
    in these complex cases we need assignment operators (= is the base level and might not work with dynamically allocated members) 
*/
int main(){
  
  CSNerd a("Jay", 110);
  CSNerd b(a); // new from existing

  CSNerd c("Jun", 120);
  CSNerd d("Tae", 130;
  d = c; // existing from existing
  // by default, during assignment (d = c), C++ copies all of c's member variables over to d
  // but this only works if classes don't dynamically allocate any memory
  // need specialized assignment operator function
  // if we don't define, C++ provides the default version that just copies the member variable as we just saw
}
/*
  C++ syntax for defining assignment operators is confusing so define a simpler version first
*/
class CSNerd{
  ...
  void setMeEqualTo(const CSNerd &src){ // simplified version, not the actual thing
    name_ = src.name_;
    IQ_ = src.IQ_;
  CSNerd& operator= (const CSNerd &src){ // real syntax for assignment operator 
    name_ = src.name_; // function name is operator=
    IQ_ = src.IQ_; // return type is a reference to the class
    return *this; // function returns *this when it's done
  } // why return *this?
      // enable chaining of assignments and to maintain consistency with the behavior of built-in types
  ...
};
/*
  where we need to define an assignment operator
    example of using C++ default assignment operator and shallow copy (PiNerd, create ann object then PiNerd ben(ann))
      in the example, ann points to 800. when ben is assigned to ann, the ben members also point to 800, not 900 where the ben object is allocated memory
      so similar to copy constructor, this causes problems
      also when ann is destroyed, we have memory leak because ben's members also point to ann but it got deleted before
  to do this right we need custom assignment operator (ensure no leaks of resources/memory previously held by the target object)
    target = source; // must ensure independent clones w/ deep copy, like with copy constructor
    1. free all resources held by the target object (since it starts as an existing, different object)
    2. determine what resources are used by the source object
    3. allocate a matching set of resources for the target object
    4. Copy the contents of the source objects to the target object so it's functionally identical but 100% independent
    5. return a reference to the target object
*/
class PiNerd
{
  public:
    PiNerd(int n) { … }
    ~PiNerd(){ delete[]m_pi; }
  
    // assignment operator:
    PiNerd &operator=(const PiNerd &src)
    {
      delete [] m_pi;
      m_n = src.m_n;
      m_pi = new int[m_n];
      for (int j=0;j<m_n;j++)
         m_pi[j] = src.m_pi[j];
      return *this;	    
    }  
    void showOff() { ... }	
  
  private:
  	int *m_pi, m_n;
};

int main()
{
  PiNerd ann(3);
  PiNerd ben(4);
 
  ben = ann; // ben's initial resources are freed up, then re-allocated to match the requirements of ann's
  // when *this reference is returns, ben properly points to the memory his "copied" object is allocated to
  // when destructing, ben goes first then ann, but it works because they are independent memory allocations
} 
/*
  however, there is one problem with the assignment operator above
    "Aliasing" is when we use two difference references/pointer to refer to the same variable
      causes unintended problems
*/
void f(PiNerd &x,PiNerd &y)
{
   ...
   x = y; // here, the assignment operator is called, but since the target is same as the source
} // assignment operator frees up target space, which deletes the source. 
// when we allocate new memory for the target's m_pi, we're reallocating the source to new memory address
// the new address contains random values, so target copies over those values instead of the original source because it got deleted because we tried to set ann = ann which caused source to be altered
// so trying to assignment operator an object to itself is BAD

int main()
{
  PiNerd ann(3);
  f(ann,ann); // we send the same object to f
}
/*
  the assignment operator must check to see if variable is being assigned to itself
    if so, do nothing
*/
class PiNerd
{
  ...
  PiNerd &operator=(const PiNerd &src)
  {
    delete [] m_pi;
    m_n = src.m_n;
    m_pi = new int[m_n];
    for (int j=0;j<m_n;j++)
       m_pi[j] = src.m_pi[j];
    return *this;	    
  }  
  …
};
/*
  updated steps for assignment operation
    1. check for aliasing (i.e. ben = ben) and if it's occurring go to step 5
    2. determine resources are used by the source object
    3. allocate a matching set of resources for the target object
    4. copy the contents of the source object to the target object so it's functionally identical but 100% independent
    5. return a reference to the target object
  assignment operator summary
    we are updating an existing target object to a source object, not creating (copy construction)
Linked Lists
  array stores items by reserving fixed size
    you need to know the size of your array before construction, and insertion (especially in the middle) is horrible
  linked list reserves a new memory block for each item as it's added, and links blocks together with pointers
    can hold variable number of items, growing/shrinking is easy
  think of linked lists as a scavenger hunt, each chest is a class/struct that hold clues 
    the clues are pointers to the next chest that lead you to the solution
*/
struct Chest{
  string treasure; // our first clue is a pointer variable that holds the address to the first chest
  Chest *next_chest; // we can set our last pointer to nullptr to indicate there are no further nodes in the list
};

// proper syntax for linked list

struct Node {
  string value;
  Node *next;
};

int main(){
  Node *head, *second, *third;
  head = new Node;
  second = new Node;
  third = new Node;
  head->value = "toast";
  head->next = second;
  second->value = "bacon";
  second->next = third;
  third->value = "eggs";
  third-next = nullptr;
  delete head;
  delete second;
  delete third; // note: delete command doesn't delete the pointer but kills what the pointer points to (dereferencing is bad, setting to nullptr after is good practice)
}
/*
  Normally we don't create our linked all at once in a single function
    instead we create a declared class (ADT) to hold linked list
    and add bunch of member functions to add, print items, delete item, etc.
*/
class LinkedList {
  private:
    struct Node { // nexted struct to represent Nodes in a Linked List class
      string value;
      Node* next;
    };
    Node* head_; // given the head node, we can follow the links to reach every node in the list
  public:
    void print_items(){ // print items
      Node *p;
      p = head_;
      while(p != nullptr){
        std::cout << p->value;
        p = p->next;
      }
    }
    void add_front(string v){
      Node *nn;
      nn = new Node; // note: new Node() will value initialize, not garbage initialize, might be better?
      nn->value = v;
      nn->next = head_;
      head_ = nn;
      if(is_last_node(head_) == true) tail_ = head_; // if the node we just added is last/only node in the list
    }
    void insert_after(Node *p, string v){
      Node *nn = new Node;
      nn->value = v;
      nn->next = p->next;
      p->next = nn;
    }
    void add_rear(string v){
      if(head == nullptr){ // linked list is empty
        add.front(v);
        return;
      }
      // Node *p = head_; // handle case where the list has one or more items
      // while(is_last_node(p) == false){
      //   p = p->next;
      // }
      // insert_after(p, v);    // OLD METHOD OF TRAVERSAL BEFORE ADDING TAIL POINTER
      insert_after(tail, v)
    }
   void add_alpha(string v) { // can also be used to insert items alphabetically!
     if (head_ == nullptr || v < head_->value) {
       add_front(v); 
       return;
     }
   
     Node *p = head_;
     while (is_last_node(p) == false) {
       if (v < p->next->value) {
         insert_after(p, v);
         return;
       }
       p = p->next;
     } 
  
     insert_after(p, v); // insert after last node
    }
  void del_after(Node *p){
    if(p == nullptr || p->next == nullptr) return;
    Node *target = p->next;
    p->next = target->next;
    delete target;
  }
  void del(string v) {
      if (head_ == nullptr) return;
      if (head_->value == v) {
        del_head();
        return;
      }
  
      Node *p = head_;
      while (p != nullptr) {
        if (p->next != nullptr &&
            p->next->value == v) {
          del_after(p);
          return;
        }
        p = p->next;
      }
    }
  ~LinkedList(){
    Node *p = head_;
    while(p != nullptr){
      Node *n = p->next;
      delete p;
      p = n;
    }
  }
};
int main() {
  LinkedList x;
  ...
  x.print_items();
  x.add_front("grunt");
  x.insert_after(third, "bobby");
  x.add_rear("flush");
}

}
/*
  Linked List traversal
    when you iterate through nodes of a linked list
    traversals can print like in our example above, but can also insert/delete items (added above)
  Deleting Nodes
    more complex, break into smaller parts
      first write a helper method to delete the first in the list
      then another helper method that accepts a pointer p to a node, and deletes the node just after p
      finally, write complete deletion method
    say we have a delete method that only accepts the node we want to delete
      impossible to relink!
    Destructing a list
      does traversing over each node and deleting along the way work?
        no! because you free node->next before actually moving on!
  Linked List summary
    they are complex, more than arrays
    to access the kth item, need to traverse k-1 times from the head first! no instant access!
    to add an item at the end, need to traverse all the way to the end!
      turns out we can fix this problem
  Linked Lists and Tail Pointers
    since we have, why not a tail?
      tail node points to last node of the list (added in example above)
Double-Linked Lists
  we have next and previous pointers in every node now
  every node except head has prev, every node except tail has next
*/
struct Node {
  string value;
  Node* next;
  Node* prev;
};
// can traverse both ways now, albeit allocating and linking more pointers
Node *p = head_;
while (p != nullptr)
{
    cout << p->value;
    p = p->next;
}
// OR
Node *p = tail_;
while (p != nullptr)
{
    cout << p->value;
    p = p->prev;
}
/*
Linked List Cheat Sheet
  never access node's data until validating its pointer
    if(ptr != nullptr) cout << ptr->value
  to advance ptr to the next node/end of the list
    if(ptr != nullptr) ptr = ptr->next
  to see if ptr points to the last node in a list
    if(ptr != nullptr && ptr->next == nullptr
  to get to the next node's data
    if(ptr != nullptr && ptr->next != nullptr) cout << ptr->next->value
  to get the head node's data
    if(head != nullptr) cout << head->value
  to check if a list is empty
    if(head == nullptr)
  general traversal
    while(ptr != nullptr){
      cout << ptr->value;
      ptr = ptr->next;
    }
  to check if a pointer points to the first node a list
    if(ptr == head) cout << "ptr is first node.";
Linked List vs. Array
  what is faster to get 573rd item --> array
  which is faster inserting a new item at front --> linked list
  which is faster to remove item from the middle --> linked list
  which is easier to program --> array
Linked List with Dummy Node
  every linked list we've seen so far has head pointer
    but this causes problems when adding to the end of an empty list, and we need dedicated code to check stuff
*/
class LinkedList {
private:
  struct Node {
    string value;
    Node* next;
  };
  Node  dummy_; // note: dummy is a regular node struct, not a pointer. it shouldnt hold any relevant values either, only job is to point to the head node in your actual list
  ...  // private methods
public:
  void add_front(string v) {
     Node *nn;
     nn = new Node;
     nn->val = v;
     nn->next = dummy_.next;
     dummy_.next = nn;
  }
  void add_rear(string v){
    Node *p = &dummy_;
    while (is_last_node(p) == false)
      p = p->next;
    
    // p points at last node now!
    insert_after(p, v);
  }
  ~LinkedList() {
    Node *p = dummy_.next;
    while (p != nullptr) {
      Node *n = p->next;
      delete p;
      p = n;
      // delete dummy_; --> NOT NEEDED! our dummy node was not dynamically allocated
  }
};
/*
  1. replace head pointer with a dummy node struct
  2. update methods to use the dummy node
*/











