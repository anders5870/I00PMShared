//Beh�ver kollas med valgrind.
char* istrslen(char *s, size_t length){
  char *temp2 = START(s);
  uint32_t length_old;
  length_old = (temp2[0] << 24) | (temp2[1] << 16) | (temp2[2] << 8) | temp2[3];
  uint32_t length_new = length;
  
  //Vid kortare istringl�ngd �n ny l�ngd.
  if (length_old > length_new){
    char *iStrPointer = START(s);
    //S�tter l�ngdbytesen till den nya l�ngden.
    *(iStrPointer + 0) = (length_new >> 24) & 0xFF;
    *(iStrPointer + 1) = (length_new >> 16) & 0xFF;
    *(iStrPointer + 2) = (length_new >> 8) & 0xFF;
    *(iStrPointer + 3) = length_new & 0xFF;
    //S�tter sista byten i str�ngen till '\0'.
    iStrPointer = STRING(iStrPointer);
    *(iStrPointer + length_new) = '\0';
    return iStrPointer;
    //Om l�ngderna �r lika beh�vs ingen modifikation.
  }else if (length_old == length_new){
    return s;
    //Vid l�ngre ny l�ngd skapas en ny istring.
  }else{
    //Ta n�st sista elementet i arrayen (l�ngd-1) och fylla ut resten med den.
    char *iStrPointer = s;
    char temp_string[length_new];
    //Kopierar str�ngen till temp_string.
    for (int i=0; i < length_old; ++i){
      *(temp_string+i) = *(iStrPointer+i);  
    }
    for (int i=length_old; i < length_new; ++i){
      *(temp_string + i) = *(iStrPointer+length_old-1);
    }
    *(temp_string + length_new) = '\0';
    //Nu finns hela v�r "nya" str�ng i temp_string.
    free(START(iStrPointer));
    char *new_istring = istring_mk(temp_string);
    return new_istring;
  }
}


//Tester
  str3 = istrslen(str3, 6);
  printf("8. %s\n", str3);
  printf("9. %d\n", strlen(str3));
