#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define RAND_FLOAT  (float) rand() / (float) RAND_MAX

// Matrix structure
struct Matrix {
	int rows;
	int cols;
	int size;
	float *data;
};

struct Tensor {
	int rows;
	int cols;
	int size;
	float *data;
	int dim; // dimention / rank of a Tensor
	char *dtype;
	char *device;
};

//struct Matrix *transpose(struct Matrix *matrix) {
//	struct Matrix *res = malloc(sizeof(struct Matrix));
//	res->rows = matrix->cols;
//	res->cols = matrix->rows;
//	res->size = res->rows * res->cols;
//	res->data = malloc(res->size * sizeof(int));
//	for (int i = 0; i < matrix->rows; i++) {
//		for (int j = 0; j < matrix->cols; j++) {
//			res->data[j * res->rows + i] = matrix->data[i * matrix->cols + j];
//		}
//	}
//	return res;
//}


struct Matrix *matmul(struct Matrix *matrix1, struct Matrix *matrix2) {
	// Resultant Matrix
	struct Matrix *result = malloc(sizeof(struct Matrix));
	result -> rows = matrix1 -> rows;
	result -> cols = matrix2 -> cols;
	result -> size = matrix1 -> rows * matrix2 -> cols;
	result -> data = malloc(result -> size * sizeof(float));

	// Multiply the matrices
	for (int i = 0; i < matrix1->rows; i++) {
		for (int j = 0; j < matrix2->cols; j++) {
			float sum = 0.0f;
			for (int k = 0; k < matrix1->cols; k++) {
				// Remember 'k' is shared dimention for multplication of matrix1 and matrix2
				sum += matrix1->data[i * matrix1->cols + k] * matrix2->data[k * matrix2->cols + j];
			}
			result -> data[i * result-> cols + j] = (float) sum;
		}
	}
	return result;
}

void softmax(struct Matrix *m) {
	for (int i = 0; i < m->rows; i++) {
		float res = 0.0f;
		for (int j = 0; j < m->cols; j++) {
			res += m->data[i * m->cols +j];
		}
		for (int k = 0; k < m->cols; k++) {
			m->data[i * m->cols +k] = m->data[i * m->cols +k] / res;
		}
	}
}

void dk_square_root(struct Matrix *m, float dk) {

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->data[i * m->cols + j] = m->data[i * m->cols + j] / dk;
		}
	}
}

void shape(struct Matrix *m) {
	printf("(%d, %d)\n",  m->rows,  m->cols);
}

struct Matrix *multi_head_attention(struct Matrix **arr, int SIZE) {
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

struct Matrix *self_attention(struct Matrix *Q, struct Matrix *K, struct Matrix *V, 
	 														float dk, int num_heads) {

	struct Matrix *qk = matmul(Q, K);
	dk_square_root(qk, dk);
	softmax(qk);
	struct Matrix *result = matmul(V, qk);
	return result;
		
}


int main() {
	srand(time(NULL));
	float e = 2.718;

	int rows = 2;
	int cols = 2;
	int size = rows * cols;

	struct Matrix *Q= malloc(sizeof(struct Matrix));
	struct Matrix *K= malloc(sizeof(struct Matrix));

	Q->rows = rows;
	Q->cols = cols;
	Q->size = size;
	Q->data = malloc(Q->size * sizeof(float));

	K->rows = rows;
	K->cols = cols;
	K->size = size;
	K->data = malloc(K->size * sizeof(float));

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

	int num_heads = 8;
	float d_model = 768.0f;
	float dk = d_model / (float) num_heads;

	// declare the value matrix
	struct Matrix *V = malloc(sizeof(struct Matrix));
	V->rows = rows;
	V->cols = cols;
	V->size = size;
	V->data = malloc(V->size * sizeof(float));


	// Initialize matrix V
	for (int i = 0; i < V->rows; i++) {
		for (int j = 0; j < V->cols; j++) {
			V->data[i * V->cols + j] = RAND_FLOAT;
		}
	}


	struct Matrix *result = self_attention(Q, K, V, dk, num_heads);

	for (int i = 0; i < result->rows; i++) {
		for (int j = 0; j < result->cols; j++) {
			printf("%f ", result->data[i * result->cols + j]);
		}
		printf("\n");
	}
	
	return 0;
}

