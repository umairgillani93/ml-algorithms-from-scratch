#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RAND_FLOAT (float) rand() / (float) RAND_MAX

struct Matrix {
    int rows;
    int cols;
    int size;
    float *data;
};


struct Matrix *concat(struct Matrix **arr, int SIZE) {
    int total_rows = 0;
    for (int i = 0; i < SIZE; i++) {
        total_rows += arr[i]->rows;
    }

    struct Matrix *res = malloc(sizeof(struct Matrix));
    struct Matrix *first = arr[0];
    int curr_row = first->rows;

    res->rows = total_rows;
    res->cols = first->cols;
    res->size = res->rows * first->cols;
    res->data = malloc(res->size * sizeof(float));

    for (int i = 0; i < first->rows; i++) {
        for (int j = 0; j < first->cols; j++) {
            res->data[i * res->cols + j] = first->data[i * first->cols + j];
        }
    }

    for (int k = 1; k < SIZE; k++) {
        struct Matrix *b = arr[k];
        for (int i = 0; i < b->rows; i++) {
            for (int j = 0; j < b->cols; j++) {
                res->data[(curr_row + i) * res->cols + j] = b->data[i * b->cols + j];
            }
        }
        curr_row += b->rows; 
    }

    return res;
}

int main() {
    srand(time(NULL));
    float e = 2.718;

    int rows = 2;
    int cols = 2;

    struct Matrix *Q= malloc(sizeof(struct Matrix));
    struct Matrix *K= malloc(sizeof(struct Matrix));

    Q->rows = rows;
    Q->cols = cols;
    Q->data = malloc(rows * cols * sizeof(float));

    K->rows = rows;
    K->cols = cols;
    K->data = malloc(rows * cols * sizeof(float));

    for (int i = 0; i < Q->rows; i++) {
        for (int j = 0; j < Q->cols; j++) {
            Q->data[i * Q->cols + j] = RAND_FLOAT;
        }
    }

    for (int i = 0; i < K->rows; i++) {
        for (int j = 0; j < K->cols; j++) {
            K->data[i * K->cols + j] = RAND_FLOAT;
        }
    }

    struct Matrix *arr[2];
    arr[0] = K;
    arr[1] = Q;

    struct Matrix *multi = concat(arr, 2);

    // Corrected print loop
    for (int i = 0; i < multi->rows; i++) {
        for (int j = 0; j < multi->cols; j++) {
					printf("%f ", multi->data[i * multi->cols + j]); 
        }
        printf("\n");
    }

    return 0;
}
