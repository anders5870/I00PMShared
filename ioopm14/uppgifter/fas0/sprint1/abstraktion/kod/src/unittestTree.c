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

void testFindMin(){
  BstNode root = fillFromFile("SWE.db");
  BstNode findMin(root);
  CU_ASSERT(root->value == "01");
}

void testGetNewNode(){
  BstNode node = getNewNode("Anders", "24");
  CU_ASSERT( node-> key == "Anders");
  CU_ASSERT( node-> value == "24");
  CU_ASSERT( node-> left == NULL);
  CU_ASSERT( node-> right == NULL);
}

//PRE: file must not be empty
void testFillFromFile(){
  BstNode root = fillFromFile("SMALL.db");
  //test if the file is being red
  CU_ASSERT(root != NULL );
}

void testDestroy(){
   BstNode root = fillFromFile("SMALL.db");
   destroy(root);
   CU_ASSERT(root == NULL);
}

void testDelete(){
   BstNode root = fillFromFile("SMALL.db");
  delete(root);//delete Hegeka Borizery
  BstNode test = query(root, "Hegeka Borizery");
  CU_ASSERT(test != NULL);
}

void testInsert(){
  BstNode root = fillFromFile("SMALL.db");
  insert(root);
  BstNode test = query(root, "Anders");
  CU_ASSERT(test != NULL);
}

void testQuery(){
  char buffer[128];
  buffer = "Boris";
  BstNode root = fillFromFile("SMALL.db");
  BstNode test = query(root, buffer);
  CU_ASSERT(test->value == 23);
  buffer = "Anders";
  CU_ASSERT(test == NULL);
}

void testUpdate(){
  char buffer[128];
  buffer = "Boris";
  BstNode root = fillFromFile("SMALL.db");
  update(root);
  BstNode test = query(root, buffer);
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
      (NULL == CU_add_test(pSuite1, "test of fillFromFile()", testFillFromFile)) ||
      (NULL == CU_add_test(pSuite1, "test of createTree()", testCreateTree)) ||
      (NULL == CU_add_test(pSuite1, "test of getNewNode()", testGetNewNode)) ||
      (NULL == CU_add_test(pSuite1, "test of findMin()", testFindMin))
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Advanced Functions Suite */
  if (
      (NULL == CU_add_test(pSuite2, "test of destroy()", testDestroy)) ||
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

