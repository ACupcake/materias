/**
Arquivo com declaracoes e structs
**/

typedef struct arvore{
	int numero;
	struct arvore *direita;
	struct arvore *esquerda;
	struct arvore *pai;
} arvore;

//struct para lista linear usada na funcao 'largura'
typedef struct linear{
	arvore *dados;
	struct linear *proximo;
} Lista;

arvore *cria(int inteiro);

arvore *insere_arvore(arvore *node, int inteiro);

arvore *buscar(arvore *node, int inteiro);

arvore *em_ordem(arvore *node);

arvore *pre_ordem(arvore *node);

arvore *pos_ordem(arvore *node);

arvore *libera_memoria(arvore *node);

arvore *remover(arvore *node, int inteiro);

arvore *acha_minimo(arvore *node);

arvore *acha_maximo(arvore *node);

Lista *largura(arvore *node, Lista *lista);

Lista *insere_lista(arvore *nova, Lista *node);

int buscar_intervalo(arvore *node, int n_inferior, int n_superior);

void sucessor(arvore *node, int inteiro);

void predecessor(arvore *node, int inteiro);