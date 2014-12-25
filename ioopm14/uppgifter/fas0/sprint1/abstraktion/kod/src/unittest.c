#include <string.h>
#include "CUnit/Basic.h"
#include "treeSpecific.h"
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

void testDESTROY(){
  Node root = fillFromFile("TEST2.db");
  CU_ASSERT(root != NULL);
  destroy(root);
}

void testSEARCHITERATIVEPARENT(){
  Node root = fillFromFile("TEST2.db");
  Node parent = searchIterativeParent(root, "Cecilia");
  CU_ASSERT(strcmp(parent->key, "Anders") == 0);
  parent = searchIterativeParent(root, "Karin");
  CU_ASSERT(strcmp(parent->key, "Cecilia") == 0);
  destroy(root);
}

void testQUERY(){
  Node root = fillFromFile("TEST2.db");
  Node test = query(root, "Leo");
  CU_ASSERT(strcmp(test->value, "3") == 0);
  CU_ASSERT(query(root,"Yipman") == NULL);
  destroy(root);
}

/** Discovered that greater nodes are inserted
 *  on the left instead of on the right in
 *  the insert function, so the smallest nodes
 *  will be found on the right instead of
 *  on the left by findMind() but it poses
 *  no problems as long as its behavior is
 *  known.
 */
void testFINDMIN(){
  Node root = fillFromFile("TEST2.db");
  Node min = findMin(root);
  CU_ASSERT(strcmp(min->key, "Aaa") == 0);
  root = delete(root, min->key);
  min = findMin(root);
  CU_ASSERT(strcmp(min->key, "Aaron") == 0);
  root = delete(root, min->key);
  min = findMin(root);
  CU_ASSERT(strcmp(min->key, "Aas") == 0);
  destroy(root);
}

void testGETNEWNODE(){
  Node node = getNewNode("aaaaa", "400");
  CU_ASSERT(strcmp(node->key, "aaaaa") == 0);
  CU_ASSERT(strcmp(node->value, "400") == 0);
  CU_ASSERT( node-> left == NULL);
  CU_ASSERT( node-> right == NULL);
  free(node);
}

void testFILLFROMFILE(){
  Node root = fillFromFile("TEST.db");
  Node node = NULL;
  CU_ASSERT(root != NULL);
  node = query(root, "a");
  CU_ASSERT(strcmp(node->value, "1") == 0);
  node = query(root, "acb");
  CU_ASSERT(strcmp(node->value, "20") == 0);
  node = query(root, "ccc");
  CU_ASSERT(strcmp(node->value, "39") == 0);
  destroy(root);
}

void testDELETE(){
  Node root = fillFromFile("TEST2.db");
  //delete root node
  root = delete(root, "Anders");
  CU_ASSERT(query(root, "Anders") == NULL);
  CU_ASSERT(strcmp(root->key, "Anders") != 0);
  //delete leaf node
  root = delete(root, "Leo");
  CU_ASSERT(query(root, "Leo") == NULL);
  //delete node with one child
  root = delete(root, "Ture");
  CU_ASSERT(query(root, "Ture") == NULL);
  //delete node with two children
  root = delete(root, "Karin");
  CU_ASSERT(query(root, "Karin") == NULL);
  root = delete(root, "Abba");
  CU_ASSERT(query(root, "Abba") == NULL);
  //delete all remaining except the root
  root = delete(root, "Cecilia");
  root = delete(root, "Ace");
  root = delete(root, "Aaron");
  root = delete(root, "Kerstin");
  root = delete(root, "Aas");
  root = delete(root, "Aau");
  root = delete(root, "Aaa");
  //delete root
  root = delete(root, "Erik");
  CU_ASSERT(root == NULL);
  destroy(root);
  
}

void testINSERT(){
  Node root = fillFromFile("TEST2.db");
  char *key = malloc(strlen("Kalle")+1);
  char *value = malloc(strlen("1")+1);
  strcpy(key, "Kalle");strcpy(value, "1");
  root = insertIterative(root, key, value);
  Node test = query(root, "Kalle");
  CU_ASSERT(strcmp(test->key, "Kalle") == 0);
  CU_ASSERT(strcmp(test->value, "1") == 0);
  CU_ASSERT(query(root, "Yipman") == NULL);
  destroy(root);

}

void testUPDATE(){
  Node root = fillFromFile("TEST2.db");
  Node node = query(root, "Leo");
  update(node, "50");
  CU_ASSERT(strcmp(node->value, "50") == 0);
  node = query(root, "Yipman");
  CU_ASSERT(query(root, "Yipman") == NULL); 
  // char *buffer2 = "150";
  node = query(root, "Leo");
  update(node, "150");
  node = query(root, "Yipman");
  CU_ASSERT(node == NULL);
  destroy(root);
  
}


int main()
{
  CU_pSuite pSuite1 = NULL;

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
  
  if (
      /* (NULL == CU_add_test(pSuite1, "test of CREATETREE()", testCREATETREE)) ||*/
      (NULL == CU_add_test(pSuite1, "test of DESTROY()", testDESTROY)) ||
      (NULL == CU_add_test(pSuite1, "test of SEARCHITERATIVEPARENT()", testSEARCHITERATIVEPARENT)) ||
      (NULL == CU_add_test(pSuite1, "test of QUERY()", testQUERY)) ||
      (NULL == CU_add_test(pSuite1, "test of FINDMIN()", testFINDMIN)) ||
      (NULL == CU_add_test(pSuite1, "test of GETNEWNODE()", testGETNEWNODE))||
      (NULL == CU_add_test(pSuite1, "test of FILLFROMFILE()", testFILLFROMFILE)) ||
      (NULL == CU_add_test(pSuite1, "test of DELETE()", testDELETE)) ||
      (NULL == CU_add_test(pSuite1, "test of INSERT()", testINSERT)) ||
      (NULL == CU_add_test(pSuite1, "test of UPDATE()", testUPDATE))
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

