#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main() {
	int arr[] = {0, 0, 0, 10, 23, -10, 1, 0, 0};
	int SIZE = sizeof(arr) / sizeof(arr[0]);
	
	// maximum sum with 'k' elements
	int k = 4;

	int i = 0;
	int j = i + 1;
	int best = arr[i];
	int curr = arr[i];

	while (j < SIZE) {
		while (j - i < k - 1) {
			curr += arr[j];
			j++;
		}
		best = MAX(curr, best);
		i++;
		curr = arr[i];
		j = i + 1;
		printf("i: %d, j: %d, curr: %d, best: %d\n", i, j, curr, best);
	}
	printf("%d\n", best);
	return 0;
}
