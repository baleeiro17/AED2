#include<stdio.h>
#include<stdlib.h>

/*
	-Autor: Lucas Baleeiro Dominato.
	-AVL com codigo das funcoes.
*/

Arvore* cria_arvore(){
	Arvore *a;
	
	a=(Arvore *)malloc(sizeof(Arvore));
	if( !a ) return NULL;
	
	a->raiz=NULL;
	
	return a;
}

int arvore_vazia( Arvore *a ){
	
	if( a->raiz == NULL ) return 1;
	return 0;
}

int alt_no( No * r ){
	
	if( r == NULL ) return -1;	
		
	if( alt_no(r->esq) > alt_no(r->dir) )
		return ( alt_no(r->esq) + 1 );
	else
		return ( alt_no(r->dir) + 1 );
}

int contagem_nos( No *r ){
	
	if( r == NULL ) return 0;
	
	return( alt_no(r->esq) + alt_no(r->dir) +1 );
}

int calculo_fb( No *r ){
	
	return ( alt_no(r->dir) - alt_no(r->esq) );
}	

No* rotacao_direita( No *r ){
	No *aux;
	
	aux=r->esq;
	r->esq=aux->dir;
	aux->dir=r;
	
	//atualizando já os endereços dos elementos mudados.
	//muito importante essa atualização para uma árvore com inserção e remoção de elementos de forma conjunta,mantém sempre as fbs atualizadas.
	//analisando os exemplos percebemos que as fbs que muda durante as rotações são apenas de dois nós no caso a antiga e a nova raiz da sub-árvore analisada,o resto continua a mesma.
	aux->bal=calculo_fb(aux);
	r->bal=calculo_fb(r);
	
	return aux;
}

No* rotacao_esquerda( No *r ){
	No *aux;
	
	aux=r->dir;
	r->dir=aux->esq;
	aux->esq=r;
	
	//atualizando já os endereços dos elementos mudados.
	//muito importante essa atualização para uma árvore com inserção e remoção de elementos de forma conjunta,mantém sempre as fbs atualizadas.
	//analisando os exemplos percebemos que as fbs que muda durante as rotações são apenas de dois nós no caso a antiga e a nova raiz da sub-árvore analisada,o resto continua a mesma.
	aux->bal=calculo_fb(aux);
	r->bal=calculo_fb(r);
	
	return aux;
}		

No* balaceamento( No *r){
	
	if( r->bal == -2 ){
		
		if( r->esq->bal == 1 )
			r->esq=rotacao_esquerda(r->esq);	
		r=rotacao_direita(r);
	}
	
	if( r->bal == 2 ){
		
		if( r->dir->bal == -1 )
			r->dir=rotacao_direita(r->dir);
		r=rotacao_esquerda(r);
	}
	
	//retorna o elemento prepoderente nas funções de rotações.
	return r;
}

No* insercao_folha( No *r,int chave ){
	No *novo;
	
	//em seguida temos os seguintes elementos:
	
	if( chave > r->chave ){
		
		if( r->dir == NULL ){
		
			novo=(No *)malloc(sizeof(No));
			novo->chave=chave;
			novo->esq=NULL;
			novo->dir=NULL;
			r->dir=novo;
			novo->bal=0;
			r->bal=calculo_fb(r); //já calcula o fb do nó pai aqui no caso.
			
			return r;
		}
		else{
			r->dir=insercao_folha(r->dir,chave);
			r->bal=calculo_fb(r);	//faz o calculo das fbs de todos os nós a partir do despilhamento recursivo.
			r=balaceamento(r); //checa se necessita balacear a minha árvore.
			
			return r; //breca o despilhamento,servindo como entrada para outra chamada recursiva.
		}
	}
	else if( chave < r->chave ){
		
		if( r->esq == NULL ){
			novo=(No *)malloc(sizeof(No));
			novo->chave=chave;
			novo->esq=NULL;
			novo->dir=NULL;
			r->esq=novo;
			novo->bal=0;
			r->bal=calculo_fb(r);
			
			return r;
		}
		else{
			r->esq=insercao_folha(r->esq,chave);
			r->bal=calculo_fb(r);	//faz o calculo das fbs de todos os nós a partir do despilhamento recursivo.
			r=balaceamento(r); //checa se necessita balacear a minha árvore.
			
			return r; //breca o despilhamento,servindo como entrada para outra chamada recursiva.
		}
	}
	printf("elemento duplicado.\n"); //valores duplicados não são adicionados na árvore,retorna a árvore original.
	return r;
}			
				

int insercao_arvore( Arvore *a, int chave ){
	No *novo;
	
	if( arvore_vazia(a) ){
		
		novo=(No *)malloc(sizeof(No));
		novo->chave=chave;
		novo->esq=NULL;
		novo->dir=NULL;
		a->raiz=novo;
		novo->bal=0;
	}
	else
		a->raiz=insercao_folha(a->raiz,chave);
	return 1;	
}

No* remocao_no( No *r,int chave ){
	No *lixo;
	
	//elemento não encontrado na árvore,retorna o próprio mantendo o formato original da árvore sem alterações.
	if( r == NULL ) return r;
	
	//chave encontrado removemos a mesma.
	if( chave == r->chave ){
		
		//caso do sem filhos e com filho unico.
		if( r->esq == NULL || r->dir == NULL ){
		
			if( r->esq == NULL ){
				lixo=r;
				r=r->dir;
				free(lixo);
				return r;
			}
			else{
				lixo=r;
				r=r->esq;
				free(lixo);
				return r;
			}
		}
		//remoção do nó com dois filhos.	
		else{
			
			lixo=r->dir;
			while( lixo->esq != NULL )
				lixo=lixo->esq;
			r->chave=lixo->chave; //muda os contéudos entre os nós apenas.
			r->dir=remocao_no(r->dir,lixo->chave); //remove o menor nó a direita que teve seu valor duplicado na árvore.
			r->bal=calculo_fb(r); //realiza o cálculo do fb.
			r=balaceamento(r); //faz o balaceamento da árvore.
			return r;
			
		}
	}
	
	//movimenta pela árvore e depois pelo despilhamento faz os cálculos de fb e dos balaceamentos respectivos.
	if( chave > r->chave ){
		r->dir=remocao_no(r->dir,chave);
	}
	else if( chave < r->chave ){
		r->esq=remocao_no(r->esq,chave);

	}
	r->bal=calculo_fb(r);
	r=balaceamento(r);
	return r;
}

int remocao_arvore( Arvore *a,int chave ){
	
	if( arvore_vazia(a) ) return -1;
	
	//faz a remoção e retorna o novo nó.
	//aqui prescisamos retornar toda vez a raiz, por causa de um balaceamento pode mudar a raiz principal.
	a->raiz=remocao_no(a->raiz,chave);
	
	return 0;
}				 	
		

int pos_ordem( No *r ){
	
	if( r == NULL ) return 0;
	else{
		pos_ordem(r->esq);
		pos_ordem(r->dir);
		printf("%d - %d ",r->chave,r->bal);
	}
}										

No* libera_arvore1( No *r ){
	
	if( r == NULL ) return NULL;
	else{
		libera_arvore1(r->esq);
		libera_arvore1(r->dir);
		free(r);
		return NULL;
	}
}

int libera_arvore2( Arvore *a ){
	
	if( arvore_vazia(a) ) return -1;
	
	a->raiz=libera_arvore1(a->raiz);
	//free(a);
	
	return 0;
}		
							
