#include <stdio.h>

#define MAX(a, b) ((a > b) ? (a) : (b))

int main() {
	int arr[] = {-2,1,-3,4,-1,2,1,-5,4};
  // int curr_sum = arr[0];
	
	int best_sum = arr[0];
	int overall_max= arr[0];

	int SIZE = sizeof(arr) / sizeof(arr[0]);

	for (int i = 1; i < SIZE; i++) {
		if (best_sum + arr[i] > arr[i]) {
			best_sum += arr[i];	
		}
		else {
			best_sum = arr[i];
		}
		overall_max = MAX(overall_max, best_sum);
		printf("iter: %d, arr[i]: %d, best_sum: %d\n", i, arr[i], overall_max);
	}

	printf("%d\n", overall_max);
	return 0;
}
