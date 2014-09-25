#ifndef __db_h
#define __db_h
#include <stdio.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

typedef struct BstNode {
  char* key;
  char value;
  struct bstNode* left;
  struct bstNode* right;
}BstNode;

void readline(char *dest, int n, FILE *source);
void printWelcomeMessage();
void mainLoop(BstNode* root);
Node fillFromFile(char *filename);
BstNode* treeFillFromFile(char *filename);
BstNode* createTree();
#endif

