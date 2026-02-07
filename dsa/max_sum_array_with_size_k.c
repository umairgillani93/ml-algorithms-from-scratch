#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int main() {
	int arr[] = {1, 4, 2, 10, 23, 3, 1, 0, 20};
	// maximum sum with 'k' elements
	int k = 4;

	int i = 0;
	int j = 1;
	int SIZE = 9;
	int sum = 0;
	int max_sum = 0;

	while (i < j && j < SIZE) {
		sum += (arr[i] + arr[j]);
		j++;
		if ((j - i) == k - 1) {
				i++;
				j = i + 1;	
		}
		printf("iteration: %d, sum: %d, max_sum: %d, i: %d, j: %d\n", i, sum, max_sum, i, j);
		max_sum = MAX(sum, max_sum);
	}
	printf("%d\n", max_sum);
	return 0;
}
