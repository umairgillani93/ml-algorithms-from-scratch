#include <stdio.h>
#include <stdlib.h>
#include "tensor.h"
#include "attention2.h"
#include "layer_norm.h"
#include "feed_forward_nn.h"

#define SEQ_LEN 10
#define EMB_DIM 32

Tensor *forward(Tensor *x) {
	int shape1[2] = {32, 128};
	Tensor *w1 = tensor_create_weights(2, shape1);

	Tensor *h1 = tensor_matmul(x, w1);
	
	int shape2[2] = {128, 32};
	Tensor *w2 = tensor_create_weights(2, shape2);
	Tensor *out = tensor_matmul(h1, w2);

	return out;
}	

int main() {
	int ndim = 2;
	int *shape_tokens = malloc(ndim * sizeof(int));
	if (!shape_tokens) {
		fprintf(stderr, "Something wrong with memory allocation\n");
		return 0;
	}
	shape_tokens[0] = SEQ_LEN;
	shape_tokens[1] = EMB_DIM;

	Tensor *tokens = tensor_create(ndim, shape_tokens);

	/* 
	 * we have some tensor of shape (SEQ_LEN, EMB_DIM)
	 * we want to perform some FFNN overit
	 * and what FFN does is it takes the values of tensor "FLATTEN"
	 * and assign some "WEIGHTS" to the flatten tensor
	 * and does 'Y = WX + B' for each "PERCEPTRON"
	 *
	 */


	if (!tokens) {
		fprintf(stderr, "Something wrong with memory allocation\n");
		return 0;
	}

	Tensor *res = forward(tokens);
	tensor_get(res);
	
	//int *shape_weights = malloc(ndim * sizeof(int));
	//if (!shape_weights) {
	//	fprintf(stderr, "Something wrong with memory allocation\n");
	//	return 0;
	//}

	//shape_weights[0] = EMB_DIM;
	//shape_weights[1] = EMB_DIM;

	//int num_heads = 8;

	//printf("\n");
	//Tensor *mha = multihead_attention(tokens, shape_weights, num_heads);
	//Tensor *t = layer_norm(mha);
	////Tensor *f = forward(t);
	//tensor_get(t);
	return 0;
}

