// 2018 ReVoL Primer Template
// 01-gen.cpp (��������������� ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// 001

// ���������� 1
void test1 (grammar & g1, grammar & g2) {
}

// ���������� 2, 3, 4
void test2 (grammar & g1, grammar & g2) {
}

// ���������� 5
void test3 (grammar & g1, grammar & g2) {
}

// ��������� ����� �������� � �����������
void grammar_general(grammar & g1, grammar & g2) {
    test1(g1, g2);
    //test2(g1, g2);
    //test3(g1, g2);
}

// ����� ����� � ��������
// ����� �������� � �����������
int algorithm_general(grammar & g1, FILE * target) {
    // �������������� ����������
    grammar g2;
    // ��������
    grammar_general(g1, g2);
    // ������� ���������� � �������
    g2.print(stdout);
    // ������� ���������� � ����
    g2.print(target);
    // �������� ����������
    g1 = g2;
    return 0;
}
/*/
.001.sxg
<S>
<S>=<S>[+]<T>
<S>=<T>
<T>=<T>[*]<P>
<T>=<P>
<P>=[a]
<P>=[(]<S>[)]
/*/
