#!/usr/bin/env zsh

#переменные с большой буквы(принято), без пробела
A=42ABC

#вывод
echo $A

#подстановка переменных
B=/
ls $B

#вывод переменной в строку
WHO=man
echo 42 ${WHO}s


#условный оператор
if condition; then
    #statements
elif condition2; then
    #statements
else
    #statements
fi


#циклы
while condition; do
    #statements
done

until condition; do #пока условие не выполняется
    #statements
done

for i in abcd; do
    #statements
    echo $i
done


#диапазон
{abc}
touch {1..42}.txt


#конвейеры
ls | grep #ls передаёт вывод в grep


#скобочки
# []
# [[]] для чисел
# (()) для строк


# "$A" - разделение переменной

# sum.sh 1 2 3 4
# $1 # = 1
# $#
# logger.sh $@



$? #узнать как завершилась прошлая команда

#sed awk {}   - для строк
