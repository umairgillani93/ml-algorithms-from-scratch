#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *dtype; 
	int *data;
} Tensor;

int main() {
	int EMB_DIM = 32;
	Tensor *t = malloc(sizeof(Tensor));
	t->dtype = "int";
	t->data = malloc(EMB_DIM * sizeof(int));

	for (int i = 0; i < EMB_DIM; i++) {
		t->data[i] = (rand() % 9) + 1;
	}

	for (int i = 0; i < EMB_DIM; i++) {
		printf("%d\n", t->data[i]);
	}
	return 0;
}

