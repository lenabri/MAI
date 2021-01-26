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

int sum(vector *strIdx, vector *columnIdx, vector *v) {
	int result = 0;
	int nxt = 0;
	for (int i = 0; i < strIdx->sz; ++i) {
		if (strIdx->data[i] == -1) {
			continue;
		}
		while (nxt < strIdx->sz && (nxt <= i || strIdx->data[nxt] == -1)) {
			++nxt;
		}
		int endIdx;
		if (nxt == strIdx->sz) {
			endIdx = v->sz;
		} else {
			endIdx = strIdx->data[nxt];
		}
		int curSum = 0;
		int curIdx = strIdx->data[i];
		while (curIdx != endIdx) {
			curSum += v->data[curIdx];
			++curIdx;
		}
		result += (i + 1) * curSum;
	}
	return result;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector strIdx;
	vectorInit(&strIdx);
	vector columnIdx;
	vectorInit(&columnIdx);
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
			}
			push(&columnIdx, j);
			push(&v, value);
		}
		if (flag == 1) {
			push(&strIdx, -1);
		}
	}
	printf("%d\n", sum(&strIdx, &columnIdx, &v));
}
