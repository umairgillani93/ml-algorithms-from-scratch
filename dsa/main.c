#include <stdio.h>

int main() {
	int arr[] = {-2,1,-3,4,-1,2,1,-5,4};

	int curr_sum = arr[0];
	int best_sum = arr[0];
	int SIZE = sizeof(arr) / sizeof(arr[0]);

	for (int i = 1; i < SIZE; i++) {
		curr_sum = arr[i];
		if (curr_sum + best_sum > curr_sum) {
			best_sum += curr_sum;
		}
		else {
			best_sum = curr_sum;
		}
		printf("iter: %d,  curr_sum: %d, curr_sum + arr[i - 1]: %d, best_sum: %d\n", i, arr[i], arr[i] + arr[i -1], best_sum);
	}
	return 0;
}
