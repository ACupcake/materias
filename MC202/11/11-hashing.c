/**
O arquivo eh uma implementacao de uma funcao hashing, com opcoes de busca
remocao e insercao
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main()
{
	char entrada_funcao;
	char texto[255];
	int numero, id=0;
	Hash *nova_hash = Inicializa_Hash(6251);

	while(entrada_funcao != 'f'){
		entrada_funcao = getchar();
		//insercao//
		if(entrada_funcao == 'i'){
			scanf("%s", texto);
			numero = Buscar_Hash(nova_hash, texto);
			if(numero==-1){
				Inserir_Hash(nova_hash, texto, id);
				id++;
			}
		}
		//busca//
		else if(entrada_funcao == 'b'){
			scanf("%s", texto);
			//printf("b %s\n", texto);
			numero = Buscar_Hash(nova_hash, texto);
			if(numero != -1)
				printf("%s encontrada, id %d\n", texto, numero);
			else
				printf("%s nao encontrada\n", texto);
		}
		//remocao//
		else if(entrada_funcao == 'r'){
			scanf("%s", texto);
			Remover_Hash(nova_hash, texto);
		}
	}

	Limpa_Memoria(nova_hash);

	return 0;
}