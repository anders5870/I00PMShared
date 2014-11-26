#include <stdio.h>

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

void readline(char *dest, int n, FILE *source);
Node fillFromFile(char *filename);
Node query(Node cursor, char *buffer);
void update(Node cursor);
void insert(Node list);
Node delete(Node list);
void print(Node cursor);
void destroy(Node list);
void printWelcomeMessage();
