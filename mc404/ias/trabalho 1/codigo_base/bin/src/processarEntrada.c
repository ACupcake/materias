#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ehFimdaLinha(char letra) {
	return (letra == '\n' || letra == '#' || letra == '\r');
}

int ehInstrucao(char *palavra) {
	const int numeroInstrucoes = 17;
	char *instrucoes[] = {"ld", "ldinv", "ldabs", "ldmq", "ldmqmx",
						  "store", "jump", "jge", "add", "addabs",
						  "sub", "subabs", "mult", "div", "lsh",
						  "rsh", "storend"};

	for(int i = 0; i < numeroInstrucoes; i++)
		if(!strcmp(instrucoes[i], palavra))
			return 1;
	return 0;
}

int ehDiretiva(char *palavra) {
	const int numeroDiretivas = 5;
	char *diretivas[] = {".set", ".org", ".align", ".wfill", ".word"};

	for(int i = 0; i < numeroDiretivas; i++)
		if(!strcmp(diretivas[i], palavra))
			return 1;
	return 0;
}

int pulaComentario(char *entrada, int caractere, int tamanho) {
	while(entrada[caractere] != '\n' && caractere++ < tamanho)
		;
	return caractere;
}

/* Verifica se alguma caracteristica da palavra bate com algum tipo */
TipoDoToken defineTipo(char *palavra, int letra) {
	if(palavra[0] == '0' && palavra[1] == 'x') {
		return Hexadecimal;
	} else if(isdigit(palavra[0])) {
		return Decimal;
	} else if(palavra[0] == '.') {
		return Diretiva;
	} else if (palavra[letra - 1] == ':') {
		return DefRotulo;
	} else if(ehInstrucao(palavra)) {
		return Instrucao;
	} else {
		return Nome;
	}
}

int ehEspaco(char letra) {
	return (letra == ' ' || letra == '\t');
}

int ehHexadecimal(char numero) {
	return (isdigit(numero) || ((numero >= 'a') && (numero <= 'f')));
}

int ehCaractereValido(char caractere) {
	return (isdigit(caractere) || isalpha(caractere) || caractere == '_');
}

int temErroLexico(char *palavra, TipoDoToken tipo) {
	int letra = 0;
	
	switch(tipo) {
		case (Hexadecimal):
			/* Como o tipo eh hexadecimal pula '0x' */
			letra = 2;

			/* Se todos os numeros forem hexadecimais nao tem erro lexico */
			while(palavra[letra] != '\0')
				if(!ehHexadecimal(palavra[letra++]))
					return 1;
			break;


		case (Decimal):
			/* Se todos os numeros forem decimais nao tem erro lexico */
			while(palavra[letra] != '\0')
				if(!isdigit(palavra[letra++]))
					return 1;
			break;

		
		case (Diretiva):
			if(!ehDiretiva(palavra))
				return 1;
			break;


		case (DefRotulo):
			/*A primeira paralavra do rotulo nao pode ser um numero*/
			if(isdigit(palavra[0]))
				return 1;

			/*
				Se esta dentro dos caracteres validos e tem ':' no fim 
				estao nao tem erro lexico			
			*/
			while(palavra[letra] != '\0' && palavra[letra] != ':')
				if(!ehCaractereValido(palavra[letra++]))
					return 1;

			/*
				Verifica se tem algo depois dos dois pontos ':'
				se sim eh invalido e tem erro lexico
			*/	
			if(palavra[letra] != '\0' && palavra[letra+1] != '\0')
				return 1;

			break;


		case (Instrucao):
			/* Ja verificado ao definir tipo */
			break;


		case (Nome):
			return 0;
			/*A primeira palavra do nome nao pode ser um numero*/
			if(isdigit(palavra[0]))
				return 1;

			/*Se esta dentro dos caracteres validos entao nao tem erro lexico*/
			while(palavra[letra] != '\0')
				if(!ehCaractereValido(palavra[letra++]))
					return 1;

			break;
	}

	return 0;
}

/*
int temErroGramatical(char *palavra, TipoDoToken tipo) {
	return 0;
}
*/

int temErro(char *palavra, int linha, TipoDoToken tipo) {
	if(temErroLexico(palavra, tipo)) {
		fprintf(stderr, "ERRO LEXICO: palavra inválida na linha %d!\n", linha);
		return 1;
	}
	/*temErroGramatical(palavra, tipo);*/

	return 0;
}

int processarEntrada(char* entrada, unsigned tamanho)
{
	char* palavra = malloc(sizeof(*palavra) * 65);
	unsigned int linha = 1;
	int caractere = 0;
	int letra = 0;
	TipoDoToken tipo;

	while(caractere < tamanho) {
		if(!ehFimdaLinha(entrada[caractere]) && !ehEspaco(entrada[caractere])) {
			palavra[letra++] = tolower(entrada[caractere]);
		} else {
			palavra[letra] = '\0';

			if(letra > 0) {
				tipo = defineTipo(palavra, letra);
				if(temErro(palavra, linha, tipo))
					return 1;
	
				adicionarToken(tipo, palavra, linha);
				palavra = malloc(sizeof(*palavra) * 65);
			}

			if(ehFimdaLinha(entrada[caractere])) {
				++linha;
				caractere = pulaComentario(entrada, caractere, tamanho);
			}

			letra = 0;
		}
		
		caractere++;	

	}

	/* Uma palavra a mais do que o necessario eh alocada no fim */
	free(palavra);

    return 0;
}