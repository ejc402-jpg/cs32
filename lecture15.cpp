// Binary Trees cont. --> BST Node Deletion, BST use cases, Huffman Encoding, Balanced Trees

// example is not a valid BST because Max comes before Mel

/*
Deleting a Node from a Binary Search Tree
  by simply moving an arbitrary value into Darren's slot, we violate our Binary Search Trees ordering requirement!
  when switching nodes by deleting the old and inserting the new one, the tree's structure may change drastically
  here is a high level algorithm to delete a node from a BST
    given a value V to delete from the tree:
      1. find the value V in the tree, with a slightly modified BST search
        use two pointers: a cur pointer & a parent pointer
      2. if the node was found, delete it from the tree, making sure to preserve its ordering!
        there are three cases, be careful!
          case a) the node is a leaf
            sub-case 1) the target node is NOT the root node
              unlink the parent node from the target node (cur) by setting the parent's appropriate link to nullptr (parent->right or parent->left = nullptr depending on which side it's on)
              then delete the target (cur) node
            sub-case 2) the target node is the root node
              set the root pointer to nullptr
              then delete the target (cur) node
          case b) the node has one child
            sub-case 1) the target node is NOT the root node 
              relink the parent node to the target (cur) node's only child 
              then delete the target (cur) node 
            sub-case 2) the target node is the root node
              relink the root pointer to the target (cur) node's only child 
              then delete the target (cur) node
          case c) the node has two children (hard!) 
            we need to find a replacement for our target node that still leaves the BST consistent
            we can't just pick some arbitrary node and move it up into the vacated spot!
            need to be very careful!
            to delete a node that has two children... 
              we don't actually delete the node itself!
              instead, we replace its value with one from another node!
            we want to replace the target node with either...
              1. the target node's left subtree's largest-valued child
              2. the target node's right subtree's smallest-valued child
                so pick one, copy its value up, then delete that node! --> use the above two cases to delete the replacement node position
                both are valid, since the replacement node is guaranteed to have zero or at most one child!
                BST structure is preserved if you do it right
              
    the algorithm is similar to traditional BST search but this time we have a parent node pointer
      this parent node is pointing to the node that is directly above (the parent) to the node we want to delete
*/

// algorithm for searching for target node

parent = nullptr;
cur = root; 
while(cur){
  if(V == cur->value) // then we're done
  if(V < cur->value){
    parent = cur; 
    cur = cur->left;
  }
  else if(V > cur->value){
    parent = cur;
    cur = cur->right;
  }
}

/*
Where are BST's used? 
  STL map uses a BST to store key-value pairs based on keys and also uses BST to search key lookups!
  STL set also uses BST (a special balanced kind) to enable fast searching
  multiset, multimap, etc... (these containers can have duplicate mappings unlike set and map) 
Huffman Encoding: Applying Trees to Real-World Problems 
  Huffman Encoding is a data compression technique that can be used to compress and dcompress files  (i.e. creating ZIP files)
  before we get into this, need to learn a few things
    recall ASCII code
      computer represent letters, punctuation and digit symbols using the ASCII code, storing each character as a number
      when you type a character on the keyboard, it's converted into a number and stored in the computer's memory!
    Computer Memory and Files
      similarly, when you write data out to a file, it's stored as ASCII numbers too!
    Bytes and Bits
      but, the computer actually stores all numbers as 1's and 0's (binary) instead of decimal...
      each character is represented by 8 bits where each bit can either have a value of 0 or 1
        1 = high voltage, 0 = low voltage
    Binary and Decimal
      every decimal number has an equivalent binary representation and vice versa
    Consider a Data File
      containing the the data: "I AM SAM MAM."
      as we learned, the data actually stored in the data file is: 73 32 65 77 32 83 65 77 32 77 65 77 46
      and in reality, it's REALLY stored in the computer as a set of 104 binary digits (bits) 
        not writing it out but you can imagine series of binary representations of those numbers listed above
      question: can we somehow reduce the number of bits required to store our data? YES!
  Huffman Encoding 
    to compress a file "file.dat" with Huffman encoding, we use the following steps
      1. compute the frequency of each character in file.dat
        i.e. compute a histogram 
        for "I AM SAM MAM", 'A' 3, 'I' 1, 'M' 4, 'S' 1, Space 3, Period 1
      2. build a Huffman tree (a binary tree) based on these frequencies
        create a binary tree leaf node for each entry in our table, but don't insert any of these into a tree!
        while we have more than one node left: 
          a. find the two nodes with the lowest freqs
          b. create a new parent node
          c. link the parent to each of the children
          d. set the parent's total frequency equal to the sum of it's children's frequencies 
          e. place the new parent node in our grouping
          (see lecture notes for visualization) --> https://discord.com/channels/633096463139864606/1010791176250609757/1443016576180813924
        now label each left edge with a "0" and each right edge with a "1" 
        now we can determine the new bit-encoding for each character 
        the bit encoding for a character is the path of 0's and 1's that you take from the root of the tree to the chaarcter of interest
          for example, S is encoded as 0001, A is encoded as 10, M is encoded as 01, etc...
          (see lecture notes) --> https://discord.com/channels/633096463139864606/1010791176250609757/1443016576180813924
        you will notice that characters that occurred more often have shorted big-encodings because they are closer to the root node
      3. use this binary tree to convert the original file's contents to a more compressed form
        i.e. find a sequence of bits (1s and 0s) for each char in the message
        in our example, I AM SAM MAM is 0011110011100011001110110010000
      4. save the converted (compressed) data to a file
        originalfile.dat was series of ASCII binary code values (104 bits) 
        but compressed.dat is less than four bytes or 31 bits long! --> saved 69%
    okay, but we cheated a bit... 
      if all we have is 31 bits of data, it's impossible to interpret the file!
      did 000 equal "I" or did 000 equal "Q"? Or is it actually 00 for "A"? 
      so, we must add some additional data to the top of our compressed file to specify the encoding we used
      clearly this adds some overhead to our file but there are savings anyway
  Decoding
    1. extract the encoding scheme from the compressed file
    2. build a Huffman tree (a binary tree) based on the encodings 
    3. use this binary tree to convert the compressed file's contents back to the original characters
    4. save the converted (uncompresed data to a file) 
      when you hit a leaf node, output ch and start again from the root!
Balanced Search Trees
  question: what if we insert the following values into a binary search tree? 
  [imagine some skewed values] we can an unabalanced tree!
  question: what is the Big-O cost of searching for a value in this tree? O(n) terrible!
  unfortunatly, this is a common occurrence in real life applications
  it would be nice if we could come up with an improved BST ADT that always maintains its balance
    make insertions, searches, and deletions O(log n) 
  well we did! invented 2-3 Trees, Red-Black Trees, and AVL Trees
    these BST variations work (mostly) like a regular binary search tree
    but every time you add/delete a value, they automatically shift the nodes around so the tree is balanced 
      for example, AVL Tree tracks the height of ALL subtrees in the BST
        after an insertion/deletion, if the height of the subtrees under any node is different by more than one level...
        then the AVL algorithm shifts the nodes around to maintain balance
          looks complex, it only take O(log n) time!
          just a little bit more work
  you don't need to know details about these balanced BST's for finals or projects
  but know that O(log n) time for insertion or deletion
  when in interview: confirm if the BST is balanced or not!
*/
