/*
Pointers: enable dynamic memory allocation, complex data structures, and argument passing
  & operator tells us where a variable is located in RAM - its address
    an address is NOT a variable, it is the location of a variable which takes up no storage
  * operator dereferences takes the address of the variable it points at and retrieves the value stored at that location of memory
    int* ptr = &num;
    OR
    int* ptr;
    ptr = &num;
    CANNOT DO THIS...
      int* ptr = num (null pointer exception)
      cout << *ptr;
        if you don't initialize a pointer variable then it holds a random address
      OR
      int* ptr;
      *ptr = &num;
Pointers vs References
  when you pass a variable by refernce to a function, what really happens? 
  in fact, a reference is just a simpler notation for passing by a pointer!
    under the hood, C++ uses a pointer to match the address
Debugging
  try it?
  can speed up the programming process
Include Etiquette
  never include cpp or h files in h files, or cpp files in other cpp files
  only include h files in cpp files
Arrays, Addresses and Pointers
  declaring and initialization an array, couting the array variable name outputs the address to the first element stored
  no need for & operator to get an array's address
  array-to-pointer decay
  ex. cout << nums + 2;
    adding j to p gives you the addres of the jth element in the array, not the address of the first item in the array + j literally
  ex. int *ptr = nums --> cout << ptr + 2;
    works in the same way as the previous example
      these are examples of pointer arithmetic
  ex. cout << ptr[2];  
    remember: we can use pointer and array access methods interchangeably
    this is also giving a value not address
    ptr[2] = *(ptr + 2)
Pointer Arithmetic and Arrays
  when you pass an array to a function...
    you are just passing the address to the start of the array not the array itself
*/
void printData(int *array) // parameter variable for an array is actually just a pointer == int array[]
{
  cout << array[0]; // array[-1] could work if given the address of &nums[i] - would print first element 10
  cout << array[1];
}

int main(){
  int nums[3] = {10, 20, 30};
printData(nums); // 10, 20
printData(&nums[i]); // 20, 30
printData(nums+1) // 20, 30
}
/*
  note: you need to tell the function the size of the array (can be done with sizeof() operator)
Classes, Structs, and Pointers
*/
void printInfo(Circ* ptr){
  cout << "the area is" << ptr->getArea();

int main(){
  Circ foo(3, 4, 10);
  printInfo(&foo);
}
/*
  can use pointers with structs and classes too
  before C++, people didn't use classes
    they used structs, pointers, and functions instead of classes
    it used to be a struct and then sets of functions that accepted pointers as arguments since references didn't exist back then
Classes and the "this" Pointer
  void Init(Wallet *this){
    this->num1s = this->num5s = 0;
  }
  when you do stuff like void Wallet::Init(), the code above is what's really happening (using pointers to reference what you're building) 
  C++ hides this stuff to keep it simple but you can still access it
    this->num1s = 0; is equivalent to num1s = 0;
Pointers to Functions
  Just like variables, functions have addresses in memory as well
*/

void squared(int a){
  std::cout << a*a;
}

void cubed(int a){
  std::cout << a*a*a;
}

int main(){
  
  FuncPtr f; // void (*f)(int); (void is return type of functions, asterisk * in front of pointer variable, f, and specify the types of the parameters of the functions that you want f to point to
  // if your function(s) took in an int and double, you would write (int, double) 
  // right now, variable f can only be set to point to functions that have a void return type
  // A funcptr typedef creates a more readable, custom name (an alias) for a function pointer's complex signature
  
  f = &squared;
  f(10);
  f = &cubed;
  f(2);
}
/*
Dynamic Memory Allocation... Whats the big picture?
  Often a program won't know how much memory it needs to solve a problem until it's actually running
  In these cases, C++ lets you reserve a chunk of memory on-demand and gives you a pointer to it
  your code can use the memory via the pointer and when you're done, ask C++ to unreserve it
  Dynamic memory allocation in C++ lets programs request and free memory at runtime using pointers (via new and delete), allowing flexible use of memory when the required size isn’t known in advance.
*/
void computerSomethingImportant(int count){
  ptr = askC++ForThisMuchMemory(count);
  operateOnTheMemoryAt(ptr);
  tellC++WereDoneWithThisMemory(ptr);
}
/*
New and Delete (For Arrays)
  say we wanted to define an array
    we won't know how big to make it until our program actually runs
*/
int main(){
  int *arr = nullptr;
  int size;
  std::cin >> size;
  arr = new int[size]; // can now treat pointer like an array
  arr[0] = 10;
  arr[2] = 75; // *(arr+1) = 20;
  delete []arr; // tells OS to deallocate the memory and let someone else use it in the future
    /*
    1. first, define a new pointer variable
    2. then determine the size of the array you need
    3. then use the new command to reserve the memory. Your pointer gets the address of the memory
    4. Now use the pointer just like it's an array!
    5. Free the memory when you're done
    */
}
/*
  the new command requires the type of array you want to allocate and the number of slots
  make sure the pointer's type is the same as the type of array you're creating
  Operating System: "I found {#} bytes of free memory at address 30050 for you, C++."
New and Delete (For Non-Arrays) 
  we can use new and delete to dynamically allocate individual values and arrays of any type of value!
*/

// ex. 1

struct Point{
  int x; 
  int y;
};
int main(){
  Point *ptr;
  ptr = new Point;
  ptr->x = 10;
  (*ptr).y = 20;
  delete ptr;
}

// ex. 2

class Nerd{
  public:
    Nerd(int IQ, float GPA){
      m_myIQ = IQ; 
      m_myGPA = GPA;
    }
    void saySomethingNerdy(){
      std::cout << "C++ rocks!";
    }
};

int main(){
  Nerd *ptr;
  ptr = new Nerd(150, 3.999);
  ptr->saySomethingNerdy();
  delete ptr;
}

/*
  what exactly is deleted? does it free the pointer or the object pointed to by the pointer?
    it frees the object pointed to by the pointer, and the pointer becomes dangling (dereferencing is DANGEROUS at this point)
Using new and delete in a class facilitates dynamics variable maintenance (i.e. a class that stores a fixed # of pi digits to any number of pi digits)
*/

// ex. Consider the following two programs

int main(){ // variable q is a pointer to a dynamically allocated array of string objects
  string *q;
  q = new string[5];
  q[0] = "dogs";
  q[1] = "cats";
  delete []q; // free the dynamically allocated array that q points at
}

int main(){ // variable q is an array of pointers to dynamically allocated string objects
  string *q[5]; // array of string pointers, not one pointer that is an array size 5 for strings
  q[0] = new string("dogs");
  q[1] = new string("cats");
  delete q[0]; // array was not dynamically allocated, so we only need to delete the objects pointed to by the array
  delete q[1]; // even if array was dynamically allocated, each object needs to be deleted first before deleting the array of pointers or else memory leak
  // and so on..
}

/*
Copy Construction: when we create (construct) a new object by copying the value of an existing object
  required if you want to let users make a copy of more complex class variables
  simple example
    PiNerd existingNerd(4);
    PiNerd clonedNerd = existingNerd;
    clonedNerd.showOff(); // 3.141;
      to clone more complex objects, however, we need to create a special function called a copy constructor
*/

class CSNerd{
  public:
    CSNerd(string name, int IQ){
      name_ = name; 
      IQ_ = IQ;
    }
    CSNerd (const CSNerd& old){ // must be const and a reference (we don't want to modify original object and no need to create copies of values)
      name_ = old.name_;
      IQ_ = old.IQ_;
    } // this is what a default copy constructor does --> shallow copy 
  private:
  string name_, IQ_;
};

int main(){
  CSNerd a("David", 200); 
  CSNerd b = a; // same as CSNerd b(a); --> even though it looks like an assignment, it stil calls the copy constructor!
}

/*
  in the past constructors only took simple arguments like strings and ints
    but the second constructor initializes a new object based on an existing object of the same type
  the copy constructor is not just used when you initialize a new object from an existing one
    it's used any time you make a copy of an existing object
      for example, when object is passed by value to a function
  thus, if you don't define your own copy constructor C++ provides a default one for you
    it copies all of the member variables from the old instance to the new instance
      this is called SHALLOW COPY
        but problem:
          when copying objects like this, copies point to the same member variables stored at an address
          only the original should point to that address, but the copies also point to the same private members
          if the destructor of the copies are called when they go out of scope, for example, since the copies are pointing to the original, the copy is deleting the member variables that the original points to
            causes undefined behavior when it gets to the original 
  what do we want instead? 
    a copy constructor must ensure the new object is a completely independent clone of the old object
      must be logically indentical but must not share any data stuctures in memory
      must point to different memory addresses for every member
    original and copies are allocated unique memory addressess
  for classes that point to external objects/arrays, you must define your own copy constructor
    1. determine what resources are used by the source object
    2. allocate a matching set of resources for the target object
    3. copy the contents of the source object to the target object so it's functionally identical, but 100% independent
*/

class PiNerd{
  public:   
    PiNerd(int n){...}
    ~PiNerd(){delete[]m_pi;}
    PiNerd(const PiNerd &src){
      m_pi = new int[src.m_n]; // allocates its own array after determining how much memory it needs
      m_n = src.m_n;
      for(int i = 0; i < m_n; i++){
        m_pi[j] = src.m_pi[j]; // own dynamic array allocated and hold identical values but at different locations
    } // this way, copies are destructed without messing up the original memory/members
    void...
  private:
    int *m_pi, m_n;
};
/*
Copy Construction Summary
  with copy construction, we are creating a clone of an existing variable using a constructor 
  in practice, it entails creating a new set of data structures and copying the data from old into new
  what's important is identical behavior but independent data structures and memory allocation
    not as simple as allocating a new dynamic array and copying values over
*/





