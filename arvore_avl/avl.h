#include<stdio.h>

/*
	-Autor: Lucas Baleeiro Dominato.
	-arquivo com tad e prototipos das funcoes da arvore AVl
*/

//tad da arvore AVL.
typedef struct no{
	int chave;
	struct no *esq;
	struct no *dir;
	int bal;
}No;

//TAD onde vamos guardar a raiz da árvore.
typedef struct{
	No *raiz;
}Arvore;


//prototipos das funcoes da arvore AVL.

Arvore* cria_arvore();
int arvore_vazia( Arvore *a);
int alt_no( No * r);
int contagem_nos( No *r);
int calculo_fb( No *r );
No* rotacao_direita( No *r );
No* rotacao_esquerda( No *r );
No* balaceamento( No *r );
No* insercao_folha( No *r,int chave );
int insercao_arvore( Arvore *a, int chave );
No* remocao_no( No *r,int chave );
int remocao_arvore( Arvore *a,int chave );
int pos_ordem( No *r );
No* libera_arvore1( No *r );
int libera_arvore2( Arvore *a );

	
