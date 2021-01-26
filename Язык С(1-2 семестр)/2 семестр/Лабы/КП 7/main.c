#include <stdio.h>
#include <complex.h>

typedef struct vector vector;
typedef struct sz sz;

struct vector {
    double complex data[100];
    int size;
};

struct sz {
    int n;
    int m;
};

void create_vector(vector* v) {
    v->size = 0;
}

void vector_push(vector* v, double complex value) {
    v->data[v->size++] = value;
}

void vector_print(vector* v) {
    for (int i = 0; i < v->size; i++)
        printf("%.2f %.2f   ", creal(v->data[i]), cimag(v->data[i]));
    printf("\n");
}

void read_matrix(vector* matrix, sz* s) {
    int n, m;
    double x,y;
    scanf("%d %d", &n, &m);
    vector_push(matrix, 0);
    for (int i = 1; i <= n; ++i) {
        int flag = 1;
        for (int j = 1; j <= m; ++j) {
            double complex value = 0;
            scanf("%lf %lf", &x, &y);
            value = x + y * I;
            if (value == 0) continue;
            if (flag) {
                flag = 0;
                vector_push(matrix, i);
            }
            vector_push(matrix, j);
            vector_push(matrix, value);
        }
        if (flag == 0) {
            vector_push(matrix, 0);
        }
    }
    vector_push(matrix, 0);
    s->n = n;
    s->m = m;
}

double complex get_value(vector* v, int n, int m) {
    int x = 0;
    for (int i = 0; i < v->size - 1; i++) {
        if (v->data[i] == 0) {
            if (creal(v->data[i + 1]) > n || v->data[i + 1] == 0)
                break;
            if (creal(v->data[i + 1]) < n) {
                continue;
            } else if (v->data[i + 1] == n) {
                x = i + 1;
                break;
            }
        }
    }
    if (x == 0)
        return 0;
    int flag = 1;
    for (int i = x + 1; i < v->size; i++) {
        if (v->data[i + 1] == 0) break;
        if (flag) {
            if (v->data[i] == m)
                return v->data[i + 1];
            flag = 0;
        } else {
            flag = 1;
        }
    }
    return 0;
}

int res(vector* result, vector* matrix1, vector* matrix2, int n1, int n2, int m2) {
    vector_push(result, 0);
    int diag = 1;
    if (n1 != m2) diag = 0;
    for (int i = 1; i <= n1; i++) {
        int flag = 1;
        double complex sum = 0;
        for (int k = 1; k <= m2; k++) {
            for (int j = 1; j <= n2; j++) {
                sum += get_value(matrix1, i, j) * get_value(matrix2, j, k);
            }
            if (diag) {
                if (sum == 0 && i == k) diag = 0;
                if (sum != 0 && i != k) diag = 0;
            }
            if (sum == 0) continue;
            if (flag) {
                flag = 0;
                vector_push(result, i);
            }
            vector_push(result, k);
            vector_push(result, sum);
            sum = 0;
        }
        if (flag == 0) {
            vector_push(result, 0);
        }
    }
    vector_push(result, 0);
    return diag;
}

void print_matrix(vector* v, int n, int m) {
    double complex d = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            d = get_value(v, i, j);
            printf("%.2f %.2fi   ", creal(d), cimag(d));
        }
        printf("\n");
    }
}

int main() {
    sz s1;
    sz s2;
    vector matrix1;
    vector matrix2;
    create_vector(&matrix1);
    create_vector(&matrix2);
    read_matrix(&matrix1, &s1);
    printf("Первая матрица в обычном представлении:\n");
    print_matrix(&matrix1, s1.n, s1.m);
    printf("Первая матрица во внутреннем представлении:\n");
    vector_print(&matrix1);
    printf("\n");

    read_matrix(&matrix2, &s2);
    printf("Вторая матрица в обычном представлении:\n");
    print_matrix(&matrix2, s2.n, s2.m);
    printf("Вторая матрица во внутреннем представлении:\n");

    vector_print(&matrix2);
    if (s1.m != s2.n) {
        printf("Количество столбцов первой матрицы не совпадает с количеством строк второй матрицы.\nИх перемножить нельзя!\n");
        return 1;
    }

    vector result;
    create_vector(&result);
    int diag = res(&result, &matrix1, &matrix2, s1.n, s2.n, s2.m);
    printf("\n\nРезультат:\n");
    printf("Матрица в обычном представлении:\n");
    print_matrix(&result, s1.n, s2.m);
    printf("\nМатрица во внутреннем представлении:\n");
    vector_print(&result);
    if (diag)
        printf("\nМатрица является диагональной!\n");
    else
        printf("\nМатрица не является диагональной!\n");
    
    return 0;
}
