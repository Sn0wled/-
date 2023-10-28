// 2018 ReVoL Primer Template
// 06-r�.cpp (���������� ������ ������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 05 -re -gr -rc -gr

// ���� �� ������ ������� g1 � ��������� �� � g2
void nonunit_rules(grammar & g1, grammar & g2) {
    RULE rule;
    int rule_count = g1.count();
    for (int i = 1; i <= rule_count; i++) {
        rule = g1[i];
        if (!rule.is_unit()) {
            g2.rule_add_from(g1, rule);
        }
    }
}

// ���� ������� ����������� A
void find_chain_for(grammar & g1, SSET & R) {
    int rule_count = g1.count();
    RULE rule;
    while (true)
    {
        int fix = R.count();
        for (int i = 1; i <= rule_count; i++) {
            rule = g1[i];
            if (R.contains(rule[0]) && rule.is_unit()) {
                R.insert(rule[1]);
            }
        }
        if (fix == R.count()) break;
    }
}

// ��������� ����� �� ������ �������
void nonunit_rules_for(grammar & g2, grammar & g1, SSET R) {
    int r_count = R.count();
    SYMB sym;
    for (int i = 2; i <= r_count; i++) {
        sym = R[i];
        int rule_count = g2.count();
        RULE rule;
        for (int r = 1; r <= rule_count; r++) {
            rule = g2[r];
            if (rule[0] == sym) {
                rule[0] = R[1];
                g2.rule_add(rule);
            }
        }
    }
}

// ��������� ������ �������
void remove_units(grammar & g1, grammar & g2) {
    g2.set_start_from(g1);
    nonunit_rules(g1, g2);
    SYMB last = g1.nont_count();
    for (SYMB A = 1; A <= last; A++) {
        SSET R = -A;
        find_chain_for(g1, R);
        nonunit_rules_for(g2, g1, R);
    }
}

// ����� ����� � ��������
// ���������� ������ ������
int algorithm_remove_units(grammar & g1, FILE * target) {
    // �������������� ����������
    grammar g2;
    // ��������
    remove_units(g1, g2);
    // ������� ���������� � �������
    g2.print(stdout);
    // ������� ���������� � ����
    g2.print(target);
    // �������� ����������
    g1 = g2;
    // ���������
    return 1;
}
