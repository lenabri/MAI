#include <stdio.h>
#include <string.h>

#include "student.h"

int read_bin(STUDENT* student, FILE* input) {
    fread(student->last_name, sizeof(char), STR_LEN, input);
    fread(student->initials, sizeof(char), STR_LEN, input);
    fread(&student->sex, sizeof(char), STR_LEN, input);
    fread(&student->group, sizeof(int), 1, input);
    fread(&student->mark_1, sizeof(int), 1, input);
    fread(&student->mark_2, sizeof(int), 1, input);
    fread(&student->mark_3, sizeof(int), 1, input);
    fread(&student->mark_4, sizeof(int), 1, input);
    fread(&student->mark_5, sizeof(int), 1, input);
    return !feof(input);
}

void print(STUDENT* student) {
    printf("%s %s %s %d %d %d %d %d %d\n", student->last_name, student->initials, student->sex, student->group, student->mark_1, student->mark_2, student->mark_3, student->mark_4, student->mark_5);
}

double average_mark(STUDENT* student) {
    return (student->mark_1 + student->mark_2 + student->mark_3 + student->mark_4 + student->mark_5)/5.;
}

void usage(const char* argv[]) {
    fprintf(stderr, "Использование:\n\tРаспечатать: %s <файл> -f\n\tРаспечатать p лучших студентов: %s <файл> -p <количество>\n", argv[1], argv[1]);
}

int main(int argc, const char * argv[]) {
    if (argc < 3 || argc > 4) {
        usage(argv);
        return 1;
    }
    
    FILE* input = fopen(argv[1], "r");
    STUDENT student;
    
    if (!input) {
        printf("Не получается открыть файл!\n");
        fclose(input);
        return 2;
    }
    
    if (strcmp(argv[2], "-f") == 0) {
        if (argc == 4) {
            usage(argv);
            fclose(input);
            return 1;
        }
        int k = 0;
        while (read_bin(&student, input)) {
            print(&student);
            k++;
        }
        if (k == 1) {
            printf("Файл пуст!\n");
            fclose(input);
            return 0;
        }
        return 0;
    }
    
    if (strcmp(argv[2], "-p") == 0) {
        if (argc == 3) {
            usage(argv);
            fclose(input);
            return 1;
        }
    } else {
        usage(argv);
        fclose(input);
        return 4;
    }
    
    int p;
    sscanf(argv[3], "%d", &p);
    if (!p) {
        usage(argv);
        fclose(input);
        return 3;
    }
    
    int n = 0;
    double max_mark = 0;
    while (read_bin(&student, input)) {
        n++;
        if (average_mark(&student) > max_mark)
            max_mark = average_mark(&student);
    }
    rewind(input);
    if (n == 0) {
        printf("Файл пуст!\n");
        fclose(input);
        return 0;
    }
    if (p > n) {
        printf("Введённое количество больше количества студентов!\n");
        fclose(input);
        return 3;
    }

    double current_max_mark = max_mark;
    while (p) {
        double tmp_max_mark = 0;
        while (read_bin(&student, input)) {
            double a_mark = average_mark(&student);
            if (a_mark == current_max_mark) {
                print(&student);
                if (!(--p)) break;
            }
            if (a_mark < current_max_mark && a_mark > tmp_max_mark) {
                tmp_max_mark = a_mark;
            }
        }
        current_max_mark = tmp_max_mark;
        rewind(input);
    }
    
    fclose(input);
    return 0;
}
