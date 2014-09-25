#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "db.h"

BstNode getNewNode(char *key, char *value){
  BstNode newNode = malloc(sizeof(BstNode));
  newNode->key = key;
  (*newNode).value = value;
  (*newNode).left = (*newNode).right = NULL;
  return newNode;
}


void insertNewNode(BstNode root){
  char buffer[128];
  printf("Enter key: ");
  readline(buffer, sizeof(buffer), stdin);
  puts("Searching database for duplicate keys...");
  while (root != NULL){
    if (strcmp(buffer, root->key) < 0)
      root = root->left;
    else if (strcmp(buffer, root->key) > 0)
      root = root->right;
    else{
      printf("key \"%s\" already exists!\n", buffer);
      return;
    }
  }
  puts("Key is unique!\n");
  BstNode newNode = getNewNode(buffer, buffer);
  printf("Enter value: ");
  readline(buffer, sizeof(buffer), stdin);
  newNode->value = malloc(strlen(buffer) + 1);
  strcpy(newNode->value, buffer);
  puts("");
  puts("Entry inserted successfully:");
  printf("key: %s\nvalue: %s\n", newNode->key, newNode->value);

}

BstNode insertRecursive(BstNode root, BstNode newNode){
  if (root == NULL)
    root = newNode;
  else if (strcmp(newNode->key, (*root).key) < 0)
    root->left = insertRecursive(root->left, newNode);
  else if (strcmp(newNode->key, root->key) > 1){
    root->right = insertRecursive(root->right, newNode);
  }
  return root;
}

BstNode treeFillFromFile(char *filename){
  FILE *database = fopen(filename, "r");
  char buffer[128];
  BstNode root = createTree();
  while(!(feof(database))){ 
    readline(buffer, sizeof(buffer), database);
    BstNode newNode = getNewNode(buffer, buffer);
    newNode->key = malloc(strlen(buffer) + 1); 
    strcpy(newNode->key, buffer);
    readline(buffer, sizeof(buffer), database); 
    newNode->value = malloc(strlen(buffer) + 1); 
    strcpy(newNode->value, buffer);

    insertRecursive(root, newNode);
  }
  return root;
}

BstNode createTree(){
  BstNode root = NULL;
  return root;
}

BstNode searchIterative(BstNode root, int toggle)
{
  BstNode temp = root;
  printf("Enter key: ");
  char buffer[128];
  readline(buffer, sizeof(buffer), stdin);
  puts("Searching database...\n");
  int found = 0;
  int toggleQueryOrUpdate = toggle;
  while(!found && root->key != NULL){
    if(strcmp(buffer, root->key) == 0){
      puts("Found entry:");
      printf("key: %s\nvalue: %s\n", root->key, root->value);
      found = 1;}
    else if(strcmp(buffer, root->key) == -1)
      root = root->left;
    else if(strcmp(buffer, root->key) == 1)
      root = root->right;
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  if(toggleQueryOrUpdate){
    printf("Enter new value: ");
    readline(buffer, sizeof(buffer), stdin);
    free(root->value);
    root->value = malloc(strlen(buffer) + 1);
    strcpy(root->value, buffer);
    puts("Value inserted successfully!");
  }
  return temp;
}

void updateTree(BstNode root)
{
  int toggleQueryOrUpdate = 1;
  root = searchIterative(root, toggleQueryOrUpdate);
}



void queryTree(BstNode root)
{
  int toggleQueryOrUpdate = 0;
  root = searchIterative(root, toggleQueryOrUpdate);
}

BstNode findMin(BstNode root)
{
	while(root->left != NULL) root = root->left;
	return root;
}

void deleteNode(BstNode root, char* key)
{
  printf("Enter key: ");
  char buffer[128]; 
  readline(buffer, sizeof(buffer), stdin);
  puts("Searching database...\n");
  int found = 0;
  while(!found && root->key != NULL){
    if(strcmp(buffer, root->key) == -1)
      root = root->left;
    else if(strcmp(buffer, root->key) == 1)
      root = root->right;
    else{ //found root to be deleted
      puts("Found entry");
      //case1. no child
      if (root->left == NULL && root->right == NULL){
        free(root);
        root = NULL;
      }//case2. 1 child
      else if(root->left == NULL) {
        BstNode temp = root;
        root = root->right;
        free(temp);
      }
      else if(root->right == NULL) {
        BstNode temp = root;
        root = root->left;
        free(temp);
      }
      else{ 
        BstNode temp = findMin(root->right);
        root->key = temp->key;
        deleteNode(root->right, temp->key);
      }
    }
  }
}



void printTree(BstNode root)
{
  if(root == NULL) return;
  printTree(root->left);       //Visit left subtree
  puts(root->key);
  puts(root->value);         //Print data
  printTree(root->right);      // Visit right subtree
}

//example of recursive equivalent functions (not used)


int searchRecursive(BstNode root, char *key){
  if (root == NULL)
    return 0;
  else if (strcmp(root->key, key) == 0)
    return 1;
  else if (strcmp(root->key, key) < 0)
    return searchRecursive(root->left, key);
  else
    return searchRecursive(root->right, key);
}
