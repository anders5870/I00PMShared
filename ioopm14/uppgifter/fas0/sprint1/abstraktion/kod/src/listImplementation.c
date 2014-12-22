#include "listSpecific.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//
Node fillFromFile(char *filename){ 
  FILE *database = fopen(filename, "r");
  char buffer[128]; 
  Node list = NULL; 
  while(!(feof(database))){ 
    Node newNode = malloc(sizeof(struct node)); 
    readline(buffer, sizeof(buffer), database); 
    newNode->key = malloc(strlen(buffer) + 1); 
    strcpy(newNode->key, buffer); 
    readline(buffer, sizeof(buffer), database); 
    newNode->value = malloc(strlen(buffer) + 1); 
    strcpy(newNode->value, buffer); 
    newNode->next = list; 
    list = newNode;
  }
  return list;
} 

//
Node query(Node cursor, char *buffer){
  while(cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      return cursor;
    }else{
      cursor = cursor->next;
    }
  }
  return NULL;
}

void destroy(Node list){}

void update(Node cursor){
  char buffer[128];
  printf("Enter key: ");
  readline(buffer, sizeof(buffer), stdin);
  puts("Searching database...\n");
  int found = 0;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Matching entry found:");
      printf("+key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }else{
    printf("Enter new value: ");
    readline(buffer, sizeof(buffer), stdin);
    free(cursor->value);
    cursor->value = malloc(strlen(buffer) + 1);
    strcpy(cursor->value, buffer);
    puts("Value inserted successfully!");
  }
}

void insert(Node list){
  char buffer[128];
  printf("Enter key: ");
  readline(buffer, sizeof(buffer), stdin);
  puts("Searching database for duplicate keys...");
  int found = 0;
  Node cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      printf("key \"%s\" already exists!\n", cursor->key);
      found = 1;
    }else{
      if(cursor->next == NULL){
	puts("Key is unique!\n");
	Node newNode = malloc(sizeof(struct node));
	newNode->key = malloc(strlen(buffer) + 1);
	strcpy(newNode->key, buffer);
	printf("Enter value: ");
	readline(buffer, sizeof(buffer), stdin);
	newNode->value = malloc(strlen(buffer) + 1);
	strcpy(newNode->value, buffer);
	cursor->next = newNode;
	puts("");
	puts("Entry inserted successfully:");
	printf("key: %s\nvalue: %s\n", (list)->key, (list)->value);
	break;
      }
      else{
	cursor = cursor->next;
      }
    }
  }
}

Node delete(Node list){
  printf("Enter key: ");
  char buffer[128]; 
  readline(buffer, sizeof(buffer), stdin);
  puts("Searching database...\n");
  int found = 0;
  Node cursor = list;
  Node prev = NULL;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      if(prev == NULL){ // Delete first node
	list = cursor->next;
	free(cursor);
      }else{
	prev->next = cursor->next;
      }
      found = 1;
      printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);
    }else{
      prev = cursor;
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
  return list;
}

void print(Node cursor){
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }
}

