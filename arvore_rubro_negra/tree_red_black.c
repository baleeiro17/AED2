#include<stdio.h>
#include<stdlib.h>
#include "tree_red_black.h"

/*
	-Autor : Lucas Baleeiro Dominato.
	-arquivo contem as funcoes e seus codigos.
*/

Node* make_t_nill( ){

	Node *t_nill;

	t_nill = (Node *)calloc(1,sizeof(Node) );
	if( !t_nill ){
		printf("erro ao alocar memoria\n");
		exit(1);
	}

	//iniciando parametros do t_nill.
	t_nill->color = 1;
	t_nill->right = NULL;
	t_nill->left = NULL;
	t_nill->parent = NULL;
	t_nill->key = 1000;

	return t_nill;

}

int altura_no( Node *r , Node *t_nill ){
	
	if( r == t_nill ) return -1;
	
	if( altura_no(r->left,t_nill) > altura_no(r->right,t_nill) )
		return ( altura_no(r->left,t_nill) + 1 );
	else
		return ( altura_no(r->right,t_nill) + 1 );
}

Tree* make_tree(  Node *t_nill ){

	Tree *t1;

	//inicia a arvore binaria de busca alocando memoria.
	t1 = (Tree *)calloc(1,sizeof(Tree));
	if( !t1 ){
		printf("erro ao alocar memoria fim do programa.\n");
		exit(1);
	}

	//cria a arvore binaria iniciamos a mesma.
	t1->root = t_nill;

	//retorna a arvore inicializada.
	return t1;
}

int tree_empty( Tree *t , Node *t_nill ){

	if( t->root == t_nill ) return 1; //arvore vazia.
	return 0; //arvore nao vazia.
}

int em_ordem( Node *no ,Node *t_nill ){

	if( no == t_nill ) return 0;
	else{

		em_ordem(no->left,t_nill);
		printf(" key:%d ",no->key);
		if( no->color == 1 ) printf("cor:preto  ");
		else printf("cor:vermelho ");
		em_ordem(no->right,t_nill);
	}	

}

int right_rotate( Node *no, Tree *t ){

	Node *aux;

	aux = no->left;
	no->left = aux->right;
	if( aux->right->key != 1000 ) aux->right->parent = no ; //nao e necessario atualizar quando for um t_nill.
	aux->right = no;


	//atualizando os ponteiros de pai.
	aux->parent = no->parent ;
	no->parent = aux;

	//checo se envolve raiz.
	if( t->root == no ) t->root = aux;
	else{
			if( aux->parent->key > aux->key ) aux->parent->left = aux;
			else aux->parent->right = aux;
	}

	return 1; 
}

int left_rotate( Node *no , Tree *t ){

	Node *aux;


	aux = no->right; 
	no->right = aux->left;
	if( aux->left->key != 1000 ) aux->left->parent = no; //nao e necessario atualizar quando for um t_nill.
	aux->left = no; 

	//atualizando os ponteiros de pai.
	aux->parent = no->parent;
	no->parent = aux;

	//atualizando tambem as ligacoes entre os ponteiros paternos.

	//checo se envolve raiz.
	if( t->root == no ) t->root = aux;
	else{
			if( aux->parent->key > aux->key ) aux->parent->left = aux;
			else aux->parent->right = aux;
	}

	return 1;

}

int RB_insert_fixup( Node *no , Tree *t ){

	Node *tio;

	while( no->parent->color == 0 ){

		//o pai do no inserido esta na esquerda ou direita.
		if( no->parent == no->parent->parent->left ){

			//pego o tio do no inserido e analiso o mesmo.
			tio = no->parent->parent->right;

			//se o tio for vermelho,caso 1.
			if( tio->color == 0 ){

				no->parent->color = 1; //pai do no passa a ser preto.
				tio->color = 1; //tio passa a ser preto tbm.
				no->parent->parent->color = 0; //avo passa a ser preto.
				no = no->parent->parent; //o no passa ser o seu avo e volta no looping.


			}
			//casos 2 e 3 respectivamente.
			else{

				//caso 2 da arvore rubro negra.
				if( no == no->parent->right ){


					//passa ser seu pai.
					no = no->parent;

					//e rotaciona para esquerda.
					left_rotate( no , t );


				}

				//caso 3 da arvore rubro negra.
				no->parent->color = 1;	//o pai do no passa ser preto.
				no->parent->parent->color = 0;	//o avo passa a ser vermelho.
				right_rotate( no->parent->parent , t );

			}	


		}	
		else{


			//mesma coisa so que muda o que era direita para esquerda.
			//pego o tio do no inserido e analiso o mesmo.
			tio = no->parent->parent->left;


			//se o tio for vermelho,caso 1.
			if( tio->color == 0 ){

				no->parent->color = 1; //pai do no passa a ser preto.
				tio->color = 1; //tio passa a ser preto tbm.
				no->parent->parent->color = 0; //avo passa a ser preto.
				no = no->parent->parent; //o no passa ser o seu avo e volta no looping.


			}
			//casos 2 e 3 respectivamente.
			else{

				//caso 2 da arvore rubro negra.
				if( no == no->parent->left ){

					//passa ser seu pai.
					no = no->parent;

					//e rotaciona para esquerda.
					right_rotate( no , t );


				}

				//caso 3 da arvore rubro negra.
				no->parent->color = 1;	//o pai do no passa ser preto.
				no->parent->parent->color = 0;	//o avo passa a ser vermelho.
				left_rotate( no->parent->parent , t );

			}	

		}
	}

		
	//raiz sempre e da cor preta.
	t->root->color = 1;
}

int insert_node(Tree *t , int info , Node *t_nill ){

	Node *aux,*ant; //auxilia na movimentacao da arvore.
	Node *new_node;	//para alocacao da memoria do novo no.

	//recebe a raiz da arvore.
	aux = t->root;
	ant = t->root;

	//primeiro devemos procurar onde inserir a informacao.
	while( aux != t_nill ){

		//se for maior inserimos a direita,e movimentamos a direita.
		if( aux->key < info ){

			//guarda sempre o anterior.
			ant = aux;
			aux = aux->right;

		}
		else{

			//guarda sempre o anterior.
			ant = aux;
			aux = aux->left;
		}

	}

	//saida o no sempre e inserido em uma folha.

	//alocando memoria para o no que vamos inserir.

	new_node = ( Node *)calloc(1,sizeof( Node ));
	if( !new_node ){
		printf("erro na memoria.");
		exit(1);
	}

	//guarda a informacao.
	new_node->key = info;

	//guarda a cor do no,sempre na insercao inserimos pela cor vermelha.
	new_node->color = 0;

	//os filhos sempre sao NULL(pois a mesma sempre e uma folha ).
	new_node->right = t_nill;
	new_node->left = t_nill;

	//o que varia no caso e quem vai ser o pai(parent).

	//caso do no que se torna raiz.
	if( ant == t_nill ){

		t->root = new_node;
		new_node->parent = t_nill; //nao tem pai,e a raiz.
	}
	else{
			//o seu pai e o no anterior ao mesmo que foi inserido.
			new_node->parent = ant;

			//verifca se ant e maior ou menor que elemento inserido indicacao de atualizacao dos filhos.
			if( info > ant->key )
				ant->right = new_node;
			else
				ant->left = new_node;
	}

	//funcao que checa as propriedades da tree red_black.
	RB_insert_fixup( new_node , t);

	//insercao ocorrida com sucesso.
	return 1;

}

Node* search_minimo( Node *no , Node *t_nill ){

	Node *ant;


	while( no != t_nill ){

		//guarda o anterior.
		ant=no;

		//movimenta pela esquerda.
		no=no->left;
	}

	//retorna o minimo na busca.
	return ant;
}

Node* search_maximo( Node *no , Node *t_nill){

	Node *ant;


	while( no != t_nill ){

		//guarda o anterior.
		ant=no;

		//movimenta pela esquerda.
		no=no->right;
	}

	//retorna o minimo na busca.
	return ant;
}

int delete_node( Tree *t , int info , Node *t_nill ){

	Node *aux,*guarda;
	Node *maximo;

	//variaveis usadas na coloracao e na preservacao das propriedades da tree red black.
	Node *x;
	int cor_removida;

	//recebe a raiz da arvore.
	aux = t->root;

	//procura o no que queremos remover.
	while(  aux->key != info ){

		//movimenta pela esquerda.
		if( aux->key > info ){

			aux = aux->left;
		}

		//movimenta pela direita.
		else{

			aux = aux->right;

		}

	}


	//achado no temos que analisar dois casos.

	while( 1 ){


		//guarda a cor que vai ser removida.
		cor_removida = aux->color;

		//primeiro caso,no com unico filho ou sem filhos.
		if( aux->right == t_nill ){

			//guarda o substituto do no removido(para tree red black).
			x = aux->left;

			//troca de posicao com seu unico filho.
			if( aux->parent != t_nill ){

				//caso da remocao de um no sem filhos tambem entra aqui.
				if( aux->left != t_nill ) aux->left->parent = aux->parent;

				//temos que checar se e filho da direita ou esquerda.
				if( aux->parent->key >= aux->key ){
					aux->parent->left=aux->left;

				}
				else aux->parent->right=aux->left;
			}
			else{

				t->root = aux->left;

				//caso a arvore fique vazia.
				if( aux->left != t_nill ) aux->left->parent = aux->parent;
			}	

			//sai do looping.
			break;
		}

		else if( aux->left == t_nill ){

			//guarda o substituto do no removido(para tree red black).
			x = aux->right;

			//troca de posicao com seu unico filho.
			if( aux->parent != t_nill ){

				aux->right->parent = aux->parent;

				//temos que checar se e filho da direita ou esquerda.
				if( aux->parent->key > aux->key ){
					aux->parent->left=aux->right;

				}
				else aux->parent->right=aux->right;
			}
			else{

			 	t->root = aux->right;

			 	//caso a arvore fique vazia.
			 	if( aux->right != t_nill ) aux->right->parent = aux->parent;
			} 	

			//sai do looping.
			break;

		}
		

		//caso do no com dois filhos,nesse caso procuramos o seu sucessor.
		else{

			//busca do maximo a direita.
			maximo = search_maximo( aux->left ,t_nill );


			//troca o maximo com o no a ser removido e removemos o maximo.
			aux->key = maximo->key;
			aux = maximo;


		}
	}

	//guarda o pai de aux.
	guarda = aux->parent;
	

	//desaloca a memoria do aux que e o no que queremos remover no caso.
	free(aux);

	//checamos se as propriedades da tree red black estao realizadas:

	//se a cor removida for preta,entao temos que checar:
	if( cor_removida == 1 ){

		//ajuste caso o x for igual a t.nill,acrescenta seu pai.
		if( x == t_nill ){
			x->parent = guarda; 
		}
		RB_delete_fix_up(t,x);	
	}


	return 1;
}

int RB_delete_fix_up(Tree *t,Node *x ){

	Node *irmao;

	while( x != t->root && x->color == 1 ){


		if( x == x->parent->left ){

			//irmao do x a direita.
			irmao = x->parent->right;

			//se o irmao for vermelho,caso 1.
			if( irmao->color == 0 ){

				irmao->color = 1; // muda para preto
				x->parent->color = 0 ; //muda para vermelho.
				left_rotate(x->parent,t); //rotacao esquerda.
				irmao = x->parent->right;

			}

			//se os dois filhos do irmao forem da cor preta,caso 2.
			if( irmao->left->color == 1  && irmao->right->color == 1 ){

				irmao->color = 0; //muda para vermelho.
				x = x->parent;

			}

			//caso 3 e 4.
			else{

				//a cor do filho do irmao a direita e preta,caso3.
				if( irmao->right->color == 1 ){


					irmao->left->color = 1; //muda para preto.
					irmao->color = 0;	//muda para vermelho.
					right_rotate(irmao,t);
					irmao = x->parent->right;
				}
				
				//caso 4.
				irmao->color = x->parent->color;
				x->parent->color = 1;
				irmao->right->color = 1;
				left_rotate(x->parent,t);
				x = t->root;
			}
		}	
		else{

			//inverte tudo que era right vira left.
			//irmao do x a direita.
			irmao = x->parent->left;

			//se o irmao for vermelho,caso 1.
			if( irmao->color == 0 ){

				irmao->color = 1; // muda para preto
				x->parent->color = 0 ; //muda para vermelho.
				right_rotate(x->parent,t); //rotacao esquerda.
				irmao = x->parent->left;

			}

			//se os dois filhos do irmao forem da cor preta,caso 2.
			if( irmao->left->color == 1  && irmao->right->color == 1 ){

				irmao->color = 0; //muda para vermelho.
				x = x->parent;

			}

			//caso 3 e 4.
			else{

				//a cor do filho do irmao a direita e preta,caso3.
				if( irmao->left->color == 1 ){

					irmao->right->color = 1; //muda para preto.
					irmao->color = 0;	//muda para vermelho.
					left_rotate(irmao,t);
					irmao = x->parent->left;

				}
				
				//caso 4.
				irmao->color = x->parent->color;
				x->parent->color = 1;
				irmao->left->color = 1;
				right_rotate(x->parent,t);
				x = t->root;
			}
		}
	}	

	x->color = 1; //muda para preto.

	return 1;
}
