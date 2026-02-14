#include <stdio.h>


#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main() {
	int arr[] = {2, 7, -9, 18, 12, 4, -11, 0, 4, 6, -2};
	int k = 4; // we have to sum this many numbers and then stride
	
	int i = 0; 
	int j = i + 1;
	int best = 0;

	int SIZE = sizeof(arr) / sizeof(arr[0]);
	while (j < SIZE) {
		int sum = 0;
		sum += arr[i];
		while (j - i < k - 1) {
			sum += arr[j];
			j++;
		}
		best = MAX(best, sum);
		i++;
		j = i + 1;
	}
	printf("%d\n", best);
	return 0;
}
