#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tensor.h"
#include "attention2.h"

#define RAND_FLOAT  (float) rand() / (float) RAND_MAX
#define EMB_DIM 32 // out model dimension, i.e Embedding size for each token
#define SEQ_LEN 10 // assume these are 10 tokens converted into token IDs
#define BATCH_SIZE 2
#define EPS 1e-5

Tensor *multihead_attention(Tensor *tokens, MHA *h) {
	// Projections:
	h->Q = tensor_matmul(tokens, &h->wq);
	h->K = tensor_matmul(tokens, &h->wk);
	h->V = tensor_matmul(tokens, &h->wv);
	
}	

Tensor *scaled_dot_product_attention(MHA *h, int dk) {
	Tensor *kt = tensor_transpose(h->K);
	Tensor *qkt = tensor_matmul(h->Q, kt);
	for (int i = 0; i < qkt->shape[0]; i++) {
		for (int j = 0; j < qkt->shape[1]; j++) {
			qkt->data[i * qkt->shape[1] + j] = qkt->data[i * qkt->shape[1] +j] / sqrtf(dk);;
		}
	}
	Tensor *qkt_soft = tensor_softmax(qkt); // RAND_FLOAT is random we'll calculate this later
	Tensor *ret = tensor_matmul(qkt_soft, h->V);
	return ret;
}

int main() {
	//int seed = 32;
	//srand(seed);
	int ndim = 2;

	int *shape_tokens = malloc(ndim * sizeof(int));
	int *shape_weights = malloc(ndim * sizeof(int));

	// define shape_tokens
	shape_tokens[0] = SEQ_LEN;
	shape_tokens[1] = EMB_DIM; // this is for token embeddings
	
	// weights shape
	//shape_weights[0] = EMB_DIM;
	//shape_weights[1] = EMB_DIM;
	

	Tensor *tokens = tensor_create(ndim, shape_tokens);
	int num_heads = 8;
	Tensor *mha = multihead_attention(tokens, shape_weights, num_heads);
	tensor_get(mha);
	tensor_shape(mha);
	return 0;


}
