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
void print(Node cursor);
void delete(Node list);
void insert(Node *list);
void update(Node cursor);
void query(Node cursor);
void readline(char *dest, int n, FILE *source);
void printWelcomeMessage();
void mainLoop(Node root);
Node fillFromFile(char *filename);
//BstNode* treeFillFromFile(char *filename);
Node fillFromFile(char *filename);
BstNode* createTree();
#endif

