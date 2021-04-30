#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define maxN 50
struct node         
{
/* 文字列関数を扱えるようにする */ /* 構造体 node の定義 */
  int key; struct node *parent; struct node *left; struct node *right;
};
/* 関数 inorder_tree_walk, tree_search, tree_minimum, tree_insert の宣言 */ 
void tree_print(struct node *T);
void inorder_tree_walk(struct node *x);
struct node *tree_search(struct node *x, int a);
struct node *tree_minimum(struct node *x);
struct node *tree_maximum(struct node *x);
struct node *tree_insert(struct node *T, struct node *x);
struct node *tree_delete(struct node *T, struct node *z);
/* (他の関数も宣言すること) */
int main(void) {
  struct node *Tree; 
  struct node *x;    
  int N;             
  int Data[50];      
  int i;
  char fname[128]; 
  FILE *fp; 
  printf("ファイル名を入力してください.\n"); 
  fgets(fname, sizeof(fname), stdin); 
  fname[strlen(fname) - 1] = '\0'; 
  fflush(stdin); 
  fp = fopen(fname, "r"); 
  fscanf(fp, "%d", &N);   
  if (N>maxN) {
    printf("N is too large, setting N = 50\n");
    N = maxN; 
  }         
  for (i=0;i<N;i++){
    fscanf(fp,"%d",&Data[i]);
  }
  fclose(fp);  
  Tree = NULL; 

  for (i=0;i<N;i++){
    x = (struct node *)malloc(sizeof(struct node));
    x->key = Data[i]; 
    x->parent = x->left = x->right = NULL;
    Tree = tree_insert(Tree, x);
    tree_print(Tree);
  }
  free(x);
  for (i=0;i<N;i++){
    x = (struct node *)malloc(sizeof(struct node));
    x = tree_search(Tree, Data[i]);
    Tree = tree_delete(Tree, x);
    tree_print(Tree);
  }
  free(x);
  free(Tree);
  return 0;
}

void tree_print(struct node *T){
  if (T!=NULL){
    inorder_tree_walk(T);
    printf("\n");
    printf("min=");
    printf("%d", tree_minimum(T)->key);
    printf("max=");
    printf("%d\n", tree_maximum(T)->key);
  } else {
    printf("min=");
    printf("NULL");
    printf("max=");
    printf("NULL\n");
  }
}

void inorder_tree_walk(struct node *x){
  if (x!=NULL) {
    inorder_tree_walk(x->left);
    printf("%d,",x->key);
    inorder_tree_walk(x->right);
  }
}

struct node *tree_search(struct node *x, int a){
  while (x!=NULL && x->key!=a) {
    if (a<x->key)
      x=x->left;
    else
      x=x->right;
  }
  return x;
}

struct node *tree_minimum(struct node *x){
   while (x->left!=NULL){
        x = x->left;
    }
    return (x);
}
struct node *tree_maximum(struct node *x){
   while (x->right!=NULL){
        x = x->right;
    }
    return (x);
}
struct node *tree_insert(struct node *T, struct node *x){
  struct node *r, *y, *z;
    r = T;
    y = NULL;
    z = r;
    while (z!=NULL){
        if (x->key<z->key){
            y = z;
            z = z->left;
        }
        else{
            y = z;
            z = z->right;    
        }
    }
    x->parent = y;
    if(y==NULL){
        r = x;
    }
    else{
        if (x->key>y->key){
            y->right = x;
        }
        else{
            y->left = x;
        }    
    }
    return (r); 
}

struct node *tree_delete(struct node *T, struct node *z){
  struct node *r, *y, *p, *x;
  r = T;
  if (z->right == NULL || z->left == NULL)
    y = z;
  else
    y = tree_minimum(z->right);
  p = y->parent;
  if (y->right != NULL) {
    x = y->right;
    x->parent = p;
  }else if(y->left!=NULL){
    x = y->left;
    x->parent = p;
  }else
    x = NULL;
  if(p==NULL)
    r = x;
  else{
    if(y == p->left)
      p->left = x;
    else
      p->right = x;
  }
  if (y != z) z->key = y->key;
  return r;
}
