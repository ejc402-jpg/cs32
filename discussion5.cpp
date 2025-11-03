// Recursion, Virtual Functions and Abstract Base Class

/*
Recursion
  calls itself with a smaller sub-problem
  stops at a terminal condition (base case)
  ex. troubleshoot BruinBill
    Finance --> Bursar --> Main Cashier --> Student Account --> solved
*/

// ex. palindrome with iteration and recursion

bool iterativeChecker(char str[], int s, int e){
  while (s < e){
    if(str[s] == str[e]){
      s++;
      e--;
    }
    else{
      return false;
    }
  }
  return true;
}

bool recursiveChecker(char str[], int s, int e){
  // base cass
  if(s >= e) return true;
  if(str[s] != str[e]) return false;
  // recursion
  return recursiveChecker(str, s + 1, e - 1);
}

/*
Virtual Functions
  Overloading vs. Overriding vs. Overwriting
    Overloading  
      multiple functions with the same name but different parameter lists
    Overriding
      redefines/implements a virtual function in a derived class
    Overwriting
      something else
  virtual: declares a virtual function that can be overridden in its subclasses
  = 0: marks the virtual function as pure, thus making the class abstract (ABC)
  override: enforces syntatic check (optional)
Polymorphism
  why only works with pass-by-reference/pointer?
    otherwise, derived class becomes chopped and the function doesn't work with the actual derived object, it only knows the base object parameters
*/

// Worksheet Questions
