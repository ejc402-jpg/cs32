// Sorting Algorithms II (Quicksort, Mergesort), Trees

/*
Quicksort and Mergesort are efficient "divide and conquer" sorting algorithms
  1. divide the elements to be sorted into two groups of roughly equal size
  2. sort each of these smaller groups of elements (conquer) using recursion
  3. combine the two sorted groups into one large sorted group  
  O(N*log2(N)) steps
Quicksort
  1. if the array contains only 0 or 1 element, return
  2. select an arbitrary element P from the array (typically the first element in the array)
  3. move all elements that are less than or equal to P to the left of the array and all elements greater than P to the right ("partitioning")
  4. recursively repeat this process on the left sub-array and then the right sub-array
    the partition function uses the first item as the pivot value and moves less-than-or-equal items to the left and larger ones to the right
    the return the pivot's index in the array to the QuickSort function
*/
int Partition(int a[], int low, int high)
{
  int pi = low;
  int pivot = a[low];  
  do
  {
     while ( low <= high && a[low] <= pivot )
        low++;
     while ( a[high] > pivot )
        high--;
     if ( low < high )
        swap(a[low], a[high]);
  }
  while ( low < high );
  swap(a[pi], a[high]);
  pi = high;
  return(pi); 
}

void QuickSort(int Array[],int First,int Last)
{
  if (Last – First >= 1 )
  {
    int PivotIndex;


    PivotIndex = Partition(Array,First,Last);  
    QuickSort(Array,First,PivotIndex-1); // left 
    QuickSort(Array,PivotIndex+1,Last);  // right
  }
}
/*
  mostly sorted or reverse order input arrays make quicksort pretty slow
    in this case we go through maximum amount of sub-partitions, removing one item on the left or right each time
    O(n^2)
  quicksort is also not stable (>=) --> does not maintain the relative order of records with equal keys/values
  space complexity of quicksort is proportional to the depth of recursion
    usually O(log n), for pre-sorted arrays it's O(n)
Mergesort
  basic version takes two pre-sorted arrays as inputs and outputs a combine, third sorted array
  ex. bookshelf analogy
    1. Consider the left-most book in both shelves
    2. Take the smallest of the two books
    3. Add it to the new shelf
    4. Repeat the whole process until all books are moved
*/
void merge(int data[], int n1, int n2,
           int temp[]) // input array called data and the sizes of the two parts of it to merge
{
  int i1=0, i2=0, k=0;
  int *A1 = data, *A2 = data + n1;
	
  while (i1 < n1 || i2 < n2)
  {
    if (i1 == n1)
	temp[k++] = A2[i2++]; // temp is a temporary array of size n1+n2 that holds the merged results as we loop
    else if (i2 == n2)
	temp[k++] = A1[i1++];
    else if (data[i1] <= A2[i2])
	temp[k++] = A1[i1++];
    else
	temp[k++] = A2[i2++];
  }
  for (int i=0;i<n1+n2;i++)
    data[i] = temp[i]; // copy our merged results back to the data array
}
/*
  full algorithm
    1. if array has one element, then return (it is sorted)
    2. split up the array into equal sections
    3. recursively call mergesort function on the left half
    4. recursively call mergesort function on the right half
    5. merge the two halves using our merge function
  note: the full algorithm sorts the data in-place in the array and uses a separate array for merging
  mergesort usually has good performance regardless of input data
  O(n) space because it allocates an array of size N for merging
  mergesort is preferred when processing extremely large datasets that don't fit into RAM on a single server
    because it can be divided into multiple chunks that can fit
    then a computer reads only top and bottom values 
Sorting Algorithms Overview
  https://discord.com/channels/633096463139864606/1010791176250609757/1438027459470688376
Sorting Algorithms Visualized 
  https://www.youtube.com/watch?v=kPRA0W1kECg
Trees
  a tree is a data structure that stores values in a hierarchical fashion
  we often use linked lists to build trees
    two "next" pointers, one for left and one for right
  good alternative to linked lists and arrays when you need more organization in data
  makes information easily searchable
  simplify the evaluation of mathematical expressions
  make decisions
  facts about trees
    1. made of nodes 
    2. has a "root" pointer that is like the head of the linked list
    3. top node is the "root" node 
    4. every node may have zero or more "children" nodes
    5. a node with 0 children is called "leaf" node (those that do are "parent"/"internal" nodes) 
    6. tree with no nodes is called "empty tree"
  trees can have many children (at most two for binary trees) 
*/
struct node{
  int value;
  node *pchild1, *pchild2, *pchild3, ....;
};
struct node{
  int value; 
  node* pChildren[26];
};
/*
Binary Trees
  at most two children nodes per node --> left/right children
  either two or none = full binary tree
*/
struct BYNODE{
  string value; 
  BYNODE *pleft, *pright;
};
main()
{
   BTNODE *temp, *pRoot;

   pRoot = new BTNODE;
   pRoot->value = 5;

   temp = new BTNODE;
   temp->value = 7;
   temp->left = NULL;
   temp->right = NULL;
   pRoot->left = temp;

    temp = new BTNODE;
   temp->value = -3;
   temp->left = NULL;
   temp->right = NULL;
   pRoot->right = temp;
   // etc…
/*
  Binary Tree Subtrees
    could pick any node in the tree and then focus on its subtree which includes all nodes below it
    each node has left and right subtrees
  Operations
    enumerating all the items
    searching for an item
    adding a new item at a certain position on the tree
    deleting an item
    deleting the entire tree (destruction) 
    removing a whole section of a tree (called pruning) 
    adding a whole section to a tree (called grafting) 
      in the above code, we created a binary tree with three nodes, but now what?
      later, we'll learn how to use the binary tree to speed up searching for data
      for now, learn how to iterate through each item in a tree, one at a time
        "traversing" 
  Binary Tree Traversals
    all start at the root node (like head of the linked list)
    four common ways 
      1. pre-order traversal
      2. in-order traversal
      3. post-order traversal
        all of these above use recursion and are identical algorithms
        difference in placement of the processing steps
      4. level-order traversal
        BFS to visit nodes
*/
void preorder(Node *p) // Node, Left, Right
{
  if (p == nullptr) 
    return;
  cout << p->value;
  preorder(p->left);
  preorder(p->right);
}
void postorder(Node *p) // Left, Right, Node
{
  if (p == nullptr) 
    return;
  postorder(p->left);
  postorder(p->right);
  cout << p->value;
}
void inorder(Node *p) // Left, Node, Right
{
  if (p == nullptr) 
    return;
  inorder(p->left);
  cout << p->value;
  inorder(p->right);
}



