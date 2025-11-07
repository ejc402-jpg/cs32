// Big-O, Sorting Algorithms, Appendix - ShellSort, The STL and Big-O, Space Complexity

/*
Big-O
  a technique that lets you quickly understand an algorithm's efficiency
  ex. a function that has a big-O of N^2 which means that if you pass N items to it, it will take roughly N^2 steps to process its data
  not exact, however. instead, it gives a rough estimate in terms of well-known functions log2(N), N, N*log2(N), N^2
  good way to quickly compare different algorithms and pick the best one
    so you don't look bad in job interviews
How Fast is That Algorithm?
  how do you measure the speed of an algorithm?
    1. run time OR
    2. how many computer instructions it takes to solve a problem of a given size?
      but both are not that useful, and instructions can vary drastically based on input size
  BEST CHOICE: the number of instructions used by an algorithm as a function of the size of the input data
  ex. I'm trying to sort N numbers
    Algorithm A takes 5 * N^2 instructions to do this
    Algorithm B takes 37000 * N instructions to do that
    this way, we can...
      1. compare two algorithms for a given sized input
      2. predict the performance of those algorithms when they are applied to less or more data
Big-O - The Concept
  measures an algorithm by the gross number of steps that it requires to process an input of size N in the WORST CASE scenario
  we could specifically say "Algorithm X requires 5N^2 + 3N + 20 steps to process N items
    but Big-O tells us to ignore coefficients and lower-order terms of the expression
    "the Big-O of Algorithm X is N^2."
      still gives us an overall impression of an algorithm's worst-case efficiency
  we want to use simple functions that tell us how many operations are needed to process n items of input
    n^2, (n log2(n)), etc.
    easily compare two different algorithms
Big-O - Computing It
  need to determine the number of operations an algorithm performs --> f(n)
  operations means any of the following...
    1. accessing an item (i.e. an item in an array)
    2. evaluating a mathematical expression
    3. traversing a single link in a linked list, etc.
  ex. computing a f(n)
  int arr[n][n];
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      arr[i][j] = 0;
    }
  }
  compute f(n), the # of critical operations, that this algorithm performs
  f(n) = 1 + n + n + n + n^2 + n^2 + n^2
  f(n) = 3n^2 + 3n + 1
  1. algorithm initializes the value of i once
  2. algorithm performs n comparisons between i and n
  3. algorithm increments the variable i, n times
  4. algorithm initializes the value of j, n different times
  5. algorithm performs n^2 comparisons between j and n
  6. algorithm incremeents the variable j, n^2 times
  7. algorithm sets arr[i][j] value n^2 times
General Formula
  1. determine how many steps f(n) an algorithm requires to solve a problem, in terms of the number of items n
  2. keep the most significant term of that function and throw away the rest
    ex. f(n) = 3n^2 + 3n + 1 --> f(n) = 3n^2
    ex. f(n) = 2nlog(n) + 3n --> f(n) = 2nlog(n)
  3. now remove any constant multiplier from the function
    ex. f(n) = 3n^2 --> f(n) = n^2
    ex. f(n) = 2nlog(n) --> f(n) = nlog(n)
  4. now you have your Big-O 
    ex. f(n) = 3n^2+3n+1 --> O(n^2)
    ex. f(n) = 2nlog(n) + 3n --> O(n log(n))
  If you think about it, there's no need to compute the exact f(n) anyway because you throw away all the coefficients and lower-order components!
    just focus on the most frequently occurring operation(s) to save time
    ex. arr[i][j] = 0; is f(n) = n^2 --> O(n^2)
  "This algorithm is O(n^2)" --> "to process n items, this algorithm requires roughly n^2 operations"
Big-O Complexity Table
  https://discord.com/channels/633096463139864606/1010791176250609757/1436151022031474728
  great programmers test different algorithms
  bad programmers try to optimize a single algorithm without considering alternatives
  O(n log2(n)) is pretty goated
Big-O Practice
  when working with a large number of items, evalauting Big-O is key
  in such cases when n is small, then you could just opt for the easiest solution (not the most optimal necessarily)

-----------------SEE PRACTICE PROBLEMS IN SLIDES-----------------

Ugly Cases
  sometimes you'll run into an algorithm that isn't so clear-cut
  ex. void mystery(int n){
    for(int q = 0; q < n; q++){
      for(int x = 0; x < q; x++){
        std:::cout << "Wahoo!" << std::endl;
      }
    }
  }
    outer loop runs n times
    inner loop operations depend on q which is not constant
    turns out it's f(n) = (n^2)/2 - n --> O(n^2)
  But this is not clean math, and we'd like to find a better way to address these cases without formulas
    1. locate all loops that don't run for a fixed number of iterations and determine the maximum number of iterations each loop could run for
    2. turn these loops into loops with a fixed number of iterations, using their maximum possible iteration count  
*/
int main( )
{ // O(n^3)
   for ( int x = 0; x < n; x++ )
       for (int j=0; j < x*x  ; j++)
            cout << “Burp!”;
    // x can be as high as n, x*x as high as n*n
    for (int x = 0; x < n; x++){
      for(int j = 0; i  < n*n; j++){
        std::cout << "burp!";
      }
    }
}
func1(int n)
{
   for ( int i = 0; i < n; i++ )
      for (int j=0; j  <  i  ;j++)
          cout << j;
    // i is as high as n
  for(int i = 0; i < n; i++){
    for(int j = 0; j  < i; j++){
      std::cout << j;
    }
  }
}
/*

-----------------SEE MORE PRACTICE PROBLEMS IN SLIDES-----------------

Big-O for Multi-input Algorithms
  often, an algorithm will operate on two (or more) independent data sets, each of a different size
  in these cases we must consider both independent sizes of input to compute algorithm's Big-O
ex. buffet & tinder
*/
void buffet(string people[], int p, 
	      string foods[], int f)
{
   int i, j;

   for (i=0; i < p ;i++)
      for (j=0; j < f ;j++)
          cout << people[i] << “ ate “ 
                  << foods[j] << endl;
} // O(p * f)

void tinder(string csmajors[], int c, 
	      string eemajors[], int e)
{
   for (int i=0; i < c ;i++)
       for (int j=0; j < c ;j++)
           cout << csmajors[i] << “ dates “
                   << csmajors[j] << endl;

   for (int k=0; k < e ;k++)
     cout << eemajors[k] << “ sits at home“;
} // O(c^2 + e) --> NOT O(c^2), because these are independent operations
/*
  why did we include both c^2 and e? because either variable could dominate the other!
    e could be 100000 while c is 1
*/
void tinder(string csmajors[], int c, 
	      string eemajors[], int e)
{
   for (int i=0; i < c ;i++) // c^2 iterations
       for (int j=0; j < c ;j++)
           cout << csmajors[i] << “ dates “
                   << csmajors[j] << endl;
  for (int m=0; m < c ; m++) // c iterations
     cout << csmajors[m] << “ is still a nerd”;

   for (int k=0; k < e ;k++) // e iterations
     cout << eemajors[k] << “ sits at home“;
} // STILL O(c^2 + e) because c^2 + c reduces within its own independent variable

// -----------------SEE MORE PRACTICE PROBLEMS IN SLIDES-----------------

/*
The STL and Big-O
  remember stacks, queues, sets, vectors, lists, and maps?
    these classes use algorithms to get things done too
      these algorithms have Big-Os too!
  for example, if we want to search for a word in a set that contains n words, it requires O(log2(n)) steps
  but if you want to add a value to the end of a vector holding n items, it takes one step --> O(n)
*/
void inDict(set<string> & d, string w) 
{
if(d.find(w) == d.end()){
  std::cout << w << " isn't in dictionary!";
}

}

void otherFunc(vector<int> & vec)
{
  vec.push_back(42);
  vec.erase(vec.begin()); // any guess as to why it takes n steps to delete the first item from a vector container n items?
  // when you erase, every element needs to be shifted/reindexed
}
/*
  it's important to understand the Big-O of each operation for each STL class to compute the Big-O of any code that would use the STL classes
  for example, a loop that runs D times and in each iteration, searches for an item in a set holding n items...
    then the Big-O of our whole loop would be O(D * log2(n))
    (each search in a set costs log(n)) --> ordered set == binary search
*/

// ex comparin Big-O of algorithms that use STL

void printNums( vector<int>  & v )
{
    int q = v.size();
    for ( int i = 0; i < q ; i++ ) // q times
    {
         int a = v[0];   	// get 1st item
         cout << a;      	// print it out
         v.erase( v.begin() );  // erase 1st item // q times
         v.push_back(a); 	// add it to end
    }
} // O(q^2)

/*
STL and Big-O Cheat Sheet
  when describing the Big-O of each operation on a container, we assum that the container holds n items when the operation if performed
  https://www.geeksforgeeks.org/cpp/cpp-stl-cheat-sheet/
*/

// -----------------SEE MORE PRACTICE PROBLEMS IN SLIDES-----------------

/*
Space Complexity
  Space complexity is the big-o of how much storage your algorithm uses, as a function of the data input size, n. 
*/
void reverse(int array[], int n)
{
   int tmp, i; // uses just two new variables no matter how big the array is

   for (i = 0; i < n/2; ++i)
   {
      tmp = array[i];
      array[i] = array[n-i-1];
      array[n-i-1] = tmp;
   }
} // O(1) or O(constant)
void reverse(int array[], int n)
{
   int *tmparr = new int[n]; // uses a new arrray of size n to process the input array of size n

   for (int i = 0; i < n; ++i)
      tmparr[n-i-1] = array[i];

   for (int i = 0; i < n; ++i)
      array[i] = tmparr[i];

   delete [] tmparr;
} // O(n)
/*
Recursion with Space Complexity
  be careful, space complexity gets tricky with recursion
    each call creates a whole new variable for each of the n levels of recursion
Big-O: Average Case
  sometimes an algorithm's performance varies based on the nature of the input data
*/
bool has_even(int a[], int n) 
{
  for (int i=0;i < n;i++) 
     if (a[i] % 2 == 0) 
       return true;
  return false;
}
// if the input arrays always have even number in the first position or last half...
// will be O(1) or O(N)
/*
  so in cases where an algorithm's big-O varies depending on the input data, how do we compute the overal Big-O? 
    take the average big-O considering all possible inputs
    in the has_even example, 1/2 N --> O(N)
*/

