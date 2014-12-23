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
  //printf("Destroying node %s \n", root->key);
  destroy(root->right);
  free(root->key);
  free(root->value);
  free(root);
  root->left = NULL;
  root->key = NULL;
  root->value = NULL;
  root->right = NULL;
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

void deleteLeaf(Node parent, Node delete){

}
void deleteNode(Node node){
  free(node->key);
  free(node->value);
  free(node);
  node->left = NULL;
  node->key = NULL;
  node->value = NULL;
  node->right = NULL;
  node = NULL;
}
void deleteright(Node parent, Node delete){
  Node rightchild = delete->right;
  int rightorleft = 0;
  Node parentright = parent->right;
  delete->right = NULL;
  rightorleft = (strcmp(parentright->key, delete->key)?0:1); 
  destroy(delete);
  if (rightorleft) {
    parent->right = rightchild;
  }
  else{
    parent->left = rightchild;
  }
}


void deleteleft(Node parent, Node delete){
  Node leftchild = delete->left; 
  int rightorleft = 0;
  Node parentright = parent->right;
  delete->left = NULL;
  rightorleft = (strcmp(parentright->key, delete->key)?0:1); 
  deleteNode(delete);
  if (rightorleft){
    parent->right = leftchild;
  }
  else{
    parent->right = leftchild;

  }
}

Node deleteRoot(Node root){
  Node temp = root->left;
  free(root->key);
  free(root->value);
  free(root);
  root->left = NULL;
  root->key = NULL;
  root->value = NULL;
  root->right = NULL;
  root = NULL;
  return temp;
}



Node delete(Node root, char *buffer){
  Node temp = root;
  Node delete = query(root, buffer);
  Node parent = searchIterativeParent(root, buffer); 
  if (!delete){
    printf("Node was not found!");
    return root;
  }    
  //if there are two children
  if (delete->left && delete->right){
    Node min = NULL;
    do {
      puts("two children");
      min = findMin(delete->left);
      free(delete->key); free(delete->value);
      delete->key = malloc(strlen(min->key)+1);
      delete->value = malloc(strlen(min->value)+1);
      delete->key = min->key;
      delete->value = min->value;
      delete = min;
    }while(min->left && min->right);
    //reduced to 0-1 children after the do-while
    
  }
  //NAND: Case of a leaf
  if (!(delete->left) && !(delete->right)){
    
    if (strcmp(delete->key, parent->key) >= 0 ){
      destroy(delete);
      parent->left = NULL;
    }
    else {
      destroy(delete);
      parent->right = NULL;
    }
  }
  //If right is a child
  if (!(delete->left) && (delete->right)){
    puts("A right child");
    if (strcmp(delete->key, root->key) == 0){
      return deleteRoot(root); 
    }
    deleteright(parent, delete);
  }

  //If left is a child
  if ((delete->left) && !(delete->right)){
    puts("A left child");
    if (strcmp(delete->key, root->key) == 0){
      return deleteRoot(root); 
    }
    else {
      deleteleft(parent, delete);
    }
  }
  return temp; 
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
  printf("Enter value: ");
  readline(buffer, sizeof(buffer), stdin); 
  char *value = malloc(strlen(buffer) + 1);
  strcpy(value, buffer);
  node->value = value;
  puts("");
  puts("Value inserted successfully!");
  
}
