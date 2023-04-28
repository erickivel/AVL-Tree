#include <stdio.h>
#include <stdlib.h>

#include "../include/tree.h"

struct Node *createNode(int value) {
  struct Node *newNode = malloc(sizeof(struct Node));

  if (!newNode) {
    printf("Error when creating tree");
    exit(1);
  }

  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  newNode->value = value;
  newNode->height = 0;

  return newNode;
}

struct Node *createTree() {
  struct Node *root = malloc(sizeof(struct Node));

  if (!root) {
    printf("Error when creating tree");
    exit(1);
  }

  root = NULL;

  return root;
}
void updateHeight(struct Node *root) {
  int leftHeight = root->left ? root->left->height : -1;
  int rightHeight = root->right ? root->right->height : -1;

  if (leftHeight > rightHeight)
    root->height = leftHeight + 1;
  else
    root->height = rightHeight + 1;
}

void treeInsert(struct Node **root, int value) {
  if (!*root) {
    struct Node *node = createNode(value);

    *root = node;

    return;
  }

  if ((*root)->value > value) {
    if (!(*root)->left) {
      struct Node *node = createNode(value);
      (*root)->left = node;
      node->parent = *root;
    } else {
      treeInsert(&(*root)->left, value);
    }
  } else {
    if (!(*root)->right) {
      struct Node *node = createNode(value);
      (*root)->right = node;
      node->parent = *root;
    } else {
      treeInsert(&(*root)->right, value);
    }
  }

  updateHeight(*root);
}

void printTree(struct Node *root, int depth) {
  if (!root) {
    return;
  }

  printTree(root->right, depth + 1);

  for (int i = 0; i < depth; i++) {
    if (depth - 1 == i)
      printf("     +");
    else
      printf("    ");
  }
  printf("---%d-%d\n", root->value, root->height);

  printTree(root->left, depth + 1);
}
