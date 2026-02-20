#include <stdio.h>
#include <stdlib.h>

int main() {
	int n = 10;
	int *arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		arr[i] = i + 1;
	}

	for (int i = 0; i < n; i++) {
		print(arr[i]);
	}
	return 0;
}
