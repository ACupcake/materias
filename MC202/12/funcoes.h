/**
Arquivo com declaracoes e structs
**/

typedef struct heap{
	int numero;
	struct heap *direita;
	struct heap *esquerda;
} Heap;

void CriaVetor(int *heap, int maximo);

void HeapSort(int *heap, int maximo);

void MostraHeap(int *heap, int maximo);

void Troca(int *heap, int pos, int pos2);

void Heapify(int *heap, int pai, int maximo);

void BuildHeap(int *heap, int maximo);

int RemoveMaximo(int *heap, int i, int maximo);