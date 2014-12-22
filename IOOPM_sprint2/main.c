#include "istring.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *str1 = istring_mk(NULL);
  char *str2 = istring_mk("Anders");  
  char *str3 = istring_mk("Alander");  
  char *str4 = istring_mk(" ");  
  char *str9 = istring_to_string(str2);
  char *str5 = istrcat(str9,str4);  
  char *str11 = istring_to_string(str5);
  char *str6 = istrcat(str11, str3);
  char *str7 = istring_to_string(str6);
  char *str8 = istring_mk("Erik");
  char *str10 = istring_to_string(str5);
  char *str12 = "Anders Ålander";
  char *str13 = istrncat(str9, str3,2);

  printf("An empty istring has length %zu\n", istrlen(str1));
  printf("My first name is %s\n",str2);
  printf("My last  name is %s\n",str3);
  printf("My name concatenated is %s\n", str6);
  printf("%s concatenated with the first %d chars from %s is %s\n", str2, 2, str3, str13);
  printf("%s has length %zu\n", str6, istrlen(str6));
  printf("%s is my name stored as normal string, it also has length %zu\n", str7, strlen(str7));
  printf("An istring's length can be changed without touching the string itself. %s has length %zu\n", str2, istrlen(str2));
  str2 = istrslen(str2, 15);
  printf("but we can change it to %zu\n", istrlen(str2));
  printf("Returns a pointer to the first given character in %s, for example a pointer to 's'gives %s\n", str2, istrchr(str2,'s'));
  printf("Same as above but from the end of %s. Pointer to 's' gives %s\n", str2, istrrchr(str2, 's'));
  printf("Are the strings %s and %s equal? %s\n", str2, str3, istrcmp(str2,str3)?"no":"yes");
  printf("Which one of %s and %s is greatest? %s\n", str2, str3, istrcmp(str2,str3)<0?str2:str3);
  printf("Compares the first %d characters in %s and %s. The substring of %s is greatest\n", 3, str2, str3, istrncmp(str2, str3, 3) > 0?str3:str2);
  printf("The result of copying %s into %s is %s\n", str8, str12, istrcpy(str7, str8));
  printf("The result of copying %d chars from %s into %s is %s\n", 3, str8, str12, istrncpy(str7,str8,3));

  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
  istring_rm(str4);
  istring_rm(str5);
  istring_rm(str6);
  free(str7);
  istring_rm(str8);
  free(str9);
  free(str10);
  free(str11);
  istring_rm(str13);
  return 0;
}
