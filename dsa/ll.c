#include <stdio.h>
#include <stdlib.h>

struct Node {
	int x;
	struct Node *next;
};


struct Node *first = NULL;

void create_linked_list(int A[], int size) {
	// allocate memory for a eac Node and then
	// assing them values from the array
	first = (struct Node *)malloc(sizeof(struct Node));
	first->x = A[0];
	first->next = NULL;

	struct Node *last;
	last = first;
	
	for (int i = 0; i < size; i++) {
		struct Node *node = (struct Node *)malloc(sizeof(struct Node));
		node->x = A[i];
		last->next = node;
		last = node;
	}	
}

void display(struct Node *p) {
	while (p) {
		printf("%d\n", p->x);
		p = p->next;
	}
}

int main() {
	/* This is a classical LnikedList implementation from Scratch in C language
	 * So essentially a linked list is a data structure that has the following:
	 * 1. Node
	 * 2. Each Node has some value
	 * 3. Pointer to Next Node
	 */
	int arr[5] = {1,2,3,4,5};
	int size = 5;
	create_linked_list(arr, size);
	display(first);
	return 0;
}
