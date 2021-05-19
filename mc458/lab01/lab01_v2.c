#include <stdio.h>
#include <stdlib.h>

double max(double a, double b) {
	return a > b ? a:b;
}

/*
	maxProduct:
		Produto maximo encontrado
	currProduct:
		Produto do vetor inteiro, mas reseta para 1 se encontra
		um zero ou se o produto da um numero entre 0 e 1
	bestProduct:
		Tenta pegar o melhor produto naquele momento, removendo
		do inicio se necessario
	shortTermProduct:
		Pega o melhor naquele momento
	ignoreFloatProduct:
		Produto que ignora float
*/

double maxSubArrProduct(double *arr, int arrSize) {
	double maxProduct = 1, currProduct = 1, bestProduct = 1;
	double shortTermProduct = 1, ignoreFloatProduct = 1;
	int tail = 0, tailBest = 0;;

	for(int i = 0; i < arrSize; i++) {
		if(arr[i] != 0) {
			currProduct *= arr[i];
			bestProduct *= arr[i];
			shortTermProduct = max(shortTermProduct * arr[i], arr[i]);
			ignoreFloatProduct = (abs(arr[i]) < 1) ? 1 : ignoreFloatProduct * arr[i];
		}

		if(arr[i] == 0) {
			ignoreFloatProduct = 1;
			shortTermProduct = 1;
		}

		while(tailBest < i && bestProduct < 0) {
			if(arr[tailBest] != 0) bestProduct /= arr[tailBest];
			maxProduct = max(maxProduct, bestProduct);
			tailBest++;
		}

		if(abs(currProduct) < 1 || arr[i] == 0) {
			while(tail < i) {
				if(arr[tail] != 0) currProduct /= arr[tail];
				maxProduct = max(maxProduct, currProduct);
				tail++;
			}

			if(arr[i] == 0) {
				currProduct = 1;
				bestProduct = 1;
			}

			while(arr[tail] == 0) {
				tail++;
			}
			tailBest = tail;
		}

		maxProduct = max(maxProduct, currProduct);
		maxProduct = max(maxProduct, bestProduct);
		maxProduct = max(maxProduct, shortTermProduct);
		maxProduct = max(maxProduct, ignoreFloatProduct);
	}

	while(tail < arrSize) {
		if(arr[tail] != 0) currProduct /= arr[tail];
		maxProduct = max(maxProduct, currProduct);
		tail++;
	}

	return maxProduct;
}

int main() {
	int arrSize;
	double *arr;

	scanf("%d", &arrSize);
	arr = malloc(sizeof(*arr) * arrSize);
	
	for(int i = 0; i < arrSize; i++) {
		scanf("%lf", &arr[i]);
	}

	printf("%lf\n", maxSubArrProduct(arr, arrSize));

	free(arr);

	return 0;
}