#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "db.h"
#include "stack.h"

BstNode getNewNode(char *key, char *value){
  BstNode newNode = malloc(sizeof(struct bstNode));
  newNode->key = key;
  (*newNode).value = value;
  newNode->left = newNode->right = NULL;
  return newNode;
}

BstNode insertIterative(BstNode root,  char *key_, char *value){
  BstNode tempNode = root;
  if (root == NULL){
    root = getNewNode(key_, value);
    return root;
  }
  while(root != NULL){
    if (strcmp(root->key, key_) > 0){
      if(root->right == NULL){
	root->right = getNewNode(key_, value);
	return tempNode;
      }
      root = root->right;
    }
    else {
      if(root->left == NULL){
	root->left = getNewNode(key_, value);
	return tempNode;
      }
      root = root->left;
    }
  }
  return root; //Kommer aldrig hit
}

BstNode treeFillFromFile(char *filename){
  FILE *database = fopen(filename, "r");
  char buffer[128];
  char *key;
  char *value;

  BstNode root = NULL;
  while(!(feof(database))){ 
    readline(buffer, sizeof(buffer), database);
    key = malloc(strlen(buffer) + 1);
    strcpy(key, buffer);
    readline(buffer, sizeof(buffer), database); 
    value = malloc(strlen(buffer) + 1); 
    strcpy(value, buffer);
    root = insertIterative(root, key, value);
  }
  return root;
}

BstNode createTree(){
  BstNode root = malloc(sizeof(struct bstNode));
  return root;
}

BstNode insertNode(BstNode root){
  char *key;
  char *value;
  char buffer[128];
  puts("");
  printf("Enter key: ");
  readline(buffer, sizeof(buffer), stdin); 
  key = malloc(strlen(buffer) + 1);
  strcpy(key, buffer);
  puts("Searching database for duplicate keys...!");
  if (!isNodePresentRecursive(root, key)){
    puts("Key is unique!\n");
    printf("Enter value: ");
    readline(buffer, sizeof(buffer), stdin); 
    value = malloc(strlen(buffer) + 1); 
    strcpy(value, buffer);
    root = insertIterative(root, key, value);
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", key, value); 
  } 
  else {
    printf("key \"%s\" already exists!\n", buffer);
  }
  return root;
}

BstNode findMin(BstNode root){
  puts("3.2");
  if (root == NULL) return root;
  if (root->left == NULL) return root;
  BstNode dir = root->left;
  while (dir->left != NULL)
    dir = dir->left;
  puts("3.3");
  return dir;
}

void printTreeRecursively(BstNode root){ 
  if (root == NULL) return;                  //inorder traversal
  if (root->left != NULL)
    printTreeRecursively(root->left);       //Visit left subtree
  printf("%s\t", root->key); 
  printf("%s\n", root->value);
  printf("%c\t", *(root->key));             //example pointer/array notation
  printf("%c\n", root->value[0]);           //example double pointer
  if (root->right != NULL)
    printTreeRecursively(root->right);      // Visit right subtree
}

void printTreeIteratively(BstNode root){
  if (root == NULL) return;  
  stackT stack;
  BstNode current = root;
  StackInit(&stack, MAXSTACKSIZE);
  int done = 0;
  puts("");
  printf("Key\tValue\n");
  puts("");
  while (!done) {
    if (current) {
      StackPush(&stack, current);
      current = current->left;
    } else {
      if (StackIsEmpty(&stack)) {
        done = 1;
      } else {
        current = StackPop(&stack);
        printf("%s\t%s\n",current->key,current->value);
        current = current->right;
      }
    }
  }
  StackDestroy(&stack);
}

void destroyTree(BstNode root){
    if (!root) {return;}
    destroyTree(root->left);
    printf("Destroying node %s \n", root->key);
    destroyTree(root->right);
    free(root->key);
    free(root->value);
    free(root);
    root = NULL;
}

int isNodePresentRecursive(BstNode root, char *key){
  if (root == NULL)
    return 0;
  else if (strcmp(root->key, key) == 0)
    return 1;
  else if (strcmp(root->key, key) < 0)
    return isNodePresentRecursive(root->left, key);
  else
    return isNodePresentRecursive(root->right, key);
}

BstNode insertRecursive(BstNode root, BstNode newNode){
  if (root == NULL){
    root = newNode;
    printf("%s\t%s\n",root->key,root->value);
  }
  else if (strcmp(newNode->key, root->key) < 0){;
    root->left = insertRecursive(root->left, newNode);
  }
  else if (strcmp(newNode->key, root->key) > 1){   
    root->right = insertRecursive(root->right, newNode);
  }
  return root;
}

BstNode searchIterativeParent(BstNode root, char *key){
  BstNode parent = root;
  int found = 0;
  while (root != NULL && !found){
    if (strcmp(root->key, key) > 0){
      parent = root;
      root = root->right;
    }
    else if (strcmp(root->key, key) < 0){
      parent = root;
      root = root->left;
    }
    else {
      found = 1; 
    }
  }
  return parent;
}

BstNode findNodeWithKey(BstNode root, char *key){
  int found = 0;

  while (root != NULL && !found){
    if (strcmp(root->key, key) > 0){
      root = root->right;
    }
    else if (strcmp(root->key, key) < 0){
      root = root->left;
    }
    else {
      found = 1;
    }
  }
  if(!found)
    return root = NULL;
  else{
    return root;
  }
  return root = NULL;
}


BstNode deleteNode(BstNode root){
  BstNode temp = root;
  char buffer[128];
  BstNode toBeDeleted = root;
  BstNode parentOfNodeToBeDeleted = root;
  //exit if tree is empty
  if(root == NULL) {
    puts("Database is empty...aborting...");
    return root;
  }
  //Input node from user
  printf("Enter key: ");
  readline(buffer, sizeof(buffer), stdin);

  //find parent of node to delete
  parentOfNodeToBeDeleted = searchIterativeParent(root, buffer);

  //find node to delete
  toBeDeleted = findNodeWithKey(root, buffer);

  //exit if entry to delete was not found
  if (toBeDeleted == NULL){ 
    puts("Entry to delete was not found...aborting...");
    return temp;
  }
  // Case 1:  No child
  if(toBeDeleted->left == NULL && toBeDeleted->right == NULL) {
    puts("1");
    if (toBeDeleted == root){
      free(root->key);
      free(root->value);
      free(root);
      root = NULL;
      return root;
    }
    if (parentOfNodeToBeDeleted->right == root){
      //free key and value
      free(toBeDeleted->key);
      free(toBeDeleted->value);
      //free the node and set it to NULL
      free(parentOfNodeToBeDeleted->right);
      parentOfNodeToBeDeleted->right = NULL;
    }
    else {

      free(toBeDeleted->key);
      free(toBeDeleted->value);
      
      free(parentOfNodeToBeDeleted->left);
      parentOfNodeToBeDeleted->left = NULL;
    }
    puts("Entry deleted successfully");
    
  }
  else if(toBeDeleted->left == NULL) {  //Case 2: One child
    puts("2");
    BstNode test;
    test = toBeDeleted->right;
    if (toBeDeleted == root){
      free(root->key);
      free(root->value);
      free(root);
      root = NULL;
      return test;
    }
    parentOfNodeToBeDeleted = searchIterativeParent(root, toBeDeleted->key);
    free(toBeDeleted->key);
    free(toBeDeleted->value);
    if (parentOfNodeToBeDeleted->left == toBeDeleted){
      free(toBeDeleted);
      parentOfNodeToBeDeleted->left = NULL;
      parentOfNodeToBeDeleted->left = test;
    }
    else{
      free(toBeDeleted);
      parentOfNodeToBeDeleted->right = NULL;
      parentOfNodeToBeDeleted->right = test;
    }

    puts("Entry deleted successfully");
  }
  else if(toBeDeleted->right == NULL) {
    puts("2.1");
    BstNode test;
    //1. Save test
    test = toBeDeleted->left;
    if (toBeDeleted == root){
      free(root->key);
      free(root->value);
      free(root);
      root = NULL;
      return test;
    }
    //2. Find parent of node to be deleted
    parentOfNodeToBeDeleted = searchIterativeParent(root, toBeDeleted->key);
    //3. Remove key and value from node to be deleted
    free(toBeDeleted->key);
    free(toBeDeleted->value);
    //4. Check if node to be deleted is right or left child of parent node
    if (parentOfNodeToBeDeleted->left == toBeDeleted){
      //5.1 If it is the left child, remove the node and set it to NULL
      free(toBeDeleted);
      parentOfNodeToBeDeleted->left = NULL;
      //6.1 Link parent node with test
      parentOfNodeToBeDeleted->left = test;
    }
    else{
      //5.2 Else it is the right child. Remove it and set it to NULL
      free(toBeDeleted);
      parentOfNodeToBeDeleted->right = NULL;
      //6.2 Link parent node with test
      parentOfNodeToBeDeleted->right = test;
    }

    puts("Entry deleted successfully");
  }
  else {  // case 3: 2 children
    puts("3");
    BstNode minParent = findMin(toBeDeleted->right);

    if (minParent == NULL || minParent == temp->right) {//if parent or cur is root---go right
      minParent = temp;
      BstNode right = minParent->right;
      puts("3.4");
      //free space to be overwritten and create space for the new data
      free(minParent->key);
      free(minParent->value);
      //insert new data
      minParent->key = right->key;
      minParent->value = right->value;
      //free the node the data was contained in from parent-perspective
      free(minParent->right);
      minParent->right = NULL;
    }
    else {    //if parent is NOT root---go left
      BstNode left = minParent->left;
      puts("3.4.2");
      //free space to be overwritten and create space for the new data
      free(toBeDeleted->key);
      free(toBeDeleted->value);
      //insert new data
      toBeDeleted->key = left->key;
      toBeDeleted->value = left->value;
      //find the parent
      parentOfNodeToBeDeleted = searchIterativeParent(root, left->key);
      //free the node the data was contained in from parent-perspective
      free(parentOfNodeToBeDeleted->left);
      parentOfNodeToBeDeleted->left = NULL;
    }
    puts("3.5");
    puts("Entry deleted successfully");
    printf("%p\n", temp->key);
  }
  toBeDeleted = parentOfNodeToBeDeleted = NULL;
  return temp;
}

BstNode queryTree(BstNode root, char *buffer){

  int found = 0;
  while (root != NULL && !found){
    if (strcmp(root->key, buffer) > 0){
      root = root->right;
    }
    else if (strcmp(root->key, buffer) < 0){
      root = root->left;
    }
    else {
      found = 1;
      return root;
    }
  }
  if(!found)
    return NULL;
  return root;
}

BstNode updateNode(BstNode root){

  printf("Enter key: ");
  char buffer[128];
  readline(buffer, sizeof(buffer), stdin);
  BstNode temp = root;
  int found = 0;

  while (root != NULL && !found){
    if (strcmp(root->key, buffer) > 0){
      root = root->right;
    }
    else if (strcmp(root->key, buffer) < 0){
      root = root->left;
    }
    else {
      puts("Found entry");
      found = 1;
    }
  }
  if(!found)
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  else{
    puts("");
    printf("Enter new value: ");
    readline(buffer, sizeof(buffer), stdin);
    free(root->value);
    root->value = malloc(strlen(buffer) + 1);
    strcpy(root->value, buffer);
    puts("");
    puts("Value inserted successfully!");
  }
  return temp;
}

