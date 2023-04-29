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

int balanceFactor(struct Node *root) {
  int leftHeight = root->left ? root->left->height : -1;
  int rightHeight = root->right ? root->right->height : -1;

  return leftHeight - rightHeight;
}

void balanceTree(int balanceFactorNum, struct Node **root) {
  // RR
  if (balanceFactorNum < 0 && balanceFactor((*root)->right) <= 0) {
    printf("Right Right\n");

    struct Node *x = *root;
    struct Node *y = x->right;
    x->right = y->left;
    y->left = x;

    // Update x parent
    if (x->parent) {
      if (x->parent->right == x) {
        x->parent->right = y;
      } else if (x->parent->left == x) {
        x->parent->left = y;
      }
    }

    y->parent = x->parent;
    x->parent = y;

    *root = y;

    updateHeight(x);
    updateHeight(y);
    return;
  }

  // LL
  if (balanceFactorNum > 0 && balanceFactor((*root)->left) >= 0) {
    printf("Left Left\n");

    struct Node *x = *root;
    struct Node *y = x->left;
    x->left = y->right;
    y->right = x;

    // Update x parent
    if (x->parent) {
      if (x->parent->right == x) {
        x->parent->right = y;
      } else if (x->parent->left == x) {
        x->parent->left = y;
      }
    }

    y->parent = x->parent;
    x->parent = y;

    *root = y;

    updateHeight(x);
    updateHeight(y);
    return;
  }

  // RL
  if (balanceFactorNum < 0 && balanceFactor((*root)->right) > 0) {
    printf("Right Left\n");

    struct Node *x = *root;
    struct Node *z = x->right;
    struct Node *y = z->left;

    x->right = y->left;
    z->left = y->right;
    z->parent = y;
    y->left = x;
    y->right = z;

    // Update x parent
    if (x->parent) {
      if (x->parent->right == x) {
        x->parent->right = y;
      } else if (x->parent->left == x) {
        x->parent->left = y;
      }
    }

    y->parent = x->parent;
    x->parent = y;

    *root = y;

    updateHeight(x);
    updateHeight(z);
    updateHeight(y);
    return;
  }

  // LR
  if (balanceFactorNum > 0 && balanceFactor((*root)->left) < 0) {
    printf("Left Right\n");

    struct Node *x = *root;
    struct Node *z = x->left;
    struct Node *y = z->right;

    x->left = y->right;
    z->right = y->left;
    z->parent = y;
    y->right = x;
    y->left = z;

    if (x->parent) {
      // Update x parent
      if (x->parent->right == x) {
        x->parent->right = y;
      } else if (x->parent->left == x) {
        x->parent->left = y;
      }
    }

    y->parent = x->parent;
    x->parent = y;

    *root = y;

    updateHeight(x);
    updateHeight(z);
    updateHeight(y);
    return;
  }
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

  int balanceFactorNum = balanceFactor(*root);

  if (abs(balanceFactorNum) > 1) {
    balanceTree(balanceFactorNum, root);
  }
}

struct Node *treeMax(struct Node *root) {
  if (!root->right)
    return root;

  return treeMax(root->right);
}

void treeDelete(struct Node **root, int value) {
  if (!*root) {
    return;
  }

  if ((*root)->value == value) {
    // Remove
    struct Node *antecessor;

    if ((*root)->left) {
      antecessor = treeMax((*root)->left);
    } else if ((*root)->parent->right == *root) {
      antecessor = treeMax((*root)->parent->left);
    } else {
      antecessor = treeMax((*root)->parent->parent->left);
    }

    printf("Antecessor: %d\n", antecessor->value);
    printf("Antecessor parent: %d\n", antecessor->parent->value);

    // // Point antecessor parent to null
    // if (antecessor->parent->right == antecessor) {
    //   antecessor->parent->right = NULL;
    // } else
    //   antecessor->parent->left = NULL;

    // if ((*root)->left != antecessor) {
    //   antecessor->left = (*root)->left;
    // }
    // antecessor->right = (*root)->right;

    // // Point root parent to antecessor
    // antecessor->parent = (*root)->parent;
    // if ((*root)->parent) {
    //   if ((*root)->parent->left == *root) {
    //     (*root)->parent->left = antecessor;
    //   } else if ((*root)->parent->right == *root) {
    //     (*root)->parent->right = antecessor;
    //   }
    // }

    // *root = antecessor;
  } else if ((*root)->value > value) {
    treeDelete(&(*root)->left, value);
  } else {
    treeDelete(&(*root)->right, value);
  }

  updateHeight(*root);

  // printf("=====\n");
  // printTree(*root, 0);
  // printf("=====\n");

  int balanceFactorNum = balanceFactor(*root);

  if (abs(balanceFactorNum) > 1) {
    balanceTree(balanceFactorNum, root);
  }
}

void printInOrder(struct Node *root, int depth) {
  if (!root)
    return;

  printInOrder(root->left, depth + 1);
  printf("%d,%d\n", root->value, depth);
  printInOrder(root->right, depth + 1);
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
