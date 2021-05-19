/**
Arquivo com declaracao de funcoes e structs.
**/

struct no
{
	double numero;
	struct no *A;
	struct no *B;
};
typedef struct no No;

No *inicializa(void);

No *inserir(No *numeros, int posicao, double valor);

No *inversor(No *numeros, int inicio, int fim);

No *inverter(No *numeros, No *inicial, No *antinicial, No *final, No *antfinal);

No *andar(No *numeros, No* segue); //passa para o No seguinte

No *voltar(No *apontador, No *segue); //passa para o No anterior

void mostrar(No *numeros);
