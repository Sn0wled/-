// 2018 ReVoL Primer Template
// 14-fainv.cpp (инвертирование автомата)
#include "stdafx.h"
#include "grammar.h"
#include "main.h"
// командные строки
// a13e -fainv -dfa -fainv -dfa

// обращает автомат
void fa_invert(NFA & fa) {
    for (int i = 1; i <= fa.delta_count(); i++) {
        TRAN& t = fa[i];
        SYMB tmp = t.a;
        t.a = t.b;
        t.b = tmp;
    }
    SSET tmp = fa.initials;
    fa.initials = fa.finals;
    fa.finals = tmp;
}

// точка входа в алгоритм
// инвертирование автомата
int algorithm_fa_invert(NFA & fa, FILE * target) {
    // алгоритм
    fa_invert(fa);
    // выводим КА в консоль
    fa.printn(stdout);
    // выводим КА в файл
    fa.printn(target);
    return 1;
}
