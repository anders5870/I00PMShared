#include <string.h>
#include "CUnit/Basic.h"
#include "db.h"
#include "stack.h"
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


//PRE: file must not be empty
void testFillFromFile(){
  Node root = fillFromFile("SMALL.db");
  //test if the file is being red
  CU_ASSERT(root != NULL );
}


void testDelete(){
   Node root = fillFromFile("SMALL.db");
  delete(root);//delete Hegeka Borizery
  Node test = query(root, "Hegeka Borizery");
  CU_ASSERT(test != NULL);
}

void testInsert(){
  Node root = fillFromFile("SMALL.db");
  insert(root);
  Node test = query(root, "Anders");
  CU_ASSERT(test != NULL);
}

void testQuery(){
  char buffer[128];
  buffer = "Boris";
  Node root = fillFromFile("SMALL.db");
  Node test = query(root, buffer);
  CU_ASSERT(test->value == 23);
  buffer = "Anders";
  CU_ASSERT(test == NULL);
}

void testUpdate(){
  char buffer[128];
  buffer = "Boris";
  Node root = fillFromFile("SMALL.db");
  update(root);
  Node test = query(root, buffer);
  CU_ASSERT(test->value == 100);
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
      (NULL == CU_add_test(pSuite1, "test of fillFromFile()", testFillFromFile))
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Advanced Functions Suite */
  if (
      (NULL == CU_add_test(pSuite2, "test of insert()", testInsert)) ||
      (NULL == CU_add_test(pSuite2, "test of delete()", testDelete)) ||  
      (NULL == CU_add_test(pSuite2, "test of query()", testQuery)) ||
      (NULL == CU_add_test(pSuite2, "test of update()", testUpdate))
      
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

