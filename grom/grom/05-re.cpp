// 2018 ReVoL Primer Template
// 05-re.cpp (устранение пустых правил)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 05 -re -gr

// возвращает 1, если правило вырождающееся
int is_nullable_rule(RULE rule, SSET E) {
    int sym_count = rule.count();
    if (sym_count == 0) return 1;
    SYMB sym;
    for (int s = 1; s <= sym_count; s++) {
        sym = rule[s];
        if (!E.contains(sym)) return 0;
    }
    return 1;
}

// формирует множество вырождающихся нетерминалов E
void nullable_syms(grammar & g1, SSET & E) {
    int rule_count = g1.count();
    RULE rule;
    while (1)
    {
        int fix = E.count();
        for (int r = 1; r <= rule_count; r++) {
            rule = g1[r];
            if (is_nullable_rule(rule, E)) E.insert(rule[0]);
        }
        if (fix == E.count()) break;
    }
}

// непустые правила копирует в g2
void useful_rules(grammar & g2, grammar g1) {
    int rule_count = g1.count();
    RULE rule;
    for (int r = 1; r <= rule_count; r++) {
        rule = g1[r];
        if (rule.count() != 0) g2.rule_add_from(g1, rule);
    }
}

// удаляет символ N списка P из правила rule
// если полученное правило не пусто, добавляет его в g2
// рекурсивно вызывает себя для полученного остатка правила
// последовательно для символов N-1, N-2...
void remove_nullable_from(grammar & g2, RULE rule, SSET P, int N) {
    rule.remove(N);
    if (rule.count() != 0) g2.rule_add(rule);
    for (int M = N - 1; M >= 1; M--) {
        remove_nullable_from(g2, rule, P, M);
    }
}

// формирует список вырождающихся символов правила
void rule_nullable_syms(RULE rule, SSET E, SSET & P) {
    int sym_count = rule.count();
    SYMB sym;
    for (int s = 1; s <= sym_count; s++) {
        sym = rule[s];
        if (E.contains(sym)) P.insert(s);
    }
}

// формирует правила, компенсирующие удаленные пустые правила
void complement_rules(grammar & g2, SSET E) {
    int rule_count = g2.count();
    RULE rule;
    for (int r = 1; r <= rule_count; r++) {
        rule = g2[r];
        SSET P;
        rule_nullable_syms(rule, E, P);
        int p_count = P.count();
        for (int N = p_count; N >= 1; N--) {
            remove_nullable_from(g2, rule, P, N);
        }
    }
}

// устраняет пустые правила
void remove_empty(grammar & g1, grammar & g2) {
    SSET R;
    g2.set_start_from(g1);
    nullable_syms(g1, R);
    useful_rules(g2, g1);
    complement_rules(g2, R);
    if (g2.count() == 1 || !R.contains(g2.start())) return;
    SYMB S1 = g2.get_star_nont(g2.start());
    RULE rule;
    rule[0] = S1;
    g2.rule_add(rule);
    rule.append(g2.start());
    g2.rule_add(rule);
    g2.set_start(S1);
}

// точка входа в алгоритм
// устранение пустых правил
int algorithm_remove_empty(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // алгоритм
    remove_empty(g1, g2);
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
.05.sxg
<S>
<S>=<A><B>
<A>=[a]
<A>=<B><B>
<B>=[b]
<B>=.
/*/
