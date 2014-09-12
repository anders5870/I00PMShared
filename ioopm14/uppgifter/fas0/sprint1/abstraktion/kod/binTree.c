typedef struct binTreeNode{
  char *key;
  char *value;
  struct binTreeNode *lLeaf;
  struct binTreeNode *rLeaf;
}

void addLeaf(struct binTreeNode *root, struct binTreeNode leaf){
  if(*root->key != leaf->key){
    if(*root->key > leaf->key){
      if(root->rLeaf != NULL){
	addLeaf(*root->rleaf, leaf);
      }
      else{
	*root->rLeaf = leaf;
      }
      else{
	if(*root->lLeaf != NULL){
	  addLeaf(*root->lLeaf, leaf);
	}
	else{
	  *root->lLeaf = leaf;
	}
      }
    }
  }
  else{
    //todo - error duplicate key
  }
}

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void fillFromFile(struct binTreeNode *bt, FILE *database){
  char buffer[128];
    while(!(feof(database))){
    binTreeNode newNode = malloc(sizeof(struct binTreeNode));
    readline(buffer, sizeof(buffer), database);
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    readline(buffer, sizeof(buffer), database);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    addLeaf(bt, newNode);
  }
}
