/**
O programa tem como objetivo utilizar um vetor dinamico para armazenar valores
e realizar acoes baseadas em uma fila tanto no inicio quanto no fim.
A entrada eh uma string que dita a acao a ser realizada, junto a um inteiro
em alguns casos, e a saida eh um feedback, caso for requisitado, de algum
dado do vetor.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(int argc, char const *argv[])
{
	char entrada[15];
	int numero;
	Vetor *dado=inicializa_struct();

	scanf("%s", entrada);
	while(strcmp(entrada, "exit"))
	{
		if(!strcmp("insert-first", entrada))
		{
			scanf("%d", &numero);
			dado=insere_inicio(dado, numero);
		}

		else if(!strcmp("insert-last", entrada))
		{
			scanf("%d", &numero);
			dado=insere_fim(dado, numero);
		}

		else if(!strcmp("remove-first", entrada))
			dado=remove_inicio(dado);

		else if(!strcmp("print-first", entrada))
			mostra_primeiro(dado);

		else if(!strcmp("remove-last", entrada))
			dado=remove_fim(dado);

		else if(!strcmp("print-last", entrada))
			mostra_ultimo(dado);

		else if(!strcmp("is-empty", entrada))
			esta_vazio(dado);

		scanf("%s", entrada);
	}

	free(dado->numeros);
	free(dado);

	return 0;
}
