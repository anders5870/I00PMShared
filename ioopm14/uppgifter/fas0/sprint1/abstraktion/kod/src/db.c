//Main
//#include "db.h"
#include "listSpecific.h"
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

  int choice = -1;
  char buffer[128];
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
      printf("Enter key: ");
      readline(buffer, sizeof(buffer), stdin);
      node = query(root, buffer); //queryroot = searchIterative(root, 0);//
      if (node == NULL) puts("Entry was not found");
      else printf("Key was found! It's value is: %s\n", node->value);
      break;
    case 2:
      update(root); //updateroot = searchIterative(root, 1);//
      break;
    case 3:
      insert(root); //insert(&)root = searchIterative(root, 2);//
      break;
    case 4:
      root = delete(root); //delete root = searchIterative(root,3);//
      break;
    case 5:
      print(root); //print iteratively
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
