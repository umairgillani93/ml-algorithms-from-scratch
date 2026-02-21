#include <stdio.h>
#include <stdlib.h>

#define RAND_FLOAT (float) rand() / (float) RAND_MAX
#define VOCAB_SIZE 10
#define EMB_DIM 32

typedef struct {
	int size;
	float *data;
} Vector;

typedef struct {
	char *dtype; 
	int *data;
} Tensor;

typedef struct {
	int vocab_size;
	int emb_dim;
	float *weights;
} Embedding;

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

void display_emb(Embedding *e) {
	for (int i = 0; i < e->vocab_size; i++) {
		for (int j = 0; j < e->emb_dim; j++) {
			printf("%f ", e->weights[i * e->emb_dim + j]);
		}
		printf("\n");
	}
}


Vector *ffn(Embedding *e) {
	// For each token in each sequence in each bach we need to do the same stuff
	// i.e to calculate the yn = w1*x1 + w1*x1 + ...  + wn*xn + b
	//
	Vector *out = malloc(sizeof(Vector));
	out->size= e->vocab_size;
	out->data = malloc(e->vocab_size * sizeof(float));
	
	/*
	 * Res = [
	 *       [x(1)1, x(1)2, x(1)3... x(1)n]
	 *       [x(2)1, x(2)2, x(2)3... x(2)n]
	 *       [x(3)1, x(3)2, x(3)3... x(3)n]
	 *       ] ->
	 *
	 *       y_net = [[y1],[y2], [y3]] dimension = VOCAB_SIZE * 1
	 */

	float *weights = malloc(e->emb_dim * sizeof(float));
	for (int i = 0; i < e->emb_dim; i++) {
		weights[i] = RAND_FLOAT;
	}

	for (int i = 0; i < e->vocab_size; i++) {
		float y = 0.0f;
		for (int j = 0; j < e->emb_dim; j++) {
			y += weights[j] * e->weights[i * e->emb_dim + j];	
		}
		out->data[i] = y;
	}
	return out;
}

int main() {
	Embedding *e = create_embeddings(VOCAB_SIZE, EMB_DIM);
	Vector *res = ffn(e);
	for (int i = 0; i < res->size; i++) {
		printf("%f\n", res->data[i]);
	}
	return 0;

}
