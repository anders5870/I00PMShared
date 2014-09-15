#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct binTreeNode{
  char *key;
  char *value;
  struct binTreeNode *lLeaf;
  struct binTreeNode *rLeaf;
} *BinTreeNode;

vvoid updateTree(BinTreeNode bt, char *match, char *newVal){
  while(bt != NULL){
    int check = strcmp(bt->key, match);
    if(check == 0){
      bt->value = newVal;
      return;
    }
    else{
      if(check < 0){
	bt = bt->rLeaf;
      }
      else{
	bt = bt->lLeaf;
      }
    }
  }
  // no matching key found
}

int main(int argc, char *argv[]){
  return 0;
}

void printTree(BinTreeNode bt){
  
}
