#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "db.h"

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


BstNode searchIterative(BstNode root, int toggle){
  printf("Enter key: ");
  BstNode temp = root;
  BstNode parent = root;
  char buffer[128];
  readline(buffer, sizeof(buffer), stdin);
  int found = 0;
  //toggle//0 = query, 1 = update, 2 = insert, 3 = delete
  if (toggle == 0 || toggle == 1 || toggle == 3)
    puts("Searching database...\n");
  else
    puts("Searching database for duplicate keys...\n");
  while (root != NULL && !found){
    if (strcmp(root->key, buffer) > 0){
      parent = root;
      root = root->right;
    }
    else if (strcmp(root->key, buffer) < 0){
      parent = root;
      root = root->left;
    }
    else {
      found = 1;
      if (toggle == 0 || toggle == 1 || toggle == 3){
        printf("Found entry!\n\n");
        printf("Key: %s\nValue: %s\n", root->key, root->value);
      }
      else
        printf("key \"%s\" already exists!\n", buffer);
    }
  }
  if(!found)
    printf("Could not find an entry matching key \"%s\"!\n", buffer);

  if(toggle == 1){//update
    puts("");
    printf("Enter new value: ");
    readline(buffer, sizeof(buffer), stdin);
    free(root->value);
    root->value = malloc(strlen(buffer) + 1);
    strcpy(root->value, buffer);
    puts("");
    puts("Value inserted successfully!");
  }
  if (toggle == 2){//insert
    char *key;
    char *value;
    puts("Key is unique!\n");
    printf("Enter value: ");
    key = malloc(strlen(buffer) + 1);
    strcpy(key, buffer);
    readline(buffer, sizeof(buffer), stdin); 
    value = malloc(strlen(buffer) + 1); 
    strcpy(value, buffer);
    temp = insertIterative(temp, key, value);
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", key, value);
  }
  if (toggle == 3 && found == 1){//delete
    
    // Case 1:  No child
    if(root->left == NULL && root->right == NULL) { 
      puts("1");

      if (parent->right == root){
        parent->right = NULL;
        free(parent->right);
      }
      else {
        parent->left = NULL;
        free(parent->left);
      }
      puts("Entry deleted successfully");
    }
    //Case 2: One child 
    else if(root->left == NULL) {
      puts("2");

      BstNode test;
      test = root->right;

      root->key = test->key;
      root->value = test->value;
      root->left = test->left;
      root->right = test->right;
      test = NULL;
      free(test);

      puts("Entry deleted successfully");
    }
    else if(root->right == NULL) {
      puts("2.1");
      printf("%s test 2\n", root->key);

      BstNode test;
      test = root->left;

      root->key = test->key;
      root->value = test->value;
      root->left = test->left;
      root->right = test->right;

      printf("%p  %p  %p  %p\n",root, &root, test, &test);
      test = NULL;
      free(test);
      puts("Entry deleted successfully");
    }
    // case 3: 2 children
    else { 
      puts("3");
      BstNode minParent = findMin(root->right);

      //-------------right
      if (minParent == NULL || minParent == temp->right) {
        minParent = temp;
        BstNode right = minParent->right;
        puts("3.4");
        minParent->key = right->key;
        minParent->value = right->value;
        printf("#4  root:  %s\n", root->key);

        right->key = NULL;
        right->value = NULL;  

        free(right->key);
        free(right->value);
        free(right);

        right = NULL; 

      }
      //-------------left
      else {
        BstNode left = minParent->left;
        puts("3.4.2");
        root->key = left->key;
        root->value = left->value;
        printf("#4  root:  %s\n", root->key);

        left->key = NULL;
        left->value = NULL;   

        free(left->key);
        free(left->value);
        free(left);

        left = NULL;

      }

      /* if (left->key != NULL) printf("#1 left  parent->left:  %s\n", left->key);  */
      /* if (minParent->key != NULL) printf("#2 left  parent:  %s\n", minParent->key); */
      /* if (right->key != NULL) printf("#3 left  parent->right:  %s\n", right->key); */

      puts("3.5");
      puts("Entry deleted successfully");
      printf("%p\n", temp->key);
    }
  }
  printf("%p\n", temp->key);
  return temp;
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

void printTree(BstNode root){    //inorder traversal
  if (root->left != NULL)
    printTree(root->left);       //Visit left subtree
  printf("%s\t", root->key);
  printf("%s\n", root->value);
  if (root->right != NULL)
    printTree(root->right);      // Visit right subtree
}

void destroyTree(BstNode root)  {
    if (!root) {return;}
    destroyTree(root->left);
    printf("Destroying node %s \n", root->key);
    destroyTree(root->right);
    free(root->key);
    free(root->value);
    free(root);
    root = NULL;
}


/* void destroyTree(BstNode root){ */
/*   if (root == NULL) return; */
/*   if (root->left != NULL){ */
/*     destroyTree(root->left); */
/*   }       //Visit left subtree */
/*   if (root->right != NULL){ */
/*     destroyTree(root->right); */
/*   }      // Visit right subtree */
/*   root = NULL; */
/*   free(root); */
/* } */

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


  /* BstNode deleteNode(BstNode root, char *key) { */
  /*   if(root == NULL) { */
  /*     puts("Could not find entry"); */
  /*     root = rootRoot; */
  /*     return root;  */
  /*   } */
  /*   else if (strcmp(key, root->key) < 0) */
  /*     root->left = deleteNode(root->left, rootRoot, key); */
  /*   else if (strcmp(key, root->key) > 0)  */
  /*     root->right = deleteNode(root->right, rootRoot, key); */
  /*   else { */
  /*     // Case 1:  No child */
  /*     if(root->left == NULL && root->right == NULL) {  */
  /*       free(root); */
  /*       root = NULL; */
  /*     } */
  /*     //Case 2: One child  */
  /*     else if(root->left == NULL) { */
  /*       puts("Found entry"); */
  /*       BstNode temp = root; */
  /*       root = root->right; */
  /*       free(temp); */
  /*       puts("Entry deleted successfully"); */
  /*     } */
  /*     else if(root->right == NULL) { */
  /*       puts("Found entry"); */
  /*       BstNode temp = root; */
  /*       root = root->left; */
  /*       free(temp); */
  /*       puts("Entry deleted successfully"); */
  /*     } */
  /*     // case 3: 2 children */
  /*     else {  */
  /*       BstNode temp = findMin(root->right); */
  /*       root->key = temp->key; */
  /*       root->right = deleteNode(root->right, rootRoot, temp->key); */
  /*     } */
  /*   } */
  /*   root = rootRoot; */
  /*   return root; */
  /* } */
