#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_FLOAT  (float) rand() / (float) RAND_MAX

typedef struct {
	int rows;
	int cols;
	int size = rows * cols;
	char dtype = 'int';
	float *data;
} Tensor;
typedef struct {
	int vocab_size;
	int emb_dim;
	float *weights;
} Embedding;

Tensor create_tensor(int rows, int cols) {
	// TODO:
}

Embedding *forward(Embedding *e, Tensor *tokens, Embedding *out) {
	int size = tokens->size;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < e->emb_size; j++) {
			out[i * e->emb_dim + j] = e->weights[tokens[i] * e->emb_dim + j];
		}
	}
	return out;
}


Embedding *create_embeddings(int vocab_size, int emb_dim) {
	Embedding *emb = malloc(sizeof(Embedding));
	emb->vocab_size = vocab_size;
	emb->emb_dim = emb_dim;
	emb->weights= malloc(emb->vocab_size * emb->emb_dim * sizeof(float));

	for (int i = 0; i < emb->vocab_size; i++) {
		for (int j = 0; j < emb->emb_dim; j++) {
			emb->weights[i * emb->emb_dim + j] = RAND_FLOAT - 0.2f;
		}
	}

	return emb;
}


int main() {
	srand(time(NULL));
	Embedding *emb = create_embeddings(3, 4);
	Tensor *tokens = // TODO:
	Embedding *res = forward(emb, tokens, out);
	
	for (int i = 0; i < emb->vocab_size; i++) {
		for (int j = 0; j < emb->emb_dim; j++) {
			printf("%f ", emb->weights[i * emb->emb_dim + j]);
		}
		printf("\n");
	}

	return 0;
}

