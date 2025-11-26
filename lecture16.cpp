// Hash Tables (modulus operator, open hash tables, hash table efficiency and "load factor", hashing non-numeric values, unordered_map: A hash-based STL map class), (Database) Tables

/*
Big-O Craziness
  consider a BST that holds N student records, all ordered by their name
  each student record contains a linked-list of the L classes that they have taken while at UCLA
  question: what is the Big-O to detemine if a student has taken a class? 
    O(logN + L)
Hash Tables
  hash tables are containers that offer faster insertion/deleting/searching, on average, then a BST, but they don't order their elemetns alphabetically
  used when you need to search quickly (but not keep data ordered). Turn-by-turn navigation, spell checking, virus scanning, video games
Modulus Operator
  the % operator is used to divide two numbers and obtain the remainder
  turns out it also has another interesting property!
    ex. modulus-divide a bunch of numbers by 5 and see the results 
    notice all the remainders are less than 5 (between 0-4!) 
  rule: when you divide by a given value N, all of your remainders are guaranteed to be between 0 and N-1!
The "Hash Table" 
  okay, so what's the most efficient ADt we know of to insert and search for data? 
  the BST! --> O(log2N) performance
  but we can do even better!
    imagine we want the operations of searching/inserting/deletion to be O(1) time on average
    if UCLA enrolls less than 100000 students, create an integer array with 100000 slots to stored the student ID's
      "wouldn't searching be O(log2N) at best?" 
    since we have the modulo operator, use it to pick a unique slot in the array for the ID#  
    slot = id_num % 100000 (because of the way modulo works, that will give me a slot # between 0 and 99999!
      (see example) we can think of f(x) as a mapping function 
      using this approach, can insert, find, delete an ID# in just one step!
*/

// converts a 9-digit student ID#
// into a value from 0 - 99999
int f(int id_num){
  const int array_size = 100000;
  int slot = id_num % array_size;
  return slot;
}
void insert(int arr[], int id){
  arr[f(id)] = id;
}
bool contains(int arr[], int id){
  return arr[f(id)] == id;
}
void erase(int arr[], int id){
  arr[f(id)] = -1;
}

/*
  but there is one problem
    f(x) doesn't guarantee that every ID# wil go into a unique array slot (1 and 999900001 is both slot 1) 
    every time you add an ID number, there is a chance of it collding with an existing ID that's already in the array 
  solution: an array of linked lists!
    find the right slot in the array with f(x), then can add the ID# to the linked list in that slot
    but what if a slot holds lots of items - now searching isn't an O(1) operation!
      in general, won't be a big problem considering many other slots 
      odds are a slot will only have 0 or 1 items when we visit it unless ID# generation is skewed in some way
        what we just did is called the Open Hash Table!
Open Hash Table
  implemented using an array of linked lists 
  to add, find, or erase an ID#, we use the modulo function to pick an array bucket
  then add/find/erase that ID# in the bucket's linked list!
  so long as we don't somehow overflow one single array bucket, we'll get ~O(1) performance for adding/searching/deleting!
  this approach can be used to store any type of integer value (not just student ID#'s) 
  so long as we can compute a modulo for a value, we can store it in the hash table!
  ex. https://discord.com/channels/633096463139864606/1010791176250609757/1443034973492740158
*/
void insert(list<int> arr[], int id) {
  if (!contains(arr, id))
    arr[f(id)].push_back(id);
}
bool contains(list<int> arr[], int id) {
  list<int>::iterator it; 
  for (it = arr[f(id)].begin();
       it != arr[f(id)].end(); it++) 
    if (*it == id) return true;
  return false;
}
void erase(list<int> arr[], int id) {
  arr[f(id)].remove(id);
}
/*
  but in the worst case, can we quantify how bad it will be
      technically, we could get unlucky and end up with few array buckets with O(N) linked lists
      we need to start by talking about "load" 
Hash Table Efficiency: The Load Factor
  the "load" of a hash table is defined as: L = max # of values to insert / total buckets in the array
  ex. load of 0.1 means your array has 10 times more buckets than you actually need
  ex. load of 2.0 means hash table holds twice as many values as there are buckets 
    therefore, each bucket holds 2 items on average
  for efficiency, we want our load to be less than 1.0, but it's not required
  given a particular load L, it's easy to comput the # of steps it will take to add/find/erase the average item in your hash table:
    # steps = 1 + L/2
    ex. L = 0.1 --> ~1.05 search steps
    ex. L = 10 --> ~6 search steps
Sizing Hash Table
  imagine we want to store up to 1000 items in an Open Hash Table and be able to find any item in roughly 1.25 steps.
  how many buckets must your hash table have?
  1.25 = 1 + L/2 --> solve for L given max 1000 items to find buckets
  if our hash table has 2000 buckets and we're inserting a maximum of 1000 values, we are guaranteed to have an average of 1.25 steps per insert/search!
  essentially, there's a tradeoff
    could use a really big hash table with many buckets to ensure really fast searches
    but end up wasting lots of memory
    on the other hand, a memory efficient small hash table will be slower
  question: what if we want to store other things like people's names
    no problem! compute f(x) for a string and find the slot
    but how do we compute the bucket number?
      Hash Function
        takes an input (like a string) and generates an output integer that's somehow derived from the input
*/
int hash(string s){
  int i, sum = 0;
  for(i = 0; i < s.length(); ++i) sum += s[i]; // uses ASCII code
  return sum;
} 
int f(string name){
  const int array_size = 100000;
  int slot = ?????????? % array_size;
  return slot;
}
/*
        but there is an issue
          since addition is commutative, different names will sum up to the same 
      A GREAT Hash Function for Strings
        don't need to write a function from scratch 
        String Hashing
          technique used to convert a string into a numerical value, known as a hash value or hash code
          allows for efficient comparison and manipulation of strings by reducing them to a fixed-size integer representation
*/

#include <functional> // don't forget this 

unsigned int yourMapFunction(const std::string &hashMe)
{
   std::hash<std::string> str_hash; // creates a string hasher!
   unsigned int hashValue = str_hash(hashMe); // now hash our string!
   // returns a hash value between 0 and 4 billion
   // then just add your own modulo
   unsigned int bucketNum = hashValue % NUM_BUCKETS; // finally, apply own modulo function and return a bucket # that fits into your hash table's array
   return bucketNum;
}
/*
Writing Your Own Hash Function
  but what if you need to write a hash function for some non-standard data type? 
    i.e. hashing geospatial coordinates, the array of N numbers, the contents of a data file
  best bet is to convert your data into a string, then use the same hash function as before with <functional> and str_hash
  ex. for a Circle object, concatenate its x and y coordinates and radius into a string, then hash that
Choosing a Hash Function: Tips
  1. the hash function must always give us the same output value for a given input value: 
    Today: hash("abc") --> 83948
    Tomorrow: hash("abc") --> still 83984
  2. the hash function should disperse items throughout the hash array as randomly as possible
    hash("abc") = 294
    hash("cba") = 294 (not good!)
  3. when coming up with a new hash function, always measure how well it disperses items (do some experiments)
    want consistent distribution through, not skewed or bell curve in any way (flat) 
At this point, we've created a fully functional hash table where
  we decide where to add items by hashing them to get an integer
  then using modulo to compute a bucket number
  only thing left is to figure out how a traversal works
    can we just loop through all the buckets, and traverse each bucket's nonempty linked list one-by-one?
    assume B buckets holding a total of N values
    O(N + B)
    Student ID Tracker
      and while we have to set extra pointers during insertion/deletion, they're still just O(1) operations!
      now you can traverse in O(N) time by going through the linked list
Now, we have an efficient traversal for our hash table 
  but there's no guarantee that the items will be in order like with a BST
  question: is there a way to update the data structure to enable an efficient in-order traversal
    i.e. is there a way to update the data structure to enable an O(N) ordered traversal of its values?
  nope! this is a big downside with hash tables. You get O(1) operations for insertion/seaching/deletion and O(N + B) for traversal, but no ordering like with trees
Ordered Data Containers vs. Hash Table Summary
  Having data ordered is better than a hash table when operations require a specific sequence
    range queries
    finding minimum/maximum values
    processing data sequentially
  Hash tables store elements in an arbitrary, non-sequential order based on hash values, making these operations inefficient. 
    in fact, if you want to expand your hash table's size you basically have you create a new one
      1. allocate a whole new array with more buckets
      2. rehash every value from the original table into the new table
      3. free the original table
  table of comparisons --> https://discord.com/channels/633096463139864606/1010791176250609757/1443066200417501236
The unordered_map: A hash-based version of a map
  you can use unordered_map with user-defined types
  a functor is a class/struct which has a single member function of operator()
    the function accepts the custom type as a parameter
*/
#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;	

int main( )
{
   unordered_map <string,int> hm;		  // define a new U_M
   unordered_map <string,int>::iterator iter; // define an iterator for a U_M


   hm["Carey"] = 10;			// insert a new item into the U_M
   hm["David"] = 20;

   iter = hm.find("Carey");			// find Carey in the hash map

   if (iter == hm.end())			// did we find Carey or not?
       cout << “Carey was not found!”;	// couldn’t find “Carey” in the hash map
   else 
   {
        cout << "When we look up " << iter->first;	// “When we look up Carey”
        cout << " we find " << iter->second;		// “we find 10”
   }
}

// another example

struct Point {
  int x, y;
};

// Step #1: Define an operator== for your custom type 
bool operator==(const Point &a, const Point &b)   
  { return a.x == b.x && a.y == b.y; }
 

// Step #2: Define a "functor" to compute a hash value
struct PointFunctor {   
  size_t operator()(const Point &p) const { // size_t is unsigned int
    string s = to_string(p.x) + "," + to_string(p.y);
    return std::hash<string>()(s);    
  }
};
int main() {
  unordered_map<Point, string, PointFunctor> m;

  Point p1(1, 2);
   
  m[p1] = "That point's at 1,2";  // works now!
}
/*
Tables (the big picture)
  the table is an ADT that stores a bunch of record and then provides multiple ways to search for them 
  for example, search students by phone number, full name, and/or student ID
  a simple ADT like a hash table or BST only enables searching efficiently by a single field type
  in a table ADT you store the full record (name, phone number, student, ID, GPA) just once
  then create multiple light "indexed" (i.e. using BSTs/hash tables) to speed up searching by different field types
  uses: bank databases, medical records, my.ucla grades, DMV records, FBI dossier, map segments in google maps, etc.
  ex. say you want to write a program to keep track of all your friends
    of course, you want to remember all the important dirt about each BFF
    and you want to quickly be able to search for a BFF in one or more ways (by name, phone number, birthday, phone type, social security number, favorite food....) 
  in CS lingo, a group of related data is called a "record" 
  each record has many "fields" 
  if we have many records, we call this a "table"!
  while you may have records with the same Name field value, or the same Birthday field value...
    some fields, like social security number will have unique values across all records - this type of field is useful for searching and finding a unique record!
Implementing Tables
  how could you create a record in C++? 
    use a struct or class to represent a record of data!
  how could you create a table in C++? 
    create an array or vector of your struct/class!
*/
struct Student{
  string name;
  int IDNum;
  float GPA;
  string phone;
};
vector<Student> table;
// algorithm to search by the name field
int searchByName(vector<Student> &table, string &findName){
  for(int s = 0; s < table.size(); s++){
    if(findName == table[s].name) return s; // the student you're looking for is in slot s
  }
  return -1; 
}
// algorithm to search by the phone field
int searchByPhone(vector<Student> &table, string &findPhone){
  for(int s = 0; s < table.size(); s++){
    if(findPhone == table[s].phone) return s;
  }
  return -1;
}
/*
Implementing Tables II
  heck, why not just create a whole C++ class for our table? 
*/
class TableOfStudents
{
public:
    TableOfStudents();      // construct a new table

    ~TableOfStudents();	 // destruct our table

    void addStudent(Student &stud);  // add a new Student

    Student getStudent(int s);   // retrieve Students from slot s

    int searchByName(string &name);  // name is a searchable field

    int searchByPhone(int phone);  // phone is a searchable field
    …
private:

    vector<Student> m_students;
};
/*
  in the TableOfStudents class, we used a vector to hold out table and a linear search to find Students by their name or phone
  perfectly valid table, but slow to find a student! let's make it more efficient
  we could alphabetically sort our vector of records by their names
    then we could use a binary search to quickly locate a record based on a person's name
  but then every time we add a new record, we have to re-sort the whole table!
  and if we sort by name, we can't search efficiently by other fields like phone# or ID#!
  what is we stored our records in BST (i.e. a map) organized by name? would that work? 
    now you can search the table efficiently, but we still can't search efficiently by ID or phone!
  what if we create two tables, ordering the first by name and the second by ID#? 
    but then you would have two copies of every record for both trees (huge waste of space)
Making an Efficient Table
  1. still use a vector to store our records 
  2. also add a data structure to associate each person's name with their slot # in the vector
  3. we can add another data structure to associate each person's ID with their slot number too
*/
class TableOfStudents
{
public:
    TableOfStudents();      

    ~TableOfStudents();	

    void addStudent(Student &stud);  

    Student getStudent(int s);   

    int searchByName(string &name);  

    int searchByPhone(int phone);  

private:
  vector<Student> m_students; // stores the student accounts
  // these secondary data structuers are called "indexes" 
    // each index lets us efficiently find a record based on a particular field 
    // may have as many indexes as we need for our application
  map<string, int> m_nameToSlot; // lets us quickly look up a name and find out which slot in the vector holds the related record 
  map<int, int> m_idToSlot; // lets us quickly look up an ID and find out which slot in the vector holds the related 
  map<int, int> m_phoneToSlot; 
};			     
// what does our addStudent method look like now? 
void addStudent(Student &stud){
  m_students.push_back(stud);
  int slot = m_student.size() - 1 // get slot # of new record
  m_nameToSlot[stud.name] = slot; // maps name to slot #
  m_idToSlot[stud.IDNum] = slot; // maps ID to slot #
}
/*
Complex Tables
  so to review, what do we have to do to insert a new record into our table? 
    remember, any time you delete a record or update a record's searchable fields, you also have to update indexes!
Tables
  as it turns out, databases like "Oracle" use exactly this approach to store and index data
  (the only difference is that they usually store their data on disk rather than memory)
  by the way, while the example used BSTs to index our table's fields...
    you could use any efficient data structure you like!
    like a hash table!
Using Hashing to Speed Up Table
  we can use hash tables to index our data instead of binary search trees
  then you can have O(1) searches by name!
  how should we decide to use BST or hash table for an index? 
    BST --> print things in order or perform "range queries" 
    hash table --> O(1) random searching, insertion, deletion
*/ 




