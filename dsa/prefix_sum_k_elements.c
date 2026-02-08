#include <stdio.h>

/*
 * A = [1,2,3,4,5]
 * pref_A = [1, 3, 6, 10, 15]
 */

#define MAX(a, b) (((a > b) ? (a) : (b)))


int main() {
	//int n;
	//scanf("%d",&n);
	//int A[n];
	//for (int i = 0; i < n; i++) {
	//	A[i] = i + 1;
	//}
	int n = 8;
	int A[] = {1, -2, 3, -1, 5, -3, 2, 4};
	int pref[n];
	pref[0] = A[0];

	for (int i = 1; i < n; i++) {
		pref[i] = pref[i - 1] + A[i];
	}

	int sum = 0;
	int best = 0;
	int k = 3;
	int i = 1;
	int j = k - 1;

	// pref = [1, 3, 6, 10, 15, 21, 28]
	// i = 2; j = 0 pref[2] - pref[0] = 5
	// i = 3; j = 1; pref[3] - pref[1] = 7
	// i = 4; j = 2 pref[4] - pref[2] =  
	// i = 5; j = 3; pref[5] - pref[3] = 
	
	int size = sizeof(A) / sizeof(A[0]);
	for (int i = 1; i < n - k; i++) {
		int j = i + k - 1;
		sum = pref[j] - pref[i - 1];
		best = MAX(best, sum);

	}


	printf("%d\n", best);
	return 0;
}
