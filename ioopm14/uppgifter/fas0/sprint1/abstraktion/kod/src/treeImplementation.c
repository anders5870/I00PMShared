#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "db.h"

BstNode* getNewNode(char* key, char value){
  BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
  newNode->key = key;
  (*newNode).value = value;
  (*newNode).left = (*newNode).right = NULL;
  return newNode;
}

BstNode* treeFillFromFile(char *filename)
{
  FILE *database = fopen(filename, "r");
  char buffer[128];
  BstNode* root = createTree();
  while(!(feof(database))){ 
    BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
    readline(buffer, sizeof(buffer), database);
    newNode->key = malloc(strlen(buffer) + 1); 
    strcpy(newNode->key, buffer);

    readline(buffer, sizeof(buffer), database); 
    newNode->value = malloc(strlen(buffer) + 1); 
    strcpy(newNode->value, buffer);

    root = insertNewNode(root, newNode->key, newNode->value);
  }
  return root;
}

BstNode* createTree(){
  BstNode* root = NULL;
  return root;
}

BstNode* insertNewNode(BstNode* root, char* key, char value){
  BstNode* temp = root;
  if (root == NULL)
    root->key = key;
  while (root->key != NULL)
    if (key < root->key)
      if (root->left->key == NULL)
        root->left->key = key;
      else
        root = root->left;
    else if (key > root->key)
      if (root->right->key == NULL)
        root->right->key = key;
      else 
        root = root->right;
    else
      printf("key \"%s\" already exists!\n", key);
  return temp;
}



BstNode* updateTree(BstNode* root)
{
  int toggleQueryOrUpdate = 1;
  BstNode* root = searchIterative(root, toggleQueryOrUpdate);
  return root;
}

BstNode* queryTree(BstNode* root)
{
  int toggleQueryOrUpdate = 0;
  BstNode* root = searchIterative(root, toggleQueryOrUpdate);
  return root;
}

}

BstNode* searchIterative(BstNode* root, int toggle)
{
  BstNode* temp = root;
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


BstNode* deleteNode(root, key)
{
  BstNode* temp_ = root;
  printf("Enter key: ");
  char buffer[128]; 
  readline(buffer, sizeof(buffer), stdin);
  puts("Searching database...\n");
  while(!found && root->key != NULL){
    if(strcmp(buffer, root->key) == -1)
      root = root->left;
    else if(strcmp(buffer, root->key) == 1)
      root = root->right;
    else{ //found root to be deleted
      puts("Found entry");
      //case1. no child
      if (root->left = root->right = NULL){
        free(root);
        root = NULL;
      }//case2. 1 child
      else if(root->left == NULL) {
        BstNode* temp = root;
        root = root->right;
        free(temp);
      }
      else if(root->right == NULL) {
        BstNode* temp = root;
        root = root->left;
        free(temp);
      }
      else{ 
        BstNode* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right,temp->key);
      }
    }
  }
  return temp_;
}

BstNode* findMin(BstNode* root)
{
	while(root->left != NULL) root = root->left;
	return root;
}

void printTree(BstNode* root)
{
  if(root == NULL) return;
  Inorder(root->left);       //Visit left subtree
  puts(root->key);
  puts(root->value);         //Print data
  Inorder(root->right);      // Visit right subtree
}

//example of recursive equivalent functions (not used)

BstNode* insertRecursive(BstNode* root, char* key, char value){
  if (root == NULL)
    root = addNewNode(key, value);
  else if (key <= (*root).key)
    root->left = insert(root->left, key, value);
  else (key > root->key)
    root->right = insert(root->right, key, value);
  return root;
}

int searchRecursive(BstNode* root, char* key){
  if (root == NULL)
    return 0;
  else if (root->key == key)
    return 1;
  else if (root-key <= key)
    return search(root->left, key);
  else
    return search(root->right, key);
}



