#ifndef ATTENTION_H
#define ATTENTION_H
#include "tensor.h"

typedef struct {
	Tensor wq;
	Tensor wk;
	Tensor wv;
	Tensor wo;

	Tensor *Q;
	Tensor *K;
	Tensor *V;
	Tensor *out;

	int num_heads;
} MHA;

Tensor *scaled_dot_product_attention(MHA *h, int num_heads);
Tensor *multihead_attention(Tensor *tokens, int *shape_weights, int num_heads);

#endif
