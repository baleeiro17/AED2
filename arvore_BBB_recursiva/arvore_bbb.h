#include<stdio.h>


/*
	programa que contem o tad da arvore BBB e  suas principais funcoes.
*/

typedef struct no
{
	int chave;
	struct no *dir;
	struct no *esq;
	
}No;

typedef struct 
{
	No *raiz;
	int qtd;
	
}Arvore;

//prototipos das funcoes.
Arvore* cria_arvore();
int arvore_vazia( Arvore *a);
int insere_arvore( Arvore *a,int dado );
int insere_folha( No *r,int dado );
int pre_ordem( No *r );
int em_ordem( No *r );
int pos_ordem( No *r );
int remove_arvore( Arvore *a,int chave );
No* remove_no( No *r,int chave );
int altura_no( No *r );	
No* libera_arvore1( No *r);
int libera_arvore2( Arvore *a );
int contagem_nos( No *r );
No* buscar_no(No *r,int valor_procurado);

