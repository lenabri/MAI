//
//  deque.h
//  26
//
//  Created by Юрий Лошманов on 06.05.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#ifndef deque_h
#define deque_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>

typedef struct DEQUE DEQUE;

struct DEQUE {
    int* body;
    int size;
};

DEQUE* deque_create(void);
void deque_push_right(DEQUE* d, int value);
int deque_pop_right(DEQUE* d);
void deque_push_left(DEQUE* d, int value);
int deque_pop_left(DEQUE* d);
int deque_size(DEQUE* d);
bool deque_is_empty(DEQUE* d);
void deque_print(DEQUE* d);
void deque_print_size(DEQUE* d);
void deque_destroy(DEQUE* d);

#endif /* deque_h */
