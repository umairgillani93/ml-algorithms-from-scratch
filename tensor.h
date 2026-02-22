#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *shape;
	int *stride;
	int ndim;
	float *data;
	int size;
} Tensor;

