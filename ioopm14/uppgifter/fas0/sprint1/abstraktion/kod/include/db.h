#ifndef __db_h
#define __db_h
#include <stdio.h>


/**
 * Defines a binary search tree node type with the following:\n
 * a pointer to a char array named key\n
 * a pointer to a char array named value\n
 * a pointer to a new node of the same type named left\n
 * a pointer to a new node of the same type named right \n 
 * The struct name is bstNode and the type name is BstNode\n  
 */
typedef struct bstNode {
  char *key;
  char *value;
  struct bstNode *left;
  struct bstNode *right;
} *BstNode;


/**
 * Name: getNewNode                                 \n    
 * Type: (char *key, char *value)->BstNode newNode  \n     
 * Pre:                                             \n     
 * Post: a new BstNode with the key and value specified.\n 
 */
BstNode getNewNode(char *key, char *value);


/**
 * Name: insertIterative                          \n         
 * Type: (BstNode root, char *key, char *value)->BstNode \n   
 * Pre:\n    
 * Post: Inserts a node with the specified key and value at
 * an empty place in the bst with the given root. \n
 */
BstNode insertIterative(BstNode root, char *key_, char *value); //


/**
 * Name: fillFromFile                  \n                 
 * Type: char *filename->BstNode \n       
 * Pre: a line in the specified file filename must not    
 * exceed 127 characters. The total number of lines must
 * be an even number. \n 
 * Post: reads a file where even line numbers become keys
 * and odd line numbers become values and fills a tree    
 * with the corresponding key and value at each node red 
 * from the given file. Returns the resulting bst.\n 
 */
BstNode fillFromFile(char *filename); //used by dp.c main to fill the tree from file

/**
 * Name: createTree\n
 * Type: void->BstNode\n
 * Pre:\n
 * Post: returns an empty binary search tree node BstNode.\n
 */
BstNode createTree(); //used by db.c main to create the tree


/**
 * Name: findMin\n
 * Type: BstNode root->BstNode min\n
 * Pre: asdf\n
 * Post: Returns the node with the smallest key value in root.\n
 * Returns root = NULL if root is empty\n
 */
BstNode findMin(BstNode root); // used by deleteNode to find smallest node in right subtree


/**
 * Name: destroy\n
 * Type: BstNode root->void\n
 * Pre:\n
 * Post: frees all memory used by the tree with root root\n
 */
void destroy(BstNode root); //used before exiting


/**
 * Name: searchIterativeParent\n
 * Type: (BstNode root, char *key)->BstNode parent\n
 * Pre: inget.\n
 * Post: Parent of BstNode with key key.\n
 */
BstNode searchIterativeParent(BstNode root, char *key);


/**
 * Name: query\n
 * Type: BstNode root->void\n
 * Pre:\n
 * Side effect: if the key specified by the user in  the funtions
 * runtime exists in the root bst tree print its value else
 * print out that it was not found.\n
 */
BstNode query(BstNode root, char *buffer); //option1

/**
 * Name: update\n
 * Type: BstNode root->BstNode root\n
 * Pre:\n
 * Post: an updated bst tree\n
 * Side effects: the user gets to input a key. If that key corresponds
 * to a node in the  bst tree root then the user is prompted to enter
 * a new value for that node. If the key was not found then nothing
 * is updated and the input tree will be the same as the output tree\n
 */
void update(BstNode root);//option2

/**
 * Name: insert\n
 * Type: BstNode root->BstNode root\n
 * Pre:\n
 * Post: the input tree with a new node inserted if specified key is unique\n
 * Side effects: the user is promted under function runtime to specify the
 * key and value for the new node to be inserted. If the key is unique
 * the the node will be inserted and the returned bst will contain the new
 * node.\n
 */
void insert(BstNode root);//option3

/**
 * Name: delete\n
 * Type: BstNode root->BstNode root\n
 * Pre:\n
 * Post: Node with the key specified in the function's
 * runtime deleted if such node is present. If not,
 * the input will be the same as its output.\n
 * Side effects: data is altered through user input\n
 */
BstNode delete(BstNode root);//option4


/**
 * Name: printTreeRecursively\n
 * Type: BstNode root->void\n
 * Pre:\n
 * Side effects: prints the contents of the tree to the screen\n
 */
void printTreeRecursively(BstNode root);//option5

/**
 * Name: print\n
 * Type: BstNode root->void\n
 * Pre:\n
 * Side effects: prints the contents of the tree to the screen\n
 */
void print(BstNode root);//option6


/**
 * Name: isNodePresentRecursive\n
 * Type: (BstNode root, char *key)->int\n
 * Pre:\n
 * Post: returns 1 if a node with the given key is present in
 * the tree root. returns 0 if such node is not found.\n
 */
int isNodePresentRecursive(BstNode root, char *key); 
//used by insert to check duplicate keys

BstNode insertRecursive(BstNode root, BstNode newNode);//not used

void readline(char *dest, int n, FILE *source);
void printWelcomeMessage();

//void mainLoop(BstNode root);

/**
 * Name: findNodeWithKey\n
 * Type: (BstNode root, char key*)->BstNode\n
 * Pre: inget.\n
 * Post: BstNode med nyckel key, annars med NULL.\n
 */
BstNode findNodeWithKey(BstNode root, char *key);


#endif

