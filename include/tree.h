#ifndef TREE_H
#define TREE_H

struct Node {
  int value;
  int height;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
};

void treeInsert(struct Node **root, int value);

void treeDelete(struct Node **root, int value);

void printInOrder(struct Node *root, int depth);

void freeTree(struct Node *root);

void printTree(struct Node *root, int depth);

#endif
