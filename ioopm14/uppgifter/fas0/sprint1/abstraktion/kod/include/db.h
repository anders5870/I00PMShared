#ifndef __db_h
#define __db_h
#include <stdio.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

typedef struct bstNode {
  char *key;
  char *value;
  struct bstNode *left;
  struct bstNode *right;
} *BstNode;

void printTree(BstNode root);
void deleteNode(BstNode root, char *key);
void insertNewNode(BstNode root, char *key, char *value); 
void updateTree(BstNode root);
void queryTree(BstNode root);
void readline(char *dest, int n, FILE *source);
void printWelcomeMessage();
void mainLoop(BstNode root);
Node fillFromFile(char *filename);
BstNode treeFillFromFile(char *filename);
BstNode createTree();
#endif

