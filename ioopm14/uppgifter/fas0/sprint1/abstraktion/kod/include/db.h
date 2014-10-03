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
BstNode insertIterative(BstNode root, char *key_, char *value); //
BstNode treeFillFromFile(char *filename); //used by dp.c main to fill the tree from file
BstNode createTree(); //used by db.c main to create the tree

//BstNode searchIterative(BstNode root, int toggle); //to be removed

BstNode findMin(BstNode root); // used by deleteNode to find smallest node in right subtree

void destroyTree(BstNode root); //used before exiting


/***************************************************/
/* Name: searchIterativeParent                     */
/* Type: (BstNode root, char *key)->BstNode parent */
/* Pre: inget.                                     */
/* Post: Parent of BstNode with key key.           */
/***************************************************/
BstNode searchIterativeParent(BstNode root, char *key);

Input: BstNode


BstNode searchIterative(BstNode root); // main search function

void queryTree(BstNode root); //option1
BstNode updateNode(BstNode root);//option2
BstNode insertNode(BstNode root);//option3
BstNode deleteNode(BstNode root);//option4
void printTreeRecursively(BstNode root);//option5
void printTreeIteratively(BstNode root);//option6

int isNodePresentRecursive(BstNode root, char *key); 
//used by insert to check duplicate keys

BstNode insertRecursive(BstNode root, BstNode newNode);
//recursive variant of insert

void readline(char *dest, int n, FILE *source);
void printWelcomeMessage();

void mainLoop(BstNode root);

/**************************************************/
/* Name: findNodeWithKey                          */
/* Type: (BstNode root, char key*)->BstNode       */
/* Pre: inget.                                    */
/* Post: BstNode med nyckel key, annars med NULL. */
/**************************************************/
BstNode findNodeWithKey(BstNode root, char *key)


#endif

