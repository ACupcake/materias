#include <stdio.h>
#include <stdlib.h>
 
int* countingSort(int *arr, int size, int interval) {
    int *output = malloc(sizeof(*output) * size);
    int count[interval + 1];

	for(int i = 0; i < interval + 1; i++) {
		count[i] = 0;
	}
 
    for(int i = 0; arr[i]; i++) {
        ++count[arr[i]];
    }
 
    for(int i = 1; i <= interval; i++) {
        count[i] += count[i - 1];
    }
 
    for(int i = 0; arr[i]; ++i) {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

	for(int i = 0; i < size; i++) {
		arr[i] = output[i];
	}
	return output;
}
 
void showArray(int *arr, int size) {
	for(int i = 0; i < size-1; i++) {
		printf("%d ", arr[i]);
	}
	printf("%d\n", arr[size-1]);
}

int main() {
	int *arr;
	int size;
	int interval;

	scanf("%d", &size);
	interval = (size * size) - 1;
	arr = malloc(sizeof(*arr) * interval);

	for(int i = 0; i < size; i++) {
		scanf("%d", &arr[i]);
	}

    int *result = countingSort(arr, size, interval);
 	free(arr);

	showArray(result, size);
	free(result);

    return 0;
}