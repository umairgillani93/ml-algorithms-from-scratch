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

Tensor *create_3d_tensor() {
	Tensor *t = malloc(sizeof(Tensor));
	if (!t) {
		printf("Something's wrong with Memory allocation\n-> Aborting..");
		return NULL;
	}
	t->shape = malloc(3 * sizeof(int));
	t->shape[0] = BATCH_SIZE;
	t->shape[1] = SEQ_LEN;
	t->shape[2] = EMB_DIM;

	// We'll define stride later
	t->stride= malloc(3 * sizeof(int));
	t->stride[0] = SEQ_LEN * EMB_DIM; // for next batch in memory we need SEQ_LEN * EMB_DIM steps to have next batch
	t->stride[1] = EMB_DIM; // To have next sequence in memory we need SEQ_LEN bytes shifted
	t->stride[2] = 1; // To have next float in EMB_DIM axis we need single float byte shifted
	
	t->ndim = 3;
	t->data = malloc(BATCH_SIZE * SEQ_LEN * EMB_DIM * sizeof(float));

	for (int b = 0; b < BATCH_SIZE; b++) {
		for (int s = 0; s < SEQ_LEN; s++) {
			for (int e = 0; e < EMB_DIM; e++) {
				int idx = b * t->stride[0] + s * t->stride[1] + e * t->stride[2];
				t->data[idx] = (float) (rand() % SEQ_LEN) + 1.0f;
			}
		}
	}

	return t;
}

void display_3d_tensor(Tensor *t) {
	for (int b = 0; b < BATCH_SIZE; b++) {
		for (int s = 0; s < SEQ_LEN; s++) {
			for (int e = 0; e < EMB_DIM; e++) {
				int idx = b * t->stride[0] + s * t->stride[1] + e * t->stride[2];
				printf("%0.2f ", t->data[idx]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

int main() {
	Tensor *t = create_3d_tensor();
	display_3d_tensor(t);
	return 0;
}
