// 2018 ReVoL Primer Template
// 04-ur.cpp (устранение недостижимых символов)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 03 -us -ur -gr

// добавляет нетерминалы правила rule в множество R
void find_rule_syms(RULE rule, SSET & R) {
    int symb_count = rule.count();
    SYMB symb;
    for (int s = 1; s <= symb_count; s++) {
        symb = rule[s];
        if (symb < 0) R.insert(symb);
    }
}

// формирует множество достижимых символов
void find_reachable_syms(grammar & g1, SSET & R) {
    R.insert(g1.start());
    RULE rule;
    int rule_count = g1.count();
    int fix;
    while (1) {
        fix = R.count();
        for (int r = 1; r <= rule_count; r++) {
            rule = g1[r];
            if (R.contains(rule[0])) find_rule_syms(rule, R);
        }
        if (fix == R.count()) break;
    }
}

// записывает в g2 правила, левые символы которых принадлежат R
void find_reachable_rules(grammar & g2, grammar & g1, SSET R) {
    RULE rule;
    int rule_count = g1.count();
    for (int r = 1; r <= rule_count; r++) {
        rule = g1[r];
        if (R.contains(rule[0])) g2.rule_add_from(g1, rule);
    }
}

// удаляет недостижимые символы
void remove_unreachable(grammar & g1, grammar & g2) {
    g2.set_start_from(g1);
    SSET R;
    find_reachable_syms(g1, R);
    find_reachable_rules(g2, g1, R);
}

// точка входа в алгоритм
// устранение недостижимых символов
int algorithm_remove_unreachable(grammar & g1, FILE * target) {
    // результирующая грамматика
    grammar g2;
    // устранение недостижимых символов
    remove_unreachable(g1, g2);
    // выводим грамматику в консоль
    g2.print(stdout);
    // выводим грамматику в файл
    g2.print(target);
    // выходная грамматика
    g1 = g2;
    // результат
    return 1;
}
