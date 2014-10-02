//Adam Wendelin & Anders Ålander
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char *START(char* p){
  p -= 4;
  return p;
}

char *STRING(char* p){
  p += 4;
  return p;
}



char *istring_mk(const char* str){ 
  int length = strlen(str); //ändra till istrlen?
  void *p = malloc(length + 4 + 1);
  if (p == NULL){ 
    return NULL; //out of memory
  }
  char *new_string = p;
  *new_string = length;
  new_string = STRING(new_string);
  if (!*str){
    *new_string = *str;
    return new_string;
  }
  while (*str){
    *new_string++ = *str++;
  }
  *new_string = '\0';
  return (new_string - length);
}

void istring_rm(char *str){
  START(str);
  free(str);
  str = NULL;
}

int main(){
  char *test = istring_mk("Teststring");
  istring_rm(test);
  printf("TESTING, %s \n", test); 
  return 0;
}
