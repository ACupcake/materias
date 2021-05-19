#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listaNome {
	char *palavra;
	char *valor;
	TipoDoToken tipo;
	struct listaNome *proximo;
};
struct listaNome *cabecaNome = NULL;

Token *token;
unsigned int linha;


void limpaListas() {
	struct listaNome *ptrNome = cabecaNome;

	while(ptrNome) {
		ptrNome = ptrNome->proximo;
		free(cabecaNome);
		cabecaNome = ptrNome;
	}

}

// Rótulos podem ser declarados depois do uso
int contemErro() {
	struct listaNome *ptrNome;
	int numberoDeTokens = getNumberOfTokens();
	int posicaoToken = 0;
	int estaNaLista;

	while(posicaoToken < numberoDeTokens) {
		token = recuperaToken(posicaoToken);

		if(!strcmp(token->palavra, ".set")) {
			ptrNome = (struct listaNome*) malloc(sizeof(*cabecaNome));
			
			token = recuperaToken(posicaoToken);
			ptrNome->palavra = token->palavra;
			ptrNome->TipoDoToken = Token->tipo;

			token = recuperaToken(posicaoToken);
			ptrNome->valor = token->palavra;
			
			ptrNome->proximo = cabecaNome;
			cabecaNome = ptrNome;

		} else if(token->tipo == DefRotulo) {
			ptrRotulo = (struct listaRotulo*) malloc(sizeof(*cabecaRotulo));
			
			ptrNome->palavra = token->palavra;
			/* apaga dois pontos ':' */
			ptrRotulo->palavra[strlen(ptrRotulo->palavra) - 1] = '\0';
			ptrNome->proximo = cabecaNome;
			
			cabecaNome = ptrNome;
			ptrNome->TipoDoToken = Token->tipo;

		} else if(token->tipo == Nome) {
			estaNaLista = 0;

			while(ptrNome && !estaNaLista) {
				if(!strcmp(ptrNome->palavra, token->palavra))
					estaNaLista = 1;
				ptrNome = ptrNome->proximo;
			}

			if(!estaNaLista) {
				printf("ERRO: Rótulo ou símbolo usado mas não definido: %s\n", token->palavra);
				return 1;
			}

			ptrNome = cabecaNome;
		}

		posicaoToken++;
	}

	return 0;
}

int emitirMapaDeMemoria()
{
	printf("QUEIJO\n");
	//if(contemErro()) {
	//	limpaListas();
	//	return 1;
	//}
	//
//
	//limpaListas();
    return 0;
}