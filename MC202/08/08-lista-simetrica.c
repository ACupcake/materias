/**
O programa implementa uma lista simetrico com funcoes de inserir, inverter e mostrar.
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(int argc, char const *argv[])
{
	char comando;
	int posicao, inicio, termino;
	double valor;
	No *numeros = inicializa();

	scanf("%c", &comando);
	while(comando != 't')
	{	
		switch(comando)
		{
			case('i'):
				scanf("%d %lf", &posicao, &valor);
				numeros = inserir(numeros, posicao, valor);
				break;
			case('p'):
				mostrar(numeros);
				break;
			case('v'):
				scanf("%d %d", &inicio, &termino);
				numeros = inversor(numeros, inicio, termino);
				break;
		}
		scanf("%c", &comando);
	}

	No *temp, *segue=inicializa();

	while(numeros!=NULL){
		temp=andar(numeros, segue);
		free(numeros);
		segue=numeros;
		numeros=temp;
	}
	free(numeros);

	return 0;
}
