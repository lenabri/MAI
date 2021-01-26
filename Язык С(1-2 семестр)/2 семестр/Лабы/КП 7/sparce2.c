#include <stdio.h>

typedef struct {
	int data[100];
	int sz;
} vector;

void vectorInit(vector *v) {
	v->sz = 0;
}

void push(vector *v, int value) {
	v->data[v->sz++] = value;
}

int sum(vector *v) {
	int result = 0;
	for (int i = 1; i < v->sz; ++i) {
		if (v->data[i] != -1) {
			++i;
			result += v->data[i];
		} else {
			++i;
		}
	}
	return result;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector v;
	vectorInit(&v);
	for (int i = 0; i < n; ++i) {
		int flag = 1;
		for (int j = 0; j < m; ++j) {
			int value;
			scanf("%d", &value);
			if (value == 0) continue;
			if (flag) {
				flag = 0;
				push(&v, i);
			}
			push(&v, j);
			push(&v, value);
		}
		if (flag == 0) {
			push(&v, -1);
		}
	}
	push(&v, -1);
	printf("%d\n", sum(&v));
}
