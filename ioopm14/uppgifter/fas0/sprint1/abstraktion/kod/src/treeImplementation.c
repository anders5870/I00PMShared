#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "treeSpecific.h"
#include "stack.h"

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void printWelcomeMessage(){
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
}


Node getNewNode(char *key, char *value){
  Node newNode = malloc(sizeof(struct node));
  newNode->key = key;
  (*newNode).value = value;
  newNode->left = newNode->right = NULL;
  return newNode;
}

Node insertIterative(Node root,  char *key_, char *value){
  Node temp = root;
  if (root == NULL){
    root = getNewNode(key_, value);
    return root;
  }
  while(root != NULL){
    if (strcmp(root->key, key_) > 0){
      if(root->right == NULL){
	root->right = getNewNode(key_, value);
        return temp;
      }
      root = root->right;
    }
    else {
      if(root->left == NULL){
	root->left = getNewNode(key_, value);
        return temp;
      }
      root = root->left;
    }
  }
  return root; //Kommer aldrig hit
}

Node fillFromFile(char *filename){
  FILE *database = fopen(filename, "r");
  char buffer[128];
  char *key;
  char *value;
  Node root = NULL;
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

Node createTree(){
  Node root = malloc(sizeof(struct node));
  return root;
}

Node findMin(Node root){
  if (root == NULL) return root;
  if (root->right == NULL) return root;
  Node dir = root->right;
  while (dir->right != NULL)
    dir = dir->right;
  return dir;
}

void printTreeRecursively(Node root){ 
  if (root == NULL) return;                  //inorder traversal
  if (root->left != NULL)
    printTreeRecursively(root->left);       //Visit left subtree
  printf("%s\t", root->key); 
  printf("%s\n", root->value);
  if (root->right != NULL)
    printTreeRecursively(root->right);      // Visit right subtree
}

void print(Node root){
  if (root == NULL) return;  
  stackT stack;
  Node current = root;
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

void destroy(Node root){
  if (!root) {return;}
  destroy(root->left);
  //  printf("Destroying node %s \n", root->key);
  destroy(root->right);
  free(root->key);
  free(root->value);
  free(root);
  root = NULL;
}

int isNodePresentRecursive(Node root, char *key){
  if (root == NULL)
    return 0;
  else if (strcmp(root->key, key) == 0)
    return 1;
  else if (strcmp(root->key, key) < 0)
    return isNodePresentRecursive(root->left, key);
  else
    return isNodePresentRecursive(root->right, key);
}

Node insertRecursive(Node root, Node newNode){
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

Node searchIterativeParent(Node root, char *key){
  Node parent = root;
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

Node findNodeWithKey(Node root, char *key){
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

Node deleteNode(Node node){
  free(node->key);
  free(node->value);
  free(node);
  node = NULL;
  return node;
}
Node deleteRoot(Node node){
  free(node->key);
  free(node->value);
  // free(node);
  node = NULL; 
  return node;
}

Node deleteright(Node root, Node parent, Node delete){
  Node rightchild = delete->right;
  delete->right = NULL;  
  if (strcmp(delete->key, parent->key) > 0 ){
    destroy(delete);
    parent->left = rightchild;
  }
  else if (strcmp(delete->key, parent->key) < 0){
    destroy(delete);
    parent->right = rightchild;
  }  
  else {
    root = deleteNode(root);
    return rightchild;
  }
  return root;
}

Node deleteleft(Node root, Node parent, Node delete){
  Node leftchild = delete->left; 
  delete->left = NULL;  
  if (strcmp(delete->key, parent->key) > 0 ){
    destroy(delete);
    parent->left = leftchild;
  }
  else if (strcmp(delete->key, parent->key) < 0) {
    destroy(delete);
    parent->right = leftchild;
  }
  else if(strcmp(root->key, delete->key) == 0){
    destroy(delete);
    root->left = leftchild;
    
  }
  else {
    puts("deleteroot");
    printf("root: %s parent: %s delete: %s\n", root->key, parent->key, delete->key);
    Node rootright = root->right;
    Node rootrightright = rootright->right;
    printf("rootright: %s rootrightright: %s\n", rootright->key, rootrightright->key);
    Node rootleft = root->left;
    printf("rootleft: %s \n", rootleft->key);
      
    //root = deleteNode(root);
    //return leftchild;
  }
  return root;
}

Node deleteLeaf(Node root, Node parent, Node delete){
  if (strcmp(delete->key, parent->key) > 0 ){
    puts("1");
    destroy(delete);
    parent->left = NULL;
  }
  else if (strcmp(delete->key, parent->key) < 0){
    puts("2");
    destroy(delete);
    parent->right = NULL;
  }
  else {
    puts("3");
    //  Node leftchild = delete->left;
    /*     puts("here?");
           printf("root: %s parent: %s delete: %s\n", root->key, parent->key, delete->key);
           Node rootright = root->right;
           Node rootrightright = rootright->right;
           printf("rootright: %s rootrightright: %s\n", rootright->key, rootrightright->key);*/
    root = deleteNode(delete);
    parent->left = NULL;
  }
  return root;
}

Node deleteWithTwoChildren(Node delete, Node root){
  //  puts("two children");
  Node min = NULL; 
  Node parent = NULL;
  min = findMin(delete->left);
  parent = searchIterativeParent(root, min->key);
  free(delete->key); free(delete->value);
  delete->key = malloc(strlen(min->key)+1);
  delete->value = malloc(strlen(min->value)+1);
  strcpy(delete->key, min->key);
  strcpy(delete->value, min->value);

  //reduced to 0-1 children
  //Case of a leaf
  if (!(min->left) && !(min->right)){
    root = deleteLeaf(root, parent, min);
  }
  //If right is a child
  else if (!(min->left) && (min->right)){
    root = deleteright(root, parent, min);
  }  
  //If left is a child
  else if((min->left) && !(min->right)){
    root = deleteleft(root, parent, min);
  }  
  return root;
}

Node delete(Node root, char *buffer){
  Node delete = query(root, buffer);
  if (!delete){
    return root;
  }    
  Node parent = searchIterativeParent(root, buffer); 
  if (!(delete->left) && !(delete->right)){
    root = deleteLeaf(root, parent, delete);
  }
  else if (!(delete->left) && (delete->right)){
    root = deleteright(root, parent, delete);
  }
  else if((delete->left) && !(delete->right)){
    root = deleteleft(root, parent, delete);
  }
  else{
    root = deleteWithTwoChildren(delete, root);
  }
  return root; 
}

Node query(Node root, char *buffer){
  while (root){
    if (strcmp(root->key, buffer) > 0){
      root = root->right;
    }
    else if (strcmp(root->key, buffer) < 0){
      root = root->left;
    }
    else {
      return root;
    }
  }
  return NULL;
}

void update(Node node, char *buffer){
  free(node->value);
  char *value = malloc(strlen(buffer) + 1);
  strcpy(value, buffer);
  node->value = value;
}


void writefile(Node root, char *filename) {
  
  filename = strcat(filename, ".db");

  FILE *fp = fopen(filename, "w");
  if (fp == NULL)
    {
      printf("Error opening file!\n");
      exit(1);
    }

  if (root == NULL) return;  
  stackT stack;
  Node current = root;
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
        fprintf(fp, "%s\n", current->key);
        fprintf(fp, "%s\n", current->value);
        current = current->right;
      }
    }
  }
  StackDestroy(&stack);
  
  fclose(fp);
 
}



