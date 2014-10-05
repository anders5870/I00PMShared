//Adam Wendelin & Anders Ålander
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

char *START(char* p){
  p -= 4;
  return p;
}

char *STRING(char* p){
  p += 4;
  return p;
}

/* char *istring_mk(const char* str){ */
/*   int length = strlen(str); //ändra till istrlen? */
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

char *istring_mk(const char* str){ 
  //if input string is NULL, return a NULL
  if (!str) return NULL;
  uint32_t length_of_string;
  //get the length of the input string and put it in a predefined int type 
  //of 4 byte space defined in the <stdint.h> library
  length_of_string = strlen(str);
  //create and assign space to the new string
  char *iStrPointer = malloc(length_of_string + 4 + 1);
  char *temp = iStrPointer;
  //return NULL if out of memory
  if (iStrPointer == NULL) return NULL; 
  //set the length value of the string in the first 4 bytes of the istring
  *(iStrPointer + 0) = (length_of_string >> 24) & 0xFF;
  *(iStrPointer + 1) = (length_of_string >> 16) & 0xFF;
  *(iStrPointer + 2) = (length_of_string >> 8) & 0xFF;
  *(iStrPointer + 3) = length_of_string & 0xFF;
  //set istring pointer to point at the beginning of the string
  iStrPointer = STRING(iStrPointer);
  //copy the input string into the istring
  while (*str != '\0'){
    *iStrPointer++ = *str++;
  }
  *iStrPointer = '\0';
  //set istring pointer to point at the beginning of the length bits
  iStrPointer = START(iStrPointer);
  //return the istring
  return temp;
}

void istring_rm(char *str){
  free(str);
  str = NULL;
}

/* char *istring_to_string(const char *str){ */
/*   char *string = START(str); */
 
/*   int subbuff[4]; */
/*   memcpy( subbuff, &string[0], 4 ); */
  
/* } */

char *istring_to_string(const char *str){
  // Find the length of the istring
  uint32_t length_of_istring;
  printf("%d\n",*(str+3));

  //Behöver göra om 4 första bitsen i str till ett heltal 
  //och sätta det till length_of_istring
  //sedan borde funktionen fungera
  length_of_istring =  //???

  printf("length of istring: %d\n", length_of_istring);
  // Create and assign space to the new string not_an_istring
  char *not_an_istring = malloc(length_of_istring+4+1);
  char *temp = not_an_istring;
  //return NULL if out of memory
  if (not_an_istring == NULL) return NULL; 
  
  /* *not_an_istring = *(str+4); */
  /* *(not_an_istring+1) = *(str+5); */

  int n = 0;
  int m = 4;
  while(n<length_of_istring){
    *(not_an_istring+n) = *(str+m);
    m++;
    n++;
  }
  *(not_an_istring+n) = '\0';
  // Return new_string
  return temp;

}

int main(){
  char *test = "Teststring";
  char *itest = istring_mk(test);
  printf("The istring is %s\n", STRING(itest));
  printf("The length of the istring is: %d%d%d%d\n",*(itest+0),*(itest+1),*(itest+2),*(itest+3));
  test = istring_to_string(itest);
  printf("The string after istring_to_string: %s\n",test);

  //istring_rm(itest);
  return 0;
}
