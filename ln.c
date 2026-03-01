#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tensor.h"
#include "attention2.h"
#include "layer_norm.h"

#define EPS 1e-5


float mean(float *arr, int size) {
	
	float sum = 0.0f;
	for (int i = 0; i < size; i++) {
		sum += arr[i];
	}
	return sum / (float) size;
}

//float variance(int x, int size, float mean) {
//	float var = 0.0f;
//	for (int i = 0; i < size; i++) {
//		var = (x - mean) * (x - mean);	
//	}	
//	return var;
//}	

Tensor *layer_norm(Tensor *t) {
	int rows = t->shape[0];
	int cols = t->shape[1];

	for (int i = 0; i < rows; i++) {
		float *row = t->data + (i * cols);
		
		// row mean
		float row_mean = mean(row, cols);

		// row variance
		float var_sum = 0.0f;
		for (int k = 0; k < cols; k++) {
			float diff = row[k] - row_mean;
			var_sum += (diff * diff);
		}

		float var_mean = var_sum / (float) cols;

		for (int c = 0; c < cols; c++) {
			row[c] = (row[c] - row_mean) / sqrtf(var_mean + EPS);
		}
	}

	return t;
}

int main() {
	int ndim = 2;
	int *shape = malloc(ndim * sizeof(int));
	shape[0] = 4;
	shape[1] = 4;
	Tensor *matrix = tensor_create(ndim, shape);
	Tensor *t = layer_norm(matrix);
	tensor_get(t);
	return 0;
}

