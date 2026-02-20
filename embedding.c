#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_FLOAT  (float) rand() / (float) RAND_MAX
#define EMB_DIM 32 
#define VOCAB_SIZE 10

typedef struct {
	char *dtype; 
	int *data;
} Tensor;

typedef struct {
	int vocab_size;
	int emb_dim;
	float *weights;
} Embedding;

Tensor *create_tensor() {
	Tensor *t = malloc(sizeof(Tensor));
	if (!t) {
		printf("Something's wrong will Memory allocation\n-> Aborting..");
		return NULL;
	}
	
	t->dtype = "int";
	t->data = malloc(VOCAB_SIZE	* sizeof(int));
	if (!t->data) {
		printf("Something's wrong will Memory allocation\n-> Aborting..");
		return NULL;
	}
	for (int i = 0; i < VOCAB_SIZE; i++) {
		t->data[i] = (rand() % VOCAB_SIZE) + 1;
	}
	for (int i = 0; i < VOCAB_SIZE; i++) {
		printf("%d ", t->data[i]);
	}
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


Embedding *forward(Embedding *e, Tensor *tokens) {
	Embedding *out = malloc(sizeof(Embedding));
	out->vocab_size = 1;
	out->emb_dim = e->emb_dim;
	out->weights= malloc(out->vocab_size * out->emb_dim* sizeof(float));

	for (int i = 0; i < 1; i++) {
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
  display_emb(emb);
	Tensor *tokens = create_tensor();
	Embedding *res = forward(emb, tokens);
	//display_tensor(tokens);

	return 0;
}

