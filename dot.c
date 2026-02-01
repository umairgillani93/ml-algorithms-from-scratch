#include <stdio.h>

int dot(const int *a, int *b, const int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += a[i] *b[i];
	}
	return sum;
}

int main() {
	int A[] = {2,4,6,8};
	int B[] = {1,3,7,9};

	int res = dot(A, B, 4);
	printf("%d\n", res);
	return 0;
	
}

