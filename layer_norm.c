#include <stdio.h>
#include <stdlib.h>
#include "tensor.h"
#include "attention2.h"
#include "layer_norm.h"


tensor *layer_norm(Tensor *t) {
	int size = tensor_size(t);
	int rows = t->shape[0];
	int cols = t->shape[1];

	//int *out_shape = malloc(ndim * sizeof(int));
	//out->out_shape[0] = rows;
	//out->out_shape[1] = cols;
	//
	//Tensor *out = tensor_create(ndim, shape);

	for (int i = 0; i < size; i++) {
		float *rows = t->data + (i * cols);
		float sum = 0.0f;
		for (int j = 0; j < cols; j++) {
			sum += rows[j];
		}
		float mean = sum / (float) rows;
		float var = (t->data[i] - mean) * (t->data[i] - mean);

		for (int k = 0; k < cols; k++) {
			rows[k] = (t->data[i] - mean) / sqrt(var + eps);
		}
	}
	return t;
}

int main() {
	int ndim = 2;
	int *shape = malloc(ndim * sizeof(int));
	shape[0] = 10;
	shape[1] = 32;
	Tensor *matrix = tensor_create(ndim, shape);
	Tensor *t = layer_norm(&matrix);
	tensor_get(t);
	return 0;
}

