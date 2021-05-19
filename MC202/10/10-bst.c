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
	char entrada[20];
	int inteiro, inferior, superior;
	arvore *node = NULL;
	Lista *nova_lista = NULL;

	scanf("%s", entrada);
	while(strcmp(entrada, "terminar"))
	{
		if(!strcmp(entrada, "inserir"))
		{
			scanf("%d", &inteiro);
			node = insere_arvore(node, inteiro);
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
				nova_lista = insere_lista(node, nova_lista);
				printf("%d ", node->numero);
				nova_lista = largura(node, nova_lista);
				printf("\n");
			}
			else
				printf("vazia\n");
		}
		else if(!strcmp(entrada, "buscar"))
		{
			scanf("%d", &inteiro);	
			if(buscar(node, inteiro)==NULL)
				printf("%d nao pertence\n", inteiro);
			else
				printf("%d pertence\n", inteiro);
		}
		else if(!strcmp(entrada, "buscar-intervalo"))
		{
			scanf("%d", &inferior);
			scanf("%d", &superior);
			if(!buscar_intervalo(node, inferior, superior))
				printf("nenhuma");
			printf("\n");
		}
		else if(!strcmp(entrada, "minimo"))
		{
			if(!node)
				printf("vazia\n");
			else
				printf("%d\n", acha_minimo(node)->numero);
		}
		else if(!strcmp(entrada, "maximo"))
		{
			if(!node)
				printf("vazia\n");
			else
				printf("%d\n", acha_maximo(node)->numero);
		}
		else if(!strcmp(entrada, "sucessor"))
		{
			scanf("%d", &inteiro);
			sucessor(node, inteiro);
		}
		else if(!strcmp(entrada, "predecessor"))
		{
			scanf("%d", &inteiro);
			predecessor(node, inteiro);
		}
		else if(!strcmp(entrada, "remover"))
		{
			scanf("%d", &inteiro);
			node = remover(node, inteiro);
		}
		scanf("%s", entrada);
	}

	libera_memoria(node);
	return 0;
}