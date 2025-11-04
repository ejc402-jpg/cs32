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
int main( )
{
  Dog fido(10); 

  LinkedList<Dog> dogLst;
  dogLst.insert(fido);
 
  LinkedList<string> names;
  names.insert(“Seymore”);
  names.insert(“Butts”);
}






 


