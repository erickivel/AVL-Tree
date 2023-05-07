#include <stdio.h>
#include <stdlib.h>

#include "../include/tree.h"

int main(void) {
  struct Node *root = NULL;
  char operation;
  int num;

  while (!feof(stdin)) {
    scanf("%c %d", &operation, &num);

    if (operation == 'i') {
      treeInsert(&root, num);
    } else if (operation == 'r') {
      treeDelete(&root, num);
    }
  }

  printTree(root, 0);

  printf("\n\n===========\n\n");
  printInOrder(root, 0);

  freeTree(root);

  return 0;
}
