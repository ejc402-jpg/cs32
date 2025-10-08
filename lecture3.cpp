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
  cout << array[0];
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
  can use pointers with structs and classes too
*/
void printInfo(Circ* ptr){
  cout << "the area is" << ptr->getArea();

int main(){
  Circ foo(3, 4, 10);
  printInfo(&foo);
}
/*

*/





