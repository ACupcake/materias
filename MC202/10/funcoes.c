/**
Arquivo com as funcoes utilizadas na main
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

//insere numero na lista usada na funcao 'largura'
Lista *insere_lista(arvore *nova, Lista *node)
{
	Lista *lista_percorrida = node;

	//cria novo no para a lista 'node'
	Lista *new = malloc(sizeof(Lista));
	new->dados = nova;
	new->proximo = NULL;

	//verifica se 'node' esta vazio
	if(!node) return new;

	//se 'node' nao esta vazia ela eh percorrida ate encontrar o fim
	while(lista_percorrida->proximo)
		lista_percorrida = lista_percorrida->proximo;
	lista_percorrida->proximo = new;

	return node;
}

//cria novo no na arvore
arvore *cria(int inteiro)
{
	arvore *novo_no = malloc(sizeof(arvore));

	novo_no->numero = inteiro;
	novo_no->esquerda = NULL;
	novo_no->direita = NULL;

	return novo_no;
}

//insere node na arvore caso ja nao pertenca
arvore *insere_arvore(arvore *node, int inteiro)
{
	if(!node) //caso arvore esteja vazia retorna novo valor
		return cria(inteiro);
	else if(!buscar(node, inteiro)) //verifica se inteiro ja nao esta na arvore
	{
		if(node->numero > inteiro){
			node->esquerda = insere_arvore(node->esquerda, inteiro);
			if(node) node->esquerda->pai = node; //atribui um pai ao novo node
		}
		else{
			node->direita = insere_arvore(node->direita, inteiro);
			if(node) node->direita->pai = node; //atribui um pai ao novo node
		}
	}

	return node;
}

//busca 'inteiro' elemento na arvore 'node'
arvore *buscar(arvore *node, int inteiro)
{
	arvore *no_arvore = node;

	//percorre a arvore enquanto nao encontrar NULL ou inteiro
	while(no_arvore && (no_arvore->numero != inteiro))
	{
		if(no_arvore->numero > inteiro)
			no_arvore = no_arvore->esquerda;
		else
			no_arvore = no_arvore->direita;
	}

	return no_arvore;
}

arvore *em_ordem(arvore *node)
{
	arvore *no_arvore = node;
	
	if(no_arvore)
	{
		em_ordem(no_arvore->esquerda);
		printf("%d ", no_arvore->numero);
		em_ordem(no_arvore->direita);
	}

	return no_arvore;
}

arvore *pre_ordem(arvore *node)
{
	arvore *no_arvore = node;
	
	if(no_arvore)
	{
		printf("%d ", no_arvore->numero);
		pre_ordem(no_arvore->esquerda);
		pre_ordem(no_arvore->direita);
	}

	return no_arvore;
}

arvore *pos_ordem(arvore *node)
{
	arvore *no_arvore = node;
	
	if(no_arvore)
	{
		pos_ordem(no_arvore->esquerda);
		pos_ordem(no_arvore->direita);
		printf("%d ", no_arvore->numero);
	}

	return no_arvore;
}

//mostra a arvore em largura
Lista *largura(arvore *node, Lista *lista)
{
	arvore *no_arvore = node;
	Lista *lista_pivo;

	//insere na lista os numeros adjacentes ao atual
	if(no_arvore->esquerda)
		lista = insere_lista(no_arvore->esquerda, lista);
	if(no_arvore->direita)
		lista = insere_lista(no_arvore->direita, lista);

	while(lista)
	{
		//mostra numeros adjacentes
		if(no_arvore->esquerda)
			printf("%d ", no_arvore->esquerda->numero);
		if(no_arvore->direita)
			printf("%d ", no_arvore->direita->numero);
		
		//remove numero da lista
		lista_pivo = lista;
		lista = lista->proximo;
		if(lista_pivo) free(lista_pivo);

		//chama a funcao novamente com o proximo valor da lista
		if(lista) lista = largura(lista->dados, lista);
	}

	return NULL;
}

arvore *libera_memoria(arvore *node)
{
	arvore *no_arvore = node;
	
	if(no_arvore)
	{
		libera_memoria(no_arvore->esquerda);
		libera_memoria(no_arvore->direita);
	}
	if(no_arvore) free(no_arvore);

	return no_arvore;
}

arvore *remover(arvore *node, int inteiro)
{
	arvore *no_arvore = buscar(node, inteiro);

	if(!no_arvore) //o elemento nao esta na arvore
		return node;
	else if(no_arvore->direita && no_arvore->esquerda) //elemento tem dois filhos
	{
		arvore *menor_no = acha_minimo(no_arvore->direita);

		//altera os no_arvores de 'menor_no'
		if(menor_no->direita){ //caso onde 'menor_no' tem filhos a direita
			if(menor_no->pai->numero > menor_no->numero){
				menor_no->pai->esquerda = menor_no->direita;
				menor_no->direita->pai = menor_no->pai;
			}
			else{
				menor_no->pai->direita = menor_no->direita;
				menor_no->direita->pai = menor_no->pai;
			}
		}
		//menor_no valor nao tem filhos
		else if(menor_no->pai->numero > menor_no->numero)
			menor_no->pai->esquerda = NULL;
		else
			menor_no->pai->direita = NULL;

		no_arvore->numero = menor_no->numero;
		no_arvore = menor_no;
	}
	else if(!no_arvore->pai){ //elemento nao tem pai
		//apenas um elemento na arvore
		if(!no_arvore->direita && !no_arvore->esquerda) node = NULL;

		//caso onde no_arvore nao tem filho a esquerda
		else if(no_arvore->direita) node = no_arvore->direita;

		//caso onde no_arvore nao tem filho a direita
		else if(no_arvore->esquerda)	node = no_arvore->esquerda;

		if(node) node->pai = NULL;
	}
	else if(no_arvore->direita) //caso onde o filho da esquerda eh nulo
	{
		if(no_arvore->pai->numero > no_arvore->numero)
			no_arvore->pai->esquerda = no_arvore->direita;
		else
			no_arvore->pai->direita = no_arvore->direita;
		no_arvore->direita->pai = no_arvore->pai;

	}
	else if(no_arvore->esquerda)//caso onde o filho da direita eh nulo
	{
		if(no_arvore->pai->numero > no_arvore->numero)
			no_arvore->pai->esquerda = no_arvore->esquerda;
		else
			no_arvore->pai->direita = no_arvore->esquerda;
		no_arvore->esquerda->pai = no_arvore->pai;
	}
	else //caso onde os dois filhos sao nulos mas o elemento tem pai
	{
		if(no_arvore->pai->numero > no_arvore->numero)
			no_arvore->pai->esquerda = NULL;
		else
			no_arvore->pai->direita = NULL;
	}

	free(no_arvore);
	return node;
}

//mostra o predecessor de 'inteiro' se houver
void predecessor(arvore *node, int inteiro)
{
	arvore *no_arvore = buscar(node, inteiro);

	//elemento nao esta na arvore
	if(!no_arvore)
		printf("nao ha\n");

	//verifica se no_arvore da esquerda eh nulo
	else if(no_arvore->esquerda){
		no_arvore = no_arvore->esquerda;
		while(no_arvore->direita) //percorre pela direita ate achar o ultimo nao nulo
			no_arvore = no_arvore->direita;
			
		printf("%d\n", no_arvore->numero);
	}

	//nao ha filho na direita e o pai eh MENOR que o numero recebido
	else if(no_arvore->pai && (no_arvore->pai->numero < inteiro))
		printf("%d\n", no_arvore->pai->numero);

	//nao ha filho na direita e o pai eh MARIO que o numero recebido
	else if(no_arvore->pai && (no_arvore->pai->numero > inteiro)){
		while(no_arvore && (no_arvore->numero >= inteiro))
			no_arvore = no_arvore->pai;

		if(no_arvore) printf("%d\n", no_arvore->numero);
		else printf("nao ha\n");
	}
	else
		printf("nao ha\n");
}

//mostra o sucessor de 'inteiro' se houver
void sucessor(arvore *node, int inteiro)
{
	arvore *no_arvore = buscar(node, inteiro);

	if(!no_arvore)
		printf("nao ha\n");

	//verifica se no_arvore da direita eh nulo
	else if(no_arvore->direita){
		no_arvore = no_arvore->direita;
		while(no_arvore->esquerda) //percorre pela esquerda ate achar o ultimo nao nulo
			no_arvore = no_arvore->esquerda;
		printf("%d\n", no_arvore->numero);
	}

	//nao ha filho na direita e o pai eh MAIOR que o numero recebido
	else if(no_arvore->pai && (no_arvore->pai->numero > inteiro))
		printf("%d\n", no_arvore->pai->numero);

	//nao ha filho na direita e o pai eh MENOR que o numero recebido
	else if(no_arvore->pai && (no_arvore->pai->numero < inteiro)){
		while(no_arvore && (no_arvore->numero <= inteiro))
			no_arvore = no_arvore->pai;

		if(no_arvore) printf("%d\n", no_arvore->numero);
		else printf("nao ha\n");
	}
	else
		printf("nao ha\n");
}

//percorre a arvore em ordem e se o valor estiver dentro do intervalo ele eh mostrado
int buscar_intervalo(arvore *node, int n_inferior, int n_superior)
{
	arvore *no_arvore = node;
	int verifica = 0;

	if(no_arvore)
	{
		verifica = buscar_intervalo(no_arvore->esquerda, n_inferior, n_superior) || verifica;
		if(no_arvore->numero >= n_inferior && (no_arvore->numero <= n_superior)){
			verifica = 1;
			printf("%d ", no_arvore->numero);
		}
		verifica = buscar_intervalo(no_arvore->direita, n_inferior, n_superior) || verifica;
	}

	if(verifica) return 1; //variavel 'verifica' define se algum numero do intervalo foi encontrado
	else return 0;
}

//percorre o caminho todo pela esquerda ate encontrar o ultimo nao nulo
arvore *acha_minimo(arvore *node)
{
	arvore *no_arvore = node;

	while(no_arvore->esquerda)
		no_arvore = no_arvore->esquerda;
	return no_arvore;
}

//percorre o caminho todo pela direita ate encontrar o ultimo nao nulo
arvore *acha_maximo(arvore *node)
{
	arvore *no_arvore = node;

	while(no_arvore->direita)
		no_arvore = no_arvore->direita;
	return no_arvore;
}