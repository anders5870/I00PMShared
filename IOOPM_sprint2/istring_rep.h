#ifndef ISTRING_REP_H
#define ISTRING_REP_H

#include <string.h>


/***********Custom functions *************/
//Function shifts all characters in dst 4 steps to the right, 
//making room for the istring length bits and copies src to dst. 
char *shiftRightCpy(char *dst, const char *src);
//set istring length bytes
char *setilenbytes(char *dst, int srclen);
char  *shiftRightSetLen(char *dst, int dstlen);
/**********End custom functions **********/


#endif

