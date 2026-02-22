#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tensor.h"

#define RAND_FLOAT  (float) rand() / (float) RAND_MAX
#define EMB_DIM 32 
#define SEQ_LEN 10
#define BATCH_SIZE 1
#define EPS 1e-5

typedef struct {
	char *dtype; 
	int *data;
} Tensor;

typedef struct {
	int vocab_size;
	int emb_dim;
	float *weights;
} Embedding;

Tensor *create_3d_tensor() {
	Tensor *t = malloc(sizeof(Tensor));
	if (!t) {
		printf("Something's wrong with Memory allocation\n-> Aborting..");
		return NULL;
	}
	t->shape = malloc(3 * sizeof(int));
	t->shape[0] = BATCH_SIZE;
	t->shape[1] = SEQ_LEN;
	t->shape[2] = EMB_DIM;

	// We'll define stride later
	
	t->ndim = 3;
	t->data = malloc(t->shape[1] * t->shape[2] * sizeof(float));


	return t;
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


void shape(Embedding *e) {
	printf("(%d, %d)\n", e->vocab_size, e->emb_dim);
}

Embedding *layer_norm(Embedding *e) {
	Embedding *out = malloc(sizeof(Embedding));
	out->vocab_size = e->vocab_size;
	out->emb_dim = e->emb_dim;
	out->weights = malloc(e->vocab_size * out->emb_dim * sizeof(float));

	// Calcuate the mean
	for (int i = 0; i < e->vocab_size; i++) {
		float *row = e->weights + (i * e->emb_dim);
		float *out_row = out->weights + (i * e->emb_dim);
		float sum = 0.0f;
		float var_sum = 0.0f;

		for (int j = 0; j < e->emb_dim; j++) {
			sum += row[j];
		}
		float mean = sum / e->emb_dim;

		// Calcuate the variance
		for (int j = 0; j < e->emb_dim; j++) {
			var_sum += ((row[j] - mean) * (row[j] - mean));
		}
		float var = var_sum / e->emb_dim;
		float std = sqrtf(var + EPS);
		for (int j = 0; j < e->emb_dim; j++) {
			out_row[j] = (row[j] - mean) / std;
		}
	 }
	return out;
}

Embedding *forward(Embedding *e, Tensor *tokens) {
	// Forward pass for generatin the token embeddings
	Embedding *out = malloc(sizeof(Embedding));
	out->vocab_size = e->vocab_size;
	out->emb_dim = e->emb_dim;
	out->weights= malloc(out->vocab_size * out->emb_dim* sizeof(float));

	for (int i = 0; i < e->vocab_size; i++) {
		for (int j = 0; j < e->emb_dim; j++) {
			out->weights[i * e->emb_dim + j] = e->weights[tokens->data[i]* e->emb_dim + j];
		}
	}
	return out;
}

void display_emb(Embedding *e) {
	for (int i = 0; i < e->vocab_size; i++) {
		for (int j = 0; j < e->emb_dim; j++) {
			printf("%f ", e->weights[i * e->emb_dim + j]);
		}
		printf("\n");
	}
}

void display_tensor(Tensor *t) {
	for (int i = 0; i < VOCAB_SIZE; i++) {
		printf("%d ", t->data[i]);
	}
}

int main() {
	srand(time(NULL));
	Embedding *emb = create_embeddings(VOCAB_SIZE, EMB_DIM);
  //display_emb(emb);
	Tensor *tokens = create_tensor();
	Embedding *res = forward(emb, tokens);
	Embedding *ln = layer_norm(res);
	display_emb(ln);
	shape(ln);
	

	return 0;
}

