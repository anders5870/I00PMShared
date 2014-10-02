#ifndef _STACK_H
#define _STACK_H
#define MAXSTACKSIZE 1024
#include "db.h"

typedef BstNode stackElementT;
typedef struct {
  stackElementT *contents;
  int maxSize;
  int top;
} stackT;
void StackInit(stackT *stackP, int maxSize);           //initierar en stack
void StackDestroy(stackT *stackP);                     //tar bort stacken
void StackPush(stackT *stackP, stackElementT element); //lägger ett element på stacken
stackElementT StackPop(stackT *stackP);                //returnerar översta elem och tar bort från stack
int StackIsEmpty(stackT *stackP);                      //kollar om stacken är tom
int StackIsFull(stackT *stackP);                       //kollar om stack är full

#endif  
