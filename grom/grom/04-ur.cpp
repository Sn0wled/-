// 2018 ReVoL Primer Template
// 04-ur.cpp (���������� ������������ ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 03 -us -ur -gr

// ��������� ����������� ������� rule � ��������� R
void find_rule_syms(RULE rule, SSET & R) {
    int symb_count = rule.count();
    SYMB symb;
    for (int s = 1; s <= symb_count; s++) {
        symb = rule[s];
        if (symb < 0) R.insert(symb);
    }
}

// ��������� ��������� ���������� ��������
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

// ���������� � g2 �������, ����� ������� ������� ����������� R
void find_reachable_rules(grammar & g2, grammar & g1, SSET R) {
    RULE rule;
    int rule_count = g1.count();
    for (int r = 1; r <= rule_count; r++) {
        rule = g1[r];
        if (R.contains(rule[0])) g2.rule_add_from(g1, rule);
    }
}

// ������� ������������ �������
void remove_unreachable(grammar & g1, grammar & g2) {
    g2.set_start_from(g1);
    SSET R;
    find_reachable_syms(g1, R);
    find_reachable_rules(g2, g1, R);
}

// ����� ����� � ��������
// ���������� ������������ ��������
int algorithm_remove_unreachable(grammar & g1, FILE * target) {
    // �������������� ����������
    grammar g2;
    // ���������� ������������ ��������
    remove_unreachable(g1, g2);
    // ������� ���������� � �������
    g2.print(stdout);
    // ������� ���������� � ����
    g2.print(target);
    // �������� ����������
    g1 = g2;
    // ���������
    return 1;
}
