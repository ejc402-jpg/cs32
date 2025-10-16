// Inheritance 
/*
Inheritance
  a way to form new classes using classes that have already been defined
  the new class specifieds which class it's based on and "inherits" all of the base class functions/data
    can also add its own new functions/data to allow new class to work like a combination of both original classes
  saves a lot of time coding and reduces bug-prone code duplication
  ex. defining a regular human vs. a comedian
    both exhibit similar biological functions, but say a comedian possesses additional abilities like joke-telling (unique functionality to normal humans) 
    in this case, we can define a human as a base class and make a derived class for the comedian
*/
class Person{
  public: 
    // public member functions here
  private: 
    // private members here
};
class Comedian is based on Person{
  public:
    // all public member functions from Person here... 
    void make_joke(std::string word);
    void tell_you_a_joke(std::string joke);
  private:  
    // all private members of Person here...
    std::string joke;
};
/*
  can Person use Comedian methods like tell_joke()? NO! base class knows nothing about extensions from its derived classes
  when should we use inheritance?
    given two classes A and B, if we say "A is a type of B" we should consider using inheritance
      i.e. Circle is of Shape, Comedian is of Person
      i.e. in contrast, a Person has a Name but you wouldn't say that Person is a type of Name or Name is a type of Person
        in this case, "A has a B" means adding member variables, not deriving classes
  Class Hierarchies
    Ape and Human are Primates, Primates and Marsupials are Mammals, Mammals, Reptiles, and Fish are Animals (Animals is the top of the hierarchy)
    base class: a class that serves as the basis for other classes (i.e. Primate, Mammal, Animal) 
    derived class: a class that is dervied from a base class ((i.e. Ape, Human, Fish, Reptile, Marsupial)
      (like graph theory, tree nodes that do or do not have children)
  class inheritance is also stackable (class Person --> class Student is based on Person --> class CompSciStudent is based on Student)
  Proper Syntax
*/
class BaseClass {
    // Members of the base class
};

class DerivedClass : accessSpecifier BaseClass {
    // Members of the derived class
};
/*
  three uses of inheritance
    1. reuse: when you write code once in a base class and reuse in derived classes to reduce duplication (read access modifier section) 
    2. extension: add new behaviors or data to a derived class, not present in the base class
    3. specialization: redefine an existing behavior (from the base class) with a new behavior in the derived class
    access modifiers
      1. public: every public method/member in the base class is automatically reused/exposed in the derived class and remains public in the derived class (as if it were defined there)
      2. protected: protected members of the base class remain protected in the derived class
      3. private: private members of the base class are not directly accessible in the derived class 
        while public members from the base class are reusable, private members are hidden from the derived class(es)
          ex. https://discord.com/channels/633096463139864606/1010791176250609757/1428165866901606572
        if you want to expose a private base class member to its derived class(es) but still hide it from unrelated classes/functions, use the protected keyword
          only use protected with methods, not member variables (pretty much always private)
            ex. https://discord.com/channels/633096463139864606/1010791176250609757/1428166369823953019
*/

// member access example

class Base {
public:
    int a;
protected:
    int b;
private:
    int c;
};

class Derived : public Base {
    void f() {
        a = 1; // OK (public)
        b = 2; // OK (protected)
        // c = 3; // ERROR (private)
    }
};

// inheritance example

class Base {
public:
    int pub;
protected:
    int prot;
private:
    int priv;
};

// Public inheritance
class PubDerived : public Base {
    void f() {
        pub = 1;   // still public
        prot = 2;  // still protected
        // priv = 3; // inaccessible
    }
};

// Protected inheritance
class ProtDerived : protected Base {
    void f() {
        pub = 1;   // now protected
        prot = 2;  // still protected
    }
};

// Private inheritance
class PrivDerived : private Base {
    void f() {
        pub = 1;   // now private
        prot = 2;  // now private
    }
};

/*
  Inheritance: Specialization/Overriding
    in addition to adding entirely new functions and variables to a derived class...
    you can also override or specializing existing functions
    use the virtual keyword in front of any function that you know will change 
      not using virtual for any method in the base class means it won't change AT ALL in the derived class(es)
      you just need to edit not create this way
    note: you can only use virtual keyword within your class definitions
      so virtual won't work if you define your member functions outside your class
*/
class Student {
public:
  virtual void talk() { 
    cout << “Go bruins!”; 
  }
  double get_gpa() { return gpa_; };
private:
  double gpa_;
}; 
// don't use virtual out here
class NerdyStudent: public Student {
public:
   virtual void talk() { 
     cout << “I love linked lists!”; 
   }
   ...
}; 
// don't use virtual out here

/*
    what if we actually want to call the base class's version of a virtual method that's been redefined in the derived class?
*/
class Student{
  public: 
    virtual void cheer(){
      std::cout << "Go Bruins!";
    }
};
class NerdyStudent : public Student{
  public:
    virtual void cheer(){
      std::cout << "Go Algebra!";
    }
    void attend_ucla_game(){
      Student::cheer(); // overriding the overriden method
    }
};
/*
Inheritance and Construction: how are super-classes and sub-classes constructed? 
  recall from class construction lecture:
    Phase 0: we'll learn this now (was previously we'll learn about this later)
    Phase 1: (initializer list first, actually) C++ constructs all non-primitive member variables (i.e. strings) in the order they appear in the class
    Phase 2: C++ runs the body of the constructor
  the base class needs to be constructed before the derived class constructor runs
    or else calls to the base class won't work
*/
class Gear { 
  public: 
    Gear() 
     { cout << "Grind\n"; }
  };
class GPT { 
  public: 
    GPT() 
     { cout << "Chat\n"; }
  };
class Machine { 
  public: 
    Machine() {
      cout << "Beep\n";
    }
  private:
    Gear gear_;
};
class Robot: public Machine { // base class is constructed first then the derived class
  public: 
    Robot() {
      cout << "Whir\n"; 
    }
  private:
    GPT netwk_;
};
int main() {
  Robot robbie;
}

// grind beep chat whir 

/*
Inheritance and Initializer Lists
*/
class Animal   
{
  public:
   Animal(int lbs) // in this example, the constructor required a parameter!
    { lbs_ = lbs; }
  
   void what_do_i_weigh() 
    { cout << lbs_ << " lbs!\n"; }
  
  private:
    int lbs_;
};
class Duck : public Animal // however, our Duck has no way of passing a parameter that the Animal class needs to initialize weight
{
  public:
    Duck(int lbs, int feathers) : Animal(lbs) // if a superclass requires parameters for construction then you must add it in the initializer list to the subclass constructor
    {feathers_ = feathers} // first item in the initializer list must be the name of the base class along with parameters in parentheses
                      // and if derived class has member objects whose constructors require parameters, they must be initialized this way too in the initializer list after the base class
    void who_am_i() 
     {  cout << "A duck!";  }
  
  private:
    int feathers_;
};
int main()
{
  Animal a(10); // 10 lbs
  a.what_do_i_weigh();
  Duck daffy; // old declaration when Duck() : Animal (2) was the original construction
  Duck daffy(10); // old declaration when Duck(int lbs) : Animal (lbs) was the previous construction
  Duck daffy(10, 25); // great!
}
/*
Inheritance and Destruction
  recall from class destruction
    Phase 0: C++ runs the object's destructor body first 
    Phase 1: C++ destructs all non-primitive member variables in the reverse order they appear in the class
    Phase 2: we'll learn this now (previously skipped) 
*/
// back to machine and robbie example...
class Machine { 
  public: 
    ~Machine() {
      cout << "Groan!\n";
    }
    void drain_oil()    
      { oil_= 0; }
  private:
    int oil_;
};
class Robot: public Machine { 
  public: 
    ~Robot() {
      cout << "Fizzle\n";
      drain_oil(); // since the base class has not been destructed yet, this is safe to use by the derived class
      cout << "Shudder.\n";
    }
    ...
};
int main() {
  Robot robbie;
} // Robbie is destructed!

// fizzle shudder groan
// so, base class is destructed after all of its derived classes are!

// another example

class Gear { 
public: 
  ~Gear() { cout << "Clunk\n"; }
  ...
};
class GPT { 
public: 
~GPT() { cout << "Bye\n"; }
  ...
};
class Machine { 
public: 
  ~Machine() {
    cout << "Halt\n";
  }

private:
  Gear gear_;
};
class Robot: public Machine { 
public: 
  ~Robot() {
    cout << "Fizzle\n";
  }

private:
  GPT netwk_;
};
int main() {
  Robot robbie;
} // Robbie is destructed!

// fizzle bye halt clunk

/*
Inheritance and Assignment Ops
*/
class Robot 
{ 
public: 
  void setX(int newX);
  int getX();
  void setY(int newY);
  int getY(); 
private: 
  int x_, y_;
};
class ShieldedRobot: public Robot 
{ 
public: 
  int getShield ();
  void setShield(int s);
private: 
  int shield_;
};
int main()
{
  ShieldedRobot larry, curly;

  larry.setShield(5);
  larry.setX(12);
  larry.setY(15);

  curly.setShield(75);
  curly.setX(7);
  curly.setY(9); 
  …
  larry = curly;  // what happens?
}

/*
  in that example, larry = curly works fine. 
    C++ first copies the base data from curly to larry and then copies the derived data from curly to larry (using copy constructor if present)
  however, if your base and derived classes have dynamically allocated member variables (or would otherwise need a special copy constructor/assignment operator...
    you must define assignment ops and copy constructor for the base class and also special versions of these functions for the derived class
Inheritance Review
  reuse (write code once, reuse in derived classes), extend (add new behaviors), specialize (override existing behaviors)
*/








   









