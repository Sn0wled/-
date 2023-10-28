// 2018 ReVoL Primer Template
// 02-gr.cpp (группирование правил)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 02 -gr

// группирует правила в порядке появления нетерминалов
void group_rules(grammar & g1, grammar & g2) {
    SSET P, Q;
    g2.set_start_from(g1);
    Q.insert(g1.start());
    int count_rules = g1.count();
    while (Q.count() != 0) {
        SYMB symb = Q[1];
        P.insert(symb);
        Q.remove(1);
        for (int i = 1; i <= count_rules; i++) {
            RULE rule = g1[i];
            if (rule[0] == symb) {
                g2.rule_add_from(g1, rule);
                int rule_length = rule.count();
                for (int j = 1; j <= rule_length; j++) {
                    if (P.misses(rule[j])) Q.insert(rule[j]);
                }
            }
        }
    }
}

// точка входа в алгоритм
// группирование правил
int algorithm_group_rules(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    group_rules(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    // результат
    return 1;
}
/*/
.02.sxg
<S>
<A>=<S><A>
<A>=<B>
<B>=[b]
<A>=[a]
<S>=<B>
<S>=<A><B>
/*/
