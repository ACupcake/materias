/**
Arquivo com funcoes utilizadas no programa principal
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

Vetor *inicializa_struct(void)
{
	Vetor* novo_vet = (Vetor*) malloc(sizeof(Vetor));

	novo_vet->numeros = malloc(2*sizeof(int));
	novo_vet->inicio=0;
	novo_vet->fim=0;
	novo_vet->tamanho=2;
	novo_vet->ocupado=0;

	return novo_vet;
}

//copia do vetor menor para o maior e vice e versa
void copia(Vetor *dado, int *vet)
{
	int i, j;
	
	if(dado->inicio>dado->fim) //caso o a cabeca do vetor esteja depois da cauda
	{
		for (i = dado->inicio; i < dado->tamanho; ++i) //copia do elemento 'inicio' ate o ultimo valor
			vet[i-dado->inicio]=dado->numeros[i];
		i=i-dado->inicio;
		for (j = 0; j < dado->fim+1; ++j) //copia do 0 ate o elemento 'fim'
			vet[i+j]=dado->numeros[j];
	}
	else
	{
		for (i = dado->inicio; i < dado->fim+1; ++i) //copia do elemento 'fim' ate o elemento 'inicio'
			vet[i-dado->inicio]=dado->numeros[i];
	}
}

//dobra o tamanho do vetor dentro da struct 'dado'
int *dobra(Vetor *dado)
{
	int *vet;

	vet=malloc(2*dado->tamanho*sizeof(int));
	copia(dado, vet);

	if(dado->fim>dado->inicio)
		dado->fim=dado->fim-dado->inicio;
	else
		dado->fim=dado->tamanho-(dado->inicio)+(dado->fim);
	dado->inicio=0;
	dado->tamanho*=2;

	return vet;
}

//divide em 2 o tamanho do vetor dentro da struct 'dado'
int *divide(Vetor *dado)
{
	if(dado->tamanho<=2)
		return dado->numeros;

	int *vet;

	vet=malloc(dado->tamanho*sizeof(int)/2);
	copia(dado, vet);

	if(dado->fim>dado->inicio)
		dado->fim=dado->fim-dado->inicio;
	else
		dado->fim=dado->tamanho-1-dado->inicio+dado->fim;
	dado->inicio=0;
	dado->tamanho/=2;

	return vet;
}

Vetor *insere_fim(Vetor *dado, int numero)
{
	if(dado->tamanho==dado->ocupado) //confere tamanho
		dado->numeros=dobra(dado);
	
	if(dado->fim==dado->tamanho && dado->inicio!=0) //volta o fim para o valor 0
		dado->fim=0;

	if(dado->ocupado>0)
		dado->fim+=1;
	dado->ocupado+=1;
	dado->numeros[dado->fim]=numero;

	return dado;
}

Vetor *insere_inicio(Vetor *dado, int numero)
{
	if(dado->tamanho==dado->ocupado) //confere tamanho
		dado->numeros=dobra(dado);

	if(dado->ocupado>0){
		if(dado->inicio==0)
			dado->inicio=dado->tamanho; //coloca o inicio no na ultima posicao
		dado->inicio-=1;
	}

	dado->numeros[dado->inicio]=numero;
	dado->ocupado+=1;
	return dado;
}

Vetor *remove_inicio(Vetor *dado)
{
	if(dado->tamanho/4==dado->ocupado)
		dado->numeros=divide(dado);


	if(dado->ocupado>0)
	{
		if(dado->inicio!=dado->tamanho-1)
			dado->inicio+=1;
		else
			dado->inicio=0;
		dado->ocupado-=1;
	}
	if(dado->ocupado==0) //volta os vetores para a posicao inicial
	{
		dado->inicio=0;
		dado->fim=0;
	}
	return dado;
}

Vetor *remove_fim(Vetor *dado)
{
	if(dado->tamanho/4==dado->ocupado)
		dado->numeros=divide(dado);
	
	if(dado->ocupado>0)
	{
		if(dado->fim>0)
			dado->fim-=1;
		else
			dado->fim=dado->tamanho-1;
		dado->ocupado-=1;
	}

	if(dado->ocupado==0) //volta os vetores para a posicao inicial
	{
		dado->inicio=0;
		dado->fim=0;
	}
	return dado;
}

void mostra_ultimo(Vetor *dado)
{
	if(dado->ocupado>0)
		printf("%d\n", dado->numeros[dado->fim]);
}

void mostra_primeiro(Vetor *dado)
{
	if(dado->ocupado>0)
		printf("%d\n", dado->numeros[dado->inicio]);
}

void esta_vazio(Vetor *dado)
{
	if(dado->ocupado==0)
		printf("yes\n");
	else
		printf("no\n");
}
