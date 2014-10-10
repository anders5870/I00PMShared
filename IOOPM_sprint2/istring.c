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
  char *temp2 = str;
  temp2 = START(temp2);
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


//Behöver kollas med valgrind.
char* istrslen(char *s, size_t length){
  char *temp2 = START(s);
  uint32_t length_old;
  length_old = (temp2[0] << 24) | (temp2[1] << 16) | (temp2[2] << 8) | temp2[3];
  uint32_t length_new = length;
  
  //Vid kortare istringlängd än ny längd.
  if (length_old > length_new){
    char *iStrPointer = START(s);
    //Sätter längdbytesen till den nya längden.
    *(iStrPointer + 0) = (length_new >> 24) & 0xFF;
    *(iStrPointer + 1) = (length_new >> 16) & 0xFF;
    *(iStrPointer + 2) = (length_new >> 8) & 0xFF;
    *(iStrPointer + 3) = length_new & 0xFF;
    //Sätter sista byten i strängen till '\0'.
    iStrPointer = STRING(iStrPointer);
    *(iStrPointer + length_new) = '\0';
    return iStrPointer;
    //Om längderna är lika behövs ingen modifikation.
  }else if (length_old == length_new){
    return s;
    //Vid längre ny längd skapas en ny istring.
  }else{
    //Ta näst sista elementet i arrayen (längd-1) och fylla ut resten med den.
    char *iStrPointer = s;
    char temp_string[length_new];
    //Kopierar strängen till temp_string.
    for (int i=0; i < length_old; ++i){
      *(temp_string+i) = *(iStrPointer+i);  
    }
    for (int i=length_old; i < length_new; ++i){
      *(temp_string + i) = *(iStrPointer+length_old-1);
    }
    *(temp_string + length_new) = '\0';
    //Nu finns hela vår "nya" sträng i temp_string.
    free(START(iStrPointer));
    char *new_istring = istring_mk(temp_string);
    return new_istring;
  }
}



size_t istrlen(const char *s){
  size_t length_of_istring;

  length_of_istring = (*(s-4) << 24) | (*(s-3) << 16) | (*(s-2) << 8) | *(s-1);

  return length_of_istring;

}

//Function shifts all characters in dst 4 steps to the right, 
//making room for the istring length bits and copies src to dst. 
char *shiftRight(char *dst, const char *src){
  int a = 4;
  int b = 0;
  while (*(src+b)){
    *(dst+a++) = *(src+b++); 
  }
  *(dst+a) = '\0';
  return STRING(dst);
}

char *istrcpy(char *dst, const char *src){
  uint32_t length_of_string;
  length_of_string = istrlen(src);

  dst = shiftRight(dst, src);
  
  *(dst - 4) = (length_of_string >> 24) & 0xFF;
  *(dst - 3) = (length_of_string >> 16) & 0xFF;
  *(dst - 2) = (length_of_string >> 8) & 0xFF;
  *(dst - 1) = length_of_string & 0xFF;

  return dst;

}

char *istrncpy(char *dst, const char *src, size_t n){
  uint32_t length_of_string;
  length_of_string = istrlen(src);

  int x = 0;
  int m = 4;
  while(*(src+x) && x<n){
    *(dst+m) = *(src+x);
    m++;
    x++;
  }
  *(dst) = '\0';

  *(dst + -4) = (length_of_string >> 24) & 0xFF;
  *(dst + -3) = (length_of_string >> 16) & 0xFF;
  *(dst + -2) = (length_of_string >> 8) & 0xFF;
  *(dst + -1) = length_of_string & 0xFF;

  return dst;

}

/* char *istrcat(char *dst, const char *src){ */
/*   uint32_t length_of_string; */
/*   length_of_string = strlen(src) + strlen(dst); */
/*   int dstlen = strlen(dst); */
/*   int n = 0; */
/*   int m = 4; */
/*   //move all characters in dst 4 places to the right  */
/*   while(*(dst+n)){ */
/*     *(dst+m) = *(dst+n); */
/*     m++; */
/*     n++; */
/*   } */


/*   *(dst + -4) = (length_of_string >> 24) & 0xFF; */
/*   *(dst + -3) = (length_of_string >> 16) & 0xFF; */
/*   *(dst + -2) = (length_of_string >> 8) & 0xFF; */
/*   *(dst + -1) = length_of_string & 0xFF; */

/*   int o = 0; */
/*   while (*(src+o)){ */
/*     *(dst+dstlen+o) = *(src+o); */
/*     o++; */
/*   } */
/*   *(dst+dstlen+o) = '\0'; */
/* } */

/* char *istrncat(char *dst, const char *src, size_t n){ */

/*   uint32_t length_of_string; */
/*   length_of_string = strlen(dst) +  */
/*   int dstlen = strlen(dst); */
/*   int n = 0; */
/*   int m = 4; */
/*   //move all characters in dst 4 places to the right  */
/*   while(*(dst+n)){ */
/*     *(dst+m) = *(dst+n); */
/*     m++; */
/*     n++; */
/*   } */

/*   //set the length of the string to be stored inthe 4 first bytes */
/*   *(dst + -4) = (length_of_string >> 24) & 0xFF; */
/*   *(dst + -3) = (length_of_string >> 16) & 0xFF; */
/*   *(dst + -2) = (length_of_string >> 8) & 0xFF; */
/*   *(dst + -1) = length_of_string & 0xFF; */

/*   //append n characters from src onto the end of dst */
/*   int o = 0; */
/*   while (*(src+o) && o<n){ */
/*     *(dst+dstlen+o) = *(src+o); */
/*     o++; */
/*   } */
/*   *(dst+dstlen+o) = '\0'; */
/* } */


int main(){
  char *str1 = istring_mk(NULL);
  printf("1. %s\n", (str1 == NULL) ? "True": "False");
  char str2[] = "foo";
  char *str3 = istring_mk(str2);
  //  str3 = STRING(str3);
  printf("%d%d%d%x\n",*(str3-4),*(str3-3),*(str3-2),*(str3-1));
  printf("2. %s\n", strcmp(str2, str3)  == 0 ? "True": "False");
  printf("3. %d %d\n", (int)strlen(str2), (int)strlen(str3));
  printf("4. %s\n", str3[0] == 'f' ? "True" : "False");
  printf("5. %s\n", str3[1] == 'o' ? "True" : "False");
  printf("6. %s\n", str3[2] == 'o' ? "True" : "False");
  printf("7. %s\n", str3[3] == '\0' ? "True" : "False");
  //printf("8. %c %c %c %c %c %c\n", *(str3-4),*(str3-5),*(str3-6),*(str3-7),*(str3-8),*(str3-9));
  str3 = istrslen(str3, 6);
  printf("9. %s\n", str3);
  printf("10. %d\n", (int)strlen(str3));
  char *str4 = malloc (istrlen(str3)+4 +1);
  str4 = istrcpy(str4, str3);
  printf("11. %s\n", strcmp(str3,str4) == 0 ? "True" : "False");
  char *str5 = malloc(istrlen(str3)*2);
  str5 = istrncpy(str3,str3,3);
  printf("%s\n", str5);
  printf("12. %s\n", strcmp(str5,"foo") == 0 ? "True" : "False");
  return 0;
}
