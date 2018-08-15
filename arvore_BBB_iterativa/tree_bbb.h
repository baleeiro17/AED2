#include<stdio.h>
#include<stdlib.h>

/*
	-codigo da arvore binaria de busca sem recursao.
*/

//estrutura do no .

typedef struct node
{
	struct node *right; //guarda o filho da esquerda.
	struct node *left;  //guarda o filho da direita.	
	struct node *parent;	//guarda o pai do no.
	int key; //guarda a informacao do no.
	
}Node;


//estrutura da arvore binaria de busca.
typedef struct tree
{
	Node *root; //guarda a raiz da arvore.
	
}Tree;

//prototipos das funcoes utlizadas pela arvore binaria de busca.
Tree* make_tree();
int tree_full(Tree *t); //desnecessario
int tree_empty( Tree *t);
int insert_node( Tree *t,int info );
int delete_node_1( Tree *t,int info);	//uso do minimo.
int delete_node_2( Tree *t,int info);	//uso do maximo.
int search_node( Tree *t,int info );
int em_ordem( Node *no ); //recursivo somente para teste.
int free_tree( Tree *t );
Node* search_minimo( Node *no );



