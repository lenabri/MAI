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

// sum ((i + 1) * sum(elements in ith str))

int sum(vector *idx, vector *v, int n, int m) {
	int result = 0;
	int curStrIdx = 0;
	int curSum = 0;
	for (int i = 0; i < idx->sz; ++i) {
		int strIdx = idx->data[i] / m;
		int columnIdx = idx->data[i] % m;
		if (strIdx == curStrIdx) {
			curSum += v->data[i];
		} else {
			result += (curStrIdx + 1) * curSum;
			curStrIdx = strIdx;
			curSum = v->data[i];
		}
	}
	result += (curStrIdx + 1) * curSum;
	return result;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector idx;
	vectorInit(&idx);
	vector v;
	vectorInit(&v);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int value;
			scanf("%d", &value);
			if (value == 0) continue;
			push(&idx, i * m + j);
			push(&v, value);
		}
	}
	printf("%d\n", sum(&idx, &v, n, m));
}
