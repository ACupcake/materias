/**
Arquivo com as funcoes utilizadas na main
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

//insere na lista usada na funcao 'largura'
linear *insere_linear(arvore *nova, linear *node)
{
	linear *temp = node;

	linear *new = malloc(sizeof(linear));
	new->dados = nova;
	new->proximo = NULL;

	if(temp==NULL)
		return new;

	while(temp->proximo!=NULL)
		temp = temp->proximo;
	temp->proximo = new;

	return node;
}

//cria novo no na arvore
arvore *cria(int n)
{
	arvore *novo = malloc(sizeof(arvore));
	novo->numero = n;
	novo->esquerda = NULL;
	novo->direita = NULL;
	return novo;
}

//insere no na arvore caso ja nao pertenca
arvore *insere(arvore *node, int n)
{
	arvore *novo = cria(n);
	if(novo == NULL)
		return node;
	else if(node == NULL)
		return novo;
	else if(busca(node, novo->numero)==NULL)
	{
		if(node->numero > novo->numero)
			node->esquerda = insere(node->esquerda, n);
		else
			node->direita = insere(node->direita, n);
	}
	free(novo);
	return node;
}

arvore *busca(arvore *node, int n)
{
	arvore *ponteiro = node;

	while(ponteiro != NULL && ponteiro->numero != n)
	{
		if(ponteiro->numero > n)
			ponteiro = ponteiro->esquerda;
		else
			ponteiro = ponteiro->direita;
	}
	return ponteiro;
}

arvore *em_ordem(arvore *node)
{
	arvore *ponteiro = node;
	
	if(ponteiro!=NULL)
	{
		em_ordem(ponteiro->esquerda);
		printf("%d ", ponteiro->numero);
		em_ordem(ponteiro->direita);
	}

	return ponteiro;
}

arvore *pre_ordem(arvore *node)
{
	arvore *ponteiro = node;
	
	if(ponteiro!=NULL)
	{
		printf("%d ", ponteiro->numero);
		pre_ordem(ponteiro->esquerda);
		pre_ordem(ponteiro->direita);
	}

	return ponteiro;
}

arvore *pos_ordem(arvore *node)
{
	arvore *ponteiro = node;
	
	if(ponteiro!=NULL)
	{
		pos_ordem(ponteiro->esquerda);
		pos_ordem(ponteiro->direita);
		printf("%d ", ponteiro->numero);
	}

	return ponteiro;
}

linear *largura(arvore *node, linear *lista)
{
	arvore *ponteiro = node;
	linear *temp;

	//insere na lista os numeros adjacentes
	if(ponteiro->esquerda!=NULL)
		lista = insere_linear(ponteiro->esquerda, lista);
	if(ponteiro->direita!=NULL)
		lista = insere_linear(ponteiro->direita, lista);

	while(lista!=NULL)
	{
		//mostra numeros adjacentes
		if(ponteiro->esquerda!=NULL)
			printf("%d ", ponteiro->esquerda->numero);
		if(ponteiro->direita!=NULL)
			printf("%d ", ponteiro->direita->numero);
		
		//libera memoria da lista
		temp = lista;
		lista=lista->proximo;
		if(temp!=NULL)
			free(temp);

		//chama a funcao novamente com o proximo valor da lista
		if(lista!=NULL)
			lista = largura(lista->dados, lista);
	}

	return NULL;
}

//libera memoria
arvore *libera(arvore *node)
{
	arvore *ponteiro = node;
	
	if(ponteiro!=NULL)
	{
		libera(ponteiro->esquerda);
		libera(ponteiro->direita);
	}
	if(ponteiro!=NULL)
		free(ponteiro);
	return ponteiro;
}