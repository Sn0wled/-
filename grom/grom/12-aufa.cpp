// 2018 ReVoL Primer Template
// 12-aufa.cpp (преобразование грамматики в автомат)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a11 -faau -aufa

// находит пару A->a или A->aB, возвращает номер правила
int has_pair_rule(RULE rule, int length, grammar gr) {
    int c = gr.count();
    RULE r;
    for (int i = 1; i <= c; i++) {
        r = gr[i];
        if (r[0] == rule[0] && r[1] == rule[1] && r.count() != length) {
            return i;
        }
    }
    return 0;
}

// преобразует грамматику в автомат
int grau_to_fa(grammar & gr, NFA & fa) {
    int c = gr.count();
    RULE rule;
    int length;
    TRAN tran;
    SYMB A, B;
    char a;
    fa.reg_initial_from(gr, gr.start());

    for (int i = 1; i <= c; i++) {
        rule = gr[i];
        length = rule.count();
        if (length == 2) {
            if (has_pair_rule(rule, length, gr)) {
                A = fa.reg_state_from(gr, rule[0]);
                a = gr.get_char(rule[1]);
                B = fa.reg_final_from(gr, rule[2]);
            }
            else {
                A = fa.reg_state_from(gr, rule[0]);
                a = gr.get_char(rule[1]);
                B = fa.reg_state_from(gr, rule[2]);
            }
        }
        else if (length == 1) {
            if (!has_pair_rule(rule, length, gr)) {
                A = fa.reg_state_from(gr, rule[0]);
                a = gr.get_char(rule[1]);
                B = fa.get_new_state();
                fa.reg_final_id(fa.getid(B));
            }
        }
        else {
            printf("Wrong grammar\n");
            return 0;
        }
        tran.a = A;
        tran.b = B;
        tran.c = a;
        fa.tran_add(tran);
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
