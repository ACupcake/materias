#ifndef FUNCOES_GRAFO_H
#define FUNCOES_GRAFO_H

typedef struct lista{
	int valor;
	int distancia;
	struct lista *proximo;
} Lista;

int ConstroiMatriz(int size, int grafo[size][size]);

int ConstroiGrafo(int Vmaximo, int size, int vertices[Vmaximo], int vizinhos[size], int grafo[Vmaximo][Vmaximo]);

int BuscaLargura(int inicio, int Vmaximo, int n_vizinhos, int vertices[Vmaximo], int vizinhos[n_vizinhos]);

int JaAchou(int valor, int size, int achados[size]);

Lista *AdcFila(Lista *fila, int numero, int distancia);

Lista *PercorreGrafo(int Vmaximo, int *vertices, int *vizinhos, Lista *fila, int achados[Vmaximo]);

#endif