#include "db.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

void mainLoop(BstNode root){
  int choice = -1;
  while(choice != 0){
    puts("Please choose an operation");
    puts("1. Query a key");
    puts("2. Update an entry");
    puts("3. New entry");
    puts("4. Remove entry");
    puts("5. Print database recursively");
    puts("6. Print database iteratively");
    puts("0. Exit database");
    printf("? ");
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1:
      root = searchIterative(root, 0); //query
      break;
    case 2:
      root = searchIterative(root, 1); //update
      break;
    case 3:
      root = searchIterative(root, 2); //insert(&)
      break;
    case 4:
      root = searchIterative(root, 3); //delete
      break;
    case 5:
      printTreeRecursively(root);    //print recursively 
      break;
    case 6:
      printTreeIteratively(root); //print iteratively
      break;
    case 0:
      // Exit
      destroyTree(root);
      puts("Good bye!");
      break;
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
}
