// Linear Regression model through pointers approach
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Hyper-parameters structure
struct Params  {
	float w;
	float b;
	float lr;
};

struct Data {
	int size;
	int iter;
	float (*data)[2];
};

float grad_w(float w, float b, int size, float data[][2]) {
	// 2 / size ((w * x + b) - y) * x;  
	float res = 0.0f;
	for (int i = 0; i < size; i++) {
		float x = data[i][0];
		float y = data[i][1];
		float y_hat = w * x + b;
		res += (y_hat - y) * x;
	}
	return 2.0f * res / size;
}

float grad_b(float w, float b, int size, float data[][2]) {
	// 2 / size ((w * x + b) - y);  
	float res = 0.0f;
	for (int i = 0; i < size; i++) {
		float x = data[i][0];
		float y = data[i][1];
		float y_hat = w * x + b;
		res += (y_hat - y);
	}
	return 2.0f * res / size;
}

float loss(float w, float b, int size, float data[][2]) {
	float res = 0.0f;
	for (int i = 0; i < size; i++) {
		float x = data[i][0];
		float y = data[i][1];
		float y_hat = w * x + b;
		float err = y_hat - y;
		res += err * err;
	}
	return res / (float) size;
}
int main() {
	srand(time(NULL));
	struct Params p;
	struct Data d;
	p.w = (float) rand() / (float) RAND_MAX;
	p.b = (float) rand() / (float) RAND_MAX;
	p.lr = 0.000001;

	printf("w: %f, b: %f, lr: %f\n", p.w, p.b, p.lr);
	d.size = 1000;
	d.iter = 10;
	d.data = malloc(d.size * sizeof(*(d.data)));
	if (d.data == NULL) {return -1;}

	for (int i = 0; i < d.size; i++) {
		d.data[i][0] = i;
		d.data[i][1] = i * 2 + 1;
	}

	for (int i = 0; i < d.iter; i++) {
		float cost = loss(p.w, p.b, d.size, d.data);
		float gw = grad_w(p.w, p.b, d.size, d.data);
		float gb = grad_b(p.w, p.b, d.size, d.data);

		p.w -= p.lr * gw;
		p.b -= p.lr * gb;
		printf("iteration: %d, loss: %.4f, w: %f, b: %f\n", 
			i, loss(p.w, p.b, d.size, d.data), p.w, p.b);
	}

	return 0;

}

