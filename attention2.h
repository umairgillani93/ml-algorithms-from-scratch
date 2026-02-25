#ifndef ATTENTION_H
#define ATTENTION_H

#include "tensor.h"

Tensor *scaled_dot_product_attention(Tensor *qw, Tensor *kw, Tensor *vw);

#endif
