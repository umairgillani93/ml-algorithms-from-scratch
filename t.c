#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RAND_FLOAT (float) rand() / (float) RAND_MAX

struct Matrix {
    int rows;
    int cols;
    int size;
    int *data;
};

void display(struct Matrix *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%d ", m->data[i * m->cols + j]);
        }
				printf("\n");
    }
}

int main() {
	struct Matrix *first = malloc(sizeof(struct Matrix));
	first->rows = 4;
	first->cols = 4;
	first->size = first->rows * first->cols;
	first->data = malloc(first->size * sizeof(int));

	for (int i = 0; i < first->rows; i++) {
		for (int j = 0; j < first->cols; j++) {
			first->data[i * first->cols + j] = i + j;
		}
	}

	struct Matrix *second = malloc(sizeof(struct Matrix));
	second->rows = 4;
	second->cols = 4;
	second->size = second->rows * second->cols;
	second->data = malloc(second->size * sizeof(int));

	for (int i = 0; i < second->rows; i++) {
		for (int j = 0; j < second->cols; j++) {
			second->data[i * second->cols + j] = i + j;
		}
	}

	// resultant of first and second

	struct Matrix *res= malloc(sizeof(struct Matrix));
	res->rows = first->rows;
	res->cols = first->cols + second->cols;
	res->size = first->rows * res->cols;
	res->data = malloc(res->size * sizeof(int));


	for (int i = 0; i < first->rows; i++) {
		for (int j = 0; j < first->cols; j++) {
			res->data[i * res->cols + j] = first->data[i * first->cols + j];
		}
	}


	for (int i = 0; i < second->rows; i++) {
		int curr_cols  = first->cols;
		for (int j = 0; j < second->cols; j++) {
			res->data[i * res->cols + (curr_cols + j)] = second->data[i * second->cols + j];
		}
	}


	//display(res);
	return 0;

}
