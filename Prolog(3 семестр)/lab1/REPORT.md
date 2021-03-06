# Отчет по лабораторной работе №1
## Работа со списками и реляционным представлением данных
## по курсу "Логическое программирование"

### студент: Хубецова Е.М.

## Введение
Списки представляют собой рекурсивную структуру, в который находится либо пустой элемент, либо один элемент и присоединённый к нему список. 

Они отличаются от принятых в императивных языках тем, что они могут хранить разные типы данных, имеют неограниченную длину и вложенность.

Списки в прологе можно представить как двоичные деревья, все элементы которых уходят в правое поддерево.


## Задание 1.1: Предикат обработки списка

`first_entry1(A, [_|Z], N)` и `first_entry2(A, [_|Z], N)` - предикаты для нахождение номера первого вхождения элемента со заданным значением. Они отличаются только реализацией.

Примеры использования:
```prolog
?- first_entry1(4, [-4, 3, 0, 4, 4], N).
N = 3.

?- first_entry2(3, [0, 1, 2], N).
false.
```

Реализация:
```prolog
% Без использования стандартных предикатов:
first_entry1(A, [A|_], 0) :- !.
first_entry1(A, [_|Z], N) :- first_entry1(A, Z, N1), N is N1 + 1, !.

% С использованием стандарных предикатов:
first_entry2(A, [A|_], 0) :- !.
first_entry2(A, [_|Z], N) :- permute1(Z, X), first_entry2(A, X, N1), N is N1 + 1, !.
```

В реализации с использованием стандарных предикатов рекурсия д.б. встроена в стандартный  предикат. В Вашем варианте удобно реализовать через append.


Если элемент находится в начале списка, то предикаты `first_entry1` и `first_entry2` вернут значение `0`, иначе они рекурсивно пройдут по элементам списка, пока не встретят элемент в начале переданного им подсписка, при этом, каждую итерацию увеличивая свой счётчик на единицу.

## Задание 1.2: Предикат обработки числового списка

`sum1([X|Y], N)` и `sum2([X|Y], N)` - предикаты для вычисления суммы элементов. Они отличаются только реализацией.

Примеры использования:
```prolog
?- sum1([], X).
X = 0.

?- sum1([1, 2, 3], X).
X = 6.

?- sum2([-1, 0, 1], X).
X = 0.
```

Реализация:
```prolog
% Без использования стандартных предикатов:
sum1([], 0).
sum1([X|Y], N) :- sum1(Y, N1), N is N1 + X.

% С использованием стандарных предикатов:
sum2([], 0) :- !.
sum2([X|Y], N) :- permute1(Y, Z), sum2(Z, N1), N is N1 + X, !.
```

Если список пустой, то предикаты `first_entry1` и `first_entry2` вернут значение `0`, иначе они рекурсивно пройдут по элементам списка, пока не встретят пустой переданный им список, при этом, каждую итерацию увеличивая свой счётчик на текущий элемент.

## Задание 2: Реляционное представление данных

Из преимуществ:
1. Удобно хранить информацию
2. Возможно легко поменять данные, просто подключив другой файл
3. Полная независимость данных

Из недостатков:
1. Перед использованием данные нужно структурно расположить
2. Не все представления удобны для обработки

Представление `four.pl`.
Вариант 1.

Я реализовал все предикаты в виде простых команд без параметров. То есть предикаты `task1().`, `task2().` и `task3().` выводят результат подзадания задания в соответствии с номером моего варианта. Я решил, что так лучше всего сделать, так как не нужно будет смотреть в данные, чтобы указывать конкретные группы итд.

`task1().` - предикат получения таблицы групп и среднего балла по каждой из групп. Выводит данные о всех группах, находящихся в файле представления.

Примеры использования:
```prolog
?- task1().
Группа: 102
Средний балл: 3.9444444444444446

Группа: 101
Средний балл: 3.9666666666666663

Группа: 104
Средний балл: 3.861111111111111

Группа: 103
Средний балл: 4.145833333333333

true.
```

Реализация:
```prolog
find_grade([grade(Student, Grade)|_], Student, Grade) :- !.
find_grade([_|Grades], Student, Grade) :- find_grade(Grades, Student, Grade).


sum_for_subj([], _, 0) :- !.
sum_for_subj([Student|Students], Grades, Sum) :-
    find_grade(Grades, Student, Grade),
    sum_for_subj(Students, Grades, Sum1),
    Sum is Sum1 + Grade.

evaluate_sum(_, [], 0) :- !.
evaluate_sum(Students, [Subject|Subjects], Sum) :- 
    subject(Subject, Grades),
    sum_for_subj(Students, Grades, Sum1),
    evaluate_sum(Students, Subjects, Sum2),
    Sum is Sum1 + Sum2.


group_data([]) :- !.
group_data([Group|Groups]) :- 
    write('Группа: '), write(Group), nl,
    group(Group, Students),
    findall(Subject, subject(Subject, _), Subjects),
    evaluate_sum(Students, Subjects, Sum),
    findall(_, subject(_, _), Subjects),
    length(Subjects, X),
    length(Students, Y),
    Avg is Sum / X / Y,
    write('Средний балл: '), write(Avg), nl, nl,
    group_data(Groups).


task1() :-
    findall(Group, group(Group, _), Groups),
    group_data(Groups).
```


`task2().` - предикат получения для каждого предмета список студентов, не сдавших экзамен. Выводит данные о всех предметах, находящихся в файле представления.

Примеры использования:
```prolog
?- task2().
Логическое программирование
Не сдали экзамен: 3

Математический анализ
Не сдали экзамен: 1

Функциональное программирование
Не сдали экзамен: 0

Информатика
Не сдали экзамен: 2

Английский язык
Не сдали экзамен: 2

Психология
Не сдали экзамен: 2

true.
```

Реализация:
```prolog
evaluate_grade(grade(_, Grade), Value) :-
    Grade = 2, Value is 1, !;
    Grade \= 2, Value is 0, !.

sum_fail_grades([], 0) :- !.
sum_fail_grades([Grade|Grades], Sum) :-
    sum_fail_grades(Grades, Sum1),
    evaluate_grade(Grade, Value),
    Sum is Sum1 + Value.

fails_for_subject([]) :- !.
fails_for_subject([Subject|Subjects]) :-
    write(Subject), nl,
    subject(Subject, Grades),
    sum_fail_grades(Grades, Sum),
    write('Не сдали экзамен: '), write(Sum), nl, nl,
    fails_for_subject(Subjects).

task2() :-
    findall(Subject, subject(Subject, _), Subjects),
    fails_for_subject(Subjects).
```

`task3().` - предикат для нахождения количества не сдавших студентов в каждой из групп. Выводит данные о всех группах, находящихся в файле представления.

Примеры использования:
```prolog
?- task3().
Группа: 102
Не сдало: 3

Группа: 101
Не сдало: 3

Группа: 104
Не сдало: 2

Группа: 103
Не сдало: 2

true.
```

Реализация:
```prolog
remove_duplicates([],[]).
remove_duplicates([H | T], List) :- member(H, T), remove_duplicates( T, List).
remove_duplicates([H | T], [H|T1]) :- \+member(H, T), remove_duplicates( T, T1).


is_grade_fail(Grade, Student, Res) :-
    Grade = 2, append([], [Student], Res), !;
    Grade \= 2, !.

append_for_subj([], _, []) :- !.
append_for_subj([Student|Students], Grades, List) :-
    find_grade(Grades, Student, Grade),
    append_for_subj(Students, Grades, Res1),
    is_grade_fail(Grade, Student, Res2),
    append(Res2, Res1, List).

evaluate_list(_, [], []) :- !.
evaluate_list(Students, [Subject|Subjects], Res) :- 
    subject(Subject, Grades),
    append_for_subj(Students, Grades, Res1),
    evaluate_list(Students, Subjects, Res2),
    append(Res1, Res2, Res).


group__data([]) :- !.
group__data([Group|Groups]) :- 
    write('Количество не сдавших: '), write(Group), nl,
    group(Group, Students),
    findall(Subject, subject(Subject, _), Subjects),
    evaluate_list(Students, Subjects, Res),
    remove_duplicates(Res, Failed_students),
    length(Failed_students, Cuont),
    write('Не сдало: '), write(Cuont), nl, nl,
    group__data(Groups).


task3() :-
    findall(Group, group(Group, _), Groups),
    group__data(Groups), !.
```


## Выводы
В данной лабораторной работе я научился работать со списками в языке Prolog, научился писать собственные предикаты для работы со ними и использовать встроенные. Так же я научился подключать реляционные представления данных и совершать их обработку.

Мне очень понравилось, как реализованы списки в этом языке, эта лабораторная работа заставила меня неплохо задуматься о том, как реализовать поставленные мне задачи логическим путём, о чём бы я вряд ли задумался, используя императивные языки. Например, было очень трудно было переключиться на рекурсию, я так привык работать с циклами, что сначала даже не представлял как решить эти задачи, но я справился, и полученные навыки обязательно помогут мне в будущем.
