#include <stdio.h>
#include <stdlib.h>

#define RAND_FLOAT (float) rand() / (float) RAND_MAX

int main() {
	int N = 10;
	int *x = malloc(N * sizeof(int));
	float *w = malloc(N * sizeof(float));

	for (int i = 0; i < 10; i++) {
		x[i] = i;
		w[i] = RAND_FLOAT;
	}
	
	// Single vector dot product multiplication
	float y = 0.0f;
	for (int i = 0; i < N; i++) {
		y += ((float) x[i] * w[i]);
	}
	printf("y: %f\n", y);

	return 0;

}
