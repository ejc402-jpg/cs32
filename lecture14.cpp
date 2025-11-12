// Binary Tree Traversals, Binary Search Trees, Binary Search Trees Operations
  // search for an item, inserting a new item, finding the minimum and maximum items, printing out the items in order, deleting the whole tree

/*
Remembering Pre/In/Post Traversals
  pre --> Node Left Right
  in --> Left Node Right
  post --> Left Right Node
Level Order Traversal
  does not recursion
  uses a queue and processes the nodes of our tree much like we did with our maze search (BFS)
  1. use a temp pointer variable and a queue of node pointers
  2. insert the root node pointer into the queue
  3. while the queue is not empty:
    a. dequeue the top node pointer and put it in temp
    b. process the node
    c. add the node's children to the queue if they are not nullptr
  start at the top/root node and identify the levels of children nodes that follow to determine the order of nodes visited in a level-order traversal
    process nodes by row until you reach all leaves
Time Complexities of Binary Tree Traversals
  each node requires their operations
    process the node, process left, process right
    3n --> O(n)
Traversal Use Case: Expression Evaluation (post-order traversal) 
  one use for trees is representing arithmetic expressions
  https://discord.com/channels/633096463139864606/1010791176250609757/1438278497733836991
  1. if the current node is a number, return its value
  2. recursively evaluate the left subtree and get the result
  3. recursively evaluate the right subtree and get the result
  4. apply the operator in the current node to the left and right results; return result
*/
int eval(Node *p) {
  if (p->type == VALUE)
    return p->value;
   
  int left  = eval(p->left);
  int right = eval(p->right);
  return apply(p->operator,
                left, right);
}

// Tree Challenges

// Fill in the blanks to create a function called int tree_sum(Node *root) which sums up a tree's values.

struct Node {
  int val;
  Node *left, *right;
};
int tree_sum(Node *root) {
  if (root == nullptr) return 0;

  int sum = root->val;
  sum += tree_sum(root->left);
  sum += tree_sum(root->right);

  return sum;
}

// Fill in the blanks to create a function called int shallowest_even(Node *root) that finds the depth of the shallowest even number in a tree of at most 100 levels deep. if there are no even numbers return 100

int shallowest_even(Node *root) {
  if (root == nullptr) return 100;
  if (root->val % 2 == 0) return 0;
  int d1 = shallowest_even(root->left);
  int d2 = shallowest_even(root->right);
  if (d1 == 100 && d2 == 100) 
    return 100;
  return min(d1, d2) + 1;
}
/*
Binary Search Trees Big Picture
  is a specialized type of binary tree
  enables fast (log2N) searches by ordering its data in a special way
  for every node j in the tree, all children (subtree) to j's left must be less than it, and all children (subtree) to j's right must be greater than it (alphabetized data)
    https://discord.com/channels/633096463139864606/1010791176250609757/1438283472987754497
  to see if a value V is in the tree,
    1. start at the root node
    2. compare V against the node, moving down left or right is V is less or greater
    3. repeat until you find V or hit a dead end
Binary Search Trees Operations
  1. determine if the binary search tree is empty
  2. search the binary search tree for a value
    input: a value V to search for
    output: TRUE if found, FALSE otherwise
      start at the root of the tree
      keep going until we hit the null pointer
        if V is equal to the current node's value, then found
        if less, go left
        if greater, go right
        if nullptr, not found
    two different Binary Search Tree search algorithms (one iterative, one recursive)
      log2N steps (worst case N steps) 
*/
bool Search(int v, Node *root)
{ 
  Node *ptr = root;
  while (ptr != nullptr)
  { 
    if (v == ptr->value) 
      return true;
    else if (v < ptr->value)
      ptr = ptr->left;
    else
      ptr = ptr->right;
  }
  return false; // nope
}
bool Search(int v, Node *root)
{  
  if (root == nullptr) 
    return false;  // nope
  else if (v == root->value)
    return true;  // found!!!
  else if (v < root->value)
    return Search(V,root->left);
  else  
    return Search(V,root->right);
}
/*
  3. insert an item in the binary search tree
    when doing this, must place the new node so that the resulting tree is still a valid BST!
    input: value V to insert
    if tree is empty:
      allocate a new node and put V into it
      point the root pointer to our new node. DONE
    start at the root of the tree
    while not done:
      if V is equal to the current node's value, DONE
      if V is less than current node's value:
        if left child, then go left
        else, allocate a new node and put V into it and set current node's left pointer to the new node, DONE
      if V is greater than current node's value
        if there is a right child, the go right
        else allocate a new node and put V into it and set current node's right pointer to new node, DONE
*/
struct Node
{
  Node(const std::string &myVal)
  {
     value = myVal;
     left = right = nullptr;
  }
  std::string   value;
  Node 	       *left,*right;
};
class BinarySearchTree
{
public: 
    BinarySearchTree()
    {
       m_root = nullptr;
    }

    void insert(const std::string &value)
    {
       …
    }
private:
    Node *m_root;
};
void insert(const std::string &value)
{
   if (m_root == nullptr)  
      {   m_root = new Node(value);   return; }

   Node *cur = m_root;
   for (;;)
     {
       if (value == cur->value)   return; 

       if (value < cur->value)  
          {
           if (cur->left != nullptr)      
               cur = cur->left;
           else
               {
               cur->left = new Node(value);
               return;
               }
           }
        else if (value > cur->value)
           {
            if (cur->right != nullptr)     
                cur = cur->right;
            else 
                {
                cur->right = new Node(value);
                return;
                 }
           }
      }
}
/*
    does the order in which you insert values into a tree impact the tree's structure?
      yes! 1234567 is 4261357
    O(log2n) because you need to do a binary search to find where to insert (O(1) insertion time for the node)
  4. delete an item from the binary search tree
  5. find the height of the binary search tree
  6. find the number of nodes and leaves in the binary search tree
  7. traverse the binary search tree
  8. free the memory used by the binary search tree
    post-order traversal
    O(n) --> need to process every node
*/
void FreeTree(Node *cur)
{
    if (cur == nullptr)  	  // if empty, return…
         return;

    FreeTree(cur->left);     // Delete nodes in left sub-tree.

     FreeTree (cur->right);  // Delete nodes in right sub-tree.

   delete cur;                   // Free the current node
}
/*
  9. finding the min and max of a BST
    the minimum is located at the left-most node
    the maximum is located at the right-most node
    O(log2n) --> go to the bottom of the tree
*/
int GetMin(Node *pRoot)
{
  if (pRoot == nullptr)
    return -1;  // empty

  while (pRoot->left != nullptr)
     pRoot = pRoot->left;

  return pRoot->value;
}
int GetMax(Node *pRoot)
{
  if (pRoot == nullptr)
    return -1;  // empty

  while (pRoot->right != nullptr)
     pRoot = pRoot->right;

  return pRoot->value;
}
// recursive solutions
int GetMin(Node *pRoot)
{
  if (pRoot == nullptr)
    return -1;  // empty

  if (pRoot->left == nullptr)
    return pRoot->value;

  return GetMin(pRoot->left);
}
int GetMax(Node *pRoot)
{
  if (pRoot == nullptr)
    return -1;  // empty

  if (pRoot->right == nullptr)
    return pRoot->value;

  return GetMax(pRoot->right);
}
/*
  10. printing BST in alphabetical
    in-order traversal
*/
void InOrder(Node *cur)
{
    if (cur == nullptr)  	  // if empty, return…
         return;

    InOrder(cur->left);     // Process nodes in left sub-tree.

    cout << cur->value;      // Process the current node.

    InOrder(cur->right);  // Process nodes in right sub-tree.
}






