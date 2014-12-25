#include "treeSpecific.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  printWelcomeMessage();
  char *filename = argv[1];
  printf("Loading database \"%s\"...\n\n", filename);

  Node root = fillFromFile(filename);
  Node node;
  char *key;
  char *value;
  int choice = -1;
  char buffer[128];
  while(choice != 0){
    puts("Please choose an operation");
    puts("1. Query a key");
    puts("2. Update an entry");
    puts("3. New entry");
    puts("4. Remove entry");
    puts("5. Print database");
    puts("6. Print root");
    puts("7. Write file");
    puts("0. Exit database");
    printf("? ");
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1:
      printf("Enter key: ");
      readline(buffer, sizeof(buffer), stdin);
      node = query(root, buffer); //queryroot = searchIterative(root, 0);//
      if (node == NULL) puts("Entry was not found");
      else printf("Key was found! It's value is: %s\n", node->value);
      break;
    case 2:
      
      puts("");
      printf("Enter key: ");
      readline(buffer, sizeof(buffer), stdin); 
      Node node = query(root, buffer);
      if (node){
        printf("Enter value: ");
        readline(buffer, sizeof(buffer), stdin);
        update(node, buffer);
        puts("");
        puts("Value inserted successfully!");  
      }
      else {
      printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }

      break;
    case 3:
      puts("");
      
      printf("Enter key: ");
      readline(buffer, sizeof(buffer), stdin); 
      key = malloc(strlen(buffer) + 1);
      strcpy(key, buffer);
      if (!query(root, key)){
        puts("Key is unique!\n");
        printf("Enter value: ");
        readline(buffer, sizeof(buffer), stdin); 
        value = malloc(strlen(buffer) + 1); 
        strcpy(value, buffer);
        root = insertIterative(root, key, value); //<<<Insert
        puts("");
        puts("Entry inserted successfully:");
        printf("key: %s\nvalue: %s\n", key, value); 
      } 
      else {
        printf("key \"%s\" already exists!\n", buffer);
      }
      break;
    case 4:
      printf("Enter key: ");
      readline(buffer, sizeof(buffer), stdin);
      root = delete(root, buffer); 
      printf("Node '%s' deleted successfullly\n", buffer);
      break;
    case 5:
      print(root); //print iteratively
      break;
    case 6:
      printf("Key: %s Value: %s\n", root->key, root->value);
      break;
    case 7:
      printf("Enter filename: ");
      readline(buffer, sizeof(buffer), stdin); 
      writefile(root, buffer);
      break;
    case 0:
      // Exit
      destroy(root);
      root = NULL;
      puts("Good bye!");
      break;
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
  return 0;
}
