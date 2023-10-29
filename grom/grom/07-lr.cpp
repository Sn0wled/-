// 2018 ReVoL Primer Template
// 07-lr.cpp (���������� ����� ��������)
#include "stdafx.h"
#include "grammar.h"

#include <locale.h>

// ��������� ������
// 07 -lr -gr

// ��������� ���������������� �������� ������ ��� A
void eliminate_direct(SYMB Ai, grammar & g1) {
    Ai = -Ai;
    SYMB A1 = g1.get_star_nont(Ai);
    int rule_count = g1.count();
    RULE new_rule;
    for (int r = 1; r <= rule_count; r++) {
        if (g1[r][0] == Ai) {
            if (g1[r][1] == Ai) {
                g1[r][0] = A1;
                g1[r].remove(1);
                new_rule = g1[r];
                new_rule.append(A1);
            }
            else {
                new_rule = g1[r];
                new_rule.append(A1);
            }
            g1.rule_add(new_rule);
        }
    }

}

// ��������� ����� ������� �� ����
void compile_rule(RULE rule_k, RULE rule_j, RULE & rule_new) {
    rule_new = rule_j;
    rule_new[0] = rule_k[0];
    int sym_count = rule_k.count();
    for (int s = 2; s <= sym_count; s++) rule_new.append(rule_k[s]);
}

// �������� ������� Ak->Ajx �� ������� Ak->wx, w - ������ ����� Aj
// k - ����� ������� Ak->Ajx
void replace_Aj(int k, grammar & g1) {
    RULE rule_k = g1[k];
    int rule_count = g1.count();
    int j = 1;
    RULE rule_j, rule_new;
    for (; j <= rule_count; j++) {
        rule_j = g1[j];
        if (rule_j[0] == rule_k[1]) {
            compile_rule(rule_k, rule_j, rule_new);
            g1[k] = rule_new;
            break;
        }
    }
    for (; j <= rule_count; j++) {
        rule_j = g1[j];
        if (rule_j[0] == rule_k[1]) {
            compile_rule(rule_k, rule_j, rule_new);
            g1.rule_add(rule_new);
        }
    }
}

// ����������� ������� �������� � �����
// ��� ������������ �� ������� �� Ak
// �������� ������� ���� Ak->Ajx �� Ak->wx, w - ������ ����� Aj
void indirect_to_direct(SYMB Ak, grammar & g1) {
    int rule_count = g1.count();
    for (SYMB Aj = 1; Aj < Ak; Aj++) {
        for (int k = 1; k <= rule_count; k++) {
            if (g1[k][1] == -Aj && g1[k][0] == -Ak) replace_Aj(k, g1);
        }
    }
}

// ��������� ����� ��������
void eliminate_leftr(grammar & g1) {
    int nont_count = g1.nont_count();
    for (SYMB Ai = 1; Ai <= nont_count; Ai++) {
        if (g1.is_symbol_leftr(-Ai)) eliminate_direct(Ai, g1);
        if (Ai != nont_count) indirect_to_direct(Ai + 1, g1);

    }
}

// ����� ����� � ��������
// ���������� ����� ��������
int algorithm_eliminate_leftr(grammar & g1, FILE * target) {

    setlocale(LC_ALL, ".1251");

    // ��������
    eliminate_leftr(g1);
    // ������� ���������� � �������
    g1.print(stdout);
    // ������� ���������� � ����
    g1.print(target);
    // ���������
    return 1;
}
/*/
.07.sxg
<A>
<A>=<B>[b]
<A>=[a]
<B>=<A>[a]
<B>=<B>[b]
<B>=[b]
/*/
