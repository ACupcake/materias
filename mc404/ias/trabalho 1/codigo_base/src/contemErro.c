#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contemErro.h"

struct NomesDeclarados *cabecaLista;

void limpaListas() {
	struct NomesDeclarados *ptrNome = cabecaLista;

	while(ptrNome) {
		ptrNome = ptrNome->proximo;
		free(cabecaLista);
		cabecaLista = ptrNome;
	}

}

struct NomesDeclarados* declaraNome(
						struct NomesDeclarados *ptrNome,
						int posicaoToken) {

		Token *token;
		ptrNome = (struct NomesDeclarados*) malloc(sizeof(*ptrNome));

		/* Coloca dados do token na lista ligada */
		token = recuperaToken(++posicaoToken);
		ptrNome->palavra = token->palavra;
		ptrNome->tipo = token->tipo;
		token = recuperaToken(++posicaoToken);
		ptrNome->valor = token->palavra;
		
		/* Ajusta lista ligada */
		ptrNome->proximo = cabecaLista;
		cabecaLista = ptrNome;

		return ptrNome;
}

struct NomesDeclarados* declaraRotulo(
							struct NomesDeclarados *ptrNome,
							Token *token) {

		ptrNome = (struct NomesDeclarados*) malloc(sizeof(*ptrNome));
			
		/* Coloca dados do token na lista ligada */
		ptrNome->palavra = token->palavra;
		/* apaga dois pontos ':' do fim do rotulo */
		ptrNome->palavra[strlen(ptrNome->palavra) - 1] = '\0';
		ptrNome->proximo = cabecaLista;
		ptrNome->tipo = token->tipo;

		cabecaLista = ptrNome;

		return ptrNome;
}

int ehDeclaracaoDeNome(Token *token) {
	return strcmp(token->palavra, ".set");
}

/* Verifica se o tipo do token eh 'Nome' e se ja foi declarado */
int tokenEstaNaLista(struct NomesDeclarados *ptrNome, Token* token) {
	while(ptrNome) {
		if(ptrNome->tipo == Nome && !strcmp(ptrNome->palavra, token->palavra)){
			return 1;
		}
		ptrNome = ptrNome->proximo;
	}
	return 0;
}

int ehDeclaracaoDeRotulo(struct NomesDeclarados *ptrNome,
						struct NomesUsados *ptrNomeUsado) {
	return (ptrNome->tipo == DefRotulo && !strcmp(ptrNome->palavra,\
	ptrNomeUsado->palavra));
}


struct NomesUsados * adcNome(struct NomesUsados *ptrNomeUsado,
							struct NomesDeclarados *ptrNome,
							Token *token) {
	struct NomesUsados *pivo;

	if(!tokenEstaNaLista(ptrNome, token)) {
		pivo = ptrNomeUsado;
		ptrNomeUsado = (struct NomesUsados*) malloc(sizeof(*ptrNomeUsado));
		ptrNomeUsado->palavra = token->palavra;
		ptrNomeUsado->proximo = pivo;
	}
	return ptrNomeUsado;
}

int verificaRotulo(struct NomesUsados *ptrNomeUsado,
					struct NomesDeclarados *ptrNome) {

	struct NomesUsados *pivo;

	while(ptrNomeUsado) {
		ptrNome = cabecaLista;
		while(ptrNome) {
			if(ehDeclaracaoDeRotulo(ptrNome, ptrNomeUsado))
				break;
			ptrNome = ptrNome->proximo;
		}

		/* Se o nome nao eh rotulo tratamos como erro */
		if(!ptrNome) {
			printf("ERRO: Rótulo ou símbolo usado mas não definido: %s\n", ptrNomeUsado->palavra);
			while(ptrNomeUsado) {
				pivo = ptrNomeUsado;
				ptrNomeUsado = ptrNomeUsado->proximo;
				free(pivo);
			}
			limpaListas();
			return 1;
		}

		/* Passa para proximo nome encontrado e limpa anterior */
		pivo = ptrNomeUsado;
		ptrNomeUsado = ptrNomeUsado->proximo;
		free(pivo);
	}
	return 0;
}

float contaLinha(Token *token, int posicaoToken, int linha) {
	const int numeroInstrucoes = 17;

	const char *instrucoes[] = { "ld", "ldinv", "ldabs", "ldmq",
								 "ldmqmx", "store", "jump", "jge",
								 "add", "addabs", "sub", "subabs",
								 "mult", "div", "lsh", "rsh", "storend" };

	if(!strcmp(".wfill", token->palavra)) {
		return atoi(recuperaToken(++posicaoToken)->palavra) + linha;
	}

	if(!strcmp(".word", token->palavra)) {
		return linha + 1;
	}

	if(!strcmp(".org", token->palavra)) {
		return strtol(recuperaToken(++posicaoToken)->palavra, NULL, 16);
	}

	for(int diretiva = 0; diretiva < numeroInstrucoes; diretiva++) {
		if(!strcmp(instrucoes[diretiva], token->palavra)) {
			return 0.5 + linha;
		}
	}

	return linha;
}

int contemErro() {
	Token *token;
	struct NomesDeclarados *ptrNome = NULL;
	struct NomesUsados *ptrNomeUsado = NULL;
	int numberoDeTokens = getNumberOfTokens();
	int posicaoToken = 0;
	//float linha = 0;

	while(posicaoToken < numberoDeTokens) {
		token = recuperaToken(posicaoToken);

		if(!ehDeclaracaoDeNome(token)) {
			ptrNome = declaraNome(ptrNome, posicaoToken);
			posicaoToken += 2; /* dois tokens sao chamados na funcao */

		} else if(token->tipo == DefRotulo) {
			ptrNome = declaraRotulo(ptrNome, token);
			//printf("%x\n", (int)linha);

		} else if(token->tipo == Nome) {
			ptrNomeUsado = adcNome(ptrNomeUsado, ptrNome, token);
		}
		//} else {
		//	linha = contaLinha(token, posicaoToken, linha);
		//}
		posicaoToken++;
	}

	if(verificaRotulo(ptrNomeUsado, ptrNome)){
		ptrNome = cabecaLista;
		limpaListas();		
		return 1;
	}

	ptrNome = cabecaLista;
	limpaListas();
	return 0;
}