#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
	int *shape;
	int *stride;
	int ndim;
	float *data;
} Tensor;

int main() {
	int d = 32;
	printf("%f\n", sqrtf(d));
	return 0;
}
