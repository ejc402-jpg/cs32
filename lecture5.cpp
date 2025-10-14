// Stacks and Queues
/*
Stacks
  a stack is data structure that resembles a stack of plates at a buffet (LIFO)
    the last plate/value you add is at the top of stack, and thus is the first to be removed
    used to find a path through a maze, "undo" in a word processor, and evaluate math expressions
  a stack is an ADT that holds a collection of any type of items (like ints) where the elements are always added to one end
  operations
    1. put something at the top of the stack (PUSH)
    2. remove the top time (POP) 
    3. look at the top item, without removing it
    4. check to see if the stack is empty
  note: you can only access the top item of the stack, since the other items are covered
*/
class Stack{
  public:
    Stack();
    void push(int i);
    int pop();
    bool is_empty(void);
    int peek_top();
  private:
  // what do we put here? what member variables do we need to implement a stack?
    // answer: we can use a linked list OR array and counter variable to track the top position of the stack
};
int main(){
  Stack is;
  is.push(10);
  is.push(20);
}
  // array implementation
const int SIZE = 100;
class Stack{
  public:
    Stack(){m_top = 0;} // m_top always points to the next spot in in the stack (m_top = 0 means empty stack)
    void push(int val){
      if(m_top >= SIZE) exit(-1); // overflow
      m_stack[m_top] = val; 
      m_top += 1;
    }
    int pop(){
      if(m_top == 0) exit(-1); // underflow
      m_top -= 1;
      return m_stack[m_top];
    }
    bool is_empty(void);
    int peek_top();
  private:
    int m_stack[SIZE];
    int m_top; 
};
  // which statements should the pop() method use? 
    // two options
      // 1. m_top -= 1; return;
      // 2. int v = m_stack[m_top]; m_top -= 1; return v;
  // always remember: when you push, you store the item in m_stack[m_top] and post-increment out m_top variable (after confirming you won't go past allocated stack size)
  // always remember: when you pop, you pre-decrement our m_top variable, the return the item in m_stack[m_top] (after confirming stack is not empty)
  // stacks are so common that C++ actually has an implementation in the STL library
#include <iostream>
#include <stack> 
int main(){
  std::stack<int> istack; // stack of ints
  istack.push(10);
  istack.push(20);
  std::cout << istack.top();
  istack.pop(); // note: pop does not return the top value that it throws away, access with top() before using pop() if desired
}
  // challenge
int main(){
  std::stack<int> istack; 
  istack.push(6);
  for(int i = 0; i < 2; i++){
    int n = istack.top();
    istack.pop();
    istack.push(i);
    istack.push(n*2)
  }
}
    // [bottom] 0 1 2 48 [top]
/*
  common uses for stacks (one of the MOST useful data structures) --> used for...
    1. storing undo items for your word processor
    2. evaluating mathematical expressions
    3. converting from infix expressions to postfix expressions
    4. solving mazes
      they are so fundamental they are built into every single cpu in existence
  every cpu has a built-in  stack used to hold local variables and function parameters
    when you pass a value into a function, the CPU pushed that value onto a stack in the computer's memory
      when the function returns, the values are popped off the stack and go away
    every time a local variable is declared, the program pushes it on the PC's stack automatically
      they are released from the stack as they go out of scope (most recent variables go first)
Postfix Expression Evaluation
  most people are used to infix notation, where the operator is in-between the two operands (i.e. A + B)
  postfix does A B + (operator applies to the previous two operands)
  example
    infix: (3 + 4) * 5 --> needs parentheses to enforce precedence
    postfix: 3 4 + 5 * 
    infix: 3 + 4 * 5 --> requires implicit knowledge of precedence rules
    postfix: 3 4 5 + *
  Postfix Evaluation Algorithm
    inputs: postfix expression string
    outputs: number representing answer
    private data: a stack
      1. start with the left-most token
      2. if the token is a number, push it onto the stack
      3. else if the token is an operator
        a. pop the top value into a variable called v2, and the second-to-top value into v1
        b. apply oeprator to v1 and v2 (i.e. v1/v2)
        c. push the result of the operation on the stack
      4. if there are more tokens, advance to the next token and go back to step #2
      5. after all tokens have been processed, the top # on the stack is the answer!
    challenge: 6 8 2 / 3 * -
      //  6 4 3 * -
      // 6 12 - 
      // -6
    stacks can also be used to convert infix expressions to postfix expressions 
      i.e. (3 + 5) * (4 + 3 / 2) - 5 = 3 5 + 4 3 2 / + * 5 -
      i.e. 3 + 6 * 7 * 8 - 3 = 3 6 7 * 8 * + 3 -
      why? 
        humans are used to infix, but the code to process it is complicated
        let them input in infix, then convert to postfix
  Infix to Postfix Conversion
    inputs: infix string
    outputs: postfix string (initially empty)
    private data: a stack
      1. begin at left-most infix token 
      2. if it's a #, append it to end of postfix string followed by a space
      3. if it's a ( push it onto the stack
      4. if it's an operator and the stack is empty, push the operator on the stack
      5. if it's an operator and the stack is not empty
        a. pop all operators with greater or equal precedence off the stack and append them on the postfix string
        b. stop when you reach an operator with lower precedence or a (
        c. push the new operator on the stack
      6. if you encoutner a ), pop operators off the stack and append then onto the postfix string until you pop a matching (
      7. advance to next token and go to stop #2
      8. when all infix tokens are gone, pop each operator and append it } to the postfix string
  Solving Maze (we can also use a stack to figure out if a maze is solvable or not)
    inputs: 10x10 maze in a 2D array, starting points (sx, sy), ending point (ex, ey)
    output: boolean
    private data: a stack of points
      1.   PUSH starting point onto the stack.
      2.  Mark the starting point as “discovered.”
      3.  While the stack is not empty:
      	A.  POP the top point off the stack into a variable.
      	B.  If we’re at the endpoint, DONE!  Otherwise…
      	C.  If slot to the WEST is open & is undiscovered
                 Mark (curx-1,cury) as “discovered”
                 PUSH (curx-1,cury) on stack.
      	D.  If slot to the EAST is open & is undiscovered
                 Mark (curx+1,cury) as “discovered”
                 PUSH (curx+1,cury) on stack.
      	E.  If slot to the NORTH is open & is undiscovered
                 Mark (curx,cury-1) as “discovered”
                 PUSH (curx,cury-1) on stack.
      	F.  If slot to the SOUTH is open & is undiscovered
                 Mark (curx,cury+1) as “discovered”
                 PUSH (curx,cury+1) on stack.
      4. If the stack is empty and we haven’t reached our
      goal position, then the maze is unsolvable.
        note: this is basically a DFS solution where we explore every branch of path from are starting point and subseqeunt points
          eventually, we'll either run out of points without reaching the end point or pop the end point    
*/
class Point
{
public:
  Point(int x, int y);
  int getx() const;
  int gety() const;
private:
  int m_x, m_y;      
}; 

class Stack 
{
public:
   Stack();	  // c’tor
   void push(Point &p); 
   Point pop();
   ...
private:
   ...
}; 
/*
Queues
  a queue is also a super useful daat structure that resembles a conveyer belt of dishes (FIFO)
    used for vehicle navigation, implementing twitter feeds, queueing songs on Spotify
  the queue is another ADT that is like a line at the store or the bank
  has a front and a rear --> you enqueue items at the rear end and dequeue from the front
  functions
    void enqueue(int a) inserts item at the rear of queue
    int dequeue() removes and returns the top item from the front of the queue
    bool isEmpty() determines if queue is empty
    int size() determines the # of items in the queue
    int getFront() gives the value of the top item of the queue without removing it like deque
      like a stack, can be of any data type
  common uses
    often, data flows from the Internet faster than the computer can use it
      can hold a queue to hold the data until the browser is ready to display it
      every time your computer receives a character it enqueues it
      every time your Internet browser is ready to get and display new data, it looks in the queue
  if you use a queue instead of a stack in the maze searching algorithm, it will implement BFS solution?
    instead of always exploring the most recent x, y location pushed, it explores the oldest x, y location inserted into the queue
  Solving Maze
    1.   Insert starting point onto the queue.
    2.  Mark the starting point as “discovered.”
    3.  While the queue is not empty:
    	A.  Remove the front point from the queue.
    	B.  If we’re at the endpoint, DONE!  Otherwise…
    	C.  If slot to the WEST is open & is undiscovered
               Mark (curx-1,cury) as “discovered”
               INSERT (curx-1,cury) on queue.
    	D.  If slot to the EAST is open & is undiscovered
               Mark (curx+1,cury) as “discovered”
               INSERT (curx+1,cury) on queue.
    	E.  If slot to the NORTH is open & is undiscovered
               Mark (curx,cury-1) as “discovered”
               INSERT (curx,cury-1) on queue.
    	F.  If slot to the SOUTH is open & is undiscovered
               Mark (curx,cury+1) as “discovered”
               INSERT (curx,cury+1) on queue.
    Queue Implementations
      can use an array and integer to represent a queue
        but this kinda sucks because reindexing is costly
        every time you insert an item, place it in the rear slot of the array and increment the rear count
        every time you dequeue an item, move all of the items forward an the array and decrement the rear count
      can use a linked list to represent a queue
        every time you insert an item, add a new node to the end of the linked list
        every time you dequeue an item, take it from the head of the linked list and then delete the head node
          you will need head and tail pointer for both tasks
    The Circular Queue
      clever type of array-based queue
      unlike the previous array-based queue, we never need to shift items with the circular queue
      implementation
        private data: an array: arr, int head, tail, count
        to initialize the queue, set count = head = tail = 0
        to insert new item, place it in arr[tail] and then increment the tail and count values 
        to dequeue the head item, fetch arr[head] and increment head and decrement count
        if the head or tail go past the end of the array, set it back to 0
          but requires knowledge of max queue size beforehand? 
            no! when head or tail pointers go out of the array, they are reset to 0
            subsequent elements physically look like they are in front but are later in the queue
              but queue cannot hold more elements than the size it was allocated (this is the drawback)
    also implemented in the STL library of C++  
*/
