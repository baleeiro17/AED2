#include<stdio.h>
#include<stdlib.h>
#include "tree_bbb.h"

/*
	-autor: Lucas Dominato.
	-codigo da arvore binaria de busca sem uso de recursao.
*/


Tree* make_tree(){

	Tree *t1;

	//inicia a arvore binaria de busca alocando memoria.
	t1 = (Tree *)calloc(1,sizeof(Tree));
	if( !t1 ){
		printf("erro ao alocar memoria fim do programa.\n");
		exit(1);
	}

	//cria a arvore binaria iniciamos a mesma.
	t1->root = NULL;

	//retorna a arvore inicializada.
	return t1;
}

int tree_empty( Tree *t ){

	if( t->root == NULL ) return 1; //arvore vazia.
	return 0; //arvore nao vazia.
}

int em_ordem( Node *no ){

	if( no == NULL ) return 0;
	else{

		em_ordem(no->left);
		printf(" %d  ",no->key );
		em_ordem(no->right);
	}	

}

int insert_node(Tree *t , int info ){

	Node *aux,*ant; //auxilia na movimentacao da arvore.
	Node *new_node;	//para alocacao da memoria do novo no.

	//recebe a raiz da arvore.
	aux = t->root;
	ant = t->root;

	//primeiro devemos procurar onde inserir a informacao.
	while( aux != NULL ){

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

	//os filhos sempre sao NULL(pois a mesma sempre e uma folha ).
	new_node->right = NULL;
	new_node->left = NULL;

	//o que varia no caso e quem vai ser o pai(parent).

	//caso do no que se torna raiz.
	if( ant == NULL ){

		t->root = new_node;
		new_node->parent = NULL; //nao tem pai,e a raiz.
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


	//insercao ocorrida com sucesso.
	return 1;

}

Node* search_maximo( Node *no ){

	Node *ant;


	while( no != NULL ){

		//guarda o anterior.
		ant=no;

		//movimenta pela esquerda.
		no=no->right;
	}

	//retorna o minimo na busca.
	return ant;
}

Node* search_minimo( Node *no ){

	Node *ant;


	while( no != NULL ){

		//guarda o anterior.
		ant=no;

		//movimenta pela esquerda.
		no=no->left;
	}

	//retorna o minimo na busca.
	return ant;
}

int delete_node_1( Tree *t , int info ){

	Node *aux;
	Node *minimo;

	//recebe a raiz da arvore.
	aux = t->root;

	//procura o no que queremos remover.
	while( aux != NULL && aux->key != info ){

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

		//primeiro caso,no com unico filho ou sem filhos.
		if( aux->right == NULL ){

			//troca de posicao com seu unico filho.
			if( aux->parent != NULL ){

				//caso da remocao de um no sem filhos tambem entra aqui.
				if( aux->left != NULL ) aux->left->parent = aux->parent;

				//temos que checar se e filho da direita ou esquerda.
				if( aux->parent->key > aux->key ){
					aux->parent->left=aux->left;

				}
				else aux->parent->right=aux->left;
			}
			else{

				t->root = aux->left;

				//caso a arvore fique vazia.
				if( aux->left != NULL ) aux->left->parent = aux->parent;
			}	

			//sai do looping.
			break;
		}

		else if( aux->left == NULL ){

			//troca de posicao com seu unico filho.
			if( aux->parent != NULL ){

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
			 	if( aux->right != NULL ) aux->right->parent = aux->parent;
			} 	

			//sai do looping.
			break;

		}
		

		//caso do no com dois filhos,nesse caso procuramos o seu sucessor.
		else{

			//busca do minimo a direita.
			minimo = search_minimo( aux->right );

			//troca o minimo com o no a ser removido e removemos o minimo.
			aux->key=minimo->key;
			aux=minimo;


		}
	}		

	//desaloca a memoria do aux que e o no que queremos remover no caso.
	free(aux);

	return 1;
}

int delete_node_2( Tree *t , int info ){

	Node *aux;
	Node *maximo;

	//recebe a raiz da arvore.
	aux = t->root;

	//procura o no que queremos remover.
	while( aux != NULL && aux->key != info ){

		//movimenta pela esquerda.
		if( aux->key > info ){

			aux = aux->left;
		}

		//movimenta pela direita.
		else{

			aux = aux->right;

		}

	}

	//elemento nao existe na tree binary search.
	if( aux == NULL ) return 1;

	//achado no temos que analisar dois casos.

	while( 1 ){

		//primeiro caso,no com unico filho ou sem filhos.
		if( aux->right == NULL ){

			//troca de posicao com seu unico filho.
			if( aux->parent != NULL ){

				//caso da remocao de um no sem filhos tambem entra aqui.
				if( aux->left != NULL ) aux->left->parent = aux->parent;

				//temos que checar se e filho da direita ou esquerda.
				if( aux->parent->key >= aux->key ){
					aux->parent->left=aux->left;

				}
				else aux->parent->right=aux->left;
			}
			else{

				t->root = aux->left;

				//caso a arvore fique vazia.
				if( aux->left != NULL ) aux->left->parent = aux->parent;
			}	

			//sai do looping.
			break;
		}

		else if( aux->left == NULL ){

			//troca de posicao com seu unico filho.
			if( aux->parent != NULL ){

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
			 	if( aux->right != NULL ) aux->right->parent = aux->parent;
			} 	

			//sai do looping.
			break;

		}
		

		//caso do no com dois filhos,nesse caso procuramos o seu sucessor.
		else{

			//busca do maximo a esquerda.
			maximo = search_maximo( aux->left );

			//troca o maximo com o no a ser removido e removemos o maximo.
			aux->key = maximo->key;
			aux = maximo;


		}
	}		

	//desaloca a memoria do aux que e o no que queremos remover no caso.
	free(aux);

	return 1;
}



int search_node( Tree *t, int info ){

	Node *aux;

	//recebe a raiz da minha arvore.
	aux = t->root;

	while( aux != NULL ){

		//elemento encontrado.
		if( aux->key == info ) return 1;
		else{

			//movimenta pela direita ou esquerda da tree binary search.
			if( aux->key > info ) aux = aux->left;
			else aux = aux->right;
		}

	}

	//elemento nao encontrado.
	return 0;
}

int free_tree( Tree *t ){

	//looping ate tree em vazia.
	while( !tree_empty(t) ){

		//libera memoria da TAD node.
		delete_node_2(t,t->root->key);
	}

	//libera memoria da TAD tree.
	free(t);
}


