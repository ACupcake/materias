/**
O programa cria uma lista encadeada e utiliza 3 metodos de
otimizacao de consulta a fim de identificar o numero de
tarefas de consulta para os tres metodos.
A entrada eh um valor 'n' que representa o tamanho do vetor de
1 a n, 'r' representa o numero de consultas e logo apos as consultas
sao digitadas.
A saida retorna o numero de tarefas realizadas por cada metodo.
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(int argc, char const *argv[])
{
	int i, n, r, n_mtf=0, n_transpose=0, n_count=0, *values;
	array *numbers;

	scanf("%d", &n);
	scanf("%d", &r);

	values=malloc(r*sizeof(int));

	for (i = 0; i < r; ++i)
		scanf("%d", &values[i]);

	numbers = initialize(); //inicialize array with NULL
	numbers = setarray(numbers, n); //set values from 1 to n in array
	n_mtf=loop_values(numbers, n, values, r, move_to_front);

	numbers=clean(numbers); //clean the array and return NULL
	numbers = setarray(numbers, n);
	n_transpose=loop_values(numbers, n, values, r, transpose);


	numbers=clean(numbers);
	numbers = setarray(numbers, n);
	n_count=loop_values(numbers, n, values, r, count);

	printf("%d %d %d\n", n_mtf, n_transpose, n_count);

	clean(numbers);
	free(values);

	return 0;
}
