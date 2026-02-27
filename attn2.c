#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tensor.h"
#include "attention2.h"

#define RAND_FLOAT  (float) rand() / (float) RAND_MAX
#define EMB_DIM 32
#define SEQ_LEN 10
#define BATCH_SIZE 2
#define EPS 1e-5

Tensor *multihead_attention(Tensor *tokens, int *shape_weights, int num_heads) {
	int ndim = 2;
	int dk = EMB_DIM / num_heads;
	Tensor **mha = malloc(num_heads * sizeof(Tensor *));

	for (int i = 0; i < num_heads; i++) {

		Tensor *qw = tensor_create_weights(ndim, shape_weights);	
		Tensor *kw = tensor_create_weights(ndim, shape_weights);
		Tensor *vw = tensor_create_weights(ndim, shape_weights);

		Tensor *Q = tensor_matmul(tokens, qw);
		Tensor *K = tensor_matmul(tokens, kw);
		Tensor *V = tensor_matmul(tokens, vw);

		
		Tensor *att_score = scaled_dot_product_attention(Q, K, V, dk);
		mha[i] = att_score;
	}

	 
	int *shape_r = malloc(ndim * sizeof(int));
	shape_r[0] = SEQ_LEN;
	shape_r[1] = EMB_DIM;

	Tensor *res = tensor_create(ndim, shape_r);
	int offset = 0;

	for (int i = 0; i < num_heads; i++) {
		Tensor *head = mha[i]; // This is our single head

		int head_rows = head->shape[0];
		int head_cols = head->shape[1];

		for (int r = 0; r < head_rows; r++) {
			for (int c = 0; c < head_cols; c++) {
				int src_index = r * head_cols + c;
				int dest_index = r * res->shape[1] + (offset + c);
				res->data[dest_index] = head->data[src_index];
			}
		}
		offset += head_cols;
	}

	return res;
}	

Tensor *scaled_dot_product_attention(Tensor *Q, Tensor *K, Tensor *V, int dk) {
	Tensor *kt = tensor_transpose(K);
	Tensor *qkt = tensor_matmul(Q, kt);
	for (int i = 0; i < qkt->shape[0]; i++) {
		for (int j = 0; j < qkt->shape[1]; j++) {
			qkt->data[i * qkt->shape[1] + j] = qkt->data[i * qkt->shape[1] +j] / sqrtf(dk);;
		}
	}
	Tensor *qkt_soft = tensor_softmax(qkt); // RAND_FLOAT is random we'll calculate this later
	Tensor *ret = tensor_matmul(qkt_soft, V);
	return ret;
}

int main() {
	int seed = 32;
	srand(seed);
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


	/* let's say we have a single token word "sky"
	 * this token will have it's own embedding
	 * and this embedding will have it's own projections all of them query, key and value
	 * say "sky" has embedding -> e and has q_proj -> q and has key_proj -> k and has v_proj -> value
	 * so that becomes e * wq = Q, e * wk = K and e * wv = V
	 * then onwords we calculate the attention for each single token
	 *
	 */

	// Attention(Q, K, V) = softmax(q * transpose(k) / sqrt(dk)) * v
	//Tensor *tokens = tensor_create(ndim, shape_tokens);
	//Tensor *qw = tensor_create_weights(ndim, shape_weights);	
	//Tensor *kw = tensor_create_weights(ndim, shape_weights);
	//Tensor *vw = tensor_create_weights(ndim, shape_weights);

	//Tensor *Q = tensor_matmul(tokens, qw);
	//Tensor *K = tensor_matmul(tokens, kw);
	//Tensor *V = tensor_matmul(tokens, vw);

	//int dk = EMB_DIM / 8;
	//Tensor *att_score = scaled_dot_product_attention(Q, K, V, dk);

	//tensor_shape(att_score);

}

