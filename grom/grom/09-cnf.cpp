// 2018 ReVoL Primer Template
// 09-cnf.cpp (приведение к нормальной форме Хомского)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 002 -cnf -gr

// правило для вывода терминала
void term_rule(SYMB A, SYMB a, grammar & g1, grammar & g2) {
    RULE rule;
    rule[0] = A;
    rule.append(a);
    g2.rule_add_from(g1, rule);
}

// приводит правило к нормальной форме Хомского
void rule_to_cnf(RULE rule_old, grammar & g1, grammar & g2) {
    RULE rule_new;
    if (rule_old.count() > 2) {
        rule_new[0] = rule_old[0];
        rule_new.append(rule_old[1]);
        SYMB A = g1.get_new_nont();
        rule_new.append(A);
        g2.rule_add_from(g1, rule_new);
        rule_old[0] = A;
        rule_old.remove(1);
        rule_to_cnf(rule_old, g1, g2);
    }
    else {
        g2.rule_add_from(g1, rule_old);
    }
}

// заменяет терминалы нетерминалами
void terms_to_nonts(RULE & rule, grammar & g1, grammar & g2) {
    int rule_length = rule.count();
    SYMB X;
    for (int s = 1; s <= rule_length; s++) {
        X = rule[s];
        if (X > 0) {
            SYMB A = g1.get_new_nont();
            rule[s] = A;
            term_rule(A, X, g1, g2);
        }
    }
}

// приводит грамматику к нормальной форме Хомского
int chomsky_normal_form(grammar & g1, grammar & g2) {
    g2.set_start_from(g1);
    int rule_count = g1.count();
    RULE rule;
    for (int r = 1; r <= rule_count; r++) {
        rule = g1[r];
        int rule_length = rule.count();
        if (rule_length == 0) {
            if (rule[0] == g1.start()) {
                g2.rule_add_from(g1, rule);
            }
            else {
                printf("Unexpected empty rule\n");
                return 0;
            }
        }
        else if (rule_length == 1) {
            if (rule[1] > 0) {
                g2.rule_add_from(g1, rule);
            }
            else {
                printf("Unexpected unit rule\n");
                return 0;
            }
        }
        else {
            terms_to_nonts(rule, g1, g2);
            rule_to_cnf(rule, g1, g2);
            g2.print(stdout);
        }
    }
}

// точка входа в алгоритм
// приведение к нормальной форме Хомского
int algorithm_chomsky_normal_form(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    int result = chomsky_normal_form(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    // результат
    return result;
}
/*/
.002.sxg
<S>
<S>=<S>[+]<S>
<S>=<S>[*]<S>
<S>=[a]
<S>=[(]<S>[)]
/*/
