#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 50
struct node {
/* 文字列関数を扱えるようにする */ /* 構造体 node の定義 */
  int key; struct node *parent; struct node *left; struct node *right;
};
/* 関数 inorder_tree_walk, tree_search, tree_minimum, tree_insert の宣言 */ 
void inorder_tree_walk(struct node *x);
struct node *tree_search(struct node *T, int a);
struct node *tree_minimum(struct node *x);
struct node *tree_maximum(struct node *x);
struct node *tree_insert(struct node *T, struct node *x);
/* (他の関数も宣言すること) */
int main(void){
    struct node *Tree;
    struct node *x, *y, *z;
    int N;
    int Data[maxN];
    int i;
    int a;
    char fname[128];
    FILE *fp;
    printf("ファイル名を入力してください.\n");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    fflush(stdin);
    fp = fopen(fname, "r");
    fscanf(fp, "%d", &N);
    if (N > maxN){
        printf("N is too large, setting N = %d\n", maxN);
        N = maxN; 
    }
    for (i=0; i<N; i++){
    fscanf(fp, "%d", &Data[i]);
    }
    fclose(fp);
    Tree = NULL;
    for (i=0; i<N; i++){
        x = (struct node *)malloc(sizeof (struct node));
        x->key = Data[i]; 
        x->parent = x->left = x->right = NULL;
        Tree = tree_insert(Tree, x);
        inorder_tree_walk(Tree);
        printf("\n");
        y = tree_minimum(Tree);
        a = y->key;
        printf("min=%d,",a);
        z = tree_maximum(Tree);
        a = z->key;
        printf("max=%d\n",a);
    }
    return (0); 
}
void inorder_tree_walk(struct node *x){
    if(x!=NULL){
        inorder_tree_walk(x->left);
        printf("%d,",x->key);
        inorder_tree_walk(x->right);
    }   
}
struct node *tree_search(struct node *T, int a){    
    do{
        if (a<T->key){
            T = T->left;      
        }
        else{
            T = T->right;
        }
    } while (T!=NULL && T->key!=a);
    return (T);
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

