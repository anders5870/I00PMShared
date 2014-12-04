#ifndef ISTRING_REP_H
#define ISTRING_REP_H

#include <string.h>
#include <stdint.h>


/***********Custom functions *************/
/**
 * Name: shiftRightCpy\n
 * Type: (char *dst, const char *src)->char*\n
 * Pre:\n
 * Post: Function shifts all characters in dst 4 steps to the right, 
 * making room for the istring length bits and copies src to dst,
 * and returns dst. 
 */
char *shiftRightCpy(char *dst, const char *src);

/**
 * Name: setilenbytes\n
 * Type: (char *dst, uint32_t srclen)->char*\n
 * Pre:\n
 * Post: sets the length bytes of the istring to reflect its length,
 * returns the istring with the bytes set.
 */
char *setilenbytes(char *dst, uint32_t srclen);

/**
 * Name: shiftRightSetLen\n
 * Type: (char *dst, int dstlen)->char*\n
 * Pre:\n
 * Post: Shifts all characters in dst 4 steps to the right,
 * making room for the istring length bits and sets the length
 * bytes to reflect its length, and returns the istring with
 * the bytes set. 
 */
char  *shiftRightSetLen(char *dst, int dstlen);
/**********End custom functions **********/


#endif

