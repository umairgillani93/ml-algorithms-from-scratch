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
	printf("Size of tensor: %d\n", size);
	//ndim - 1 > is always 1, fastest changing dimension
	// for next ones wer reveser loop and assign
	// stride[i] = t->stride[i + 1] * t->shape[i + 1]
	t->stride[ndim - 1] = 1;
	for (int i = ndim - 2; i >= 0; i--) {
		t->stride[i] = t->stride[i + 1] * t->shape[i + 1];
	}
	printf("Stride: %d, %d, %d\n", t->stride[0], t->stride[1], t->stride[2]);
	// define the data now
	t->data = malloc(size * sizeof(float));
	for (int i = 0; i < size; i++) {
		t->data[i] = (rand() % 10) + 1.0f;
		// printf("%f ", t->data[i]);
	}	

	return t;
}

Tensor *matmul(Tensor *a, Tensor *b) {
	int rows_a = a->shape[0];
	int cols_a = a->shape[1];

	int rows_b = b->shape[0];
	int cols_b = b->shape[1];

	// resultant tensor having shape (rows_a, cols_b);
	int ndim_r = 2;
	int *shape_r = malloc(2 * sizeof(int));
	shape_r[0] = a->shape[0];
	shape_r[1] = b->shape[1];

	Tensor *r = tensor_create(ndim_r, shape_r);
	printf("Created resultant tensor\n");

	for (int i = 0; i < rows_a; i++) {
		for (int j = 0; j < cols_b; j++) {
			float sum = 0.0f;
			for (int k = 0; k < cols_a; k++) {
				sum += (a->data[i * a->stride[0] + k * a->stride[1]]  * b->data[k * b->stride[0] + j * b->stride[1]]);
			}
			r->data[i * r->stride[0] + j * r->stride[1]] = sum;
		}
	}
	return r;
}

void tensor_free(Tensor *t) {
	if (!t) return;
	free(t->data);
	free(t->stride);
	free(t->shape);
	free(t);
	printf("Freed successfully!\n");
}

void tensor_get(Tensor *t) {
	if (!t) return;
	int size = 1;
	for (int i = 0; i < t->ndim; i++) {
		size *= t->shape[i];
	}
	printf("size: %d\n", size);
	for (int i = 0; i < size; i++) {
		printf("%0.2f ", t->data[i]);
	}		
}

Tensor *transpose(Tensor *a) {
	int ndim = 2;
	int *shape = malloc(ndim * sizeof(int));
	shape[0] = a->shape[1];
	shape[1] = a->shape[0];
	Tensor *t = create_tensor(ndim, shape);

	int size = 1;
	for (int i = 0; i < ndim; i++) {
		size *= shape[i];
	}

	for (int j = 0; j < size; j++) {
		t->data[i] = a->data[i];
	}
	
	return t;
}

int main() {
	int seed = 32;
	srand(seed);

	int ndim_a = 2;
	int ndim_b = 2;
	int *shape_a = malloc(ndim_a * sizeof(int));
	int *shape_b = malloc(ndim_b * sizeof(int));

	shape_a[0] = SEQ_LEN;
	shape_a[1] = EMB_DIM;

	shape_b[0] = EMB_DIM;
	shape_b[1] = SEQ_LEN;

	Tensor *a = tensor_create(ndim_a, shape_a);
	//Tensor *b = tensor_create(ndim_b, shape_b);
	tensor_get(a);
	printf("\n");
	Tensor *t = transpose(a);
	tensor_get(t);
	
	//a->ndim = ndim_a;
	//b->ndim = ndim_b;

	//Tensor *r = matmul(a, b);
	//tensor_get(r);


	return 0;
}
