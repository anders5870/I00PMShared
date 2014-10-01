#ifndef __db_h
#define __db_h
#include <stdio.h>



typedef struct bstNode {
  char *key;
  char *value;
  struct bstNode *left;
  struct bstNode *right;
} *BstNode;

BstNode getNewNode(char *key, char *value);
BstNode insertIterative(BstNode root, char *key_, char *value);
BstNode treeFillFromFile(char *filename);
BstNode createTree();
BstNode searchIterative(BstNode root, int toggle);
BstNode findMin(BstNode root);
void printTreeRecursively(BstNode root);
void printTreeIteratively(BstNode root);
void destroyTree(BstNode root);



int searchRecursive(BstNode root, char *key);
BstNode insertRecursive(BstNode root, BstNode newNode);

void insertNewNode(BstNode root); 
void updateTree(BstNode root);
void queryTree(BstNode root);
void readline(char *dest, int n, FILE *source);
void printWelcomeMessage();
void mainLoop(BstNode root);
#endif

