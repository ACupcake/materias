#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listaRotulo {
	char *palavra;
	int linha;
	struct listaRotulo *proximo;
};
struct listaRotulo *cabecaRotulo = NULL;

struct listaNome {
	char *palavra;
	char *valor;
	struct listaNome *proximo;
};
struct listaNome *cabecaNome = NULL;

Token *token;
unsigned int linha;


void limpaListas() {
	struct listaRotulo *ptrRotulo = cabecaRotulo;
	struct listaNome *ptrNome = cabecaNome;

	while(ptrNome) {
		ptrNome = ptrNome->proximo;
		free(cabecaNome);
		cabecaNome = ptrNome;
	}

	while(ptrRotulo) {
		ptrRotulo = ptrRotulo->proximo;
		free(cabecaRotulo);
		cabecaRotulo = ptrRotulo;
	}
}

// Rótulos podem ser declarados depois do uso
int contemErro() {
	struct listaNome *ptrNome;
	struct listaRotulo *ptrRotulo;
	struct listaNome *ptrPivoNome;
	struct listaRotulo *ptrPivoRotulo;
	int numberoDeTokens = getNumberOfTokens();
	int posicaoToken = 0;
	int estaNaLista;

	while(posicaoToken < numberoDeTokens) {
		token = recuperaToken(posicaoToken);
	
		if(!strcmp(token->palavra, ".set")) {
			ptrNome = (struct listaNome*) malloc(sizeof(*cabecaNome));
			ptrNome->palavra = recuperaToken(++posicaoToken)->palavra;
			ptrNome->valor = recuperaToken(++posicaoToken)->palavra;
			ptrNome->proximo = cabecaNome;
			cabecaNome = ptrNome;

		} else if(token->tipo == DefRotulo) {
			ptrRotulo = (struct listaRotulo*) malloc(sizeof(*cabecaRotulo));
			ptrRotulo->palavra = token->palavra;
			/* apaga dois pontos ':' */
			ptrRotulo->palavra[strlen(ptrRotulo->palavra) - 1] = '\0';
			ptrRotulo->linha = -1;
			ptrRotulo->proximo = cabecaRotulo;
			cabecaRotulo = ptrRotulo;

		} else if(token->tipo == Nome) {
			estaNaLista = 0;
			ptrPivoNome = cabecaNome;
			ptrPivoRotulo = cabecaRotulo;

			while(ptrPivoNome && !estaNaLista) {
				if(!strcmp(ptrPivoNome->palavra, token->palavra))
					estaNaLista = 1;
				ptrPivoNome = ptrPivoNome->proximo;
			}
			while(ptrPivoRotulo && !estaNaLista) {
				if(!strcmp(ptrPivoRotulo->palavra, token->palavra))
					estaNaLista = 1;
				ptrPivoRotulo = ptrPivoRotulo->proximo;
			}
	
			if(!estaNaLista) {
				printf("ERRO: Rótulo ou símbolo usado mas não definido: %s\n", token->palavra);
				return 1;
			}
		}

		posicaoToken++;
	}

	return 0;
}

int emitirMapaDeMemoria()
{
	if(contemErro()) {
		limpaListas();
		return 1;
	}

	

	limpaListas();
    return 0;
}