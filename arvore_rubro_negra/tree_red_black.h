#include<stdio.h>

/*
	-Autor : Lucas Baleeiro Dominato.
	-arquivo contem os TADs da arvore rubro negra e os prototipos das funcoes.
*/

typedef struct node{
	int color; //0 vermelho e 1 preto.
	int key;
	struct node *right;
	struct node *left;
	struct node *parent;

}Node;

typedef struct tree{
	
	Node *root; //raiz da arvore.

}Tree;

//prototipos das funcoes.
Node* make_t_nill();
Tree* make_tree(Node *t_nill );
int tree_empty( Tree *t,Node *t_nill);
int altura_no( Node *r , Node *t_nill );
int em_ordem( Node *no ,Node *t_nill );
int insert_node(Tree *t , int info , Node *t_nill);
int RB_insert_fixup( Node *no, Tree *t ); //parametros sao o no inserido e o tad da arvore.
int RB_delete_fix_up(Tree *t,Node *x);	
int delete_node( Tree *t , int info, Node *t_nill ); //com mudancas para adequacao da redblack.
Node* search_minimo( Node *no ,Node *t_nill);
Node* search_maximo( Node *no , Node *t_nill);
int left_rotate( Node *no , Tree *t );
int right_rotate( Node *no, Tree *t );
