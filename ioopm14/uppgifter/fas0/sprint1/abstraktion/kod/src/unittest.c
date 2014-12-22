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

void testCREATETREE(){
  Node root = createTREE();
  CU_ASSERT(root == NULL);
  destroy(root);
}

void testDESTROY(){
  Node root = fillFromFile("TEST.db");
  destroy(root);
  CU_ASSERT(root == NULL);
}

void testQUERY(){
  Node root = fillFromFile("TEST2.db");
  Node test = query(root, "Leo");
  CU_ASSERT(test->value == "3");
  CU_ASSERT(query(root,"Yipman") == NULL);
}

void testFINDMIN(){
  Node root = fillFromFile("TEST.db");
  Node min = findMin(root);
  CU_ASSERT(min->value == "1");
  Node root = delete(min);
  min = findMin(root);
  CU_ASSERT(min->value == "2");
  min = findMin(root);
  CU_ASSERT(min->value == "3");
  destroy(root);
}

void testGETNEWNODE(){
  Node node = getNewNode("aaaa", "40");
  CU_ASSERT( node-> key == "aaaa");
  CU_ASSERT( node-> value == "40");
  CU_ASSERT( node-> left == NULL);
  CU_ASSERT( node-> right == NULL);
}

void testFILLFROMFILE(){
  Node root = fillFromFile("TEST.db");
  Node node = NULL;
  CU_ASSERT(root != NULL);
  node = query(root, (char*)'a');
  CU_ASSERT(node->value == "1");
  node = query(root, (char*)'acb');
  CU_ASSERT(node->value == "20");
  node = query(root, (char*)'ccc');
  CU_ASSERT(node->value == "39");
  destroy(root);
}

void testDELETE(){
  Node root = fillFromFile("TEST2.db");
  //delete root node
  delete(root, "Anders");
  CU_ASSERT(query(root, "Anders") == NULL);
  CU_ASSERT(root->key != "Anders");
  //delete leaf node
  delete(root, "Leo");
  CU_ASSERT(query(root, "Leo") == NULL);
  //delete node with one child
  delete(root, "Ture");
  CU_ASSERT(query(root, "Ture") == NULL);
  //delete node with two children
  delete(root, "Karin");
  CU_ASSERT(query(root, "Karin") == NULL);
  //Two more nodes
  delete(root, "Kerstin");
  CU_ASSERT(query(root, "Kerstin") == NULL);
  delete(root, "Erik");
  CU_ASSERT(query(root, "Erik") == NULL);
  //Last node that should be the root node
  CU_ASSERT(root->key == "Cecilia");
  delete(root, "Cecilia");
  CU_ASSERT(query(root, "Cecilia") == NULL);
  CU_ASSERT(root == NULL);

}

void testINSERT(){
  Node root = fillFromFile("TEST2.db");
  insert(root, getNewNode("Abba", "1"));
  Node test1 = query(root, "Abba");
  CU_ASSERT(test1->key == "Abba");
  CU_ASSERT(test1->value == "1");
  CU_ASSERT(query(root, "Yipman") == NULL);
  destroy(root);
}

void testUPDATE(){
  Node root = fillFromFile("TEST2.db");
  update(root, "Leo", "5");
  Node test = query(root, "Leo");
  CU_ASSERT(test->value == "5");
  update(root, "Yipman", "1");
  CU_ASSERT(query(root, "Yipman") == NULL);
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
      (NULL == CU_add_test(pSuite1, "test of CREATETREE()", testCREATETREE)) ||
      (NULL == CU_add_test(pSuite1, "test of DESTROY()", testDESTROY)) ||
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

