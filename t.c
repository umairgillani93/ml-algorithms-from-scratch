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

Tensor *tensor_softmax(Tensor *t) {
	Tensor *r = malloc(sizeof(Tensor));
	if (!r) {return NULL;}
	r->shape = t->shape;
	r->stride = t->stride;
	r->ndim = t->ndim;
	r->data = malloc(r->shape[0] * r->shape[1] * sizeof(float));

	int rows = t->shape[0];
	int cols = t->shape[1];

	for (int i = 0; i < rows; i++) {
		float max = -INFINITY;
		for (int j = 0; j < cols; j++) {
			if (t->data[i * cols + j] > max) {
				max = t->data[i * cols + j];
			}
		}

		float sum = 0.0f;
		for (int j = 0; j < cols; j++) {
			sum += expf(t->data[i * cols + j] - max);
		}

		// now find division
		for (int k = 0; k < cols; k++) {
			r->data[i * cols + k] = expf(t->data[i * cols + k] - max) / sum;
		}
	}
	return r;
}

int main() {
	int shape[2] = {2, 4};
	int ndim = 2;
	Tensor *t = tensor_create(ndim, shape);
	Tensor *s = softmax(t);

	for (int i = 0; i < s->shape[0]; i++) {
		for (int j = 0; j < s->shape[1]; j++) {
			printf("%f ", s->data[i * s->shape[1] + j]);
		}
	}

	return 0;

}

