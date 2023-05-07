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

void updateHeight(struct Node *root) {
  int leftHeight = root->left ? root->left->height : -1;
  int rightHeight = root->right ? root->right->height : -1;

  root->height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

int balanceFactor(struct Node *root) {
  int leftHeight = root->left ? root->left->height : -1;
  int rightHeight = root->right ? root->right->height : -1;

  return leftHeight - rightHeight;
}

struct Node *balanceTree(int balanceFactorNum, struct Node **root) {
  // RR
  if (balanceFactorNum < 0 && balanceFactor((*root)->right) <= 0) {
    printf("Right Right\n");

    struct Node *x = *root;
    struct Node *y = x->right;
    x->right = y->left;

    // Update x parent
    if (x->parent) {
      if (x->parent->right == x) {
        x->parent->right = y;
      } else if (x->parent->left == x) {
        x->parent->left = y;
      }
    }

    if (y->left)
      y->left->parent = x;

    y->left = x;

    y->parent = x->parent;
    x->parent = y;

    updateHeight(x);
    updateHeight(y);
    return y;
  }

  // LL
  if (balanceFactorNum > 0 && balanceFactor((*root)->left) >= 0) {
    printf("Left Left\n");

    struct Node *x = *root;
    struct Node *y = x->left;
    x->left = y->right;

    // Update x parent
    if (x->parent) {
      if (x->parent->right == x) {
        x->parent->right = y;
      } else if (x->parent->left == x) {
        x->parent->left = y;
      }
    }

    if (y->right)
      y->right->parent = x;

    y->right = x;

    y->parent = x->parent;
    x->parent = y;

    updateHeight(x);
    updateHeight(y);
    return y;
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

    if (y->left)
      y->left->parent = x;
    y->left = x;

    if (y->right)
      y->right->parent = z;
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

    updateHeight(x);
    updateHeight(z);
    updateHeight(y);
    return y;
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

    if (y->right)
      y->right->parent = x;
    y->right = x;

    if (y->left)
      y->left->parent = z;
    y->left = z;

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

    updateHeight(x);
    updateHeight(z);
    updateHeight(y);
    return y;
  }

  return *root;
}

void treeInsert(struct Node **root, int value) {
  if (!*root) {
    *root = createNode(value);
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
    *root = balanceTree(balanceFactorNum, root);
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

  // Binary search
  if ((*root)->value > value) {
    treeDelete(&(*root)->left, value);
  } else if ((*root)->value < value) {
    treeDelete(&(*root)->right, value);
  } else if ((*root)->value == value) {

    // Remove
    if (!(*root)->left || !(*root)->right) {
      struct Node *child = (*root)->left ? (*root)->left : (*root)->right;

      if (child) {
        *root = child;
      } else {
        child = *root;
        *root = NULL;
      }

      free(child);
      return;
    } else {
      struct Node *antecessor;

      if ((*root)->left) {
        antecessor = treeMax((*root)->left);
      } else if ((*root)->parent->right == *root) {
        antecessor = treeMax((*root)->parent->left);
      } else {
        antecessor = treeMax((*root)->parent->parent->left);
      }

      (*root)->value = antecessor->value;

      // Point antecessor parent to null
      if (antecessor->parent->right == antecessor) {
        antecessor->parent->right = NULL;
      } else
        antecessor->parent->left = NULL;

      free(antecessor);
    }
  }

  updateHeight(*root);

  int balanceFactorNum = balanceFactor(*root);

  if (abs(balanceFactorNum) > 1) {
    *root = balanceTree(balanceFactorNum, root);
  }
}

void printInOrder(struct Node *root, int depth) {
  if (!root)
    return;

  printInOrder(root->left, depth + 1);
  printf("%d,%d\n", root->value, depth);
  printInOrder(root->right, depth + 1);
}

void freeTree(struct Node *root) {
  if (!root)
    return;

  freeTree(root->left);
  freeTree(root->right);

  free(root);
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
