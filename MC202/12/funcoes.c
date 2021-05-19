/**
Arquivo com funcoes necessarias no heapsort
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void CriaVetor(int *heap, int maximo){
	int numero;

	for(int pos=0; pos<maximo; pos++){
		scanf("%d", &numero);
		heap[pos] = numero;
	}
}

void Troca(int *heap, int pos, int pos2){
  int pivo = heap[pos2];
  heap[pos2] = heap[pos];
  heap[pos] = pivo;
}

int RemoveMaximo(int *heap, int i, int maximo){
  Troca(heap, 0, i);
  return maximo-1;
}

//ordena valores sempre com pai>filho
void Heapify(int *heap, int pai, int maximo){
  int maior;
  int dir=(pai*2+2); //posicao filho da direira
  int esq=(pai*2+1); //posicao filho da esquerda

  //verifica quem eh maior//
  if(esq<maximo && heap[esq]>heap[pai])
    maior=esq;
  else 
    maior=pai;
  if(dir<maximo && heap[dir]>heap[maior])
    maior=dir;

  //troca e realiza recursao se nao estiver no fim//
  if(maior!=pai){
    Troca(heap, pai, maior);
    Heapify(heap, maior, maximo);
  }
}

//Constroi o heap com o vetor desordenado//
void BuildHeap(int *heap, int maximo){
  //percorre o array de 'no' em 'no' a partir pai do ultimo elemento//
  for(int pai=maximo/2-1; pai>=0; pai--)
    Heapify(heap, pai, maximo);
}

//ordenacao crescente
void HeapSort(int *heap, int maximo){
  int i;
  //constroi heap
  BuildHeap(heap, maximo);
  //deixa um 'no' pai sempre maior que o filho com heapify
  for (i = maximo-1; i >= 0; i--) {
    maximo = RemoveMaximo(heap, i, maximo);
    Heapify(heap, 0, maximo);
  }
}

void MostraHeap(int *heap, int maximo){
  for (int i = 0; i < maximo; ++i)
    printf("%d ", heap[i]);
  printf("\n");
}