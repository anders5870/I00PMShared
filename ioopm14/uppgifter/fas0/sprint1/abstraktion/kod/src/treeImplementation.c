#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "db.h"

BstNode getNewNode(char *key, char *value){
  BstNode newNode = malloc(32);
  newNode->key = key;
  (*newNode).value = value;
  newNode->left = newNode->right = NULL;
  return newNode;
}

BstNode insertIterative(BstNode root,  char *key, char *value){
  BstNode tempNode = root;
  while(root != NULL){
    if (strcmp(root->key, key) <= 0)
      root = root->left;
    else 
      root = root->right;
  }
  root = getNewNode(key, value);
  return tempNode;
}


BstNode treeFillFromFile(char *filename){
  FILE *database = fopen(filename, "r");
  char buffer[128];
  char *key;
  char *value;

  BstNode root = malloc(32);
  root->key = root->value = NULL;
  root->left = root->right = NULL;

  while(!(feof(database))){ 
    readline(buffer, sizeof(buffer), database);

    key = malloc(strlen(buffer) + 1);
    strcpy(key, buffer);
    readline(buffer, sizeof(buffer), database); 
    value = malloc(strlen(buffer) + 1); 
    strcpy(value, buffer);
 
    root = insertIterative(root, key, value);
  }
  puts("");
  if (root->left && root->right != NULL)
    printf("both left and right are not empty\n");
  else if (root->right != NULL)
    printf("right is not empty\n");
  else if (root->left != NULL)
    printf("left is not empty\n");
  else 
    printf("both left and right are empty\n");
  puts("");
  return root;
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

BstNode createTree(){
  BstNode root = malloc(32);
  /* BstNode root = NULL; */
  return root;
}

BstNode searchIterative(BstNode root, int toggle){
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

void updateTree(BstNode root){
  int toggleQueryOrUpdate = 1;
  root = searchIterative(root, toggleQueryOrUpdate);
}

void queryTree(BstNode root){
  int toggleQueryOrUpdate = 0;
  root = searchIterative(root, toggleQueryOrUpdate);
}

BstNode findMin(BstNode root){
  while(root->left != NULL) root = root->left;
  return root;
}

void deleteNode(BstNode root, char* key){
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

void printTree(BstNode root){

  if (root->left != NULL)
    printTree(root->left);       //Visit left subtree
  printf("%s\ti print\n", root->key);
  printf("%s\ti print\n", root->value);
  if (root->right != NULL)
    printTree(root->right);      // Visit right subtree
}

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


/* int placed = 0;

  while (!placed){
    if (root->key == NULL){
      printf("%s\tdebug root in insert\n", root->key);
      root->key = newNode->key;
      root->value = newNode->value;
      printf("%s\tdebug root in insert\n", root->key);
      placed = 1;
    }
    else{
      if (strcmp(root->key, newNode->key) < 0)
        root = root->left;
      else {
        root = root->right;
      }
    }
  }*/

/* BstNode Insert(BstNode T, char *key, char *value) */
/* { */
/*   BstNode temp=T; */
/*   BstNode node=malloc(32); */
/*   node->key=key; */
/*   node->value=value; */
/*   node->left=NULL; */
/*   node->right=NULL; */
/*   if (T==NULL) */
/*     { */
/*       T=node; */
/*       return(T); */
/*       //printf("%d\n",T->Element); */
/*     } */
/*   else */
/*     { */
/*       while(1) */
/*         { */
/*           if ((strcmp(temp->key, key) >= 0) && temp->left==NULL) */
/*             { */
/*               temp->left=node; */
/*               break; */
/*             } */
/*           else if ((strcmp(temp->key, key) >= 0) && temp->left!=NULL) */
/*             { */

/*               temp=temp->left; */
/*             } */
/*           else if ((strcmp(temp->key, node->key) < 0) && temp->right==NULL) */
/*             { */
/*               temp->right=node; */
/*               break; */
/*             } */
/*           else */
/*             { */
/*               temp=temp->right; */
/*             } */
/*         }    */
/*       return(T); */
/*     }             */
/* } */
