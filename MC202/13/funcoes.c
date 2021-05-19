#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int ConstroiMatriz(int size, int grafo[size][size]){
	int i, j, tamanho = 0;
	/*Zera valores do grafo e da matriz achados*/
	for (i = 0; i < size; ++i){
		for (j = 0; j < size; ++j){
			grafo[i][j]=0;
		}
	}

	/*Pega valores dos vizinhos no grafo*/
	scanf("%d,%d", &i, &j);
	while(i != 0 || j != 0){
		if(j!=i){
			if(!grafo[j][i]) tamanho++;
			grafo[j][i]=1;

			if(!grafo[i][j]) tamanho++;
			grafo[i][j]=1;
		}
		scanf("%d,%d", &i, &j);
	}

	return tamanho+1;
}

/**Constroi o vetor de adjacencias**/
int ConstroiGrafo(int Vmaximo, int size, int vertices[Vmaximo], int vizinhos[size], int grafo[Vmaximo][Vmaximo]){
	int contador = 0, CntVizinhos = 1;
	int i, j, achou;

	vertices[0] = 0;

	for(i =0 ; i<size;i++){
		vizinhos[i]=-1;
	}

	for (i = 1; i < Vmaximo; ++i){
		achou = 0; /**Variavel de controle**/

		for (j = 1; j < Vmaximo; ++j){
			/**Se o valor esta marcado com 1 no grafo ele eh adicionado ao vetor de vizinhos**/
			if(grafo[i][j]){
				vizinhos[contador++] = j;
				achou = 1;
			}
		}

		/**Se o guarda achou esta foi alterado adicionamos o indice do elemento no vetor de vertices**/
		if(achou){
			vertices[CntVizinhos++] = contador;
		}
		else{
			vertices[CntVizinhos++] = contador;
		}
	}
	
	/**Coloca o ultimo valor como o mais alto para comparacao**/
	vertices[CntVizinhos] = contador;

	return 1;
}

Lista *AdcFila(Lista *fila, int numero, int distancia){
	Lista *novo, *pivo = fila;

	/**Constroi novo node**/
	novo = malloc(sizeof(Lista));
	if(!novo){
		return fila;
	}
	novo->valor = numero;
	novo->proximo = NULL;
	novo->distancia = distancia;

	/*Adiciona novo nó ao fim da lista*/
	if(!fila){
		fila = novo;
	}
	else{
		while(pivo->proximo){
			pivo = pivo->proximo;
		}
		pivo->proximo = novo;
	}

	return fila;
}

/*Verifica se valor ja foi encontrado anteriormente no grafo*/
int JaAchou(int valor, int size, int achados[size]){
	if(achados[valor]){
		return 1;
	}
	return 0;
}

Lista *PercorreGrafo(int Vmaximo, int *vertices, int *vizinhos, Lista *fila, int achados[Vmaximo]){

	if(vertices[fila->valor+1]==-1){
		return fila;
	}
	/**Pega limite superior e inferior na matriz 'vertices' **/
	for (int i = vertices[fila->valor]; i < vertices[fila->valor+1]; ++i)
	{
		/**Verifica se ja achou valor, caso tenha encontrado adiciona na lista no vetor 'achados' e mostra**/
		if(!JaAchou(vizinhos[i], Vmaximo, achados)){
			fila = AdcFila(fila, vizinhos[i]-1, fila->distancia+1);
			printf("%d %d\n", vizinhos[i], fila->distancia+1);
			achados[vizinhos[i]] = 1;
		}
	}
	return fila;
}

int BuscaLargura(int inicio, int Vmaximo, int n_vizinhos, int vertices[Vmaximo], int vizinhos[n_vizinhos]){
	Lista *fila=NULL, *pivo;
	int achados[Vmaximo];

	//**Atribui valores a matriz de controle dos valores encontrados**/
	for (int i = 0; i < Vmaximo; ++i){
		achados[i] = 0;
	}

	/**Coloca como achado valor inicial passado e atribui a fila**/
	achados[inicio] = 1;
	printf("%d 0\n", inicio);
	fila = AdcFila(fila, inicio-1, 0);

	/*Trabalha com fila para percorrer o grafo em ordem*/
	while(fila){
		fila = PercorreGrafo(Vmaximo, vertices, vizinhos, fila, achados);
		/**Limpa fila a cada volta**/
		pivo = fila->proximo;
		free(fila);
		fila = pivo;
	}
	return 1;
}