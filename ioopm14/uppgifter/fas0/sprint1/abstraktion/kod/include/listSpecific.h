#include <stdio.h>

/**
 *Defines a list node type with the following:\n
 * a pointer to a char array named key\n
 * a pointer to a char array named value\n
 * a pointer to a new node of the same type named next\n
 * The struct name is node and the type name is Node\n  
 */
typedef struct node{
char *key;
char *value;
 struct node *next;
} *Node;


/**
 *Name: readLine\n
 *Type: (char *dest, int n, FILE *source)->void\n
 *Pre: n == sizeof(*dest)\n
 *Side effects: The next line of text in *source is written into *dest\n
 */
void readline(char *dest, int n, FILE *source);


/**
 * Name: fillFromFile                  \n                 
 * Type: char *filename->Node \n       
 * Pre: a file with the name filename exists.\n A line in the specified file filename must not    
 * exceed 127 characters.\n The total number of lines must
 * be an even number. \n
 * Post: reads a file where even line numbers become keys
 * and odd line numbers become values and fills a tree    
 * with the corresponding key and value at each node red 
 * from the given file. Returns the resulting list.\n
 * Side effects: reads the file found with filename.\n
 */
Node fillFromFile(char *filename);


/**
 * Name: query\n
 * Type: (Node cursor, char *buffer)->Node\n
 * Pre: true\n
 * Post: if the key specified by the user in the functions
 * runtime exists in the list it returns the corresponding Node.\n
 */
Node query(Node cursor, char *buffer);


/**
 * Name: update\n
 * Type: Node cursor->void\n
 * Pre: true\n
 * Side effects: the user gets to input a key. If that key corresponds
 * to a node in the cursor list then the user is prompted to enter
 * a new value for that node. If the key was not found then nothing
 * is updated.\n
 */
void update(Node cursor);


/**
 * Name: insert\n
 * Type: Node list->void\n
 * Pre: true\n
 * Side effects: the user is prompted under function runtime to specify the
 * key and value for a new node to be inserted. If the key is unique
 * then the node will be inserted at the end of list.\n
 */
void insert(Node list);


/**
 * Name: delete\n
 * Type: Node list->Node list\n
 * Pre:\n
 * Post: Node with the key specified in the function's
 * runtime deleted if such node is present. If not,
 * the output will be the same as its input.\n
 * Side effects: data is altered through user input\n
 */
Node delete(Node list);


/**
 * Name: print\n
 * Type: Node list->void\n
 * Pre: true\n
 * Side effects: prints the contents of list to the screen\n
 */
void print(Node cursor);


/**
 * Name: destroy\n
 * Type: Node list->void\n
 * Pre: true\n
 * Post: frees all memory used by the list with the root list\n
 */
void destroy(Node list);

/**
 * Name: printWelcomeMessage\n
 * Type: void\n
 * Pre: true\n
 * Side Effects: Prints a welcome message to DB\n
 */
void printWelcomeMessage();
