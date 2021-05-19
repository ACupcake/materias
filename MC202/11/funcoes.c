/**
Arquivo com as funcoes utilizadas na main
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//transforma caracteres em inteiros
unsigned long djb2(char *str){
  unsigned long hash = 6251;
  int c;
  
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 32 + hash + c
  
  return hash;
}

Hash *Inicializa_Hash(int tamanho)
{
	Hash* nova_hash = (Hash*) malloc(sizeof(Hash));

	if(nova_hash){
		nova_hash->TAMANHO = tamanho;
		nova_hash->valores = malloc(tamanho*sizeof(Lista*));
		nova_hash->ocupado = 0;
		for(int i = 0; i<tamanho; i++)
			nova_hash->valores[i] = NULL;
	}

	return nova_hash;
}

int Inserir_Hash(Hash *nova_hash, char *texto, int id)
{
	//verifica se a lista é nula ou se esta cheia ou se valor ja existe//
	if(!nova_hash || nova_hash->ocupado == nova_hash->TAMANHO)
		return 0;

	//acha posicao na tabela//
	unsigned long pos = djb2(texto) % nova_hash->TAMANHO;
	
	Lista *novo;

	//cria novo no//
	novo = (Lista*) malloc(sizeof(Lista));
	if(!novo) return 0;
	strcpy(novo->texto, texto);
	novo->id = id;
	novo->removido=0;
	nova_hash->ocupado++;
	//printf("i %s\n", texto);
	//insercao caso nao ocorra colisao//
	if(!nova_hash->valores[pos] || nova_hash->valores[pos]->removido==1){
		if(nova_hash->valores[pos] && nova_hash->valores[pos]->removido)
			novo->removido=2;
		nova_hash->valores[pos]=novo;
	}
	//caso onde ocorre colisao na insercao//
	else{
		//printf("real\n");
		//recalcula posicao//
		unsigned long pos2, posn;
		int n=2;
		pos2 = ((djb2(texto)) % (nova_hash->TAMANHO-1))+1;

		if(!nova_hash->valores[pos2] || nova_hash->valores[pos2]->removido==1){
			if(nova_hash->valores[pos2] && nova_hash->valores[pos2]->removido)
				novo->removido=2;
			nova_hash->valores[pos2]=novo;
		}
		else{
			//printf("real 2\n");
			posn = pos2;
			while(nova_hash->valores[posn] && !(nova_hash->valores[posn]->removido==1) ){
				posn=(pos+n*pos2) % (nova_hash->TAMANHO);
				n++;
			}
			if(nova_hash->valores[posn] && nova_hash->valores[posn]->removido==1)
				novo->removido=2;
			nova_hash->valores[posn]=novo;
		}
	}
	return 1;
}

int Buscar_Hash(Hash *nova_hash, char *texto){
	//pega posicao//
	unsigned long pos = djb2(texto) % nova_hash->TAMANHO, pos2, posn;
	int n=2;
	
	Lista *pivo = nova_hash->valores[pos];

	//anda com o pivo ate encontrar o no pedido ou nulo//
	if(pivo && (pivo->removido || strcmp(pivo->texto, texto)))
	{
		pos2 = ((djb2(texto)) % (nova_hash->TAMANHO-1))+1;
		pivo = nova_hash->valores[pos2];

		if(pivo && (pivo->removido || strcmp(pivo->texto, texto))){
			while(pivo && strcmp(pivo->texto, texto) ){
				posn=(pos+n*pos2) % (nova_hash->TAMANHO);
				n++;
				pivo = nova_hash->valores[posn];				
			}

			//if(n>=6251) pivo=NULL;
		}
	}
	//se nao encontrado, eh retornado 0//
	if(!pivo) return -1;
	if(pivo->removido) return -1;

	//se o no eh encontrado seu id eh retornado somando 1 para evitar o valor 0//
	return pivo->id;
}

int Remover_Hash(Hash *nova_hash, char *texto){

	int numero = Buscar_Hash(nova_hash, texto);
	unsigned long pos = djb2(texto) % nova_hash->TAMANHO, pos2, posn;
	int n=2;
	Lista *pivo = nova_hash->valores[pos];
	//printf("r %s\n", texto);
	//valor foi encontrado na busca//
	if(numero!=-1)
	{
		if(pivo && (pivo->removido || strcmp(pivo->texto, texto)))
		{
			pos2 = ((djb2(texto)) % (nova_hash->TAMANHO-1))+1;
			pivo = nova_hash->valores[pos2];

			if(pivo && (pivo->removido || strcmp(pivo->texto, texto)) ){
				while(pivo && strcmp(pivo->texto, texto)){
					posn=(pos+n*pos2) % (nova_hash->TAMANHO);
					n++;
					pivo = nova_hash->valores[posn];
				}
				//if(n>=6251) pivo=NULL;
			}
		}

		if(pivo) pivo->removido=1;
		return 1;
	}
	else
		return 0;
}

void Limpa_Memoria(Hash *nova_hash){
	Lista *pivo;

	//procura e limpa listas encadeadas criadas em colisao
	for(int i = 0; i<nova_hash->TAMANHO; i++){
		pivo = nova_hash->valores[i];
		free(pivo);
	}

	//limpa tabela e lista de valores
	free(nova_hash->valores);
	free(nova_hash);
}