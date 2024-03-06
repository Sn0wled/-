// 2018 ReVoL Primer Template
// 16-rexfa.cpp (преобразование выражения в автомат)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// r16 -rexfa

// предварительное описание
int E(NFA & fa, NFA & part);
// ссылка на выражение
char * rx = 0;
// текущая точка в выражении
int index = 0;
// текущий символ выражения
char current() {
    return rx[index];
}
// следующий символ выражения
char getnext() {
    char c = rx[index];
    if (c != 10) index++;
    return c;
}
// первичный автомат
void primary(NFA & fa, NFA & part, char c) {
}
// итерация
void iteration(NFA & fa, NFA & part) {
}
// конкатенация
void concat(NFA & fa, NFA & part, NFA & tail) {
}
// объединение
void unite(NFA & fa, NFA & part, NFA & tail) {
}
// элемент выражения
int P(NFA & fa, NFA & part) {
    char c = getnext();
    int result;
    if (c == 10) {
        return 10;
    }
    else if (c == '(') {
        // выражение в скобках
        result = E(fa, part);
        if (result != 1) return result;
    }
    else if (c == '1') {
        // константа
    }
    else if (c > 122) {
        // недопустимый знак
    }
    else if (c > 96) {
        // переменная
    }
    return 0;
}
// унарная операция
int U(NFA & fa, NFA & part) {
    char c = 0;
    int result = T(fa, part);
    return 1;
}
// конкатенации
int T(NFA & fa, NFA & part) {
    NFA tail;
    char c = 0;
    int result = T(fa, part);
    return 1;
}
// объединения
int E(NFA & fa, NFA & part) {
    NFA tail;
    char c = 0;
    int result = T(fa, part);
    return 1;
}

// преобразует регулярное выражение в конечный автомат
int rex_to_fa(char * rex, NFA & fa) {
    rx = rex;
    NFA part;
    int result = E(fa, part);
    fa = part;
    return result;
}

// точка входа в алгоритм
// преобразование выражения в автомат
int algorithm_rex_to_fa(char * rex, NFA & fa, FILE * target) {
    // алгоритм
    int result = rex_to_fa(rex, fa);
    // выводим КА в консоль
    fa.printi(stdout);
    // выводим КА в файл
    fa.printi(target);
    // результат
    return result;
}
