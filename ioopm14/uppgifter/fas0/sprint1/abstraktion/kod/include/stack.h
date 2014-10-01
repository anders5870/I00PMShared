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
void StackInit(stackT *stackP, int maxSize);
void StackDestroy(stackT *stackP);
void StackPush(stackT *stackP, stackElementT element);
stackElementT StackPop(stackT *stackP);
int StackIsEmpty(stackT *stackP);
int StackIsFull(stackT *stackP);

#endif  
