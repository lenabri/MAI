//
//  main.c
//  26
//
//  Created by Юрий Лошманов on 06.05.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#include <stdio.h>

#include "deque.h"

void concatenate(DEQUE* d1, DEQUE* d2, DEQUE* res) {
    for (int i = 0; i < deque_size(d1); i++)
        deque_push_right(res, d1->body[i]);
    for (int i = 0; i < deque_size(d2); i++)
        deque_push_right(res, d2->body[i]);
}

void quick_sort(int* array, int left, int right) {
    int i = left, j = right, tmp;
    int pivot = array[(left + right) / 2];
    while(i <= j) {
        for (; array[i] < pivot; i++);
        for (; array[j] > pivot; j--);
        if (i <= j) {
            tmp = array[i];
            array[i++] = array[j];
            array[j--] = tmp;
        }
    }
    if(left < j) quick_sort(array, left, j);
    if(i < right) quick_sort(array, i, right);
}

int main() {
    int command;
    DEQUE* d1 = deque_create();
    DEQUE* d2 = deque_create();
    DEQUE* res = deque_create();
    printf("1. Добавить в первый дек\n2. Добавить во второй дек\n3. Удалить из первого дека\n4. Удалить из второго дека\n5. Объединить деки\n6. Отсортировать дек\n7. Распечатать дек\n8. Распечатать размер дека\n9. Выйти\n\n");
    do {
        printf("Введите команду: ");
        scanf("%d", &command);
        switch (command) {
            case 1:
            {
                int comm;
                printf("\t1. Добавить слева (в начало)\n\t2. Добавить справа (в конец)\n\t3. Выйти\n\n");
                do {
                    printf("\tВведите команду: ");
                    scanf("%d", &comm);
                    if (comm == 1) {
                        int value;
                        printf("\tВведите значение: ");
                        scanf("%d", &value);
                        deque_push_left(d1, value);
                    } else if (comm == 2) {
                        int value;
                        printf("\tВведите значение: ");
                        scanf("%d", &value);
                        deque_push_right(d1, value);
                    }
                } while (comm != 3);
                break;
            }
            case 2:
            {
                int comm;
                printf("\t1. Добавить слева (в начало)\n\t2. Добавить справа (в конец)\n\t3. Выйти\n\n");
                do {
                    printf("\tВведите команду: ");
                    scanf("%d", &comm);
                    if (comm == 1) {
                        int value;
                        printf("\tВведите значение: ");
                        scanf("%d", &value);
                        deque_push_left(d2, value);
                    } else if (comm == 2) {
                        int value;
                        printf("\tВведите значение: ");
                        scanf("%d", &value);
                        deque_push_right(d2, value);
                    }
                } while (comm != 3);
                break;
            }
            case 3:
            {
                int comm;
                printf("\t1. Удалить слева (с начала)\n\t2. Удалить справа (с конца)\n\t3. Выйти\n\n");
                do {
                    printf("\tВведите команду: ");
                    scanf("%d", &comm);
                    if (comm == 1) {
                        deque_pop_left(d1);
                    } else if (comm == 2) {
                        deque_pop_right(d1);
                    }
                } while (comm != 3);
                break;
            }
            case 4:
            {
                int comm;
                printf("\t1. Удалить слева (с начала)\n\t2. Удалить справа (с конца)\n\t3. Выйти\n\n");
                do {
                    printf("\tВведите команду: ");
                    scanf("%d", &comm);
                    if (comm == 1) {
                        deque_pop_left(d1);
                    } else if (comm == 2) {
                        deque_pop_right(d1);
                    }
                } while (comm != 3);
                break;
            }
            case 5:
            {
                deque_destroy(res);
                res = deque_create();
                concatenate(d1, d2, res);
                break;
            }
            case 6:
            {
                int comm;
                printf("\t1. Отсортировать первый дек\n\t2. Отсортировать второй дек\n\t3. Отсортировать третий дек (результат объединения)\n\t4. Выйти\n\n");
                do {
                    printf("\tВведите команду: ");
                    scanf("%d", &comm);
                    if (comm == 1) {
                        quick_sort(d1->body, 0, d1->size - 1);
                    } else if (comm == 2) {
                        quick_sort(d2->body, 0, d2->size - 1);
                    } else if (comm == 3) {
                        quick_sort(res->body, 0, res->size - 1);
                    } else if (comm == 4) {
                        break;
                    } else {
                        printf("Неверная команда!\n");
                    }
                } while (comm != 4);
                break;
            }
            case 7:
            {
                int comm;
                printf("\t1. Распечатать первый дек\n\t2. Распечатать второй дек\n\t3. Распечатать третий дек (результат объединения)\n\t4. Выйти\n\n");
                do {
                    printf("\tВведите команду: ");
                    scanf("%d", &comm);
                    if (comm == 1) {
                        deque_print(d1);
                    } else if (comm == 2) {
                        deque_print(d2);
                    } else if (comm == 3) {
                        deque_print(res);
                    } else if (comm == 4) {
                        break;
                    } else {
                        printf("Неверная команда!\n");
                    }
                } while (comm != 4);
                break;
            }
            case 8:
            {
                int comm;
                printf("\t1. Распечатать размер первого дека\n\t2. Распечатать размер второго дека\n\t3. Распечатать размер третьего дека (результата объединения)\n\t4. Выйти\n\n");
                do {
                    printf("\tВведите команду: ");
                    scanf("%d", &comm);
                    if (comm == 1) {
                        deque_print_size(d1);
                    } else if (comm == 2) {
                        deque_print_size(d2);
                    } else if (comm == 3) {
                        deque_print_size(res);
                    } else if (comm == 4) {
                        break;
                    } else {
                        printf("Неверная команда!\n");
                    }
                } while (comm != 4);
                break;
            }
            case 9:
                break;
            default:
                printf("Неверная команда!\n");
                break;
        }
    } while (command != 9);
    deque_destroy(d1);
    deque_destroy(d2);
    deque_destroy(res);
    return 0;
}
