#include <string.h>
#include "CUnit/Basic.h"
#include "istring_rep.h"
#include "istring.h"
#include <stdlib.h>

int init_suite_1(void)
{
  return 0;
}

int clean_suite_1(void)
{
  return 0;
}

int init_suite_2(void)
{
  return 0;
}

int clean_suite_2(void)
{
  return 0;
}


void testISTRING_MK(void)
{
  char *str1 = istring_mk(NULL);
  CU_ASSERT(str1[0] == '\0');
  char str2[] = "foo";
  char *str3 = istring_mk(str2);
  char *str4 = istring_mk("  ");
  CU_ASSERT(str4[0] == ' ');
  CU_ASSERT(str4[1] == ' ');
  CU_ASSERT(istrlen(str4) == 2);
  CU_ASSERT(strlen(str3) == strlen(str2));
  CU_ASSERT(strcmp(str2, str3)  == 0);
  CU_ASSERT(str3[0]  == 'f');
  CU_ASSERT(str3[1]  == 'o');
  CU_ASSERT(str3[2]  == 'o');
  CU_ASSERT(str3[3]  == '\0');
  str3[0]  = 'F';
  CU_ASSERT(strcmp(str2, str3) > 0);
  istring_rm(str1);
  istring_rm(str3);
}

void testISTRING_RM(void)
{
  istring_rm(istring_mk("test"));
}

void testISTRLEN(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("ekieki");
  CU_ASSERT(istrlen(str1) == 4);
  CU_ASSERT(istrlen(str2) == 6);
  //START(str2)->length = 3; 
  //CU_ASSERT(istrlen(str2) == 3);
  CU_ASSERT(strlen(str2) == 6);
  istring_rm(str1);
  istring_rm(str2);
}

void testISTRING_TO_STRING(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_to_string(str1);
  char *str3 = istring_mk("");
  char *str4 = istring_to_string(str3);
  CU_ASSERT(strcmp(str2, "spam") == 0);
  CU_ASSERT(strcmp(str3, str4) == 0);
  istring_rm(str1);
  free(str2);
}


void testISTRCAT(void)
{
  // "natur" + "rutan"
  char *str1 = "natur";
  char *str2 = istring_mk("rutan");
  char *str3 = istrcat(str1,str2);
  CU_ASSERT(istrcmp(str3, "naturrutan") == 0);
  istring_rm(str2); 
  istring_rm(str3);
 // "" + "abc" 
  str1 = "";
  str2 = istring_mk("abc");
  str3 = istrcat(str1, str2);
  CU_ASSERT(istrcmp(str3, "abc") == 0);
  istring_rm(str2); 
  istring_rm(str3); 
  // "abc" + ""
  str1 = "abc";
  str2 = istring_mk("");
  str3 = istrcat(str1, str2);
  CU_ASSERT(istrcmp(str3, "abc") == 0);
  istring_rm(str2); 
  istring_rm(str3);
  // "" + ""
  str1 = "";
  str2 = istring_mk("");
  str3 = istrcat(str1, str2);
  CU_ASSERT(istrcmp(str3, "") == 0);
  istring_rm(str2); 
  istring_rm(str3);
 
  // Own tests implemented
  //CU_FAIL("Test not implemented yet");
}

void testISTRNCAT(void)
{
  //choklad + boll (bollar)
  char *str1 = "choklad";
  char *str2 = istring_mk("bollar");
  char *str3 = istrncat(str1,str2,4);
  CU_ASSERT(istrcmp(str3, "chokladboll") == 0);
  istring_rm(str2); 
  istring_rm(str3); 
  // "" + "" (abc)
  str1 = "";
  str2 = istring_mk("abc");
  str3 = istrncat(str1, str2, 0);
  CU_ASSERT(istrcmp(str3, "") == 0);
  istring_rm(str2); 
  istring_rm(str3); 
  // "" + abc
  str1 = "";
  str2 = istring_mk("abc");
  str3 = istrncat(str1, str2, 3);
  CU_ASSERT(istrcmp(str3, "abc") == 0);
  istring_rm(str2); 
  istring_rm(str3);
  // "" + ""
  str1 = "";
  str2 = istring_mk("");
  str3 = istrncat(str1, str2, 3);
  CU_ASSERT(istrcmp(str3, "") == 0);
  istring_rm(str2); 
  istring_rm(str3);
  // "abc" + ?? //how to deal with n = -1?
  str1 = "abc";
  str3 = istrncat(str3, str1, 3);
  CU_ASSERT(istrcmp(str1, str3) == 0);
  istring_rm(str3);
  // Own tests implemented
  //CU_FAIL("Test not implemented yet");
}

void testISTRCHR(void)
{
  char *str = istring_mk("spam spam bacon spam");
  char *str2 = istring_mk(" ");
  CU_ASSERT(istrchr(str2, ' ') == str2);
  CU_ASSERT(istrchr(str, 's') == str);
  CU_ASSERT(istrchr(str, 'b') == str + 10);
  CU_ASSERT(istrchr(str, 'c') == str + 12);
  CU_ASSERT(istrchr(str, 's') == str);
  CU_ASSERT(istrchr(str, '\0') == str + 20);
  CU_ASSERT(istrchr(str, 'x') == NULL);
  istring_rm(str);
}

void testISTRRCHR(void)
{
  char *str = istring_mk("spam spam bacon spam");
  CU_ASSERT(istrrchr(str, 's') == str + 16);
  CU_ASSERT(istrrchr(str, 'b') == str + 10);
  CU_ASSERT(istrrchr(str, 'c') == str + 12);
  CU_ASSERT(istrrchr(str, 's') == str + 16);
  CU_ASSERT(istrrchr(str, '\0') == str + 20);
  CU_ASSERT(istrrchr(str, 'x') == NULL);
  istring_rm(str);
}

void testISTRCMP(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("spam");
  char *str3 = istring_mk("Spam");
  CU_ASSERT(istrcmp(str1, str1) == 0);
  CU_ASSERT(istrcmp(str1, str2) == 0);
  CU_ASSERT(istrcmp(str2, str3) > 0);
  CU_ASSERT(istrcmp(str3, str2) < 0);
  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
}

void testISTRNCMP(void)
{
  char *str1 = istring_mk("spam ");
  char *str2 = istring_mk("spam");
  char *str3 = istring_mk("Spam");
  CU_ASSERT(istrncmp(str1, str2, 4) == 0);
  CU_ASSERT(istrncmp(str1, str2, 5) > 0);
  CU_ASSERT(istrncmp(str2, str3, 4) > 0);
  CU_ASSERT(istrncmp(str3, str2, 4) < 0);
  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
}

//Minnesläcka.
void testISTRCPY(void)
{
  //copy "spam" from str1 into str2
  char *str1 = istring_mk("spam");
  char *str2 = malloc(strlen(str1)+ 4+1);
  str2 = istrcpy(str2,str1);
  CU_ASSERT(istrcmp(str1, str2) == 0);
  istring_rm(str1);
  //copy "" from str1 into str2
  str1 = istring_mk("");
  str2 = str2-4;
  str2 = istrcpy(str2,str1);
  CU_ASSERT(istrcmp(str1, str2) == 0);
  istring_rm(str1);
  istring_rm(str2);
  // Own tests implemented
  // CU_FAIL("Test not implemented yet");
}


void testISTRNCPY(void)
{
  //copy 0 characters from str1 into str2
  char *str1 = istring_mk("spam");
  char *str2 = malloc(strlen(str1)+4+1);
  str2 = istrncpy(str2,str1, 0);
  CU_ASSERT(istrcmp(str2,"") == 0);
  istring_rm(str1);
  //Copys 4 chars from str1 to str2
  str1 = istring_mk("spam");
  str2 = str2-4;
  str2 = istrncpy(str2,str1, 4);
  CU_ASSERT(istrcmp(str1,str2) == 0);
  istring_rm(str1);
  //copy 10 chars from str1 into str2
  str1 = istring_mk("");
  str2 = str2-4;
  str2 = istrncpy(str2,str1, 10);
  CU_ASSERT(istrcmp(str2, "") == 0);
  istring_rm(str1);
  istring_rm(str2);
  // Own tests implemented
  // CU_FAIL("Test not implemented yet");
}


void testISTRSLEN(void)
{
  char *str1 = istring_mk("");
  char *str2 = istring_mk("ekieki");
  str1 = istrslen(str1, 2);
  str2 = istrslen(str2, 9);
  CU_ASSERT(istrlen(str1) == 0);
  CU_ASSERT(istrlen(str2) == 9);
  CU_ASSERT(str1[0] == '\0');
  CU_ASSERT(str2[8] == 'i');
  //START(str2)->length = 3; 
  //CU_ASSERT(istrlen(str2) == 3);
  CU_ASSERT(strlen(str1) == 0);
  CU_ASSERT(strlen(str2) == 9);
  str1 = istrslen(str1, 0);
  CU_ASSERT(str1[0] == '\0');
  istring_rm(str1);
  istring_rm(str2);
}


void testISTRFIXLEN(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("spam");

  str1[2] = '\0';
  str2[4] = 'a';
  
  istrfixlen(str1);
  istrfixlen(str2);
  CU_ASSERT(istrlen(str1) == strlen(str1));
  CU_ASSERT(istrlen(str1) == 2);
  CU_ASSERT(str2[4] == '\0');
  CU_ASSERT(istrlen(str2) == 4);
  istring_rm(str1);
  istring_rm(str2);
}


int main()
{
  CU_pSuite pSuite1 = NULL;
  CU_pSuite pSuite2 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  pSuite2 = CU_add_suite("Advanced Functions Suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suites */
  /* Basic Functions Suite */
  if (
      (NULL == CU_add_test(pSuite1, "test of istring_mk()", testISTRING_MK)) ||
      (NULL == CU_add_test(pSuite1, "test of istring_rm()", testISTRING_RM)) ||
      (NULL == CU_add_test(pSuite1, "test of istring_to_string()", testISTRING_TO_STRING)) ||
      (NULL == CU_add_test(pSuite1, "test of istrlen()", testISTRLEN))
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Advanced Functions Suite */
  if (
      (NULL == CU_add_test(pSuite2, "test of istrcat()", testISTRCAT)) ||
      (NULL == CU_add_test(pSuite2, "test of istrncat()", testISTRNCAT)) ||
      (NULL == CU_add_test(pSuite2, "test of istrchr()", testISTRCHR)) || 
      (NULL == CU_add_test(pSuite2, "test of istrrchr()", testISTRRCHR)) || 
      (NULL == CU_add_test(pSuite2, "test of istrcmp()", testISTRCMP)) ||
      (NULL == CU_add_test(pSuite2, "test of istrncmp()", testISTRNCMP)) ||
      (NULL == CU_add_test(pSuite2, "test of istrcpy()", testISTRCPY)) ||
      (NULL == CU_add_test(pSuite2, "test of istrslen()", testISTRSLEN)) ||
      (NULL == CU_add_test(pSuite2, "test of istrfixlen()", testISTRFIXLEN)) ||
      (NULL == CU_add_test(pSuite2, "test of istrncpy()", testISTRNCPY))
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

