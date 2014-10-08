char *strcpy(char *dst, const char *src) {
  char *cp = dst;
  while (*cp++ = *src++);
  return dst;
}

/* char *istring_mk(const char* str){ */
/*   int length = strlen(str); //Å‰ndra till istrlen? */
/*   void *p = malloc(length + 4 + 1); */
/*   if (p == NULL){ */
/*     return NULL; //out of memory */
/*   } */
/*   char *new_string = p; */
/*   *new_string = length; */
/*   new_string = STRING(new_string); */
/*   if (!*str){ */
/*     *new_string = *str; */
/*     return new_string; */
/*   } */
/*   while (*str){ */
/*     *new_string++ = *str++; */
/*   } */
/*   *new_string = '\0'; */
/*   return (new_string - length); */
/* } */

/* char *istring_to_string(const char *str){ */
/*   char *string = START(str); */
 
/*   int subbuff[4]; */
/*   memcpy( subbuff, &string[0], 4 ); */
  
/* } */


int main(){
  char *test = "Teststring";
  char *itest = istring_mk(test);
  printf("1. The istring is %s\n", STRING(itest));
  printf("2. The length of the istring is: %d%d%d%d\n",*(itest+0),*(itest+1),*(itest+2),*(itest+3));
  test = istring_to_string(itest);
  printf("3. The string after istring_to_string: %s\n",test);
  istring_rm(test);
  istring_rm(itest);
  return 0;
}
