/*
Destructors - why do we need them? 
  free dynamically allocated memory
  close files or network connections
  release system resources
  ex. ~ClassName(){...}
  no arguments, automatically called when an object:
    1. goes out of scope
    2. is deleted (heap allocation) 
  but only one per class (compiler generates a default destructor if you don't make one) 
  nuances
    order of destruction  
      1. local vars are destroyed in reverse order of creation
      2. in inheriting, outside-in (class composition) 
*/
#include <iostream>
using namespace std;

struct A {
    A()  { cout << "A constructed\n"; }
    ~A() { cout << "A destroyed\n"; }
};

struct B {
    B()  { cout << "B constructed\n"; }
    ~B() { cout << "B destroyed\n"; }
};

struct C {
    A a;
    B b;
    C()  { cout << "C constructed\n"; }
    ~C() { cout << "C destroyed\n"; }
};

int main() {
    C c;
}

// A constructed
// B constructed
// C constructed
// C destroyed
// B destroyed
// A destroyed

/*
copy constructors
  called when an object is initialized from another (of the same type)
    passing objects by value to functions
    returning objects by value from functions
  ex. A b = a;
  what happens if your object has other objects?
    Behavior
      ClassName(const ClassName& other){...}
      notice it take s const reference to another object of the same type
      no return type
      usually public
      only one
    Default copy constructor is provided by the compiler - performs a shallow copy
      shallow copy: creates a new object but only copies references to nested objects so the new and original objects share the same inner objects
        can lead to...
          1. double deletion
          2. dangling pointers
          3. more dangers...
      deep copy: creates a new object and recursively copies all nested objects, resulting in completely independent objects where changes to one do not affect the other
    `  no risks that shallow copies have
  ex. what would happen if copy constructor looked like this:
    1. (incorrect) ClassName(const ClassName other){...}
      causes infinite recursion --> crash because trying to pass by value means creating a copy
    2. (correct) ClassName(const ClassName& other){...}
      no copy is made, can pass contents of other into *this
assignment operator
  how do we assign one object to another after both have been constructed? 
  protects from...
    1. shared pointers
    2. double deletes
    3. memory/resource leaks
  behavior
    ClassName& operator = (const ClassName& other){...}
    Called when an object is already constructed and is assigned the value of another object of the same type (wait for polymorphism)
    returns a reference to *this
      chained assignments is ok!
      a = b = c;
    compiler gives you a shallow copy default
  self-assignment check is crucial:
    if(this == &other) return *this
    why?
      Because without the check, assigning an object to itself could make it delete or overwrite its own data, causing corruption or crashes.
      consts can only be initialized, not reinitialized
      references must be bound at construction, can't be re-bound
      so, what happens if your object has these?
        the compiler deletes its own default assignment operator
        if you use one, you must define one
rule of three
  if you have one of these:
    1. destructor
    2. assignment operator
    3. copy constructor 
  you need all of them (good coding practice)
*/
