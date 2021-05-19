/*
	Problem: Maximum Product Subarray
*/

#include <stdio.h>
#include <stdlib.h>

double MAX(double a, double b) {
	return a > b ? a:b;
}

void getMaxMovingHead(double *array, int *headPtr, double *maxProduct, int tailPtr, double currProduct) {
	double currVal = currProduct;

	while((*headPtr) != tailPtr) {
		currVal = currVal / array[(*headPtr)];
		(*maxProduct) = MAX(currVal, *maxProduct);
		(*headPtr)++;
	}
}

void jumpZeros(double *array, int *headPtr, int *tailPtr) {
	while(array[*headPtr] == 0) {
		(*headPtr)++;
		(*tailPtr)++;
	}
}

/* Solution using two pointers O(2n)=O(n) */
double findMaxSubSequenceProduct(double *array, int arrSize) {
	int headPtr = 0, tailPtr = 0;
	double maxProduct = array[0], currProduct = maxProduct;

	for(tailPtr = 1; tailPtr < arrSize; tailPtr++) {
		
		if(array[tailPtr] != 0) {
			currProduct *= array[tailPtr];
		} else {
			/* Move head pointer to the first element after zero and
			 * check if there is a bigger product
			 */
			getMaxMovingHead(array, &headPtr, &maxProduct, tailPtr, currProduct);
			/* Jump first zero */
			headPtr++; tailPtr++;
			/* Jump other zeros, if they exist */
			jumpZeros(array, &headPtr, &tailPtr);
			/* Adjust pointer to next nonzero value */
			if(headPtr < arrSize) {
				currProduct = array[headPtr];
			}
		}
		maxProduct = MAX(currProduct, maxProduct);
	}
	/* Move head pointer to the end and check if there is a bigger product */
	getMaxMovingHead(array, &headPtr, &maxProduct, tailPtr, currProduct);

	return maxProduct;
}

int main() {
	int totalNumbers;
	double *sequence;

	scanf("%d", &totalNumbers);
	sequence = malloc(sizeof(*sequence) * totalNumbers);
	
	for(int i = 0; i < totalNumbers; i++) {
		scanf("%lf", &sequence[i]);
	}

	//6 decimal digits output
	printf("%lf\n", findMaxSubSequenceProduct(sequence, totalNumbers));

	free(sequence);

	return 0;
}