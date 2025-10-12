// Notes go when slides are posted

Use initializer lists for all objects, consts, and references.
Use constructor body mainly for logic that can’t be done in the initializer list.
Always pay attention to declaration order for dependencies.

// Worksheet 

#include <iostream>
using namespace std;
class A {
  public:
  A() { cout << "DC" << endl; }
  A(const A& other) { cout << "CC" << endl; }
  A& operator=(const A& other) {
    cout << "AO" << endl;
    return *this;
  }
  ~A() { cout << "Destructor!" << endl; }
};
int main() {
  A arr[3];
  arr[0] = arr[1];
  A x = arr[0];
  x = arr[1];
  A y(arr[2]);
  cout << "DONE" << endl;
}

// DC
// DC
// DC
// AO
// CC
// AO
// CC
// DONE
// Destructor!
// Destructor!
// Destructor!
// Destructor!
// Destructor!

#include <iostream>
#include <string>
using namespace std;
class Account {
  public:
    Account(int x) { cash = x; }
    int cash;
};
class Billionaire {
  public:
    Billionaire(string n) {
      offshore = Account(1000000000);
      name = n;
    }
    Account account;
    Account* offshore;
    string name;
};
int main() {
  Billionaire jim = Billionaire("Jimmy");
  cout << jim.name << " has " << jim.account.cash + jim.offshore->cash << endl;
}

// Output: Jimmy has 1000010000

/* Find the 4 errors in the following class definition so the main function runs correctly
1. offshore is a pointer, so offshore = new Account(1000000000);
2. account is not initialized in Billionare class declaration (non-static members that are objects must be initialized in the initializer list if they don't have a default constructor)
  Billionare(string n) : account (10000) {
    offshore = new Account(1000000000);
    name = n;
  } 
3. no destructor for offshore (memory leak!)
  ~Billionare(){
    delete offshore;
  }
4. inefficient copy constructor call
  just use the constructor when creating the jim Billionare object
    Billionaire jim("Jimmy");
*/

#include <iostream>
using namespace std;
class B {
  int m_val;
  public:
    B(int x) : m_val(x) { cout << "Wow such " << x << endl; }
    B(const B& other) {
      cout << "There's another me???" << endl;
      m_val = other.m_val;
    }
    ~B() { cout << "Twas a good life" << endl; }
};
class A {
  int m_count;
  B* m_b;
  public:
    A() : m_count(9.5) {
      cout << "Construct me with " << m_count << endl;
      m_b = new B(m_count + 10);
    }
    A(const A& other) {
      cout << "Copy me" << endl;
      m_count = other.m_count;
      m_b = (other.m_b != nullptr) ? new B(*other.m_b) : nullptr;
    }
    ~A() {
      cout << "Goodbye cruel world" << endl;
      if (m_b) delete m_b;
    }
    int getCount() { return m_count; }
};
int main() {
  A a1, a2;
  A a3 = a2;
  B b1(a3.getCount());
  cout << "Where are we?" << endl;
}

// Construct me with 9
// Wow such 19
// Construct me with 9
// Wow such 19
// Copy me
// There's another me???
// Construct me with 19.5
// Wow such 9
// Where are we? 
// Twas a good life 
// Good bye cruel world
// Twas a good life
// Good bye cruel world
// Twas a good life
// Good bye cruel world
// Twas a good life

#include <iostream>
using namespace std;
class A {
  public:
    A(int sz) : n(sz), arr(new int[sz]), b(nullptr), str(""){}
    A(const A& other) {
      b = (other.b == nullptr) ? nullptr : new B(*other.b);
      n = other.n;
      arr = new int[n];
      str = other.str;
      for(int i = 0; i < n; i++){
        arr[i] = other.arr[i];
      }
    }
    A& operator=(const A& other) {
      if(this == &other) return *this;
      delete[] arr;
      delete b;
      n = other.n;
      str = other.str;
      arr = new int[n];
      for(int i = 0; i < n; i++){
        arr[i] = other.arr[i];
      }
      b = new B(*other.b);
      return *this;
    }
    //...other functions
    ~A() {
      delete[] arr; 
      delete b;
    }
  private:
    B* b; // one dynamically allocated B object; assume B has a
    // default constructor, a copy constructor, and an
    // assignment operator
    int* arr; // dynamically allocated array
    int n; // size of arr (determined by a constructor)
    string str;
};

#include <iostream> // question 5
#include <string>
using namespace std;
class Account {
  public:
    Account(int x) { cash = x; }
    int cash;
};
class Billionaire {
  public:
    Billionaire(string n) : account(0) {
      offshore = new Account(1000000000);
      name = n;
    }
    Billionaire(const Billionaire& other) : account(0) {
      offshore = new Account(0); // would be new Account(other.offshore->cash);
      name = other.name;
    }
    ~Billionaire(){
      delete offshore;
    }
    Account account;
    Account* offshore;
    string name;
};
int main() {
  Billionaire jim = Billionaire("Jimmy");
  Billionaire jimClone = jim;
  cout << jimClone.name << " has " << jimClone.account.cash + jimClone.offshore->cash << endl;
  cout << jim.name << " has " << jim.account.cash + jim.offshore->cash << endl;
}
