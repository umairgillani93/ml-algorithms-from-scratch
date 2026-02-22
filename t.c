#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int vocab_size;
	int emb_dim;
	int *weights;
} Embedding;

int main() {
	int rows = 2;
	int cols = 3;

	Embedding *m = malloc(sizeof(Embedding));
	m->vocab_size = rows;
	m->emb_dim= cols;
	m->weights = malloc(m->vocab_size * m->emb_dim * sizeof(int));

	for (int i = 0; i < m->vocab_size; i++) {
		for (int j = 0; j < m->emb_dim; j++) {
			m->weights[i * m->emb_dim + j] = i * m->emb_dim + j;
		}
	}

	for (int i = 0; i < m->vocab_size; i++) {
		for (int j = 0; j < m->emb_dim; j++) {
			printf("%d ", m->weights[i * m->emb_dim + j]);
		}
		printf("\n");
	}
	return 0;
}
