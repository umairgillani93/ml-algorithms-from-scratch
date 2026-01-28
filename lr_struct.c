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

float grad_w(struct Params *p, struct Data *d) {
	// 2 / size ((w * x + b) - y) * x;  
	float res = 0.0f;
	for (int i = 0; i < d->size; i++) {
		float x = d->data[i][0];
		float y = d->data[i][1];
		float y_hat = p->w * x + p->b;
		res += (y_hat - y) * x;
	}
	return 2.0f * res / d->size;
}

float grad_b(struct Params *p, struct Data *d) {
	// 2 / size ((w * x + b) - y) * x;  
	float res = 0.0f;
	for (int i = 0; i < d->size; i++) {
		float x = d->data[i][0];
		float y = d->data[i][1];
		float y_hat = p->w * x + p->b;
		res += (y_hat - y);
	}
	return 2.0f * res / d->size;
}


float loss(struct Params *p, struct Data *d) {
	float res = 0.0f;
	for (int i = 0; i < d->size; i++) {
		float x = d->data[i][0];
		float y = d->data[i][1];
		float y_hat = p->w * x + p->b;
		float err = y_hat - y;
		res += err * err;
	}
	return res / (float) d->size;
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
		float cost = loss(&p, &d);
		float gw = grad_w(&p, &d);
		float gb = grad_b(&p, &d);

		p.w -= p.lr * gw;
		p.b -= p.lr * gb;
		printf("iteration: %d, loss: %.4f, w: %f, b: %f\n", 
			i, loss(&p, &d), p.w, p.b);
	}

	return 0;

}

