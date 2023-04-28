#include "../include/tree.h"

int main(void) {
  struct Node *root = createTree();

  treeInsert(&root, 4);
  treeInsert(&root, 2);
  treeInsert(&root, 6);
  treeInsert(&root, 7);
  treeInsert(&root, 3);
  treeInsert(&root, 1);
  treeInsert(&root, 5);
  treeInsert(&root, 5);
  treeInsert(&root, 5);
  treeInsert(&root, 5);

  printTree(root, 0);

  return 0;
}
