/**
Arquivo com funcoes utilizadas no programa principal
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

No *inicializa(void)
{
	return NULL;
}

No *andar(No *apontador, No *segue)
{
	if(apontador->A == segue) return apontador->B;
	else return apontador->A;
}

No *voltar(No *apontador, No *segue)
{
	if(apontador->A == segue) return apontador->A;
	else return apontador->B;
}

No *inserir(No *numeros, int posicao, double valor)
{
	No *apontador = numeros, *pivo, *segue = inicializa();

	No *temp=(No*) malloc(sizeof(No));
	temp->numero = valor;

	if(numeros == NULL) //inserir valor em lista vazia
	{
		numeros = temp;
		numeros->A = inicializa();
		numeros->B = inicializa();
	}
	else if(posicao == 0) //inserir na primeira posicao
	{
		temp->A = numeros;
		if(apontador->B==pivo)
		{
			pivo = apontador->B;
			apontador->B = temp;
			temp->A = numeros;
			apontador = apontador->B;
			apontador->B = pivo;
		}
		else
		{
			pivo = apontador->A;
			apontador->A = temp;
			temp->B = numeros;
			apontador = apontador->A;
			apontador->A = pivo;
		}
		return apontador;
	}
	else //inserir na posicao 'posicao' ou na ultima posicao caso nao seja possivel
	{
		for(int i = 0; i != posicao-1 && (andar(apontador, segue)!=NULL); i++)
		{
			pivo = apontador;
			apontador = andar(apontador, segue);
			segue = pivo;
		}
		if(apontador->B==pivo)
		{
			pivo = apontador->A;
			apontador->A = temp;
			apontador->A->B = apontador;
			apontador = apontador->A;
			apontador->A = pivo;
		}
		else
		{
			pivo = apontador->B;
			apontador->B = temp;
			apontador->B->A = apontador;
			apontador = apontador->B;
			apontador->B = pivo;
		}
	}
	return numeros;
}

void mostrar(No *numeros)
{
	No *apontador = numeros, *pivo, *segue = inicializa();
	while(apontador != NULL)
	{
		printf("%.4lf ", apontador->numero);
		pivo = apontador;
		apontador = andar(apontador, segue);
		segue = pivo;
	}
	printf("\n");
}

No *inverter(No *numeros, No *inicial, No *antinicial, No *final, No *antfinal)
{
	int flag; //flag dita o prox valor da lista
	No *temp;

	//valor da lista posterior ao final e anterior ao inicio com null
	if(voltar(inicial, antinicial)==NULL && andar(final, antfinal)==NULL)
	{
		numeros=final;
		return numeros;
	}

	//valor da lista anterior ao primeiro com null
	if(voltar(inicial, antinicial)==NULL)
	{
		if(inicial->B == NULL)
			inicial->B = andar(final, antfinal);
		else
			inicial->A = andar(final, antfinal);
		
		if(final->A == andar(final, antfinal))
		{
			if(final->A->B == final)
				final->A->B=inicial;
			else
				final->A->A=inicial;
		}
		else
		{
			if(final->B->B == final)
				final->B->B=inicial;
			else
				final->B->A=inicial;
		}

		numeros=final;

		if(numeros->B == voltar(numeros, antfinal))
			numeros->A = inicializa();
		else
			numeros->B = inicializa();

		return numeros;
	}
	else if(inicial->B == voltar(inicial, antinicial))
	{
		flag=1;
		if(inicial->B->A != andar(voltar(inicial, antinicial), inicial))
			inicial->B->A = final;
		else
			inicial->B->B = final;
	}
	else
	{
		flag=0;
		if(inicial->A->A != andar(voltar(inicial, antinicial), inicial))
			inicial->A->A = final;
		else
			inicial->A->B = final;
	}

	//valor posterior ao elemento final com null
	if(andar(final, antfinal)==NULL)
	{
		if(inicial->A==voltar(inicial, antinicial))
		{
			if(final->A==NULL) final->A=inicial->A;
			else final->B=inicial->A;

			if(inicial->A->A==inicial) inicial->A->A=final;
			else inicial->A->B=final;

			inicial->A=inicializa();
		}
		else
		{
			if(final->A==NULL) final->A=inicial->B;
			else final->B=inicial->B;

			if(inicial->B->B==inicial) inicial->B->B=final;
			else inicial->B->A=final;

			inicial->B=inicializa();
		}

	}
	else if(final->B == andar(final, antfinal))
	{

		if(final->B->A == voltar(andar(final, antfinal), final))
			final->B->A = inicial;
		else
			final->B->B = inicial;

		if(flag)
		{
			temp = final->B;
			final->B = inicial->B;
			inicial->A = temp;
			//final->A = inicial->B;
			//inicial->B = final->B;
		}
		else
		{
			temp = final->B;
			final->B = inicial->A;
			inicial->A = temp;
		}
	}
	else
	{
		if(final->A->A != voltar(andar(final, antfinal), final))
			final->A->B = inicial;
		else
			final->A->A = inicial;

		if(flag)
		{
			temp = final->A;
			final->A = inicial->B;
			inicial->B = temp;
		}
		else
		{
			temp = final->A;
			final->A = inicial->A;
			inicial->A = temp;
		}
	}
	return numeros;
}

No *inversor(No *numeros, int inicio, int fim)
{
	No *inicial, *antinicial, *final, *antfinal;
	
	//procura inicio da lista
	No *apontador = numeros, *segue = inicializa(), *pivo;
	for(int i = 0; i != inicio && andar(apontador, segue) != NULL; i++)
		{
			pivo = apontador;
			apontador = andar(apontador, segue);
			segue = pivo;
		}
	antinicial=segue;
	inicial=apontador;

	//procura final da lista
	apontador = numeros; segue = inicializa();
	for(int i = 0; i != fim && andar(apontador, segue) != NULL; i++)
		{
			pivo = apontador;
			apontador = andar(apontador, segue);
			segue = pivo;
		}
	antfinal=segue;
	final=apontador;

	//funcao inverte inicial e final
	numeros=inverter(numeros, inicial, antinicial, final, antfinal);
	return numeros;
}
