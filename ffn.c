#include <stdio.h>
#include <stdlib.h>
#include "tensor.h"
#include "attention2.h"
#include "layer_norm.h"
#include "feed_forward_nn.h"

#define SEQ_LEN 10
#define EMB_DIM 32

Tensor *forward(Tensor *t) {
	int ndim = 2;

	int *shape_weights = malloc(ndim * sizeof(int));

	shape_weights[0] = EMB_DIM;
	shape_weights[1] = EMB_DIM;

	Tensor *w = tensor_create_weights(ndim, shape_weights);

	Tensor *res = tensor_matmul(t, w);
	tensor_get(res);

	return res;
}	

int main() {
	int ndim = 2;
	int *shape = malloc(ndim * sizeof(int));
	shape[0] = SEQ_LEN;
	shape[1] = EMB_DIM;
	
	Tensor *t = tensor_create(ndim, shape);
	forward(t);

	/* 
	 * we have some tensor of shape (SEQ_LEN, EMB_DIM)
	 * we want to perform some FFNN overit
	 * and what FFN does is it takes the values of tensor "FLATTEN"
	 * and assign some "WEIGHTS" to the flatten tensor
	 * and does 'Y = WX + B' for each "PERCEPTRON"
	 *
	 */


	return 0;
}
