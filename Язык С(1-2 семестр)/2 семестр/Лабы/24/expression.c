#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MIN_CAP 4
#define N 10


/*

Какие бывают типы токенов

number 1, 2, 0.65, .345
variable x, my_var31, _HI
operation + - * / ^ ~
(
)

*/

typedef enum {
    NUMBER,
    VARIABLE,
    OPERATION,
    LBR,
    RBR,
    NONE
    // Добавьте свои типы токенов по желанию, например функции
} TOKEN_TYPE;

typedef enum {
    PLUS = '+',
    MINUS = '-',
    MULT = '*',
    DIVIDE = '/',
    POWER = '^',
    UN_MINUS = '~'
    // Добавьте больше операций, если требуется
} OPERATION_TYPE;

/*
Объединения
Позволяют использовать переменную как будто у нее может быть несколько разных типов.
По сути это просто возможность по разному интерпретировать один и тот же кусок памяти.

union NAME {
    type1 field1;
    type2 field2;
    ...
    typeN fieldN;
};

Все описанное про определение enum работает и с union
*/

typedef struct {
    TOKEN_TYPE type;
    union {
        double number;
        char name[N];
        OPERATION_TYPE operation;
    } content;
} Token;

// Далее идет реализация стека. Описаны только прототипы использовавшихся функций

typedef Token StackContentType;

typedef struct {
    ...
} Stack;

void stackInit(Stack*);

void stackDestroy(Stack*);

bool stackEmpty(Stack*);

void stackPush(Stack*, StackContentType);

StackContentType stackPop(Stack*);

/*
Здесь можно сделать и по другому чтобы была возможность посмотреть элемент на вершине стека, не доставая его. 
Например

StackContentType stackTop();

void stackPop(Stack*);
*/

/*

Основные шаги для разбора выражения:

1) Разбить пользовательский ввод на токены
2) Перевести в постфиксную запись
3) Построить дерево разбора

*/

char _getNextSymbol() {
    // Пропускаем пробельные символы. Вспомогательная функция
    char c;
    do {
        c = getchar();
    } while (c == ' ' || c == '\t');
    return c;
} 

bool getToken(Token *res, TOKEN_TYPE prevType) {
    // Считываем один токен из входного потока. Сигнализируем о конце ввода.
    /*
        Определяем по первому символу ввода что за токен получили
        
        Числа вещественные, возможно начинаются с "."
        Переменные могут содержать латинские буквы верхнего и нижнего регистра, подчеркивание и цифры, но не могут начинаться с цифры 
        Скобки
        Знаки арифметических операций

        Тип предыдущего токена используется для того чтобы можно было определить что получен унарный минус

        ####

        ungetc - возвращает символ обратно в поток.
        scanf("%[a-zA-Z_0-9]"... считывает строку до тех пор пока не встретит символ не перечисленный в []
    */
    char c = _getNextSymbol();
    if (c == '\n' || c == EOF) {
        return false;
    }
    if ((c >= '0' && c <= '9') || c == '.') {
        ungetc(c, stdin);
        scanf("%lf", &res->content.number);
        res->type = NUMBER;
    } else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_') {
        ungetc(c, stdin);
        scanf("%[a-zA-Z_0-9]", res->content.name);
        res->type = VARIABLE;
    } else if (c == '(') {
        res->type = LBR;
    } else if (c == ')') {
        res->type = RBR;
    } else if (c == '-' ) {
        res->type = OPERATION;
        // как определить что получен унарный минус?
    } else if (c == '+' || c == '*' || c == '/' || c == '^'){
        res->type = OPERATION;
        res->content.operation = c;
    } else {
        // получили что-то чего мы не ожидаем
        res->type = NONE;
    }
    return true;
}

/*

( 2 + x ) * 3 инфиксная
* + 2 x 3 префиксная (польская)
2 x + 3 * постфисксная (обратная польская)


алгоритм Дейкстры (сортировочная станция)
инфиксная -> постфиксная

*/

/*
Используется вспомогательный стек (tmp) и стек для результата(result)

Числа и переменные перемещаем сразу в стек с результатом
Открывающую скобку кладем во временный стек
На закрывающую скобку:
    Перемещаем все из временного стека в стек с результатом, до тех пока не встретим открывающую
    Если так и не встретили, то ошибка
На операцию:
    До тех пор пока на вершине стека операция с большим либо равным приоритетом, перемещаем ее в result.
    Как только это условие не выполняется кладем текущую операцию в tmp

После того как закончился ввод, tmp может быть не пуст. Переместить все из tmp в result, если в процессе встречаем (, то ошибка

В итоге получаем стек в формате (сверху вниз)

Операция
Аргумент2
Аргумент1

где в качестве аргумента может быть так же другая операция, либо по-честному число или переменная.
(Да да для внимательных товарищей нужно сказать что может быть просто один аргумент без операций)
Есть еще унарный минус и у него только один аргумент.

###

Вытесняем операции с >= приоритетом
Для правоассоциативных операций только то что >

Приоритеты
4 ~ (пр. асс)
3 ^ (пр. асс)
2 * /
1 + -

Пояснение про правоассоциативность:

Выражение
2^3^4

result : 2 3 4
tmp    : ^ ^

RESULT : 2 3 4 ^ ^ -> 2 ^ (3 ^ 4) = 2 ^ 81

Если же знак степени будет вытеснять другие знаки степени в результат, то получим

result : 2 3 ^ 4
tmp    : ^

RESULT : 2 3 ^ 4 ^ -> (2 ^ 3) ^ 4 = 8 ^ 4

*/

bool forcePush(OPERATION_TYPE a, OPERATION_TYPE b) {
    // Проверяем нужно ли переместить операцию типа "a" в стек с результатом, если сейчас получили "b"
    switch (b) {
        case UN_MINUS:
            break;
        case POWER:
            if (a == UN_MINUS) {
                return true;
            }
            break;
        case MULT:
        case DIVIDE:
            if (a == UN_MINUS || a == POWER || a == MULT || a == DIVIDE) {
                return true;
            }
        case PLUS:
        case MINUS:
            break;
    }
    return false;
}

bool readAndConvertExpression(Stack *result) {
    // Считываем выражение и преобразуем его в постфиксную запись
    Stack tmp;
    stackInit(&tmp);
    Token curToken;
    OPERATION_TYPE prevType = NONE;
    /*
        prevType - Тип предыдущего токена.
        Как было написано выше нужен для того чтобы опеределить какую операцию означает "-".
        Так же позволит определить ошибки ввода.
        Подумайте как с его помощью понять что введено не корректное выражение. Например:
        + 1xyz
        2 3 *
        И исправьте функцию, чтобы подобное трактовалось как ошибка.
    */

    bool okExpression = true;
    while (getToken(&curToken, prevType) && okExpression) {
        if (curToken.type == NONE) {
            return false;
        }
        prevType = curToken.type;
        Token topToken;
        switch (curToken.type) {
            case NUMBER:
            case VARIABLE:
                stackPush(result, curToken);
                break;
            case LBR:
                stackPush(&tmp, curToken);
                break;
            case RBR:
                while (!stackEmpty(&tmp)) {
                    topToken = stackPop(&tmp);
                    if (topToken.type == LBR) {
                        break;
                    }
                    stackPush(result, topToken);
                }
                if (topToken.type != LBR) {
                    okExpression = false;
                }
                break;
            case OPERATION:
                if (stackEmpty(&tmp)) {
                    topToken.type = NONE;
                } else {
                    topToken = stackPop(&tmp);
                }
                // Допишите согласно алгоритму ;-)
        }
    }

    while (!stackEmpty(&tmp)) {
        Token curToken = stackPop(&tmp);
        if (curToken.type == LBR) {
            okExpression = false;
            break;
        }
        stackPush(result, curToken);
    }

    stackDestroy(&tmp);
    return okExpression;
}

typedef struct _Treenode Treenode;
typedef Token TreenodeContent;

struct _Treenode {
    TreenodeContent value;
    Treenode *l, *r;
};

typedef struct {
    Treenode *root;
} ExpressionTree;

bool _buildNode(Stack *expression, Treenode *node) {
    // Заполняем содержимое вершины дерева и рекурсивно строим для его детей если требуется.
    // В случае ошибки (подумайте какие могут возникнуть) возвращаем false
    // if operation then build for right and left
    // else do nothing
}

bool buildTree(Stack *expression, ExpressionTree *tree) {
    // create root
    return _buildNode(expression, tree->root);
}

int main() {
    Stack expression;
    stackInit(&expression);
    if (!readExpPostfix(&expression)) {
        printf("Incorrect expression\n");
        return 1;
    }

    printf("RESULT STACK. TOP -> BOTTOM\n");

    while (!stackEmpty(&expression)) {
        Token top = stackPop(&expression);
        switch (top.type) {
            case NUMBER:
            printf("%lf ", top.content.number);
            break;
            case VARIABLE:
            printf("%s ", top.content.name);
            break;
            case OPERATION:
            printf("%c ", top.content.operation);
        }
    }
    printf("\n");

    // ExpressionTree tree;
    // if (!buildTree(&expression, &tree)) bad;

    // if (!empty(expression)) bad;

    /*
    После построения дерева можете производить с ним любые операции.
    Вывод выражения осуществляется так же как и печать дерева с прошлого занятия, нужно лишь не печатать лишние пробельные символы
    Значение вывести switch'ом выше

    Поскольку при выводе выражения в строку не видно структуру дерева, то приоритет операций, заданный скобками, теряется.
    Решением этой проблемы может быть вывод скобок (быть может избыточных) для того чтобы было понятно в каком порядке выполняются операции

    Не забывайте освобождать память.
    */

    return 0;
}
