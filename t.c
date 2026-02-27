#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
	int *shape;
	int *stride;
	int ndim;
	float *data;
} Tensor;

Tensor *tensor_create(int ndim, int *shape) {
	Tensor *t = malloc(sizeof(Tensor));
	if (!t) {
		fprintf(stderr, "something's wrong with memory allocation\n-> aborting..");
		return NULL;
	}
	t->shape = malloc(ndim * sizeof(int));
	t->stride = malloc(ndim * sizeof(int));
	t->ndim = ndim;


	// define the shape of Tensor
	for (int i = 0; i < ndim; i++) {
		t->shape[i] = shape[i];
	}
	// calcuate size of tensor in self-contained fashion
	int size = 1;
	for (int i = 0; i < ndim; i++) {
		size *= shape[i];
	}
	//printf("Size of tensor: %d\n", size);
	//ndim - 1 > is always 1, fastest changing dimension
	// for next ones wer reveser loop and assign
	// stride[i] = t->stride[i + 1] * t->shape[i + 1]
	t->stride[ndim - 1] = 1;
	for (int i = ndim - 2; i >= 0; i--) {
		t->stride[i] = t->stride[i + 1] * t->shape[i + 1];
	}
	//printf("Stride: %d, %d, %d\n", t->stride[0], t->stride[1], t->stride[2]);
	// define the data now
	t->data = malloc(size * sizeof(float));
	for (int i = 0; i < size; i++) {
		t->data[i] = (rand() % 10) + 1.0f;
		// printf("%f ", t->data[i]);
	}	

	return t;
}

void tensor_get(Tensor *t) {
	if (!t) return;
	int size = 1;
	for (int i = 0; i < t->ndim; i++) {
		size *= t->shape[i];
	}
	//printf("size: %d\n", size);
	for (int i = 0; i < size; i++) {
		printf("%0.2f ", t->data[i]);
	}		
}

int main() {
	int shape[2] = {2, 3};
	int ndim = 2;
	Tensor *t = tensor_create(ndim, shape);
	Tensor *q = tensor_create(ndim, shape);

	Tensor **arr = malloc(2 * sizeof(Tensor));

	return 0;
}
