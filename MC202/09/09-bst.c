/**
O programa eh uma implementacao de arvore binaria e algumas formas de percorrer/buscar
valores dentro da arvore.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main()
{
	arvore *node = NULL;
	char entrada[15];
	int inteiro;
	linear *lista = NULL;

	scanf("%s", entrada);
	while(strcmp(entrada, "terminar"))
	{
		if(!strcmp(entrada, "inserir"))
		{
			scanf("%d", &inteiro);
			node = insere(node, inteiro);
		}
		else if(!strcmp(entrada, "em-ordem"))	
		{
			if(node!=NULL)
				em_ordem(node);
			else
				printf("vazia");
			printf("\n");
		}
		else if(!strcmp(entrada, "pre-ordem"))
		{
			if(node!=NULL)
				pre_ordem(node);
			else
				printf("vazia");
			printf("\n");
		}
		else if(!strcmp(entrada, "pos-ordem"))	
		{
			if(node!=NULL)
				pos_ordem(node);
			else
				printf("vazia");
			printf("\n");
		}
		else if(!strcmp(entrada, "largura"))
		{
			if(node!=NULL)
			{
				lista = insere_linear(node, lista);
				printf("%d ", node->numero);
				lista = largura(node, lista);
				printf("\n");
			}
			else
				printf("vazia\n");
		}
		else if(!strcmp(entrada, "buscar"))
		{
			scanf("%d", &inteiro);	
			if(busca(node, inteiro)==NULL)
				printf("%d nao pertence\n", inteiro);
			else
				printf("%d pertence\n", inteiro);
		}
		scanf("%s", entrada);
	}

	libera(node);
	return 0;
}