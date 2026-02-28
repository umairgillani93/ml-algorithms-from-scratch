#ifndef ATTENTION_H
#define ATTENTION_H

#include "tensor.h"

Tensor *scaled_dot_product_attention(Tensor *qw, Tensor *kw, Tensor *vw, int num_heads);
Tensor *multihead_attention(Tensor *tokens, int *shape_weights, int num_heads);

#endif
