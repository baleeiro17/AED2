#include<stdio.h>
#include "arvore_bbb.h"

//codigo das funcoes da arvore BBB.

Arvore* cria_arvore(){
	Arvore *a;
	
	a=(Arvore *)malloc(sizeof( Arvore));
	if( !a ) return NULL;
	
	a->raiz=NULL;
	a->qtd=0;
	
	return a;
}

int arvore_vazia( Arvore *a ){
	
	if( a->raiz == NULL ) return 1;
	return 0;
	
}

//calcula a altura de um determinado nó se quisermos saber a altura da árvore basta fornecer a sua raiz.
int altura_no( No *r ){
	
	if( r == NULL ) return -1;
	
	if( altura_no(r->esq) > altura_no(r->dir) )
		return ( altura_no(r->esq) + 1 );
	else
		return ( altura_no(r->dir) + 1 );
}

//retorna a quantidade de nós por sub-árvore.
int contagem_nos( No *r ){
	
	if( r == NULL ) return 0;
	
	return ( contagem_nos(r->esq) + contagem_nos(r->dir) + 1 );
	
}

//perceba que aqui as ligações são feitas manualmente como no caso da listas,sempre inserimos no local adequdo e manualmente colocamos o NULL,o que não era feito na remoção,onde removemos um elemento e não checamos as ligações anteriores daquele elemento,na nossa nova resolução isso ocorre.
int insere_folha( No *r,int chave ){
	No *novo;
	
	
	//caso a chave seja maior que raiz ou o nó comparado.
	if( chave > r->chave ){
	
		//movimenta pela direita da árvore,sempre mantendo o r como pai,da possivel folha que vamos inserir.
		if( r->dir == NULL ){
			
			//lidando com os contéudos dos nós.
			novo=(No *)malloc(sizeof(No));
			novo->chave=chave;
			novo->esq=NULL;
			novo->dir=NULL;
			
			//liga com a árvore,pois ainda temos o seu possivel pai como r.
			r->dir=novo;
			return 1; //ocorreu tudo ok;
		}
		//movimenta pela direita.
		//importante do uso do return é que o mesmo não gera pilhas,para baixo,ao achar o seu ponto a função termina.
		else return insere_folha(r->dir,chave);
	}
	else if( chave < r->chave ){
		
		//movimenta pela esquerda da árvore,sempre mantendo o r como pai, da possivel folha que vamo inserir.
		if( r->esq == NULL ){
			//lidando com os contéudos dos nós.
			novo=(No *)malloc(sizeof(No));
			novo->chave=chave;
			novo->esq=NULL;
			novo->dir=NULL;
			
			//liga com a árvore,pois ainda temos o seu possivel pai como r.
			r->esq=novo;
			return 1; //ocorreu tudo ok.
		
		}
		//movimenta pela esquerda.
		//importante do uso do return é que o mesmo não gera pilhas.
		else return insere_folha(r->esq,chave);
	}
	else return 0; //elemento duplicado provalvemente.
}

int insere_arvore( Arvore *a,int chave){
	No *novo;
	
	//lidando com os casos.
	
	//arvore vazia.
	if( arvore_vazia(a) ){
	
		novo=(No *)malloc(sizeof(No));
		novo->chave=chave;
		a->raiz=novo;
		novo->esq=NULL;
		novo->dir=NULL;
		return 1;
	}	
	else{
		if( !insere_folha(a->raiz,chave) ){
			//printf("elemento duplicado\n");
			return 0; //codigo de erro.
		}
		return 1;
	}	
}




No* remove_no( No *r ,int chave ){
	No *lixo;
	
	//pensando no caso da chave não existir na árvore teremos então:
	//evita a procura de dados em uma mémoria NULL.
	if( r == NULL ){
		//printf("chave não existente na árvore.\n");
		return r; //para manter as ligações da árvore intactas no despilhamento.
	}	
	
	if( r->chave == chave ){
		
		//entro no processo de remoção do nó.
		//nó com um filho e sem filho.
		if( r->esq == NULL || r->dir == NULL ){
			
			//serve para o caso do nó sem filhos e com um filho.
			if( r->esq == NULL ){
				lixo=r;
				r=r->dir;
				free(lixo);
				lixo=NULL;
				return r;
			}
			else{
				lixo=r;
				r=r->esq;
				free(lixo);
				lixo=NULL;
				return r;
			}		
		}
		//caso do nó com dois filhos.
		else{
			
			lixo=r->esq;
			//movimenta pela esquerda em busca do maior elemento na sub-árvore da esquerda..
			//aqui faz uso de um aux para movimentar na árvore não de uma recursão.
			while( lixo->dir != NULL )
				lixo=lixo->dir;
			
			//troca os contéudos de lugares.
			r->chave=lixo->chave;
			//faço o processo de eliminação do lixo.
			r->esq=remove_no(r->esq,lixo->chave);
			
			//retorna o elemento que foi mudado,caso ele seja a raiz é importante,porém esse return evita o desempilhamento,ultrapasse as proximas linhas de código.
			return r;
		}
	}
	
	//uso do return evita desempilhamentos desnecesários aqui.
	if( chave > r->chave ) r->dir=remove_no(r->dir,chave);
	else if( chave < r->chave ) r->esq=remove_no(r->esq,chave);
	return r; //reafirma as posições da árvore binaria.
}


int remove_arvore( Arvore *a,int chave ){
	
	if( arvore_vazia(a) ) return -1; //arvore vazia nada há remover.
	
	//casos de remoção.
	//remoção da raiz.
	if( a->raiz->chave == chave ){
		a->raiz=remove_no(a->raiz,chave);
	}
	else	remove_no(a->raiz,chave);
}


No* libera_arvore1( No *r){
	
	if( r == NULL ) return NULL;			
	else{
		libera_arvore1(r->esq);
		libera_arvore1(r->dir);
		free(r);
		return NULL;//vai enviar NULL no fim para nossa a->raiz,além de liberar todas as mémorias.
	}
}

int libera_arvore2( Arvore *a ){
	
	if( arvore_vazia(a) ) return -1;
	
	a->raiz=libera_arvore1(a->raiz); //árvore se torna vazia neste caso.
	return 0;
}

int pre_ordem( No *r ){
	
	if( r == NULL ) return 0;
	else{
		printf("%d",r->chave);
		pre_ordem(r->esq);
		pre_ordem(r->dir);
	}
}

int em_ordem( No *r ){
	
	if( r == NULL ) return 0;
	else{
		em_ordem(r->esq);
		printf("%d ",r->chave);
		em_ordem(r->dir);
	}
}

No* buscar_no(No *r,int valor_procurado){

	if( r == NULL ) return r; //retorna NULL caso o elemento não seja encontrado.
	
	if( r->chave == valor_procurado ) return r; //retorna o elemento encontrado.
	
	if( valor_procurado > r->chave ) return buscar_no(r->dir,valor_procurado);
	else return buscar_no(r->esq,valor_procurado);
}	

int pos_ordem( No *r){
	
	
	if( r == NULL ) return 0;
	else{
		pos_ordem(r->esq);
		pos_ordem(r->dir);
		printf("%d",r->chave);
	}
}	
