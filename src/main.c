#include "../include/tree.h"

int main(void) {
  struct Tree *tree = createTree();

  treeInsert(tree, 4);
  treeInsert(tree, 2);
  treeInsert(tree, 6);
  treeInsert(tree, 7);
  treeInsert(tree, 3);
  treeInsert(tree, 1);
  treeInsert(tree, 5);
  treeInsert(tree, 5);
  treeInsert(tree, 5);
  treeInsert(tree, 5);

  printTree(tree->root, 0);

  return 0;
}
