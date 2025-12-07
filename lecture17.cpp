// Priority Queues, Heap Sort

/*
Priority Queues
  special type of queue that allows us to keep a prioritized list of items
  each item you insert into the priority queue has a "rating" indicating how important it is 
  this determines the order of their queued position, NOT order of insertion!
  ex. emergency room (prioritize the most critical condition people, not the most recent or earliest, per se)
  supports three primary operations
    1. insert a new item into the queue
    2. peek at the value of the highest priority item 
    3. remove the highest priority item from the queue
  when you define a priority queue, you obviously need to specify how to determine the the priority of each item in the queue
    ex. priority = amount of bloos lost + number of cuts
    this is the challenge! design an efficient data structure for the priority queue!
  ex. let's assume we want to have a priority queue with three priority levels (high/medium/low)
    what data structure(s) should we use? 
      use three linked lists, one per priority level
    to dequeue: 
      if high-priority list isn't empty, dequeue from it
      if empty, go to next level and so on
      using pointers to point to the next element after dequeueing is smart, pointing to a next pointer that is null means the priority level is exhausted
  but what if we have a HUGE number of priorities?
    the HEAP data structure is one of the most efficient ways to implement priority queue
      heap data structure uses a special type of binary tree to hold its data
      but is NOT a binary search tree
The Heap ADT
  heap: tree-based data structure used to implement priority queues and do efficent sorting
  MUST be a complete binary tree
  two types of heaps:
    1. minheaps
      the smallest item is always at the tree's root
      the value in every node must be <= the values of that node's children
      every time you extract or add an item, you update the tree to maintain this property
      quickly insert a new item into the heap
      quickly extract the largest item into the heap
    2. maxheaps
      the largest item is at the root
      the value in every node must be >= the values of that node's children
      same deal when you add or extract an item, must maintain property
      quickly insert a new item into the heap
      quickly extract the smallest item from the heap
      note: by definition, the biggest (highest priority) item is always at the root, meaning it's O(1) time to find the highest priority item!
      extracting the biggest item
        1. if the tree is empty, return error
        2. otherwise, the top item in the tree is the biggest value. save this value
        3. if the heap has only one node, then delete it and return the saved value
        4. copy the value from the right-most node in the bottom-most row to the root node
        5. delete the right-most node in the bottom-most row
        6. repeatedly swap the just-moved value with the larger of its two children until the value is greater than or equal to both of its children ("sifting" down) 
        7. return the saved value to the user
      adding a value 
        1. if the tree is empty, create a new root node and return
        2. otherwise, insert the new node in the bottom-most, left-most open spot of the tree (so it's still a complete tree)
        3. compare the new value with its parent's value
        4. if the new value is greater than its parent's value, then swap them
        5. repeat steps 3-4 until the new value rises to its proper place ("reheapification")
  the heap is fast --> O(log2n) to keep the proper item at the top when you extract/insert items
  used for prioritize processing of data, find the shortest path for route navigation, sort arrays efficiently, merge streams of ordered data, etc.
  all heaps use a special type of "complete" binary tree
    the top N-1 levels of the tree are completely filled with nodes (all except for last row, but also could be anyway) 
    all nodes on the bottom-most level must be as far left as possible (with no empty slots between nodes) 
Implementing A Heap
  we could implement a head using classic binary tree nodes (value, left/right pointers)
    but this has some challenges
      1. it's not easy to locate the bottom-most, right-most node during extraction
      2. it's not easy to locate the bottom-most, left-most open sport to insert a new node during insertion
      3. it's not easy to locate a node's parent to do reheapification swaps
  array? 
    we know that each level of the tree has two times the number of nodes in the previous level (complete binary tree)
    we just copy our nodes a level at a time into an array (except for the last level)
    ex. int heap[1000];
      root node value in heap[0], then next two, then next four, etc. (level by level)
      use a simple int count variable to track how many items are in the heap
    there is no need to use a node-based tree if we have this array!
    some properties
      1. we can always find the root value in heap[0]
      2. we can always find the bottom-most, right-most node in heap[count-1]
      3. we can always find the bottom-most, left-most empty spot (to add new value) in heap[count]
      4. we can add or remove a node by simply setting heap[count] = value and/or updating our count!
    we need to figure out how to locate the left and right children of a node in the array
      ex. given a node in slot j, in what slos can we find j's child nodes? 
      leftChild(j) = 2 * j + 1
      rightChild(j) = 2 * j + 2
    finally, need to figure out how to locate the parent of a node in the array
      ex. given a node in slot k, give a function that returns the parent's slot # in the array
        parent(k) = (k-1)/2 (because of integer division, works whether it's left or right child of a parent node)
Heap-Array Summary
  1. root of heap = array[0]
  2. if the data for a node appears in array[i], its children, if they exist, are in these locations:
    left child: array[2i + 1]
    right child: array[2i + 2]
  3. if the data for a non-root node is in array[k], then its parent is always at array[(k-1)/2] (use integer divison)
Using Array to Implement a Heap
  first, use a simple array to implement a maxheap
  need the following operations:
    1. locate the root node of a tree
    2. locate (and delete) the bottom-most, right-most node in the tree
    3. add a new node in the bottom-most left-most empty position in the tree
    4. easily locate the parent and children of any node in the tree
  extracting from a maxheap (array version) 
    1. if the count == 0 (empty tree) return error
    2. otherwise, heap[0] holds the biggest value (save that value) 
    3. if the count == 1 (only node) then set count == 0 and return the saved value
    4. copy the value from the right-most, bottom-most node to the root node 
      heap[0] = heap[count-1]
    5. delete the right-most node in the bottom-most row; count = count - 1
    6. repeatedly swap the just-moved value with the larger of its two children
      starting with i = 0, compare and swap:
        heap[i] with heap[2*i+1] and heap[2*i+2]
    7. return the saved value to the user
  adding a node to the maxheap (array version) 
    1. insert a new node in the bottom-most, left-most open slot 
      heap[count] = value
      count += 1
    2. compare the new value in heap[count-1] with its parent's value: heap[((count-1)-1)/2]
    3. if the new value is greater than its parent's value, then swap them 
    4. repeat steps 2-3 until the new value rises to its proper place or we reach the top of the array
Complexity of the Heap 
  what is the Big-O cost of inserting a new item into a heap? 
    every time you insert a new item, keep comparing it with its parent until it reaches the right spot
    since our tree is a COMPLETE binary tree, if it has N entries, it's guaranteed to be exactly log2(N) levels deep!
    worst case: log2(N) comparisons and swaps of our new value (true whether or not our heap is stored in an array!)
  what is the Big-O cost of extracting the maximum/minimum item from a heap? 
    just as with heap insertion, when we extract a value we need to bubble an item from the root down the tree
    since the maximum levels in our tree is log2(N), the worst case that this requires log2(N) swaps
    O(log2(N))
Heapsort
  O(n*log2(n)) sort that uses a maxheap in a super clever way to sort a bunch of values
  used in job interviews 9 :(
The Naive Heapsort
  ex. given an array of randomly-ordered values, how could we use a heap to sort those values? 
    1. insert all N numbers into a new maxheap 
    2. while there are numbers left in the heap:  
      a. remove the biggest value from the heap
      b. place it in the last open slot of the array
  while that works, it's not the official heapsort algorithm
  Big-O of our naive heapsort, assuming N numbers is 2 * Nlog2(N) total steps, or O(Nlog2(N))
    insertion: N items * log2(N) steps per item
    extractoins: N items * log2(N) steps per item
    not bad, but there's an even faster way to use a heap to sort an array
The Efficient Heapsort
  in naive algorithm, we took every item from the array and inserted it into a separate maxheap
  then we had to remove each value from our new heap and stick it back into our original array
    SLOW!
  we can avoid creating a whole new maxheap and moving numbers back and forth
The Efficient (Official) Heapsort
  1. convert your randomly-arranged input array into a maxheap by cleverly shuffling around the values in the array
    for(curNode = lastNode through rootNode){
      a. focus on the subtree rooted at curNode
      b. think of this subtree as a maxheap
      c. keep shifting the top value down until your subtree becomes a valid maxheap
    }
    this algorithm basically builds mini maxheaps (heapify) from the leaves up until the whole thing is a maxheap
      once you heapify the root node, you are done? 
    by last node, we mean the bottom-most, right-most node in the tree (last element in the array) 
    note: visually explained using binary tree, but this function applies on the input array
    there is one more thing to consider
      if you noticed, we wasted a bunch of time looking at single-node sub-trees
      but if you only had to reheapify once we reached a sub-tree with at least two nodes...
      wouldn't it be great if we could jump straight to this node to save time? 
        we can!
    update the shuffling algorithm slightly
    for(curNode = lastNode through rootNode){
      a. focus on the startNode of curNode
        startNode = N/2 - 1
      b. think of this subtree as a maxheap
      c. keep shifting the top value down until your subtree becomes a valid maxheap
    }
  2. identical to naive heapsort algorithm
    while there are numbers left in the heap:
      1. extract the biggest value from the maxheap and re-heapify (recall the algorithm)
        this frees up the last slot in the array
      2. now put the extracted value into this freed-up slot of the array
Big-O of Heapsort
  step 1 has Big-O of O(N) --> can convert random array into maxheap in O(N) steps
  step 2 has Big-O of O(Nlog2(N)) --> extract N items, each item reheapification is log2(N)
*/
