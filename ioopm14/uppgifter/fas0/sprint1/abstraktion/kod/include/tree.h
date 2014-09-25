//tree specific
/* void addLeaf(BinTreeNode *root, BinTreeNode leaf); */
/* char *queryTree(BinTreeNode bt, char *match); */
/* void updateTree(BinTreeNode bt, char *match, char *newVal); */
/* void insertLeaf(BinTreeNode bt, char key, char value); */
/* void deleteNode(BinTreeNode bt, char *match); */
/* void printTree(BinTreeNode bt); */
typedef char* treeKeyT;
typedef int treeValueT;
typedef struct
{
  treeKeyT key;
  treeValueT value;
} treeElementT;

typedef struct treeCDT *treeADT;
