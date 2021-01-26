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

int sum(vector *strIdx, vector *v) {
	int result = 0;
	for (int i = 0; i < strIdx->sz; ++i) {
		if (strIdx->data[i] == -1) {
			continue;
		}
		int curSum = 0;
		int curIdx = strIdx->data[i];
		while (curIdx != -1) {
			curSum += v->data[curIdx + 1];
			printf("%d ", v->data[curIdx + 1]);
			curIdx = v->data[curIdx + 2];
		}
		result += (i + 1) * curSum;
	}
	printf("\n");
	return result;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector strIdx;
	vectorInit(&strIdx);
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
				push(&strIdx, v.sz);
			} else {
				push(&v, v.sz + 1);
			}
			push(&v, j);
			push(&v, value);
		}
		if (flag == 0) {
			push(&v, -1);
		} else {
			push(&strIdx, -1);
		}
	}
	printf("%d\n", sum(&strIdx, &v));
}
