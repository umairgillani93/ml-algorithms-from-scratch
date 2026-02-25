#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tensor.h"
#include "attention2.h"

#define RAND_FLOAT  (float) rand() / (float) RAND_MAX
#define EMB_DIM 32 
#define SEQ_LEN 10
#define BATCH_SIZE 2
#define EPS 1e-5


int main() {
	int seed = 32;
	srand(seed);
	int ndim = 2;
	//Tensor *tokens = malloc(sizeof(Tensor));
	//Tensor *q_weights = malloc(sizeof(Tensor));
	//Tensor *k_weights = malloc(sizeof(Tensor));
	//Tensor *v_weights = malloc(sizeof(Tensor));

	int *shape_tokens = malloc(ndim * sizeof(int));
	int *shape_weights = malloc(ndim * sizeof(float));

	// define shape_tokens
	shape_tokens[0] = SEQ_LEN;
	shape_tokens[1] = EMB_DIM; // this is for token embeddings
	
	// weights shape
	shape_weights[0] = EMB_DIM;
	shape_weights[1] = EMB_DIM;


	/* let's say we have a single token word "sky"
	 * this token will have it's own embedding
	 * and this embedding will have it's own projections all of them query, key and value
	 * say "sky" has embedding -> e and has q_proj -> q and has key_proj -> k and has v_proj -> value
	 * so that becomes e * wq = Q, e * wk = K and e * wv = V
	 * then onwords we calculate the attention for each single token
	 *
	 */

	// Attention(Q, K, V) = softmax(q * transpose(k) / sqrt(dk)) * v
	Tensor *tokens = tensor_create(ndim, shape_tokens);
	Tensor *qw = tensor_create_weights(ndim, shape_weights);	
	Tensor *kw = tensor_create_weights(ndim, shape_weights);
	Tensor *vw = tensor_create_weights(ndim, shape_weights);

	Tensor *qwt = transpose(qw);
	tensor_shape(tokens);
	tensor_shape(qwt);
	Tensor *q_proj = matmul(tokens, qwt);
	Tensor *s = tensor_softmax(q_proj);
	tensor_get(s);

	return 0;
}

