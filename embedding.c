#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_FLOAT  (float) rand() / (float) RAND_MAX

typedef struct {
	int vocab_size;
	int emb_dim;
	float *weights;
} Embedding;

int main() {
	srand(time(NULL));
	Embedding *emb = malloc(sizeof(Embedding));
	emb->vocab_size = 3;
	emb->emb_dim = 5;
	emb->weights= malloc(emb->vocab_size * emb->emb_dim * sizeof(float));

	for (int i = 0; i < emb->vocab_size; i++) {
		for (int j = 0; j < emb->emb_dim; j++) {
			emb->weights[i * emb->emb_dim + j] = RAND_FLOAT - 0.2f;
		}
	}

	for (int i = 0; i < emb->vocab_size; i++) {
		for (int j = 0; j < emb->emb_dim; j++) {
			printf("%f ", emb->weights[i * emb->emb_dim + j]);
		}
		printf("\n");
	}
	return 0;
}

