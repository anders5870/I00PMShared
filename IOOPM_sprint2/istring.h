#ifndef ISTRING_H
#define ISTRING_H

#include <string.h>



/**
 * Name: istring_mk\n
 * Type: const char* str->char*\n
 * Pre:\n
 * Post: Returns a new istring instance created from supplied
 * string. Returns NULL if out of memory. Returns NULL string if
 * argument str is NULL.
 */
char *istring_mk(const char* str); 

/**
 * Name: istring_rm\n
 * Type: char *str->void\n
 * Post: Deallocates the supplied istring.
 */
void istring_rm(char *str); 

/**
 * Name: istring_to_string\n
 * Type: const char *str->char*\n
 * Post: Returns a standard null terminated char* representation of the
 * supplied istring. Returns NULL if out of memory.
 * Note: Both the istring and normal string has allocated memory.
 */
char *istring_to_string(const char *str); 

/**
 * Name: istrfixlen\n
 * Type: char *s->size_t\n
 * Post: Inspects the length of the string from str and if it differs from
 * length, updates length accordingly. If str does not contain a \0
 * token, it will be inserted at the first element which is not a
 * printable ascii character, and length updated accordingly. This
 * function must be as efficient as possible and not rescan the string
 * if it can be avoided.\n
 *
 * This function is useful when istrings have been manipulated as
 * regular C strings, to reestablish the length invariant.
 */
size_t istrfixlen(char *s); 

/**
 * Name: istrslen\n
 * Type: (char *s, size_t length)-> char* \n
 * Post: Sets the length of an istring and inserts a corresponding '\0'
 * character. If the length argument is out of bounds for the string,
 * a new istring should be returned with the contents of the original
 * string. The last character of the original string will be repeated
 * to fill the string to its given length.
 */
char* istrslen(char *s, size_t length);

/*
 * For definitions, see the manual page of respective function on the
 * solaris system and the assignment text.
 * 
 * Think about whether having O(1) access to the length can be used to
 * improve the implementations if the string.h equivalents and use
 * that to guide your implementations!
 */

/**
 * Name: istrchr\n
 * Type: (const char *s, int c)->char*\n
 * Pre:\n
 * Post: The strchr function searches string for the first occurrence of c. 
 * The null character terminating string is included in the search.
 * The strchr function returns a pointer to the first occurrence of character
 * c in string or a null pointer if no matching character is found.
 */
char *istrchr(const char *s, int c);

/**
 * Name: istrrchr\n
 * Type: (constchar *s, int c)->char*\n
 * Pre:\n
 * Post: The strrchr function searches string for the last occurrence of c. 
 * The null character terminating string is included in the search.
 * The strrchr function returns a pointer to the last occurrence of 
 * character c in string or a null pointer if no matching character is found.
 */
char *istrrchr(const char *s, int c); 

/**
 * Name: istrcmp\n
 * Type: (const char *s1, const char *s2)->int\n
 * Pre:\n
 * Post: compares strings s1 and s2. Returns -1 if s1 is greater than s2,
 * returns 0 if s1 and s2 are equal, returns 1 if s2 is greater than s1.
 */
int istrcmp(const char *s1, const char *s2); 

/**
 * Name: istrncmp\n
 * Type: (const char *s1, const char *s2, size_t n)->int\n
 * Pre:\n
 * Post: compares the n first characters in s1 and s2. Returns -1 if if the 
 * substring of s1 is greater than the substring of s2, returns 0 if the
 * substring of s1 is equal to the substring of s2, returns 1 if the substring
 * of s2 is greater than the substring of s1.
 */
int istrncmp(const char *s1, const char *s2, size_t n); 

/**
 * Name: istrlen\n
 * Type: const char *s->size_t\n
 * Pre:\n
 * Post: returns the length of the given istring
 */
size_t istrlen(const char *s);

/*
 * I nedanstående funktioner är dst en pekare till en vanlig
 * sträng och inte en istring. Däremot skall minnesutrymmet
 * "konverteras" till en istring av funktionerna, d.v.s. efter att
 * t.ex. istrcpy anropats bör man vid anropsplatsen göra dst =
 * STRING(dst) för att hoppa över längd-delen av strängen.
*/

/**
 * Name: istrcpy\n
 * Type: (char *dst, const char *src)->char*\n
 * Pre:\n
 * Post: copies src into dst and returns dst.
 */
char *istrcpy(char *dst, const char *src); 

/**
 * Name: istrncpy\n
 * Type: (char *dst, const char *src, size_t n)-> char*\n
 * Pre: n>=0\n
 * Post: copies n charachers from src into dst and returns dst.
 */
char *istrncpy(char *dst, const char *src, size_t n); 

/**
 * Name: istrcat\n
 * Type: (char *dst, const char *src)->char*\n
 * Pre:\n
 * Post: concatenates dst with src. Returns the concatenated string.
 */
char *istrcat(char *dst, const char *src); 

/**
 * Name: istrncat\n
 * Type: (char *dst, const char *src, size_t n)->char*\n
 * Pre: n>=0\n
 * Post: concatenates dst with the first n characters from src.
 */
char *istrncat(char *dst, const char *src, size_t n); //done and validated with unittests

#endif

