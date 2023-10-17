// 2018 ReVoL Primer Template
// 03-us.cpp (���������� ���������� ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 03 -us

// ���������� 1, ���� ������� ��������
int are_known_syms(RULE rule, SSET R) {
    int symbol_count = rule.count();
    SYMB A;
    for (int s = 1; s <= symbol_count; s++) {
        A = rule[s];
        if (A < 0 && !R.contains(A)) return 0;
    }
    return 1;
}

// ��������� ��������� ����������� ������������
void find_usefull_syms(grammar & g1, SSET & R) {
    int rule_count = g1.count();
    int fix;
    RULE rule;
    while (1) {
        fix = R.count();
        for (int r = 1; r <= rule_count; r++) {
            rule = g1[r];
            if (are_known_syms(rule, R)) {
                R.insert(rule[0]);
            }
        }
        if (R.count() == fix) break;
    }
}

// ���������� � g2 �������, ����������� ������� ����������� R
void find_usefull_rules(grammar & g2, grammar & g1, SSET R) {
    int rule_count = g1.count();
    RULE rule;
    for (int r = 1; r <= rule_count; r++) {
        rule = g1[r];
        if (R.contains(rule[0])) {
            if (are_known_syms(rule, R)) {
                g2.rule_add_from(g1, rule);
            }
        }
    }
}

// ������� ���������� �������
void remove_useless(grammar & g1, grammar & g2) {
    g2.set_start_from(g1);
    SSET R;
    find_usefull_syms(g1, R);
    find_usefull_rules(g2, g1, R);
}

// ����� ����� � ��������
// ���������� ���������� ��������
int algorithm_remove_useless(grammar & g1, FILE * target) {
    // �������������� ����������
    grammar g2;
    // ���������� ���������� ��������
    remove_useless(g1, g2);
    // ������� ���������� � �������
    g2.print(stdout);
    // ������� ���������� � ����
    g2.print(target);
    // �������� ����������
    g1 = g2;
    // ���������
    return 1;
}
/*/
.03.sxg
<S>
<S>=[a]
<S>=<A>
<A>=<A><B>
<B>=<C>
<C>=[b]
/*/
