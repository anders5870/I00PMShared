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

char *istring_mk(const char* str){ 
  //if input string is NULL, return a NULL
  if (str == NULL) return NULL;
  uint32_t length_of_string;
  //get the length of the input string and put it in a predefined int type 
  //of 4 byte space defined in the <stdint.h> library
  length_of_string = strlen(str);
  //create and assign space to the new string
  char *iStrPointer = malloc(length_of_string + 4 + 1);
  //return NULL if out of memory
  if (iStrPointer == NULL) return NULL; 
  char* temp = iStrPointer;
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
  temp = STRING(temp);
  return temp;
}

void istring_rm(char *str){
  if (str == NULL) return;
  str = START(str);
  free(str);
  str = NULL;
}


char *istring_to_string(const char *str){
  //  char *temp2 = str;
  char *temp2 = START(str);
  // Find the length of the istring
  uint32_t length_of_istring;
  //  printf("0.1 %d\n",*(temp2+3));

  //Gör om de 4 första bitsen i str till ett heltal 
  //och sätter det till length_of_istring mha byte-shifting
  length_of_istring = (temp2[0] << 24) | (temp2[1] << 16) | (temp2[2] << 8) | temp2[3];

  //printf("0.2 length of istring: %d\n", length_of_istring);
  // Create and assign space to the new string not_an_istring
  char *not_an_istring = malloc(length_of_istring+4+1);
  char *temp = not_an_istring;
  //return NULL if out of memory
  if (not_an_istring == NULL) return NULL; 
  //Copies the contents of the istring str into the new string not_an_istring
  int n = 0;
  int m = 4;
  while(n<length_of_istring){
    *(not_an_istring+n) = *(temp2+m);
    m++;
    n++;
  }
  *(not_an_istring+n) = '\0';
  // Return new_string
  return temp;

}

/* int main(){ */
/*   char *str1 = istring_mk(NULL); */
/*   printf("1. %s\n", (str1 == NULL) ? "True": "False"); */
/*   char str2[] = "foo"; */
/*   char *str3 = istring_mk(str2); */
/*   //  str3 = STRING(str3); */
/*   printf("2. %s\n", strcmp(str2, str3)  == 0 ? "True": "False"); */
/*   printf("3. %d %d\n", (int)strlen(str2), (int)strlen(str3)); */
/*   printf("4. %s\n", str3[0] == 'f' ? "True" : "False"); */
/*   printf("5. %s\n", str3[1] == 'o' ? "True" : "False"); */
/*   printf("6. %s\n", str3[2] == 'o' ? "True" : "False"); */
/*   printf("7. %s\n", str3[3] == '\0' ? "True" : "False"); */
/*   return 0;  */
/* } */
