#include <stdio.h>

int main() {
	char A[] = "0123456";
	int SIZE = sizeof(A) / sizeof(A[0]);
	for (int i = 0; i < SIZE; i++) {
		printf("%d\n", A[i] - '0');
	}
	return 0;
}
