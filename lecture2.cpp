/*
Construction: the process of initializing a new object for use when it's first created 
  class composition: when a class holds member variable(s) that are also classes
  default constructor: one which has no required arguments
    but it can still have code/instructions if manually created (not when no constructor is provided)    
Destruction: frees the memory and resources used by an object when its lifetime ends
  Both are foundational to OOP
Constructor: a function that initializes an object when it's first created 
  After memory is reserved when a construcor is called, construction of an object runs in three phases
    1. Talk about it later
    2. C++ constructs all non-primitive member variables (i.e. strings) in the order they appear in the class
    3. C++ runs the {body} of your constructor
      Non-primitive? strings (automatically initialized "", objects/arrays you create). Primitive? int, double, float (garbage assignment)
  What if you don't define a constructor? 
    C++ provides a hidden, empty one but still goes through the same member initialization phases from before
  Why does C++ construct member variables before running the constructor?
    it's allowed to use member variables inside the constructor (most commonly when you are passing initialization arguments inside the constructor when creating the class object)
    otherwise, trying to assign or access undefined member variables leads to undefined behavior
  initializor list: code that explicitly papses in value(s) to the constructor(s) of one or more member variables
    if you write them with : belly(5) (for example) after the constructor declaration but before the constructor body, the member variables of that class can be initialized immediately rather than assigning them values after they are created
    while non-primitive members take precedence before constructor body, initialization lists are before both
    they can also initialize primitives!
    best practice is to order the variables in the initializer list the same order as the variables listed in the class
  Constructor Overloading (Function Overloading): allows for multiple constructors of the same class object type as long as each constructor accepts a different number/types of arguments
    function overloading is when you define multiple functions with the same name but different numbers/types of parameters
  When are constructors called?
    1. when you create a new object
    2. it is called N times for an array of N objects (once for each element)
    3. it is NOT called when you just define a pointer variable
    4. constructor is called when you use new to dynamically create a new object
    5. if variable is declare in a loop, a new version is constructed during EVERY iteration!
  Summary
    constructor is a function that initializes an object when it's first created 
    C++ calls the constructor for an object's nonprimitive member variable(s) in the order they're defined
    then C++ runs the constructor's {body} to complete initialization
    when we have multiple levels of class composition, construction follows the same pattern
    we can use an initializer list to initialize member variables that require parameters for construction 
    constructors are run every time a new object is defined (except if just a pointer is defined)
    classes can have more than one constructor (with different parameterss, aka constructor overloading)
Destructors: a function that frees all the resources that an object allocates during its lifetime
  an object often reserves system resources (i.e. memory, disk) 
    destructors ensure those resoures are automatically freed up when an object goes away
  When must you have a destructor?
    Any time a class allocates a system resource, your class must have a destrutor that...
      1. Reserves memory using the new command --> frees the allocatd memory with the delete command
      2. Opens/creates a disk file --> closes/deletes the disk file
      3. connects to another computer --> disconnects from the other computer
  Destruction of an object runs in three phases
    1. C++ runs the object's destructor {body} first
    2. C++ destructs all non-primitive member variables in the reverse order they appear in the class
    3. Learn about this later
      After the destructors have run, the object's RAM is freed
    If we don't define a destructor, C++ provides a hidden, empty one, going through the same destruction phases we learned a second ago
    [stopped at slide 28]
*/
