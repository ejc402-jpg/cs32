// Generic Programming (Custom Comparison Operator, Templates, STL, STL Itertors and Algorithms)

/*
Generic Programming
  when you write a function or class in a manner so that it can process many different types of data
  for example, a generic sorting function can sort an array holding ANY type of value (i.e. numerical, lexicographically, etc.)
  for example, a generic linked list class that can hold ANY type of variable
  can quickly reuse the generic function/class to solve many different problems
*/
int main(){
  list<int> list_of_integers;
  list<string> list_of_strings;
  list_of_integers.push_back(42);
  list_of_strings.push_back("ITS LIT!");
}
/*
  Part 1: Allowing Generic Comparisons
    consider the following main function that compares various objects 
      notice that the way we compare two dogs (by weight) is different then the way we compare two circles (by radius)
      imagine a way to compare objects like circles and dogs just like we compare two integers
        we can!
          all comparison operators accept const reference parameters
          must return boolean value
*/
int main()
{
  int i1 = 3, i2 = 5;
  if (i1 > i2)
    cout << “i1 is bigger”;
  Circ a(5), b(6);
  if (a.radius() > b.radius())
    cout << “a was bigger”;
  Dog fido(10), spot(20);
  if (fido.weight() > spot.weight())
    cout << “fido is bigger”;
}
class Dog{
public: 
  int getWeight() const{return m_weight;} // const functions allows it to work with comparing const objects
  bool operator<(const Dog& other) const{ // defined inside the class, can access private members
    if (m_weight < other.m_weight){ // comparison operators defined in the class have one "other" parameter like a copy constructor
      return true;
    }
    return false;
  }
private:
  int m_weight;
};
bool operator>=(const Dog &a, const Dog &b){ // like an assignment operator!
  if(a.getWeight() >= b.getWeight()) return true;
  return false;
}

/*
    Custom Comparison Operators
      since a and b are const objects, getWeight() better take const objects as well
        otherwise you'll see a cryptic error
      question: if we define an operator like == does C++ automatically define related operators like != for us?
        no! must explicitly define the operators you want to use
  Part 2: Writing Generic Functions
    here are several different swap functions for different types of values
    wouldn't it be great to write a single swap that works for any values?
      to turn any function into a generic function...
        1. add the following line above your function: template <typename poop> 
        2. then use xxx as your data type throughout the function --> swap(xxx a, xxx b)
          now you can use your generic function with any data type?
*/
Circle a(5), b(6);
Dog c(100), d(750);

SwapCircle(a,b);
SwapDog(c,d);

// the new way

... (we’ll learn how in a sec)

int main()
{
  Circ a(5), b(6);
  Dog c(10), d(75);
  int e = 5, f = 10;
 
  OurGenericSwap(a,b);
  OurGenericSwap(c,d);
 
  OurGenericSwap(e,f);
}	

template <typename T> // template <class T> equivalent syntax here
void swap(T &a, T &b){
  int temp; 
  temp = a; 
  a = b; 
  b = temp; 
}
int main(){
  Dog d1(10), d2(20);
  Circle c1(1), c2(5);

  swap(d1,d2);
  swap(c1,c2);
  ...
}

/*
  Function Template Details
    always place the templated functions in a header file, including the ENTIRE template function implementation in the header file, not just prototype
    we can think of templates as a time-saving/bug-reducing/source-simplifying technique rather than one that reduces the size of your compiled program
*/

// swap.h
template <typename Data> 
void swap(Data &x, Data &y){
  Data temp; 
  temp = x;
  x = y;
  y = temp; 
}
// program.cpp 
#include 'swap.h'

int main(){ // each time you use a template function with a different type of variable, the compiler generates a new version of the function just for that type!
  int a = 5, b = 6;
  swap(a,b);
  Dog a(13), b(41);
  swap(a,b);
  string x("a"), y("z");
  swap(x,y); // works for all cases!
}

  // you must use the template data type (i.e. Data) to define the type of at least one formal parameter, or you'll get an ERROR
  
  GOOD:
   
  template <typename Data>
  void swap(Data &x, Data &y) // Data used to specify the types of x and y
  {
      Data temp;
      temp = x;
      x = y;
      y = temp;
  }
  
  BAD:
   
  template <typename Data>
  Data getRandomItem(int x) // Data was not used to specify the type of any parameters
  {
     Data temp[10];
     return temp[x];
  }

// ex. will this work? 
  // no! if a function has two or more templated parameters with the same type (i.e. Data) you must pass in the exact same type of variable/value for both!

max.h
 
template <typename Data>
Data max(Data x, Data y)
{
  if (x > y)
    return x;
  else
    return y;
}

#include “max.h”

int main() {
  int a = 5;
  float b = 10; 
  cout << max(a,b) << 
          " is bigger\n";
}

// note: you can override a template function with a specialize (non-templated) version if you'd like

template <typename Data>
Data bigger(Data &x, Data &y)
{
   if (x > y)
      return x;
   else
      return y;
}

Dog bigger(Dog &x, Dog &y)
{
   if (x.bark() > y.bark())
      return x;
   else if (x.bark() < y.bark())
      return y;
   // barks are equal, check bite
   if (x.bite() > y.bite())
      return x;
   else 
      return y;
}

int main()
{
    Circle a, b, c;
    c = bigger(a,b); // calls templated version

    Dog fido, rex, winner;
    winner = bigger(fido,rex); // calls specialized version
}

// ex. Hairy Template example
  // if your templated function uses an operator on templated variable...
  // then C++ requires that all values passed in support that operator
  // so if you use such a function with a user-defined class, you must define the operator for that class!

bool operator>(const Dog &a,const Dog &b)
{
  if (a.weight() > b.weight())
    return true;
  else return false;
}
bool operator>(const Circ &a,const Circ &b)
{
  if (a.radius() > b.radius())
    return true;
  else return false;
}
template <typename Data>
void winner(Data &x, Data &y)
{
   if (x > y)
      cout << “first one wins!\n”;
   else
      cout << “second one wins!\n”;
}
int main(){
  int i1 = 3, i2 = 4;
  winner(i1, i2); // valid because C++ has built-in comparison operators defined for integers
  Dog a(5), b(6);
  winner(a, b); // now works 
  Circ c(3), d(4); 
  winner(c, d); // now works
}

/*
  Multi-Type Templates
    and yes, you can do this too...
*/
template <typename T, typename U>
void passTwoTypes(const T& first, const U& second) {
  std::cout << " First: "  << first  << 
               " Second: " << second << std::endl;
}
int main() {
  passTwoTypes(32, "CS32 rules!");
  passTwoTypes("CS131 is cool too!", 131.0);
}

/*
  Part 3: Writing Generic Classes
    we can use template to make entire classes generic as well
*/

template <typename Item>
class HoldOneValue // this class can hold any type of data you like - just like the C++ stack or queue classes!
{
public:
  void setVal(Item a)
  { 
    m_a = a;
  }
  void printTenTimes()
  {
    for (int i=0;i<10;i++) // we dont update every int to Item, cuz this is counter variable
      cout << m_a;
  }
private:
    Item m_a;
};

int main()
{
    HoldOneValue<int> v1;
    v1.setVal(10);
    v1.printTenTimes();
 
    HoldOneValue<string> v2;
    v2.setVal("ouch");
    v2.printTenTimes();
} 

// if you have externally-defined member functions, things get ugly
  // you add the prefix: template <typename xxx> before the class definition itself AND before each function definition that is outside the class
  // then update the types of use the templated type...
  // finally, place the postfix: <xxx> between the class name and the :: in all function defs

template <typename Item>
class Foo
{
public:
    void setVal(Item a);
    void printVal();
private:
    Item m_a;
};
template <typename Item> 
void Foo<Item>::setVal(Item a)
{
    m_a = a;
}
template <typename Item>
void Foo<Item>::printVal()
{
    cout << m_a << "\n";
}

/*
  Template Classes
    very useful when building container objects like linked lists
*/

// Before

class LinkedListofStrings
{
public:
    LinkedListofStrings();		
  bool insert(string &value);
  bool delete(string &value);
  bool retrieve(int i, string &value);
  int size();
   ~LinkedListofStrings();		
private:
  …
};

class LinkedListofDogs
{
public:
    LinkedListofDogs();		
  bool insert(Dog &value);
  bool delete(Dog &value);
  bool retrieve(int i, Dog &value);
  int size();
   ~LinkedListofDogs();		
private:
  …
};

// after

template <class HoldMe>
class LinkedList
{
public:
   LinkedList();		
  bool insert(HoldMe &value);
  bool delete(HoldMe &value);
  bool retrieve(int i, HoldMe &value);
  int size();
   ~LinkedList();		
private:
  …
};

#include “linkedlist.h”
int main()
{
  Dog fido(10); 

  LinkedList<Dog> dogLst;
  dogLst.insert(fido);
 
  LinkedList<string> names;
  names.insert(“Seymore”);
  names.insert(“Butts”);
}

/*
Programming Dingleberries
  if your recursive function returns a value, then always make sure you somehow use the return value every time you call your program recursively
*/

bool foundRoute(int maze[10][10], int cx, int cy) {
   ...
   if (foundRoute(maze,cx+1,cy)) { /* do something */ } 
   ...
   if (foundRoute(maze,cx,cy-1)) { /* do something */ } 
}

/*
  Part 4: The Standard Template Library (aka "STL")
    the STL is a collection of pre-written, tested classes provided by the authors of C++ 
    all built using templates, able to be used with many different data types
    save a lot of time in programming
    we already saw stack and queue (containers because they hold items)
    1. Vector (fast access to any element but adding new items is often slower)
      #include <vector> 
      std::vector<string> holder (empty vector initially)
      std::vector<int> geeks(950) (950 items vector)
      vectors grow/shrink automatically when you add/remove items
      push_back() to append to end of vector 
      can add items, change, or remove items with pop_back() 
      front() and back() to retrieve ends of vector (if they exist) 
      .size() function works for vectors but not arrays
      .empty() to check if vector is empty
      question: vectors are implementally internally and dynamically allocated arrays. what happens when the array is full and try to add a new item?
        the vector object will allocate a new array that's 2x the original size then copies over all items and deletes the old array
    2. List (fast insertion/deleting but slow access to middle elements
      doubly linked list
      #include <list> 
      push_back, pop_back, front, back, size, and empty methods like in vector
      also has push_front and pop_front
      BUT, you cannot access list elements using brackets []
  Iterating Through The Items
    only the vector allows brackets to access elements (not list and others)
    to enumerate the contents of a container, use an iterator variable
      pointer variable but used with STL containers
      start by pointing an iterator to some item in your container, like the first item
      like a pointer, increment/decrement to navigate the container's items
      read/write each value it points
    vector<string>::iterator it2;
    list<float>::iterator it3; 
      to define, write the container type and two colons, followed by word "iterator" and a variable name
    to use the iterator, point it at an item in the container (i.e first item using begin() method)
    once iterator points to a value, use * operator to access the value
    * operator with an iterator is called operator overloading
    in summary....
      an iterator is an object that knows:
      1. what element it points to
      2. how to find the previous and next items in the container 
*/

int main()
{
  vector<int> myVec;
  myVec.push_back(1234);
  myVec.push_back(5);
  myVec.push_back(7);
  vector<int>::iterator it; 
  it = myVec.begin(); // When you call the begin() method it returns an iterator to the very first item in the container.
  it++; // can also move backward, just make sure the iterator doesnt go out of range
  std::cout << *it; // second item
}

/*
  In addition to the begin() method, there is also an end() method
    get this, the end() returns an iterator the points just past the last item in the vector
      because if end() returned an iterator pointing to the last item, loops would miss the last item
*/

int main(){
  vector<int> myVec; 
  myVec.push_back(1234);
  myVec.push_back(5);
  myVec.push_back(7);
  vector<int>::iterator it;
  it = myVec.begin();
  while(it != myVec.end()){ // myVec.end() is address right after the last item in the container
    std::cout << *it; 
    it++;
  }
}

it = myVec.end();
it--; // gives you the last item

/*
STL and Classes/Structs
  can also create STL containers of classes or structs
*/

class Nerd
{
public:
    void beNerdy( );
    …
};
int main()
{
  list<Nerd> 	nerds;
  Nerd d;
  nerds.push_back(d);
  list<Nerd>::iterator it; 
  it = nerds.begin();
  (*it).beNerdy(); // or the one below
  it->beNerdy(); // or the one above
}

// when passing containers to functions, pass containers by reference or const reference to save time and memory (which one depends on if the container will be modified)
// also try to initialize the vector with the expected number of items and use brackets to update them
  // push_back at initialization will result in multiple reallocations/array copies

// bad example

void practice(std::vector<double> v) 
{
   for (int i=0; i < v.size(); ++i)
     std::cout << v[i] << std::endl;
}
int main() 
{
  std::vector<double> squares;

  for (double i=0;i < 1000000; ++i)
     squares.push_back(i*i);
  practice(squares);
}

// good example

void practice(const std::vector<double>& v) 
{
   for (int i=0; i < v.size(); ++i)
     std::cout << v[i] << std::endl;
}
int main() 
{
  std::vector<double> squares(1000000);

  for (double i=0;i < 1000000; ++i)
     squares[i] = i*i;

  practice(squares);
}

/*
Const Iterators and Headaches
  when you pass a container as a const reference parameter in a function, you can't just use a regular iterator!
  you need const_iterator
*/

void tickleNerds(  const list<Nerd> &nerds)
{
  list<string>::iterator it;   // won’t work
  for (it=nerds.begin(); it != nerds.end(); it++)
    cout << *it << “ says teehee!\n”;
  list<string>::const_iterator it;   // works!!!
  for (it=nerds.begin(); it != nerds.end(); it++)
    cout << *it << “ says teehee!\n”;
}

int main()
{
  list<string> 	nerds;
  
  nerds.push_back(“Carey”);
  nerds.push_back(“David”);
  …

  tickleNerds(nerds);
}

// Iterator in Code

class MyIterator   
{
 public:
  float val() { return cur->value; }
  void down() { cur = cur->next; }
  void up()   { cur = cur->prev; }
 
  Node *cur;    
};

class LinkedList
{
public:
  …

  MyIterator begin()
  {
     MyIterator temp;
     temp.cur = m_head;
     return temp;
  }

private:
   Node *m_head;
};

int main()
{
  LinkedList GPAs; // list of GPAs

  ...

  MyIterator itr = GPAs.begin();
  cout << itr.val();    // like *it 
  itr.down();           // like it++;
  cout << itr.val();
}

// C++ Syntactic Sugar: Looping Over Containers
  // iterating over a vector/list is pretty ugly

// Old way: Explicit use of iterators for iteration 
void print_items(list<int>& items) 
{
  for (list<int>::iterator i = items.begin(); i != items.end(); i++) 
  {
    int val = *i;
    cout << val << endl; 
  }
}
// New way: Implicit use of iterators for iteration  
void print_items(list<int>& items) 
{
  for (auto val : items)
    cout << val << endl; 
  for (auto& val : items)
    cout << val << endl; // reference, no copying
}

/*
Other STL containers
  so far we've learned how to use the STL to create linked lists and dynamic arrays (vectors) 
  what else can it do for us/
  3. Map 
    allows us to associate keys to values
*/

#include <map> 
#include <string> 

int main(){
  map<string, int> name2Fone; // map<first, second> 
  name2Fone["carey"] = 394827; // first is "carey", second is 394827
  name2Fone[2938] = ["bob"]; // ERROR!
  std::cout << name2Fone["carey"];
  map<string, int> name2Age;
  map<string, int>::iterator it; 
  it = name2Age.find("Dan"); // if the find method can't locate your item, it returns an iterator to the end of the map!
  // must check for and handle this
  if(it == name2Age.end()){
    std::cout << "Not found!" << std::endl; 
    return;
  }
  cout << it->first; 
  cout << it->second;
  cout << (*it).second;
  cout << (*it).first;
  // if we want to iterate through a map
  map<string, int>::iterator it;
  for(it = name2Age.begin(); it != name2Age.end(); it++){
    std::cout << it->first;
    std::cout << it->second;
  // note: max class always orders its items in ascending lexicographical order, based on the first (key) field
      // automatically ordered 
  }
}

/*
      you can even associate more complex data types like structs and classes
*/

struct stud	// student class
{
  string name;
  int idNum;
};

bool operator<(const stud &a, const stud &b){ // define own operator for the left-hand class/struct
  return(a.idNum < b.idNum); // or (a.name < b.name);
  // you only need to define the < operator function if you're mapping from your struct/class (not to it)
}

int main()
{
  map<stud,float>  stud2GPA; // associate a given student to their GPA

  stud d;
  d.name = “David Smallberg”;
  d.idNum = 916451243;
  
  stud2GPA[d] = 1.3;
}

/*
  4. Set
    container that kkeeps track of unique items
    can be unordered, no duplicates, but usually alphabetically ordered
    insert, size, erase
    iterating through the set is the same syntax as map
      set<int>::iterator it; 
      for(it = myMap.begin(); it != myMap.end(); it++) ....
    can have sets of other data types as well, but need to define the operator< for your classes
*/

struct Course
{
   string name;
   int units;
};

bool operator<(const Course &a, const Course &b) return (a.name < b.name);

int main()
{
  set<Course> myClasses;

  Course lec1;
  lec1.name = “CS32”;
  lec1.units = 16;
  
  myClasses.insert(lec1);
}

// Deleting an Item from an STL container
  // most STL containers use erase() method
  // first search for the item you want to delete
  // if item found (i.e. it != myContainer.end()) remove the item pointed to by the iterator

int main()
{
   set<string>  geeks;
 
   geeks.insert("carey");
   geeks.insert("shana");
   geeks.insert("alex");
  set<string>::iteratorit;
  it = geeks.find("Carey");
  if(it != geeks.end()){
    std::coutt << "bye bye" << std::endl;
    geeks.erase(it); // killshot
  }
} 

/*
Iterator Gotchas
  what happens to an existing iterator if you add a new item to a vector?
    the iterator is considered invalid and must not be used 
    why? adding an item might cause the vector to move all its items to a new array!
    similarly, erasing an item from a vector, all iterators pointing after that item must be considered invalid
  fortunately, the same problem doesn't occur with sets, lists, or maps
    EXCEPT if you delete the item the iterator is currently pointing to and then try to deference
    ex. 
      it = s.find("Carey")
      s.erase(it);
      std::cout << *it;
Deleting Items in a Loop
*/
bool is_awesome(string s) { ... }

int main() {
   list<string> things;
 
   things.insert("chocolate");
   things.insert("cs32");
   things.insert("vomit");
   things.insert("dogs");
 
   list<string>::iterator it;
   it = things.begin();
   while (it != things.end()) {
     if (!is_awesome(*it))
       it = things.erase(it); // when you erase(), it returns an iterator to the item following the erased item
     else
       it++;
   }
}

/*
  Part 5: STL Algorithms
    STL also provides some additional functions that work with many different types fo data
      find(), set_intersection, sort()
    the sort function
      #include <algorithm> 
      fast sorting function that works on arrays and vectors (ascending)
      sort(n.begin(), n.end());
      sort(&arr[0], &arr[4]);
*/

// ex. sort Dogs based on how nasty their bite is first, then bark second

#include <algorithm>

class Dog
{
public:
  int getBark() { return m_barkVolume; }
  int getBite() { return m_bitePain; }
};

// returns true if dog A should go before dog B
bool  customCompare(const Dog &a, const Dog &b)
{
   if (a.getBite() > b. getBite())
      return true; // Dog a has a nastier bite!
   if (a.getBite() < b.getBite())
      return false; // Dog b has a nastier bite!

   return a.getBark() > b.getBark();
}

int main()
{
   Dog arr[4] = {...};
  sort ( arr, arr+4, &customCompare); // pass this function's address as a parameter to sort()
} 

/*
  Part 6: Compound STL Data Structures
    let's say you want to maintain a list of courses for each UCLA student
    how could we do it with the STL? 
      create a map between student's name and list of courses
    in many cases, you'll want to combine multiple STL containers to represent more complex associations like these
*/
#include <map>
#include <list>
class Course 
{
public:
     …
};
int main()
{
map<string, list<Course>> crsmap;   
Course  c1(“cs”,”32”), 
            c2(“math”,”3b”),
            c3(“english”,”1”);

crsmap[“carey”].push_back(c1);
crsmap[“carey”].push_back(c2);
crsmap[“david”].push_back(c1);
crsmap[“david”].push_back(c3);
}

// Challenges 
// 1. design a compound STL data structure that allows us to associate people (Person objects) and each person's unique group of friends (also Person objects) 
map<Person, set<Person>>  facebook; // remember you need define operator< if you have a set containing your own class, and if mapping from own class
bool operator<(const Person &a, const Person &b) return (a.getName() < b.getName());
// 2. design a compound STL data structure to associate people's names with all the course names they've taken, and further associate each course name with a grade
map<string, map<string, Grade>> x; 
