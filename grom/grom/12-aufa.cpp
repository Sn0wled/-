// 2018 ReVoL Primer Template
// 12-aufa.cpp (преобразование грамматики в автомат)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a11 -faau -aufa

// находит пару A->a или A->aB, возвращает номер правила
int has_pair_rule(RULE rule, int length, grammar gr) {
    int c = gr.count();
    for (int i = 1; i <= c; i++) {
        RULE r = gr[i];
        if (r[0] == rule[0] && r[1] == rule[1] && r.count() == length) return i;
    }
    return 0;
}

// преобразует грамматику в автомат
int grau_to_fa(grammar & gr, NFA & fa) {
    fa.reg_initial_from(gr, gr.start());
    int c = gr.count();
    for (int i = 1; i <= c; i++) {
        RULE r = gr[i];
        int rc = r.count();
        if (rc != 1 && rc != 2) {
            printf("Grammar is wrong\n");
            return 0;
        }
        int length = r.count();
        int pair = has_pair_rule(r, (1 + length % 2), gr);
        if (length == 1 && pair != 0) {
            TRAN t;
            t.a = fa.reg_state_from(gr, r[0]);
            t.b
        }
    }
    return 1;
}

// точка входа в алгоритм
// преобразование грамматики в автомат
int algorithm_grau_to_fa(grammar & gr, NFA & fa, FILE * target) {
    // алгоритм
    int result = grau_to_fa(gr, fa);
    // выводим КА в консоль
    fa.printi(stdout);
    // выводим КА в файл
    fa.printi(target);
    // результат
    return result;
}
