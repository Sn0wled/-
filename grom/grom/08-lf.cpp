// 2018 ReVoL Primer Template
// 08-lf.cpp (левая факторизация)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// 08 -lf -gr

// является pref префиксом правила rule ?
int is_prefix_for(RULE rule, RULE pref) {
    int pref_count = pref.count();
    for (int s = 1; s <= pref_count; s++) {
        if (rule[s] != pref[s]) return 0;
    }
    return 1;
}

// максимальный префикс для правила j
// возвращает длину префикса правила j
int max_prefix_for_rule_number(int j, grammar g1) {
    int rule_count = g1.count();
    int max_prefix = 0;
    RULE pref = g1[j];
    while (pref.count() > 0)
    {
        for (int r = 1; r <= rule_count; r++) {
            if (r != j) {
                if (g1[r][0] == pref[0]) {
                    if (is_prefix_for(g1[r], pref)) return pref.count();
                }
            }
        }
        pref.remove();
    }
    return 0;
}

// ищет префикс максимальной длины для A
// возвращает длину префикса
int find_prefix_for(SYMB A, grammar g1, RULE & pref) {
    int max_len = 0;
    int max_rule = 0;
    int len;
    int r;
    for (r = 1; r <= g1.count(); r++) {
        if (g1[r][0] == A) {
            len = max_prefix_for_rule_number(r, g1);
            if (max_len < len) {
                max_len = len;
                max_rule = r;
            }
        }
    }
    if (max_len != 0) {
        pref = g1[max_rule];
        while (pref.count() != max_len)
        {
            pref.remove();
        }
    }
    return max_len;
}

// устраняет префикс pref нетерминала pref[0]
void eliminate_prefix(grammar & g1, RULE pref) {
    int symbol_count = pref.count();
    SYMB A1 = g1.get_star_nont(pref[0]);
    int rule_count = g1.count();
    for (int r = 1; r <= rule_count; r++) {
        if (g1[r][0] == pref[0] && is_prefix_for(g1[r], pref)) {
            g1[r][0] = A1;
            for (int i = 0; i < symbol_count; i++) {
                g1[r].remove(1);
            }
        }
    }
    RULE rule;
    rule = pref;
    rule.append(A1);
    g1.rule_add(rule);
}

// алгоритм левой факторизации
int left_factoring(grammar & g1) {
    int found;
    while (true)
    {
        found = 0;
        for (SYMB A = 1; A <= g1.nont_count(); A++) {
            RULE pref;
            int prefix_count = find_prefix_for(-A, g1, pref);
            if (prefix_count != 0) {
                found = 1;
                eliminate_prefix(g1, pref);
            }
        }
        if (found == 0) break;
    }
    return 1;
}

// точка входа в алгоритм
// левая факторизация
int algorithm_left_factoring(grammar & g1, FILE * target) {
    // алгоритм
    int result = left_factoring(g1);
    // выводим грамматику в консоль
    g1.print(stdout);
    // выводим грамматику в файл
    g1.print(target);
    // результат
    return result;
}
/*/
.08.sxg
<A>
<A>=[a][b][a][b]
<A>=[a][b][c][d]
<A>=[a][b][c][e]
<A>=[a][b][c][f]
/*/
