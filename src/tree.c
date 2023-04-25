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

  return newNode;
}

struct Tree *createTree() {
  struct Tree *newTree = malloc(sizeof(struct Tree));

  if (!newTree) {
    printf("Error when creating tree");
    exit(1);
  }

  newTree->root = NULL;

  return newTree;
}

void auxInsertTree(struct Node *root, int value) {
  if (root->value > value) {
    if (!root->left) {
      struct Node *node = createNode(value);
      root->left = node;
      node->parent = root;

      return;
    }

    auxInsertTree(root->left, value);
  } else {
    if (!root->right) {
      struct Node *node = createNode(value);
      root->right = node;
      node->parent = root;

      return;
    }

    auxInsertTree(root->right, value);
  }
}

void treeInsert(struct Tree *tree, int value) {
  if (!tree->root) {
    struct Node *node = createNode(value);

    tree->root = node;

    return;
  }

  auxInsertTree(tree->root, value);
}

void printTree(struct Node *root, int depth) {
  if (!root) {
    return;
  }

  printTree(root->right, depth + 1);

  for (int i = 0; i < depth; i++) {
    if (depth - 1 == i)
      printf("    +");
    else
      printf("    ");
  }
  printf("---%d\n", root->value);

  printTree(root->left, depth + 1);
}
