/**
Arquivo com declaracao de funcoes e structs.
**/

struct vetor
{
	int *numeros;
	int inicio;
	int fim;
	int tamanho;
	int ocupado;
};
typedef struct vetor Vetor;

Vetor *inicializa_struct(void);

Vetor *insere_fim(Vetor *dado, int num);

Vetor *insere_inicio(Vetor *dado, int numero);

Vetor *remove_inicio(Vetor *dado);

Vetor *remove_fim(Vetor *dado);

int *divide(Vetor *dado);

int *dobra(Vetor *dado);

void mostra_primeiro(Vetor *dado);

void mostra_ultimo(Vetor *dado);

void copia(Vetor *dado, int *vet); //copia de um vetor menor para um maior e vice e versa

void esta_vazio(Vetor *dado); //retorna yes se o vetor estiver vazio e no caso contrario
