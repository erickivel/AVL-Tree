#ifndef TREE_H
#define TREE_H

struct Node {
  int value;
  int height;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
};

struct Node *createTree(void);

void treeInsert(struct Node **root, int value);

void printTree(struct Node *root, int depth);

#endif
