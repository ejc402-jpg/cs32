// Recursion 

/*
Normally functions call other functions...
  But some problems are much easier when one function calls itself!
  Each time a recursive function calls itself, it must pass in a simpler sup-problem than the one it was asked to solve
    Eventually it reached the simplest subproblem, which it solves without needing to call itself
  Done in AI chess players, sudoku solvers, ciphers, circuit boards, job interviews
Recursion Idea
  want a big problem to be solved
  if the problem trivially solved? return
  if not, break the problem into two or more simpler sub-problems until the simplest problem can be solved
  collect all the solutions to the sub-problems and construct a complete problem solution, return that
*/

int factorial(int n){
  if(n == 0) return 1; // base case
  int fact_of_n = n*factorial(n-1);
  return fact_of_n;
}

/*
The Lazy Person's Sort (merge sort) 
  new sorting algorithm --> input: bunch of index cards with numbers
    1. split the cards into two roughly-equal piles
    2. hand one pile to nerdy Student A and ask them to sort it
    3. hand the other pile to nerdy student B and ask them to sort it
    4. take the two sorted piles and merge them into a single sorted pile
  but the nerdy students are lazy, they also break their piles into halves and tell two other nerds to sort
  what happens when the piles get reduced into one card piles? and so many nerds are involved?
    one card piles are already sorted, so the person that sent them can merge them properly
    then we keep working back up until we get the entire pile back, merged 
*/

void mergeSort(int arr[], int n){
  if (n <= 1) return;
  int mid = n/2; 
  mergeSort(arr, mid); // sort first half
  mergeSort(arr+mid, n - mid); // sort second half
  merge(arr, 0, mid, n);
}

/*
When you write a recursive function...
  You need to figure our how the function can use itself (subset of inputs) to solve the complete problem
  Trust the recursive calls will work
Two Rules of Recursion (ex. factorial code above)
  1. every recursive function must eventually stop calling itself
    the function must identify the simplest possible input and return result without calling itself
    "stopping condition" or "base case"
  2. every time a recursive function calls itself, it must pass in a smaller sub-problem
    ensures that we will eventually reach the base case and stop recursing
  With the absence of either, we end up in an infinite loop (infinite recursion)!
Array and Linked List Refresher
*/

void print(int arr[], int n){
  for(int i = 0; i < n; i++){
    std::cout << arr[i] << " ";
  }
}

print(x, n - 1); // prints first n - 1 items
print(&x[1], n - 1); // prints last n - 1 items

struct Node{
  int val; 
  Node* next
};

void print_list(Node* ptr){
  while(ptr){
    std::cout << ptr->val;
    ptr = ptr->next;w
  }
}

int main(){
  Node* head;
  head = create_linked_list();
  print_list(head->next); // print starting at the node following the first node
}

/*
Three Steps to Writing a Recursive Function
  1. figure out the base cases
    the simplest possible input(s) and returns a result without a recursive call 
    every recursive function must start with code to handle all base cases and return a result immediately
    common base case inputs
      integer input value of 0 or 11
      empty array or array holding a single item
      empty linked list or one node linked list
      empty string or string with single character
    ex. sum of array (base case: 0 items), inorder (base case: 0 or 1 items), first odd and last odd (base case: 0 items)
  2. write your function...but without using recursion
    the examples below all work but delegates processing to a helper function
*/
    int fact(int x){ // iterative solution
      int f = 1; 
      for(int i = 2; i < x; i++){
        f *= i;
      }
      return f;
    }
    int fact(int n){ // recursive solution
      if(n == 0 || n == 1){
        return 1;
      }
      int f = n * fact(n-1);
      return f;
    }
  // ex. complete the function which prints an array from first to last
    void printHelper(int arr[], int x){
      for(int i = 0; i < x; i++){
        std::cout << arr[i] << std::endl;
      }
    }
    void print(int arr[], int n){
      if (n == 0) return;
      std::cout << arr[0] << endl;
      printHelper(arr+1, n - 1);
    }
  // prints an array in reverse (version 1)
    // prints all of the items in
    // an array in reverse using
    // iteration  
    void printr'(int arr[], int x) {
      for (int i=x-1; i >= 0; --i)
        cout << arr[i] << endl;
    }
    // prints all of the items in
    // an array in reverse  
    void printr(int arr[], int n) {
      if (n == 0) // base case
        return;   // from before
    
       
      printr'(________, n - 1 );
       
      cout << _______ << endl;
    }
  // prints an array in reverse (version 2)
    // prints all of the items in
    // an array in reverse using
    // iteration  
    void printr'(int arr[], int x) {
      for (int i=x-1; i >= 0; --i)
        cout << arr[i] << endl;
    }
    // prints all of the items in
    // an array in reverse.  
    void printr(int arr[], int n) {
      if (n == 0) // base case
        return;   // from before
    
      cout << arr[_______] << endl;
       
      printr'(________, n - 1);
    }
  // sums the items in an array
    // computes the sum of all
    // items in an array iteratively 
    int sum'(int arr[], int x) {
      int s = 0;
      for (int i=0; i < x; ++i) 
        s += arr[i];
    
      return s;
    }
    // sums all #s in array 
    int sum(int arr[], int n) {
      if (n == 0)  // base case
        return 0;  // from before
     
      int tot = a[0]+
        sum'(arr + 1, n - 1);
    
      return tot;
    }
  // determines whether an array is in order
    // determines if all the items
    // in an array are in order, 
    // using iteration
    bool inorder'(int arr[], int x) {
    
      if (x < 2) return true;
    
      for (int i=0; i < x - 1; ++i) 
        if (arr[i] > arr[i+1])
          return false;
    
      return true;
    }
    // determines if all items in an
    // array are in ascending order 
    bool inorder(int arr[], int n) {
      if (n == 0)    // base case
        return true; // from before
      if (n == 1)    // base case
        return true; // from before
    
      if (_______ > _______)
        return false;
    
      return inorder'(_______, ___);
    }
  // find the first odd number in an array
    // returns the first odd number
    // in an array, or -1 if no odds, 
    // using iteration
    int firstodd'(int arr[], int x) {
    
      for (int i=0; i < x; ++i) 
        if (arr[i] % 2 == 1)
          return arr[i];
    
      return -1;
    }
    // returns the first odd number
    // in an array, or -1 if no odds 
    int firstodd(int arr[], int n) {
      if (n == 0)  // base case
        return -1; // from before
    
      if (_______ % 2 == 1)
        return _________;
    
      return firstodd'(_______, n-1);
    }
  // last number in an array
    // returns the last odd number
    // in an array, or -1 if no odds, 
    // using iteration
    int lastodd'(int arr[], int x) {
    
      for (int i=x-1; i >= 0; --i) 
        if (arr[i] % 2 == 1)
          return arr[i];
    
      return -1;
    }
    // returns the last odd number
    // in an array, or -1 if no odds int lastodd(int arr[], int n) {
      if (n == 0)  // base case
        return -1; // from before
    
      int q = lastodd'(______, ____);
    
      if (q != ____) return q;
    
      if (______ % 2 == 1)
        return arr[0];
      return -1; // no odd found!
    }
// 3. convert your function into a recursive version in just one step
  int firstodd(int arr[], int n){
    if (n == 0) return -1;
    if(arr[0] % 2 == 1) return arr[0];
    return firstodd(arr+1, n-1);
  }
  int fact(int n){
    if(n == 0) return 1;
    int f = n * fact(n-1);
    return f;
  }
  void print(int arr[], int n){
    if(n==0) return;
    std::cout << arr[0] << std::endl;
    print(arr + 1, n - 1);
  }
  void printr(int arr[], int n){
    if(n == 0 ) return;
    printr(arr + 1, n - 1);
    std::cout << arr[0] << std::endl;
  }
  int sum(int arr[], int n){
    if(n == 0) return 0;
    int tot = arr[0] + sum (arr + 1, n - 1);
    return tot;
  }
  int inorder(int arr[], int n){
    if (n == 0) return true;
    if(n == 1) return true;
    if(arr[0] > arr[1]) return false;
    return inorder(arr+1, n-1);
  }
  int firstodd(int arr[], int n){
    if(n == 0) return -1;
    if( arr[0] % 2 == 0) return arr[0];
    return firstOdd(arr + 1, n - 1);
  }
  int lastodd(int arr[], int n){
    if(n == 0) return -1;
    int q = lastodd(arr + 1, n - 1);
    if(q != -1) return q;
    if( arr[0] % 2 == 1) return arr[0];
    return -1;
  }
/*
Recursion on Linked Lists
  using recursion on linked lists is similar to using recursion on arrays
  the only difference is that we always recurse from top-to-bottom (not bottom up)
  1. figure out the base cases
    empty linked list or linked list holding a single node
*/
  void printr(Node* p){
    if(!p) return;
  }
  int sum(Node* p){
    if (!p) return 0;
  }
  int lastOdd(Node* p){
    if(!p) return -1;
  }
  int max(Node* p){
    if(!p) return -1;
    if(!p->next) return p->val;
  }
  bool inorder(Node *p){
    if(!p) return true;
    if(!p->next) return true;
  }
// 2. solve it NON-RECURSIVELY
  void printr(Node* p){
    if(!p) return;
    printr'(p->next); // assume we have a function that prints last n - 1 nodes in reverse order
    std::cout << p->val << std::endl;
  }
  int sum(Node* p){
    if(!p) return 0;
    int s = p->val + sum'(p->next); // assume such a function exists
    return s;
  }
  int lastodd(Node* p){
    if(!p) return -1;
    int q = lastodd'(p->next); // assume such a function exists and works
    if(q != -1) return q;
    if(p->val % 2 == 1) return p->val;
    return -1;
  }
  int max(Node* p){
    if(!p) return -1;
    if(!p->next) return p->val;
    int max_rest = max'(p->next);
    if(p->val > max_rest) return p->val;
    return max_rest;
  }
  bool inorder(Node* p){
    if(!p) return true;
    if(!p->next) return true;
    if(p->val > p->next->val) return false;
    retrun inorder'(p->next);
  }
// 3. you know the drill
  void printr(Node* p){
    if(!p) return;
    printr(p->next);
    std::cout << p->val << std::endl;
  }
  int sum(Node* p){
    if(!p) return 0;
    int s = p->val + sum(p->next);
    return s;
  }
  int lastodd(Node* p){
    if(!p) return -1;
    int q = lastodd(p->next);
    if(q != -1) return q;
    if(p->val % 2 == 1) retrun p->val; 
    return -1;
  }
  int max(Node* p){
    if(!p->next) return p->val;
    int max_rest = max(p->next);
    if(p->val > max_rest) return p->val;
    return max_rest;
  }
  bool inorder(Node* p){
    if (!p) return true;
    if(!p->next) return true;
    if(p->val > p->next->val) return false;
    return inorder(p->next);
  }
// bonus: finding biggest node in the list
  int biggest(Node* cur){
    if(!cur->next) return cur->val;
    int rest = biggest(cur->next);
    return max(rest, cur->val);
  }
    



    






    
