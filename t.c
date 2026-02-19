#include <stdio.h> #include <stdlib.h>
#include <math.h>
#include <time.h>

#define RAND_FLOAT (float) rand() / (float) RAND_MAX

typedef struct {
	int id;
	char *word;
} Hash;

int main() {

	srand(time(NULL));
	for (int i = 0; i < 9; i++) {
		int x = (rand() % 9) + 1;
		printf("%d\n", x);
	}
	return 0;
}
