#ifndef ISTRING_H
#define ISTRING_H

#include <string.h>

/*
 * Returns a new istring instance created from supplied
 * string. Returns NULL if out of memory. Returns NULL string if
 * argument str is NULL. 
 */
char *istring_mk(const char* str); //done and validated with unittests

/*
 * Deallocates the supplied istring.
 */
void istring_rm(char *str); //done and validated with unittests

/*
 * Returns a standard null terminated char* representation of the
 * supplied istring. Returns NULL if out of memory.
 * Note: Both the istring and normal string has allocated memory.
 */

char *istring_to_string(const char *str); //done and validated with unittests

/*
 * Inspects the length of the string from str and if it differs from
 * length, updates length accordingly. If str does not contain a \0
 * token, it will be inserted at the first element which is not a
 * printable ascii character, and length updated accordingly. This
 * function must be as efficient as possible and not rescan the string
 * if it can be avoided.
 *
 * This function is useful when istrings have been manipulated as
 * regular C strings, to reestablish the length invariant.
 */
size_t istrfixlen(char *s); //done and validated with unittests

/* 
 * Sets the length of an istring and inserts a corresponding '\0'
 * character. If the length argument is out of bounds for the string,
 * a new istring should be returned with the contents of the original
 * string. The last character of the original string will be repeated
 * to fill the string to its given length.
 */
char* istrslen(char *s, size_t length); //done and validated with unittests

/*
 * For definitions, see the manual page of respective function on the
 * solaris system and the assignment text.
 * 
 * Think about whether having O(1) access to the length can be used to
 * improve the implementations if the string.h equivalents and use
 * that to guide your implementations!
 */
char *istrchr(const char *s, int c); //done and validated with unittests
char *istrrchr(const char *s, int c); //done and validated with unittests
int istrcmp(const char *s1, const char *s2); //done and validated with unittests
int istrncmp(const char *s1, const char *s2, size_t n); //done and validated with unittests
size_t istrlen(const char *s); //done and validated with unittests

/*
 * I nedanstående funktioner är dst en pekare till en vanlig
 * sträng och inte en istring. Däremot skall minnesutrymmet
 * "konverteras" till en istring av funktionerna, d.v.s. efter att
 * t.ex. istrcpy anropats bör man vid anropsplatsen göra dst =
 * STRING(dst) för att hoppa över längd-delen av strängen.
*/
char *istrcpy(char *dst, const char *src); //done and validated with unittests

char *istrncpy(char *dst, const char *src, size_t n); //done and validated with unittests
char *istrcat(char *dst, const char *src); //done and validated with unittests
char *istrncat(char *dst, const char *src, size_t n); //done and validated with unittests

#endif

