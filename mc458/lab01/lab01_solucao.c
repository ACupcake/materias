#include <stdio.h>
#include <stdlib.h>

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}

double maxSubArrProduct(double *arr, int arrSize) {
    if(arrSize <= 0) {
        return 0;
    }

    double currMax = arr[0];
    double maxProd = currMax;

    for(int i = 1; i < arrSize; i++) {
        double lastMax = currMax;
        currMax = max(arr[i], arr[i] * lastMax);
        maxProd = max(maxProd, currMax);
    }
    return max(1, maxProd);
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