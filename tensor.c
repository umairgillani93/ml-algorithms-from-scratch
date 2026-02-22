#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tensor.h"

#define RAND_FLOAT  (float) rand() / (float) RAND_MAX
#define EMB_DIM 32 
#define SEQ_LEN 10
#define BATCH_SIZE 2
#define EPS 1e-5

Tensor *tensor_create(int ndim, int *shape) {
	Tensor *t = malloc(sizeof(Tensor));
	if (!t) {
		printf("something's wrong with memory allocation\n-> aborting..");
		return NULL;
	}
	t->shape = malloc(ndim * sizeof(int));
	t->stride = malloc(ndim * sizeof(int));
	int size = 1;
	for (int i = 0; i < ndim; i++) {
		size *= shape[i];
	}
	t->data = malloc(size * sizeof(float));


	// define the shape of Tensor
	for (int i = 0; i < ndim; i++) {
		t->shape[i] = shape[i];
	}
	//ndim - 1 > is always 1, fastest changing dimension
	// for next ones wer reveser loop and assign
	// stride[i] = t->stride[i + 1] * t->shape[i + 1]
	t->stride[ndim - 1] = 1;
	for (int i = ndim - 2; i >= 0; i--) {
		t->stride[i] = t->stride[i + 1] * t->shape[i + 1];
	}
	// define the data now
	for (int i = 0; i < size; i++) {
		t->data[i] = (rand() % 10) + 1.0f;
	}	

	return t;
}

void tensor_free(Tensor *t) {
	if (!t) return;
	free(t->data);
	free(t->stride);
	free(t->shape);
	free(t);
	printf("Freed successfully!\n");
}

void tensor_get(Tensor *t, int size) {
	for (int i = 0; i < size; i++) {
		printf("%0.2f ", t->data[i]);
	}		
}

int main() {
	srand(time(NULL));
	int ndim = 3;
	int *shape = malloc(ndim * sizeof(int));
	int size = BATCH_SIZE * SEQ_LEN * EMB_DIM;

	shape[0] = BATCH_SIZE;
	shape[1] = SEQ_LEN;
	shape[2] = EMB_DIM;

	Tensor *t = tensor_create(ndim, shape);
	tensor_get(t, size);
	tensor_free(t);

	return 0;
}
