#include <stdio.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

void readline(char *dest, int n, FILE *source);
