#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;


typedef struct binTreeNode{
  char *key;
  char *value;
  struct binTreeNode *lLeaf;
  struct binTreeNode *rLeaf;
}*BinTreeNode;

void readline(char *dest, int n, FILE *source);
//list specific
void query(Node list);
void update(Node list);
void insert(Node *list);
void delete(Node list);
void print(Node list);

//tree specific
void addLeaf(BinTreeNode *root, BinTreeNode leaf);
char *queryTree(BinTreeNode bt, char *match);
void updateTree(BinTreeNode bt, char *match, char *newVal);
void insertLeaf(BinTreeNode bt, char key, char value);
void deleteNode(BinTreeNode bt, char *match);
void printTree(BinTreeNode bt);
