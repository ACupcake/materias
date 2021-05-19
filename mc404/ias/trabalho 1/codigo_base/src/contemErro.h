#ifndef CONTEMERRO_H
#define CONTEMERRO_H

struct NomesDeclarados {
	TipoDoToken tipo;
	char *palavra;
	char *valor;
	int linha;
	struct NomesDeclarados *proximo;
};

struct NomesUsados {
	char *palavra;
	struct NomesUsados *proximo;
};

/* Limpa listas ligadas com dados dos tokens */
void limpaListas();

struct NomesDeclarados* declaraNome(
						struct NomesDeclarados *ptrNome,
						int posicaoToken);

struct NomesDeclarados* declaraRotulo(
							struct NomesDeclarados *ptrNome,
							Token *token);

int ehDeclaracaoDeNome(Token *token);

/* Verifica se o tipo do token eh 'Nome' e se ja foi declarado */
int tokenEstaNaLista(struct NomesDeclarados *ptrNome, Token* token);

int ehDeclaracaoDeRotulo(struct NomesDeclarados *ptrNome,
						struct NomesUsados *ptrNomeUsado);

/*
	Se token de nome nao esta na lista, salvamos para verificar
	se nao eh um rotulo declarado posteriormente.
*/
struct NomesUsados * adcNome(struct NomesUsados *ptrNomeUsado,
							struct NomesDeclarados *ptrNome,
							Token *token);

/* Verifica se nome eh um rotulo que foi declarado posteriormente */
int verificaRotulo(struct NomesUsados *ptrNomeUsado,
					struct NomesDeclarados *ptrNome);

/* Verifica se tokens de nomes e rotulos foram usados corretamente */
int contemErro();

/* Declara token na lista ligada como um rotulo */
struct NomesDeclarados* declaraRotulo(
							struct NomesDeclarados *ptrNome,
							Token *token);

/* Declara token na lista ligada como um nome */
struct NomesDeclarados* declaraNome(
						struct NomesDeclarados *ptrNome,
						int posicaoToken);

#endif