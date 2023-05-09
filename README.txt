Main Data Structure
  The tree is made of the Node struct which has value (int), height (int), parent node, left node, and right node.

Main Algorithms

- Tree insertion
  To insert a new node, a binary search (recursively) finds where the new node should be in the leaves (as it's done with BST),
  then it's inserted. If the node provided is NULL, that means it's the root so the function just creates a new node
  and set it as the root. After the node is inserted the recursion goes back on the path that it came updating the height of the nodes
  and balancing it if necessary (abs(balance factor) > 1).

- Tree deletion
  To delete a node, a binary search (recursively) finds where the new node is (as it's done with BST),
  then replace it with its predecessor and frees this node. If the node found has only one node it's replaced by it,
  otherwise if it has no children the node is set as NULL and freed.
  After the node is replaced the recursion goes back on the path that it came 
  updating the height of the nodes and balancing it if necessary (abs(balance factor) > 1).

- Balance Tree

- Update Height:
  This function receives a node (the root of a subtree) and updates its height by 
  setting it as the greatest height between its two children + 1;

- Balance Factor:
  This function receives a node (the root of a subtree) and returns its right child height 
  subtracted from its left child height, if a child is NULL its height is set as -1.

- Tree Max:
  This function receives a node (the root of a subtree) and returns the node with the highest
  value of its branch by recursively getting the right node of the previous until it's NULL,
  then it returns the last one.

