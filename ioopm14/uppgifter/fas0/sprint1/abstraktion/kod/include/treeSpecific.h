#ifndef __treeSpecific_h
#define __treeSpecific_h
#include <stdio.h>


/**
 * Defines a binary search tree node type with the following:\n
 * Two pointers to char arrays named key and value
 * Two pointers to a node of this type named left and right\n
 */
typedef struct node {
  char *key;
  char *value;
  struct node *left;
  struct node *right;
} *Node;


/**
 * Name: getNewNode                                 \n    
 * Type: (char *key, char *value)->Node newNode  \n     
 * Pre:                                             \n     
 * Post: a new Node with the key and value specified.\n 
 */
Node getNewNode(char *key, char *value);


/**
 * Name: insertIterative                          \n         
 * Type: (Node root, char *key, char *value)->Node \n   
 * Pre:\n    
 * Post: Inserts a node with the specified key and value at
 * an empty place in the bst with the given root. \n
 */
Node insertIterative(Node root, char *key_, char *value); //


/**
 * Name: fillFromFile                  \n                 
 * Type: char *filename->Node \n       
 * Pre: a line in the specified file filename must not    
 * exceed 127 characters. The total number of lines must
 * be an even number. \n 
 * Post: reads a file where even line numbers become keys
 * and odd line numbers become values and fills a tree    
 * with the corresponding key and value at each node red 
 * from the given file. Returns the resulting bst.\n 
 */
Node fillFromFile(char *filename); 

/**
 * Name: createTree\n
 * Type: void->Node\n
 * Pre:\n
 * Post: returns an empty binary search tree node Node.\n
 */
Node createTree(); 


/**
 * Name: findMin\n
 * Type: Node root->Node min\n
 * Pre: asdf\n
 * Post: Returns the node with the smallest key value in root.\n
 * Returns root = NULL if root is empty\n
 */
Node findMin(Node root); // used by deleteNode to find smallest node in right subtree


/**
 * Name: destroy\n
 * Type: Node root->void\n
 * Pre:\n
 * Post: frees all memory used by the tree with root root\n
 */
void destroy(Node root); //used before exiting


/**
 * Name: searchIterativeParent\n
 * Type: (Node root, char *key)->Node parent\n
 * Pre: inget.\n
 * Post: Parent of Node with key key.\n
 */
Node searchIterativeParent(Node root, char *key);


/**
 * Name: query\n
 * Type: Node root->Node\n
 * Pre:\n
 * Post: returns the value component of the Node with
 * specified key read from buffer
 * If no such Node is found it returns NULL.\n
 */
Node query(Node root, char *buffer); 

/**
 * Name: update\n
 * Type: Node root->Node root\n
 * Pre:\n
 * Post: an updated bst with root root\n
 * Side effects: the user gets to input a key. If that key corresponds
 * to a node in the  bst tree root then the user is prompted to enter
 * a new value for that node. If the key was not found then nothing
 * will be changed.\n
 */
void update(Node root);

/**
 * Name: insert\n
 * Type: Node root->void\n
 * Pre:\n
 * Post: attempt to add a new Node in the bst with root root.
 * Side effects: the user is promted under function runtime to specify the
 * key and value for the new node to be inserted. If the key is unique
 * the the node will be inserted and the returned bst will contain the new
 * node. If the key is not unique user will be notified and nothing
 * will be updated\n
 */
void insert(Node root);

/**
 * Name: delete\n
 * Type: Node root->Node root\n
 * Pre:\n
 * Post: attempt to delete  a Node in thebst with root root
 * Returns the root of the tree. 
 * Side effects: the user is prompted under function runtime to specify
 * the key of the Node to be deleted. If such node is found it is
 * removed from the bst. If the key was not found the user will be 
 * notified and nothing will be updated\n
 */
Node delete(Node root);


/**
 * Name: printTreeRecursively\n
 * Type: Node root->void\n
 * Pre:\n
 * Side effects: prints the contents of the tree to the console\n
 */
void printTreeRecursively(Node root);

/**
 * Name: print\n
 * Type: Node root->void\n
 * Pre:\n
 * Side effects: prints the contents of the tree to the console\n
 */
void print(Node root);


/**
 * Name: isNodePresentRecursive\n
 * Type: (Node root, char *key)->int\n
 * Pre:\n
 * Post: returns 1 if a node with the given key is present in
 * the bst with root root. Returns 0 if such node was not found.\n
 */
int isNodePresentRecursive(Node root, char *key);


/**
 * Name: insertRecursive\n
 * Type: (Node root, Node newNode)->Node\n
 * Pre:\n
 * Post: Inserts newNode in the bst with root root in an empty
 * position if the key is unique. Returns the Node that was
 * inserted. If the key
 * of the Node to be inserted already existed in the bst,
 * that existing Node will be returned and the bst will be unchanged\n
 */
Node insertRecursive(Node root, Node newNode);//not used


/**
 * Name: readline\n
 * Type: (char *dest, int n, FILE *source)->void\n
 * Pre: (length of a line in source + 1) <= (n)\n
 * Side effects: reads a line from source and copies it into dest\n
 */
void readline(char *dest, int n, FILE *source);


/**
 * Name: printWelcomeMessage\n
 * Type: void->void\n
 * Pre: 
 * Side effects: Prints welcome message to the console\n
 */
void printWelcomeMessage();

/**
 * Name: findNodeWithKey\n
 * Type: (Node root, char key*)->Node\n
 * Pre: inget.\n
 * Post: Node med nyckel key, annars med NULL.\n
 */
Node findNodeWithKey(Node root, char *key);


#endif

