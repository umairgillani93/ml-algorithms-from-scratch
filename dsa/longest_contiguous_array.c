#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main() {
	char A[] = "aaabbcccddddddddddddddddddddd555555555";
	int size = sizeof(A) / sizeof(A[0]) - 1;

	int max_char = 1; // initially consider first character as max
	int best_char = 1;

	for (int i = 1; i < size; i++) {
		if (A[i] == A[i - 1]) {
			max_char++;
		}
		else {
			best_char = max(best_char, max_char);
			max_char = 1;
		}
		//printf("iteration: %d, max_char: %d, best_char: %d\n", i, max_char, best_char);
	}

	best_char = max(best_char, max_char);
	printf("best_char: %d\n",  best_char);
	return 0;
}
