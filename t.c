#include <stdio.h>
#include <stdlib.h>

struct Params {
	float (*data)[2];
};

int main() {
	struct Params d;
	int size = 10;
	d.data = malloc(size * sizeof(*(d.data)));
	for (int i = 0; i < size; i++) {
		d.data[i][0] = i;
		d.data[i][1] = i * 2;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%f\n", d.data[i][j]);
		}
	}
	return 0;
	
}
