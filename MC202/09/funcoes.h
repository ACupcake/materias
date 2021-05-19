/**
Arquivo com declaracoes e structs
**/

typedef struct arvore{
	int numero;
	struct arvore *direita;
	struct arvore *esquerda;
} arvore;

//struct para lista linear usada na funcao 'largura'
typedef struct linear{
	arvore *dados;
	struct linear *proximo;
} linear;

arvore *cria(int n);

arvore *insere(arvore *node, int n);

arvore *busca_insere(arvore *node, int n);

arvore *busca(arvore *node, int n);

arvore *em_ordem(arvore *node);

arvore *pre_ordem(arvore *node);

arvore *pos_ordem(arvore *node);

arvore *armazena(arvore *node);

arvore *libera(arvore *node);

linear *largura(arvore *node, linear *lista);

linear *insere_linear(arvore *nova, linear *node);