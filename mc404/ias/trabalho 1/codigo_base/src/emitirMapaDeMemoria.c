#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contemErro.h"

struct NomeDeclarado {
	TipoDoToken tipo;
	char *palavra;
	char *valor;
	int ehRotulo;
	int ladoNome;
};

struct NomeDeclarado vetorNomes[1000];
int quantidadeNomes = 0;

enum lado { ESQUERDA = 0, DIREITA = 1 };
int lado;

int linha = 0;

void trocaLado() {
	if(lado == ESQUERDA) {
		lado = DIREITA;
		printf(" ");
	} else {
		lado = ESQUERDA;
		printf("\n");
		linha++;
	}
}

int nomeNaoEhIgual(int contador, Token *token) {
	return contador < quantidadeNomes &&\
	strcmp(vetorNomes[contador].palavra, token->palavra);
}

int achaNomeSalvo(Token* token) {
	int contador = 0;
	while(nomeNaoEhIgual(contador, token))
		contador++;
	return contador;
}

void armazenaNome(int posicaoToken) {
	Token *token;

	/* armazena palavra */
	token = recuperaToken(++posicaoToken);
	vetorNomes[quantidadeNomes].palavra = token->palavra;

	/* armazena dados do nome */
	token = recuperaToken(++posicaoToken);
	vetorNomes[quantidadeNomes].valor = token->palavra;
	vetorNomes[quantidadeNomes].tipo = token->tipo;
	vetorNomes[quantidadeNomes].ehRotulo = 0;
	vetorNomes[quantidadeNomes].ladoNome = -1;
	quantidadeNomes++;
}

void alteraLinha(int posicaoToken) {
	Token *token;
	token = recuperaToken(++posicaoToken);
	linha = strtol(token->palavra, NULL, 16);
}

int pegaEndereco(int contador) {
	int endereco = 0;
	if(contador < quantidadeNomes) {
		if(vetorNomes[contador].tipo == Decimal)
			endereco = atoi(vetorNomes[contador].valor);
		else
			endereco = strtol(vetorNomes[contador].valor, NULL, 16);
	}
	//e se for rotulo ainda nao declarado
	return endereco;
}

int wfill(int posicaoToken) {
	Token *token;
	int repeticao;
	int endereco;
	int contador;

	token = recuperaToken(++posicaoToken);
	repeticao = atoi(token->palavra) - 1;
	token = recuperaToken(++posicaoToken);

	if(token->tipo == Nome) {
		contador = achaNomeSalvo(token);
		endereco = pegaEndereco(contador);
	} else if(token->tipo == Decimal) {
		endereco = atoi(token->palavra);
	} else {
		endereco = strtol(token->palavra, NULL, 16);
	}
	//safe belt contra erro gramatical em repeticao grande
	while(repeticao-- >= 0 && repeticao < 1050){
		printf("%.3X 00 000 00 %.3X\n", linha++, endereco);
	}

	lado = ESQUERDA;

	return 0;
}

int word(int posicaoToken) {
	Token *token;
		int endereco;
	int contador;

	token = recuperaToken(++posicaoToken);
	if(token->tipo == Hexadecimal){
		printf("%.3X 00 000 00 %.3lX\n", linha++, strtol(token->palavra, NULL, 16));
	} else if(token->tipo == Decimal){
		printf("%.3X 00 000 00 %.3X\n", linha++, atoi(token->palavra));
	} else if(token->tipo == Nome) {
		contador = achaNomeSalvo(token);
		endereco = pegaEndereco(contador);
		printf("%.3X 00 000 00 %.3X\n", linha++, endereco);
	}
	return 0;
}

int trataDiretiva(Token* token, int posicaoToken) {
	const int numeroDiretivas = 5;
	const char *diretivas[] = { ".set", ".org", ".align", ".wfill", ".word" };
	int diretiva;
	int endereco;

	/* Encontra diretiva correta */
	for(diretiva = 0; diretiva < numeroDiretivas; diretiva++)
		if(!strcmp(diretivas[diretiva], token->palavra)) {
			break;
		}

	switch(diretiva) {
		case(0):
			armazenaNome(posicaoToken);
			return 2;

		case(1):
			alteraLinha(posicaoToken);
			return 1;

		case(2):
			/* Acha multiplo do parametro de align */	
			token = recuperaToken(++posicaoToken);
			endereco = atoi(token->palavra);
			while(linha % endereco != 0)
				linha++;
			return 1;

		case(3):
			endereco = wfill(posicaoToken);
			if(endereco != -1)
				return 2;
			return -(posicaoToken + 1);

		case(4):
			endereco = word(posicaoToken);			
			if(endereco != -1)
				return 1;
			return -(posicaoToken + 1);
	}

	return 0;

}

int naoTemParametro(int instrucao) {
	return instrucao == 0x14 || instrucao == 0x15 || instrucao == 0x0A;
}

void trataInstrucao(Token *token, int posicaoToken) {
	int ladoProxInstrucao = -1;
	Token *tokenLado;
	int contador = 0;

	const int numeroInstrucoes = 17;
	const char *instrucoes[] = { "ld", "ldinv", "ldabs", "ldmq",
								 "ldmqmx", "store", "jump", "jge",
								 "add", "addabs", "sub", "subabs",
								 "mult", "div", "lsh", "rsh", "storend" };

	const int hexL[] = { 0x01, 0x02, 0x03, 0x0A,
						 0x09, 0x21, 0x0D, 0x0F,
						 0x05, 0x07, 0x06, 0x08,
						 0x0B, 0x0C, 0x14, 0x15, 0x12 };
	
	const int hexD[] = { 0x01, 0x02, 0x03, 0x0A,
						 0x09, 0x21, 0x0E, 0x10,
						 0x05, 0x07, 0x06, 0x08,
						 0x0B, 0x0C, 0x14, 0x15, 0x13 };

	tokenLado = recuperaToken(posicaoToken+1);
	if(tokenLado->tipo == Nome) {
		contador = achaNomeSalvo(tokenLado);
		ladoProxInstrucao = vetorNomes[contador].ladoNome;
	}

	for(int diretiva = 0; diretiva < numeroInstrucoes; diretiva++) {
		if(!strcmp(instrucoes[diretiva], token->palavra)) {
			if(lado == ESQUERDA)
				printf("%.3X ", linha);

			if(ladoProxInstrucao == DIREITA)
				printf("%.2X ", hexD[diretiva]);
			else
				printf("%.2X ", hexL[diretiva]);

			/* Instrucoes sem parametro */
			if(naoTemParametro(hexL[diretiva])) {
				printf("000");
				trocaLado();
			}
			break;
		}
	}
}

void defineRotulo(Token *token) {
	char *linhaEmString;

	vetorNomes[quantidadeNomes].palavra = token->palavra;
	linhaEmString = malloc(sizeof(*linhaEmString));
	sprintf(linhaEmString, "%x", linha);
	vetorNomes[quantidadeNomes].valor = linhaEmString;
	/* apaga dois pontos ':' do fim do rotulo */
	vetorNomes[quantidadeNomes].palavra[strlen(token->palavra)] = '\0';
	vetorNomes[quantidadeNomes].tipo = token->tipo;
	vetorNomes[quantidadeNomes].ehRotulo = 1;
	vetorNomes[quantidadeNomes].ladoNome = lado;
	quantidadeNomes++;
}

int emitirMapaDeMemoria()
{
	Token *token;
	int posicaoToken = 0;
	int numberoDeTokens = getNumberOfTokens();
	int contador;
	int endereco;

	if(contemErro())
		return 1;

	while(posicaoToken < numberoDeTokens) {
		token = recuperaToken(posicaoToken);

		switch(token->tipo) {
			case(Instrucao):
				trataInstrucao(token, posicaoToken);
				break;		
			case(Diretiva):
				posicaoToken += trataDiretiva(token, posicaoToken);
				if(posicaoToken == -1)
					return 1;
				break;
			case(DefRotulo):
					defineRotulo(token);
				break;
			case(Hexadecimal):
				printf("%.3lX", strtol(token->palavra, NULL, 16));
				trocaLado();
				break;
			case(Decimal):
				printf("%.3X", atoi(token->palavra));
				trocaLado();
				break;
			case(Nome):
				contador = achaNomeSalvo(token);
				endereco = pegaEndereco(contador);
				printf("%.3X", endereco);
				trocaLado();
				break;
		}

		posicaoToken++;
	}
	if(lado == DIREITA)
		printf("00 000\n");

    return 0;
}