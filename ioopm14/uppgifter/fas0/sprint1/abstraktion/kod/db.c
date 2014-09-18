//Main
#include "db.h"


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

void mainLoop(Node list){
  int choice = -1;
  while(choice != 0){
    puts("Please choose an operation");
    puts("1. Query a key");
    puts("2. Update an entry");
    puts("3. New entry");
    puts("4. Remove entry");
    puts("5. Print database");
    puts("0. Exit database");
    printf("? ");
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1:
      query(list);
      break;
    case 2:
      update(list);
      break;
    case 3:
      insert(&list);
      break;
    case 4:
      delete(list);
      break;
    case 5:
      print(list);      
      break;
    case 0:
      // Exit
      puts("Good bye!");
      break;
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
}

int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  printWelcomeMessage();
  char *filename = argv[1];
  printf("Loading database \"%s\"...\n\n", filename);
  Node list = fillFromFile(filename);
  mainLoop(list);
  return 0;
}
