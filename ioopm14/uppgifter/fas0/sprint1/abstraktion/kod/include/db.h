#ifndef __db_h
#define __db_h
#include <stdio.h>


/**************************************************************/
/* Defines a binary search tree node type with the following: */
/* a pointer to a char array named key                        */
/* a pointer to a char array named value                      */
/* a pointer to a new node of the same type named left        */
/* a pointer to a new node of the same type named right       */
/* The struct name is bstNode and the type name is BstNode    */
/**************************************************************/
typedef struct bstNode {
  char *key;
  char *value;
  struct bstNode *left;
  struct bstNode *right;
} *BstNode;


/*********************************************************/
/* Name: getNewNode                                      */
/* Type: (char *key, char *value)->BstNode newNode       */
/* Pre:                                                  */
/* Post: a new BstNode with the key and value specified. */
/*********************************************************/
BstNode getNewNode(char *key, char *value);


/************************************************************/
/* Name: insertIterative                                    */
/* Type: (BstNode root, char *key, char *value)->BstNode    */
/* Pre:                                                     */
/* Post: Inserts a node with the specified key and value at */
/* an empty place in the bst with the given root.           */
/************************************************************/
BstNode insertIterative(BstNode root, char *key_, char *value); //


/**********************************************************/
/* Name: treeFillFromFile                                 */
/* Type: char *filename->BstNode                          */
/* Pre: a line in the specified file filename must not    */
/* exceed 127 characters. The total number of lines must  */
/* be an even number.                                     */
/* Post: reads a file where even line numbers become keys */
/* and odd line numbers become values and fills a tree    */
/* with the corresponding key and value at each node red  */
/* from the given file. Returns the resulting bst.        */
/**********************************************************/
BstNode treeFillFromFile(char *filename); //used by dp.c main to fill the tree from file

/***********************************************************/
/* Name: createTree                                        */
/* Type: void->BstNode                                     */
/* Pre:                                                    */
/* Post: returns an empty binary search tree node BstNode. */
/***********************************************************/
BstNode createTree(); //used by db.c main to create the tree


/***************************************************************/
/* Name: findMin                                               */
/* Type: BstNode root->BstNode min                             */
/* Pre:                                                        */
/* Post: Returns the node with the smallest key value in root. */
/* Returns root = NULL if root is empty                        */
/***************************************************************/
BstNode findMin(BstNode root); // used by deleteNode to find smallest node in right subtree


/**********************************************************/
/* Name: destroyTree                                      */
/* Type: BstNode root->void                               */
/* Pre:                                                   */
/* Post: frees all memory used by the tree with root root */
/**********************************************************/
void destroyTree(BstNode root); //used before exiting


/***************************************************/
/* Name: searchIterativeParent                     */
/* Type: (BstNode root, char *key)->BstNode parent */
/* Pre: inget.                                     */
/* Post: Parent of BstNode with key key.           */
/***************************************************/
BstNode searchIterativeParent(BstNode root, char *key);


/******************************************************************/
/* Name: queryTree                                                */
/* Type: BstNode root->void                                       */
/* Pre:                                                           */
/* Side effect: if the key specified by the user in  the funtions */
/* runtime exists in the root bst tree print its value else       */
/* print out that it was not found.                               */
/******************************************************************/
BstNode queryTree(BstNode root, char *buffer); //option1

/***********************************************************************/
/* Name: updateNode                                                    */
/* Type: BstNode root->BstNode root                                    */
/* Pre:                                                                */
/* Post: an updated bst tree                                           */
/* Side effects: the user gets to input a key. If that key corresponds */
/* to a node in the  bst tree root then the user is prompted to enter  */
/* a new value for that node. If the key was not found then nothing    */
/* is updated and the input tree will be the same as the output tree   */
/***********************************************************************/
BstNode updateNode(BstNode root);//option2

/****************************************************************************/
/* Name: insertNode                                                         */
/* Type: BstNode root->BstNode root                                         */
/* Pre:                                                                     */
/* Post: the input tree with a new node inserted if specified key is unique */
/* Side effects: the user is promted under function runtime to specify the  */
/* key and value for the new node to be inserted. If the key is unique      */
/* the the node will be inserted and the returned bst will contain the new  */
/* node.                                                                    */
/****************************************************************************/
BstNode insertNode(BstNode root);//option3

/********************************************************/
/* Name: deleteNode                                     */
/* Type: BstNode root->BstNode root                     */
/* Pre:                                                 */
/* Post: Node with the key specified in the function's  */
/* runtime deleted if such node is present. If not,     */
/* the input will be the same as its output.            */
/* Side effects: data is altered through user input     */
/********************************************************/
BstNode deleteNode(BstNode root);//option4


/***************************************************************/
/* Name: printTreeRecursively                                  */
/* Type: BstNode root->void                                    */
/* Pre:                                                        */
/* Side effects: prints the contents of the tree to the screen */
/***************************************************************/
void printTreeRecursively(BstNode root);//option5

/***************************************************************/
/* Name: printTreeIteratively                                  */
/* Type: BstNode root->void                                    */
/* Pre:                                                        */
/* Side effects: prints the contents of the tree to the screen */
/***************************************************************/
void printTreeIteratively(BstNode root);//option6


/**************************************************************/
/* Name: isNodePresentRecursive                               */
/* Type: (BstNode root, char *key)->int                       */
/* Pre:                                                       */
/* Post: returns 1 if a node with the given key is present in */
/* the tree root. returns 0 if such node is not found.        */
/**************************************************************/
int isNodePresentRecursive(BstNode root, char *key); 
//used by insert to check duplicate keys

BstNode insertRecursive(BstNode root, BstNode newNode);//not used

void readline(char *dest, int n, FILE *source);
void printWelcomeMessage();

void mainLoop(BstNode root);

/**************************************************/
/* Name: findNodeWithKey                          */
/* Type: (BstNode root, char key*)->BstNode       */
/* Pre: inget.                                    */
/* Post: BstNode med nyckel key, annars med NULL. */
/**************************************************/
BstNode findNodeWithKey(BstNode root, char *key);


#endif

