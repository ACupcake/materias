/**
Implementacao de heapsort implicito
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{
	int maximo;
	scanf("%d", &maximo);

	int heap[maximo];

	CriaVetor(heap, maximo);
	HeapSort(heap, maximo);
	MostraHeap(heap, maximo);
	
	return 0;
}