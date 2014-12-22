//Anders Ålander
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <assert.h>

char *START(char* p){
  p -= 4;
  return p;
}

char *STRING(char* p){
  p += 4;
  return p;
}

/***********Custom functions **********/

//Function shifts all characters in dst 4 steps to the right, 
//making room for the istring length bits and copies src to dst. 
char *shiftRightCpy(char *dst, const char *src){
  if (src == NULL) return NULL;
  int a = 4;
  int b = 0;
  while (*(src+b)){
    *(dst+a++) = *(src+b++); 
  }
  *(dst+a) = '\0';
  return STRING(dst);
}

//set istring length bytes
char *setilenbytes(char *dst, uint32_t srclen){
  *(dst - 4) = (srclen >> 24) & 0xFF;
  *(dst - 3) = (srclen >> 16) & 0xFF;
  *(dst - 2) = (srclen >> 8) & 0xFF;
  *(dst - 1) = srclen & 0xFF;
  return dst;
}

char  *shiftRightSetLen(char *dst, int dstlen){
  //shift right
  dst = STRING(dst);
  //set len
  dst = setilenbytes(dst, dstlen);
  return dst;
}

/**********End custom functions **********/

char *istring_mk(const char* str){ 
  uint32_t length_of_string;
  if (str == NULL){
    return istring_mk("");
  }
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
  if (str == NULL) return NULL;
  
  // Find the length of the istring
  uint32_t length_of_istring;
  //Gör om de 4 första bitsen i str till ett heltal 
  //och sätter det till length_of_istring mha byte-shifting
  length_of_istring = (str[-4] << 24) | (str[-3] << 16) | (str[-2] << 8) | str[-1];
  // Create and assign space to the new string not_an_istring
  char *not_an_istring = malloc(length_of_istring+1);
  //return NULL if out of memory
  if (not_an_istring == NULL) return NULL; 
  //Copies the contents of the istring str into the new string not_an_istring
  int n = 0;
  while(n<length_of_istring){
    *(not_an_istring+n) = *(str+n);
    n++;
  }
  *(not_an_istring+n) = '\0';
  // Return new_string
  return not_an_istring;
}


char* istrslen(char *s, size_t length){
  char *temp2 = START(s);
  uint32_t length_old;
  length_old = (temp2[0] << 24) | (temp2[1] << 16) | (temp2[2] << 8) | temp2[3];
  uint32_t length_new = abs(length);
  
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
    //Fyller ut resten med sista bokstaven.
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

int istrcmp(const char *s1, const char *s2){
  int i;
  for(i = 0;*(s1+i) != '\0' || *(s2+i) != '\0'; i++){
    //if s1 is longer than s2 but otherwise equal
    if(*(s1+i) == '\0')
      return -1;
    //if s2 is longer than s1 but otherwise equal
    if(*(s2+i) == '\0')
      return 1;
    //if *(s1+i) is greater than *(s2+i) then return 1
    if ((uint8_t)*(s1+i) > (uint8_t)*(s2+i))
      return 1;
    //if the other way around return -1
    else if  ((uint8_t)*(s1+i) < (uint8_t)*(s2+i))
      return -1;
  }
  //if both s1 and s2 reaches the end simultaneously they must be equal, so return 0
  return 0;
}

int istrncmp(const char *s1, const char *s2, size_t n){
  int i;
  for(i = 0;(*(s1+i) != '\0' || *(s2+i) != '\0') && i<n; i++){
    //if s1 is longer than s2 but otherwise equal
    if(*(s1+i) == '\0')
      return -1;
    //if s2 is longer than s1 but otherwise equal
    if(*(s2+i) == '\0')
      return 1;
    //if *(s1+i) is greater than *(s2+i) then return 1
    if ((uint8_t)*(s1+i) > (uint8_t)*(s2+i))
      return 1;
    //if the other way around return -1
    else if  ((uint8_t)*(s1+i) < (uint8_t)*(s2+i))
      return -1;
  }
  //if n pairs from s1 and s2 are equal or they reach the end 
  //simultaneously return 0.
  return 0;
}

size_t istrlen(const char *s){
  size_t length_of_istring;

  length_of_istring = (*(s-4) << 24) | (*(s-3) << 16) | (*(s-2) << 8) | *(s-1);

  return length_of_istring;

}


char *istrcpy(char *dst, const char *src){
  uint32_t srclen = istrlen(src);
  if (src == NULL) return NULL;
  dst = shiftRightCpy(dst, src);
  dst = setilenbytes(dst, srclen);
  return dst;

}

char *istrncpy(char *dst, const char *src, size_t n){
  //If n is negative... CRASH!
  assert((int)n>=0);   

  dst = shiftRightSetLen(dst, n);
  int i;
  for (i = 0; i<n; i++){
    *(dst+i) = *(src+i);
  }
  //dont forget the null byte...
  *(dst+i) = '\0';
  //return the n characters from src as its own object
  return dst; 
}

char *istrcat(char *dst, const char *src){
  uint32_t srclen;
  uint32_t dstlen;
  //handle empty strings
  if (src[0] == '\0') srclen = 0;
  if (dst[0] == '\0') dstlen = 0;
  //get the length constants
  srclen = istrlen(src);
  dstlen = strlen(dst);
  //create space for the concatenated string
  char *dstcpy_ = malloc (dstlen + srclen+1 +4);
 
  //shift right and copy dst into the new space
  dstcpy_ = shiftRightCpy(dstcpy_, dst);
  //set the length bytes of the new space
  dstcpy_ = setilenbytes(dstcpy_, srclen+dstlen);
  //until src reaches null, copy each char in src ontop of dst in dstcpy_
  int i;
  for (i = 0; *(src+i); i++){
    *(dstcpy_+dstlen+i) = *(src+i);
  }
  //lastly add the null character
  *(dstcpy_+dstlen+i) = '\0';
  return dstcpy_;
}

char *istrncat(char *dst, const char *src, size_t n){
  uint32_t srclen;
  uint32_t dstlen;

  //in the case n is negative... CRASH!
  assert((int)n>=0);
  //handle empty strings
  if (src[0] == '\0') srclen = 0;
  if (dst[0] == '\0') dstlen = 0;
  //get the length constants
   srclen = istrlen(src);
   dstlen = strlen(dst);
  //create space for the new string
  char *dstcpy = malloc(dstlen+1 + n + 4);
  //copy dst into the new string and shift it 4 bytes 
  dstcpy = shiftRightCpy(dstcpy, dst);
  //set the length bytes
  dstcpy = setilenbytes(dstcpy, srclen+n);
  //append n characters from src onto the end of the newly created string
  int i;
  for ( i = 0; i<n && src[i] != '\0'; i++){
    *(dstcpy + dstlen + i) = *(src + i);
  }
  //dont forget to add the null byte
  *(dstcpy + dstlen + i) = '\0';
  //return the newly created appended string
  return dstcpy;

}


char *istrchr(const char *s, int c){
  if (!s){
    return NULL;
  }
  int len = istrlen(s);
  for(int i = 0; i <= len; ++i){
    if (s[i] == c){
      // char* i = malloc(sizeof(char));
      return (char *)s+i;  
    } 
  } 
  return NULL;
}



char *istrrchr(const char *s, int c){
  if (!s){
    return NULL;
  }
  int len = istrlen(s);
  char *last_found = NULL;
  for (int i = 0; i <= len; ++i){
    if (s[i] == c){
      last_found = (char *)&s[i];
    } 
  }
  return last_found;
}


size_t istrfixlen(char *s){
  if (!s){
    return 0;
  }
  int len = istrlen(s);
  for (int i = 0; i < len ;++i){
    if (!isprint(s[i])){
      istrslen(s, i);
      return 1;
    }
  }
  s[len] = '\0';
  return 1;
}


