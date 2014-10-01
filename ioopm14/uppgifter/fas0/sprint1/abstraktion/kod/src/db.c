//Main
#include "db.h"

int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  printWelcomeMessage();
  char *filename = argv[1];
  printf("Loading database \"%s\"...\n\n", filename);
  BstNode tree = treeFillFromFile(filename);

  mainLoop(tree);//make linked 
                 //structure type-independent
  return 0;
}
