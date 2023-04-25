#ifndef TREE_H
#define TREE_H

struct Node {
  int value;
  struct Node *parent;
  struct Node *left;
  struct Node *right;
};

struct Tree {
  struct Node *root;
};

struct Tree *createTree(void);

void treeInsert(struct Tree *Tree, int value);

void printTree(struct Node *root, int depth);

#endif
