// 2018 ReVoL Primer Template
// 02-gr.cpp (������������� ������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 02 -gr

// ���������� ������� � ������� ��������� ������������
void group_rules(grammar & g1, grammar & g2) {
}

// ����� ����� � ��������
// ������������� ������
int algorithm_group_rules(grammar & g1, FILE * target) {
    // �������������� ����������
    grammar g2;
    // ��������
    group_rules(g1, g2);
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
.02.sxg
<S>
<A>=<S><A>
<A>=<B>
<B>=[b]
<A>=[a]
<S>=<B>
<S>=<A><B>
/*/
