#include <stdio.h>
#include <stdlib.h>
#include "tensor.h"

Tensor *create_tensor() {
	// Define a row-vector Tensor
	Tensor *vector = malloc(sizeof(Tensor));
	// A row-vector has only one row and 'n' columns
	vector->ndim = 1;
	int cols = 4;
	vector->shape = malloc(vector->ndim * sizeof(int));
	vector->stride = malloc(vector->ndim * sizeof(int));
	vector->data = malloc(cols * sizeof(float));

	vector->shape[0] = cols;
	vector->stride[0] = 1;

	for (int i = 0; i < cols; i++) {
		vector->data[i] = (float) i + 1;
	}
	return vector;
}

int main () {
	Tensor *t = create_tensor();
	int cols = 4;
	for (int i = 0; i < cols; i++) {
		printf("%.1f ", t->data[i]);
	}
	return 0;
}
