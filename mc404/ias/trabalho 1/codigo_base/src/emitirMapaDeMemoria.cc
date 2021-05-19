#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contemErro.h"

extern struct NomesDeclarados *cabecaNome;
int linha = 0;
enum lado { ESQUERDA = 0, DIREITA = 1 };

int trocaLado(int lado) {
	if(lado == ESQUERDA)
		return DIREITA;
	return ESQUERDA;
}

int trataDiretiva(Token* token, int posicaoToken) {
	const int numeroDiretivas = 5;
	const char *diretivas[] = { ".set", ".org", ".align", ".wfill", ".word" };
	struct NomesDeclarados *pivoLista;
	int i;
	int repeticao;
	int endereco;

	for(i = 0; i < numeroDiretivas; i++)
		if(!strcmp(diretivas[i], token->palavra)) {
			break;
		}

	switch(i) {
		case(0):
			return 2;
			break;
		case(1):
			token = recuperaToken(++posicaoToken);
			linha = strtol(token->palavra, NULL, 16);
			return 1;
			break;
		case(2):
			break;
		case(3):
			token = recuperaToken(++posicaoToken);
			repeticao = atoi(token->palavra);
			token = recuperaToken(++posicaoToken);
			if(token->tipo == Nome) {
				pivoLista = cabecaNome;
				while(pivoLista && strcmp(pivoLista->palavra, token->palavra)) {
					pivoLista = pivoLista->proximo;
				}
				endereco = strtol(pivoLista->valor, NULL, 16);
				//strtol(pivoLista->valor, NULL, 16)
			} else {
				if(token->tipo == Decimal)
					endereco = atoi(token->palavra);
				else
					endereco = strtol(pivoLista->valor, NULL, 16);
			}
				
			while(repeticao-- > 0){
				printf("%.3x 00 000 00 %.3x\n", linha++, endereco);
			}

			return 2;
			break;
		case(4):
			printf("%.3x 00 000 00 %.3lx\n", linha++, strtol(recuperaToken(++posicaoToken)->palavra, NULL, 16));
			return 1;
			break;
	}

	return 0;

}

void trataInstrucao(Token *token) {
	const int numeroInstrucoes = 17;
	const char *instrucoes[] = { "ld", "ldinv", "ldabs", "ldmq",
								 "ldmqmx", "store", "jump", "jge",
								 "add", "addabs", "sub", "subabs",
								 "mult", "div", "lsh", "rsh", "storend" };

	//tem instrucao que se estiver a direita eh um numero a esquerda eh outro
	//recupera proximo token e ve o q eh
	const int hex[] = {	0x01, 0x02, 0x03, 0x0A,
						0x09, 0x21, 0x0D, 0x0F,
						0x05, 0x07, 0x06, 0x08,
						0x0B, 0x0C, 0x14, 0x15, 0x12 };

	for(int i = 0; i < numeroInstrucoes; i++)
		if(!strcmp(instrucoes[i], token->palavra)) {
			printf("%.2x ", hex[i]);
			
			/* Instrucoes sem parametro */
			if(hex[i] == 0x14 || hex[i] == 0x15) {
				printf("000 ");
			}
		}
}

int emitirMapaDeMemoria()
{

	int posicaoToken = 0;
	int numberoDeTokens = getNumberOfTokens();
	Token *token;
	struct NomesDeclarados *pivoLista;
	//int lado = ESQUERDA;

	if(contemErro()) {
		limpaListas();
		return 1;
	}
	
	
	while(posicaoToken < numberoDeTokens) {
		token = recuperaToken(posicaoToken);
		
		switch(token->tipo) {
			case(Instrucao):
				trataInstrucao(token);
				break;		
			case(Diretiva):
				posicaoToken += trataDiretiva(token, posicaoToken);
				//fazer contador de prints
				break;
			case(DefRotulo):
				//ver linha em que foi definido
				break;
			case(Hexadecimal):
				//printf("%.3lx ", strtol(token->palavra, NULL, 16));
				break;
			case(Decimal):
				break;
			case(Nome):
				pivoLista = cabecaNome;
				while(pivoLista && strcmp(pivoLista->palavra, token->palavra)) {
					pivoLista = pivoLista->proximo;
				}

				if(pivoLista && pivoLista->tipo == Nome){
					printf("%.3lx ", strtol(pivoLista->valor, NULL, 16));
				} else if (pivoLista) {
					printf("<R> ");
				}
				
				break;
		}

		posicaoToken++;
	}

	limpaListas();
    return 0;
}