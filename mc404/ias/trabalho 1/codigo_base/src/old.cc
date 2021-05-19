int linha = 0;

struct node {
	char *palavra;
	char *valor;
	struct node *proximo;
};
struct node *cabeca = NULL;

void trataNome(char *palavra, char *valor) {
	struct node *ponteiro = (struct node*) malloc(sizeof(struct node));

	ponteiro->palavra = palavra;
	ponteiro->valor = valor;

	if(cabeca == NULL) {
		cabeca = ponteiro;
	} else {
		ponteiro->proximo = cabeca;
		cabeca = ponteiro;
	}
}

void limpaLista() {
	struct node *ponteiro = cabeca;

	while(ponteiro != NULL) {
		ponteiro = ponteiro->proximo;
		free(cabeca);
		cabeca = ponteiro;
	}

}

int nomeEstaDefinido(char *palavra) {
	struct node *ponteiro = cabeca;

	while(ponteiro)
		if(!strcmp(palavra, cabeca->palavra))
			return 1;
	return 0;
}

void trataInstrucao(Token *token, int pos) {
	const int numeroInstrucoes = 17;
	const char *instrucoes[] = {"ld", "ldinv", "ldabs", "ldmq", "ldmqmx",
						  		"store", "jump", "jge", "add", "addabs",
						  		"sub", "subabs", "mult", "div", "lsh",
						  		"rsh", "storend"};


	const int hex[] = {	1, 2, 3, 10, 9, 0x21, 13, 0x0f, 
						5, 7, 6, 8, 11, 12, 0x14, 0x15, 0x13 };

	for(int i = 0; i < numeroInstrucoes; i++)
		if(!strcmp(instrucoes[i], token->palavra)) {
			printf("%.2x ", hex[i]); //instrucoes[i]
			return;
		}

}

int mostraNumero(Token *token) {
	if(token->tipo == Hexadecimal) {
		printf("%.3x 00 000 00 %.3x\n", linha++, (int)strtol(token->palavra, NULL, 16));
	} else if(token->tipo == Decimal) {
		printf("%.3x 00 000 00 %.3x\n", linha++, atoi(token->palavra));
	} else {
		if(nomeEstaDefinido(token->palavra)){
			printf("%.3x 00 000 00 %.3x\n", linha++, atoi(token->palavra));
		} else {
			printf("ERRO: Rótulo ou símbolo usado mas não definido: %s\n", token->palavra);
				return 1;
		}
	}

	return 0;
}

int trataDiretiva(Token* token, int pos) {
	const int numeroDiretivas = 5;
	const char *diretivas[] = {".set", ".org", ".align", ".wfill", ".word"};
	int i;
	int repeticao;
	int erro = 0;

	for(i = 0; i < numeroDiretivas; i++)
		if(!strcmp(diretivas[i], token->palavra)) {
			break;
		}

	switch(i) {
		case(0):
			trataNome(recuperaToken(pos+1)->palavra, recuperaToken(pos+2)->palavra);
			pos += 2;
			break;
		case(1):
			linha = atoi(recuperaToken(++pos)->palavra);
			break;
		case(2):
			break;
		case(3):
			//verificar se n eh nome
			repeticao = atoi(recuperaToken(++pos)->palavra);
			token = recuperaToken(++pos);
			while(repeticao-- > 0){
				erro = mostraNumero(token);
				if(erro)
					return -1;
			}
			break;
		case(4):
			//loop infinito em 6, repeticao de codigo
			//conversao decimal hex pode dar errado em ultimo else
			token = recuperaToken(++pos);
			erro = mostraNumero(token);
			if(erro)
				return -1;
			break;
	}

	return pos;

}

void trataHexadecimal(char *palavra) {
	printf("%.3x ", atoi(palavra));
}

void trataDecimal(char *palavra) {
	printf("%.3x ", atoi(palavra));
}

/*
    ---- Voce deve implementar essa função para a Parte 2! ----
    Utilize os tokens da estrutura de tokens para montar seu código!
    Retorna:
        *  1 caso haja erro na montagem; (imprima o erro em stderr)
        *  0 caso não haja erro.
 */
int emitirMapaDeMemoria()
{
	int numberoDeTokens = getNumberOfTokens();
	Token* token;
	int pulaLinha = 0;

	for(int pos = 0; pos < numberoDeTokens; pos++) {
		token = recuperaToken(pos);

		switch(token->tipo) {
			case(1000):
				trataInstrucao(token, pos);
				break;
			case(1001):
				pos = trataDiretiva(token, pos);
				if(pos == -1)
					return 1;
				break;
			case(1002):
				//trataNome(token->palavra);
				//++pulaLinha;
				break;
			case(1003):
				trataHexadecimal(token->palavra);
				++pulaLinha;
				break;
			case(1004):
				trataDecimal(token->palavra);
				++pulaLinha;
				break;
			case(1005):
				//pos = trataNome(token, pos);
				break;
		}
	
		if(pulaLinha == 2) {
			printf("\n %.3d", linha++);
			pulaLinha = 0;
		}

	}