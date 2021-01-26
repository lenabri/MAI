//
//  deque.c
//  26
//
//  Created by Юрий Лошманов on 06.05.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#include "deque.h"

DEQUE* deque_create() {
    DEQUE* d = (DEQUE*)malloc(sizeof(DEQUE));
    d->size = 0;
    return d;
}

void deque_push_right(DEQUE* d, int value) {
    d->body = (int*)realloc(d->body, (d->size + 1) * sizeof(int));
    d->body[d->size] = value;
    d->size++;
}

int deque_pop_right(DEQUE* d) {
    int res = d->body[d->size];
    d->body = (int*)realloc(d->body, (d->size - 1) * sizeof(int));
    d->size--;
    return res;
}

void deque_push_left(DEQUE* d, int value) {
    d->body = (int*)realloc(d->body, (d->size + 1) * sizeof(int));
    int tmp = d->body[0];
    for (int i = d->size - 1; i >= 0; i--) {
        tmp = d->body[i];
        d->body[i] = d->body[i + 1];
        d->body[i + 1] = tmp;
    }
    d->body[0] = value;
    d->size++;
}

int deque_pop_left(DEQUE* d) {
    int res = d->body[d->size];
    int tmp1, tmp2;
    tmp1 = d->body[0];
    tmp2 = d->body[1];
    for (int i = 0; i < d->size - 1 ; i++)
        d->body[i] = d->body[i+1];
    d->body[d->size-1] = tmp2;
    d->body = (int*)realloc(d->body, (d->size - 1) * sizeof(int));
    d->size--;
    return res;
}

int deque_size(DEQUE* d) {
    return d->size;
}

bool deque_is_empty(DEQUE* d) {
    return d->size != 0;
}

void deque_print(DEQUE* d) {
    if (d->size == 0) {
        printf("\tДек пуст!\n");
        return;
    }
    printf("\t");
    for (int i = 0; i < d->size; i++)
        printf("%d ", d->body[i]);
    printf("\n");
}

void deque_print_size(DEQUE* d) {
    if (d->size == 0) {
        printf("\tДек пуст!\n");
        return;
    }
    printf("\tРазмер дека: %d\n", d->size);
}

void deque_destroy(DEQUE* d) {
    free(d->body);
    free(d);
}
