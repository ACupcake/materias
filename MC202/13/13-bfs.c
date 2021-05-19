/**
-Implementacao de busca em largura com lista de adjacencias
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{
	int Vmaximo, vertice_ini, n_vizinhos;

	scanf("%d", &Vmaximo);
	Vmaximo++;

	int grafoMat[Vmaximo][Vmaximo];
	int vertices[2*Vmaximo];

	n_vizinhos = ConstroiMatriz(Vmaximo, grafoMat);

	int vizinhos[2*n_vizinhos];
	n_vizinhos-=1;
	scanf("%d", &vertice_ini);


	printf("Origem da busca: %d\n", vertice_ini);
	printf("Vertices alcancados e distancias:\n");
	ConstroiGrafo(Vmaximo, n_vizinhos, vertices, vizinhos, grafoMat);
	BuscaLargura(vertice_ini, Vmaximo, n_vizinhos, vertices, vizinhos);
	return 0;
}