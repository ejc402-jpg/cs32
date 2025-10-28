// Polymorphism (Introduction, Virtual Functions, Virtual Destructors, Pure Virtual Functions, Abstract Base Classes)

class Person {
public:
  string getName();
  string talk();
};

class Student : public Person {
  string talk(){return "Go Bruins!";}
};

class Prof : public Person {
  string talk(){return "Pop quiz!";}
};

void AskPersonToTalk(Person &p){ // looks like a person but behaves as a class? 
  cout << p.getName() << " says " << p.talk();
}

int main(){
  Student stud("Sam");
  AskPersonToTalk(stud); // "Sam says Go Bruins!"
  Professor prof("Juan");
  AskPersonToTalk(prof); // "Juan says Pop Quiz!"
}

/*
ex. consider the function that accepts a Person as an argument
  could we also pass a Student as a parameter to it? yes!
  once I define a function that accepts a reference or pointer to a Person...
  not only can I pass Person variables to that function...
    but I can also pass any variable that was derived from a Person!
  why? every Student is a Person, so every Student can do what a Person can do and then some
    every Student object, since it's derived from a Person class, is technically a Person object plus additional stuff specific to the Student class
Polymorphism: any time we use a base pointer or a base reference to access a derived object
  you MUST use a pointer or reference for polymorphism to work!
  otherwise something called "chopping" happens
    C++ will basically chop off all the data/methods of the derived (Student) class and only send the base (Person)
*/

void SayHi(Person *p)
{
  cout << "Hello " << p->getName();
}

void SayHi(Person& p)
{
  cout << "Hello " << p.getName();
}

void SayHi(Person p) // SayHi function is no longer dealing with the original Student variable, but a CHOPPED temporary variable that has no Student attributes!

/*
  ex. two classes derived from Shape: Square and Circle
    imagine we're a company that sells shapes where its $3.25 per square foot
*/

class Shape{
  public:
    virtual double getArea(){return 0;}
    ....
  private:
    ....
};

class Square : public Shape {
public:
  Square(int side){m_side = side;}
  virtual double getArea(){return m_side * m_side;}
private:
  int my_side
};

class Circle : public Shape {
public:
  Circle(int rad){m_rad = rad;}
  virtual double getArea(){return 3.14*m_rad*m_rad;}
private:
  int m_rad;
};

// void PrintPriceSq(Square &x)
// {
//   cout << “Cost is: $“; 
//   cout << x.getArea() * 3.25;
// }

// void PrintPriceCir(Circle &x)
// {
//   cout << “Cost is: $“; 
//   cout << x.getArea() * 3.25;
// }

void PrintPrice(Shape &x) // we don't need a price calculator for every shape! this works for any shape
{ // don't forget the pointer/reference
  cout << “Cost is: $“; 
  cout << x.getArea() * 3.25; // when you call a virtual function, C++ figures out the correct version (based on Shape) to use and calls it automatically!
}

int main()
{
  Square s(5);
  Circle c(10);

  PrintPriceSq(s);
  PrintPriceCir(c);
}

/*
Inheritance vs. Polymorphism
  Inheritance: derive one or more classes from a common base class
    each derived class by definition inherits a common set of functions from our base class
    the derived classes may re-define any virtual functions originally defined in the base class (specializing that function for the specific class)
  Polymorphism: may use a base class pointer/reference to access any variable that is of a type derived from our base calss
    the same function call automatically causes different actions to occur, depending on what type of variable is currrently being referred/pointed to
    must use pointer/referenc to prevent being "chopped"!
    it's possible to design and implement systems that are more easily extensible (i.e. adding more shapes)
      every time the program accesses an object through a base class reference or pointer...
        the referred-to object automatically behaves in an appropraite manner without requiring writing more special code for every type
  ex. graphic design class to plot shapes
    if we add a virtual plotShape() method to our shape classes, we can now simply ask all of the objects to draw themselves!
*/

class Shape{
public:
  ....
  virtual void plotShape();
  ....
};

class GfxDesign {
public:
  GfxDesign() { count_ = 0; }
  void addCircle(double rad) 
   { arr_[count_++] = new Circle(rad); }
  void addSquare(double side) 
   { arr_[count_++] = new Square(side); }
  ...
  void drawAll() {
    for (int i=0;i<count_;i++) 
      arr[i]->plotShape();
  }
private:
  int count_;
  Shape *arr_[100];
}; 

int main() {
  GfxDesign g;
  g.addCircle(5); 
  g.addSquare(10);
  g.addTriangle(3);

  g.drawAll();
}

//  ex. omitting virtual keyword, swapping methods

class Shape{
public:
  virtual double getArea(){return 0;} // if we removed double, calling in printPrice would always invoke base class version of the getArea() function 
};

class Square : public Shape{
public:
  virtual double getArea(){return m_side*m_side;}
  void setSide(int side){m_side = side;}
private:
  int m_side;
};

void printPrice(Shape &x){
  cout << "Cost is $" << x.getArea() * 3.25; // this is fine because getArea() is virtual and in base class
  x.setSide(10); // illegal because not every shape has a setSide(), only rectanglg does
}

// ex. politicians and people 
  // we can refer to a subclass object (i.e. Politician) as if it were a superclass object (i.e. Person)
  // this is called "upcast" where we use a base pointer/reference to access a derived object

class Person
{
public:
  string getName() 
  { return m_name; }
  ...
 private:
  ...
};

class Politician: public Person
{
public:
 void tellALie() 
  { cout << m_myLie; }
 void wasteMoney(int dollars)
  { m_specialInterest += dollars; }
 private:
 ...
};

int main()
{
  Politician carey;
  Person *p;

  p = &carey; // OK!
  cout << p->getName();
}

int main()
{
  Politician *p;
  Person david;

  p = &david; // THIS IS NOT OKAY!! David is a person, but lacks the attributes of a politcian
  ... // more specifically, you can't use a subclass pointer/reference to refer to a superclass variable
}

// ex. calling derived virtual methods 

class Geek
{
public:
  void tickleMe() 
  { 
    laugh(); 
  }
  virtual void laugh()
  { cout << “ha ha!”; }
};

class HighPitchGeek: public Geek
{
public:
  virtual void laugh()
  { cout << “tee hee hee”; }
};

int main()
{
  Geek *ptr = new 
    HighPitchGeek;
   ptr->tickleMe(); // "tee hee hee"
   delete ptr; // C++ always calls the most-derived version of a function associated with an object, as long as it’s marked virtual!
} 

/*
Polymorphism and Virtual Destructors 
  you should always make sure that you use virtual destructors when you use inheritance/polymorphism
  ex. programs with and without virtual destructors  
    Summary: 
      All professors think they’re smart.  (Hmm… is 95 smart???)
      All math professors keep a set of flashcards with the first 6 square numbers in their head.
    technically, if you don't make your destructor virtual your program will have undefined behavior
      destructors need to be declared virtual in a base class when objects of derived classes are intended to be deleted through a pointer to the base class
      ALWAYS MAKE IT VIRTUAL IN THE BASE CLASS (derived classes it's good practice) 
*/

class Prof
{
public:
  Prof()
  {
    m_myIQ = 95;
  }

  virtual ~Prof()
  {
    cout << “I died smart: ”
    cout << m_myIQ;
  }
 private:
  int m_myIQ;
};

class MathProf: public Prof
{
public:
 MathProf()
 {
   m_pTable = new int[6];

   for (int i=0;i<6;i++)
    m_pTable[i] = i*i;
 }
 virtual ~MathProf()
 { 
   delete [] m_pTable; 
 }
 private:
 int *m_pTable;
};

int main()		
{
   Prof *p; // p is a Prof pointer pointing to a MathProf variable
   p = new MathProf; // allocating memory for Prof and then MathProf
   ...
   delete p; // Now, because the base destructor (~Prof()) is virtual, the compiler performs dynamic dispatch → it checks the actual type of the object (MathProf).
  // so ~MathProf() runs first, then ~Prof() --> no memory leak!
}

// ex. no virtual destructors

class Person {
public:
    ~Person() { cout << "Person destroyed\n"; }
};

class Student : public Person {
public:
    ~Student() { cout << "Student destroyed\n"; }
};

int main() {
    Person* p = new Student();
    delete p; // BAD! Student's destructor ~Student() is NEVER called! --> memory leak
    return 0;
}

/*
So how does it all work?
  vtable (short for virtual table): a hidden lookup table the compiler creates whenever your class has at least one virtual function.
    It’s how C++ implements runtime polymorphism — the ability for a base pointer or reference to call the correct derived function dynamically (based on the actual object type).
Pure Virtual Functions
  ex. shapes plotter
    imagine many derived classes of Shape representing shapes
    each class has a virtual method plotOnScreen() and on the outside, one display(Shaoe *shapes[100]) method, where each entry in the array is a shape object of any shape but derived from Shape
      the Shape class plotOnScreen() method may never be called, but you CANNOT delete it!
      void display(Shape *shapes[100]) is operating on Shape objects, so the compiler expects the Shape class to have a plotOnScreen() method
      So even though we'll never call the base version of plotOnScreen()...
        We have to define it in our base class to do polymorphism.
        That's ugly! The function's { code } doesn't even do anything useful!
          but it's necessary to properly display the derived class objects using their virtual plotOnScreen() method
  so do we really need the dummy code in the base class if it's never used??? 
    these are called "pure virtual" functions 
    pure virtual functions: pure virtual function is a virtual function in a base class that has no default implementation and is declared by appending $ = 0$ to its signature. Its purpose is to force any concrete (non-abstract) derived class to provide its own implementation
    As it turns out, C++ actually has an official way to define a member function without { code }!
    ex. back to shapes
      Abstract Base Class: a base class that has at least one pure virtual function defined in it
*/

class Shape
{
public:
 Shape(float x, float y) {
   m_x = x;
   m_y = y;
 }
  virtual void plotOnScreen() = 0; // means that derived classes must provide {code} for these functions! 
  virtual float getArea() = 0; // essentially, our base class can specify what methods MUST be implemented in derived classes while avoiding dummy code!
  float getX() const { return m_x; }
  float getY() const { return m_y; }

 private:
 float m_x, m_y;
};

/*
      while an Abstract Base Class can be used as a base class to derive other classes...
        you CANNOT define regular objects with your base class
      if you define an Abstract Base Class, its derived class(es):
        1. must either provide {code} for ALL pure virtual functions
        2. or the derived class becomes an Abstract Base Class itself!
          abstract base classes are meant to represent concepts, not things (design intent) 
*/

class Shape {
public:
    virtual void draw() = 0;   // pure virtual function
};

Shape s;   // ❌ error
// the compiler refuses because the vtable for Shape is incomplete - there's at least one virtual function (draw) with no code attached

class Circle : public Shape {
public:
    void draw() override { cout << "Drawing a circle\n"; }
};

Circle c;       // ✅ OK
Shape* p = &c;  // ✅ OK
p->draw();      // prints "Drawing a circle"

class IncompleteShape : public Shape {
    // forgot to override draw()
};

IncompleteShape s;  // ❌ still abstract

// note: override is not strictly necessary but good practice

/*
Why should you use pure virtual functions and create Abstract Base Classes anyway?
  you force the user to implement certain functions to prevent common mistake!
    for example, what if you create a Rectangle object and forget to define its own getCircum()?
Even thought you can't CREATE a variable with an Abstract Base Class type...
  you can still use Abstract Base Class references and pointers to implement polymorphism!
*/


int main()
{
 Shape s; // ERROR

 ...
}

void foo(Shape &x){
  cout << x.getArea();
}

void bar(Shape *p) {
  cout << p->getCircum();
}

int main(){
  Square s(5);
  foo(s);

  Rectangle r(20,30); // valid
  bar(&r);
}

// ex. pure virtual functions / ABC's

class Animal // Abstract Base Class because it has two pure virtual functions
{
public:
   virtual void GetNumLegs() = 0;
   virtual void GetNumEyes() = 0;
   ...
};

class Insect: public Animal // Also Abstract Base Class since it has at least one pure virtual function
{
public:
   void GetNumLegs()  {  return(6); } // note: if a base class defines a function as virtual, all derived class automatically treat that function as virtual
  // Insect does not define GetNumEyes
   ...
};

class Fly: public Insect // regular class since it has no pure virtual functions
{
public:
   void GetNumEyes()  {  return(2); }
   ...
};

/*
Summary for pure virtual functions and ABC's
  avoid writing dummy logic for unused base class methods
  prevent bugs but forcing the programmer to implement the correct versions of functions in derived classes


  // POLYMORPHISM CHEAT SHEET AND CHALLENGE PROBLEMS STARTING SLIDE 54 
  // https://docs.google.com/presentation/d/1tRRzsRDMg2oyjauE--JP_ce741pMf2K4cVztI1Zsqoo/edit?usp=sharing
*/
