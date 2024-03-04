// 2018 ReVoL Primer Template
// 13-dfa.cpp (�������������� ��� � ���)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// a13a -dfa
// a13e -dfa
// a13b -dfa

// ������������� ���������
SSET inspected;

// ��������� ��������� A ��������� ��� state
void closure(SYMB state, SSET & A, NFA & fa1) {
}

// ��������� ��������� A ��������� ��� A
void closureA(SSET & A, NFA & fa1) {
}

// ��������� 2^(n-1)
int power2n(int n) {
    if (n > 31) throw "power2n: too many states found";
    int m = 1;
    for (int i = 1; i < n; i++) m <<= 1;
    return m;
}

// ��������� ������������� ��������� ���, ������������ ���
// ������������ ��������� ���������, ���� ����
int reg_state(SSET & A, NFA & fa1, NFA & fa2) {
    char buf[16] = {};
    int number = 0;
    int final;
    SYMB regstate;
    for (int i = 1; i <= A.count(); i++) {
        int s = A[i];
        final = fa1.finals.contains(s);
        number += power2n(s);
    }
    sprintf(buf, "%d", number);
    regstate = fa2.reg_state_id(buf);
    if (final) fa2.finals.insert(regstate);
    return regstate;
}

// ���� ������ ���������
// A - ��������� ��� - ��������� ��������� ���
// initial - ������� ���������� ���������
int follow_dfa_state(SSET A, NFA fa1, NFA & fa2, int initial = 0) {
    SSET T, C;
    int state_a = 0, state_b = 0;
    state_a = reg_state(A, fa1, fa2);
    if (initial) fa1.initials.insert(state_a);
    inspected.insert(state_a);
    return 1;
}

// ����������� ��� � ���
int nfa_to_dfa(NFA & fa1, NFA & fa2) {
    inspected.clear();
    return follow_dfa_state(fa1.initials, fa1, fa2, 1);
}

// ����� ����� � ��������
// �������������� ��� � ���
int algorithm_dfa(NFA & fa1, FILE * target) {
    // �������� ��
    NFA fa2;
    // ��������
    int result = nfa_to_dfa(fa1, fa2);
    // ������� �� � �������
    fa2.printn(stdout);
    // ������� �� � ����
    fa2.printn(target);
    // �������� ��
    fa1 = fa2;
    // ���������
    return result;
}
/*/
.a13a.sxg
{A}
(A,a)={A}
(A,a)={B}
(A,b)={A}
(B,b)={C}
{C}
/*/
/*/
.a13e.sxg
{1}
(1, )={2,8}
(2, )={3,5}
(3,a)={4}
(4, )={7}
(7, )={2}
(5,b)={6}
(6, )={7}
(7, )={8}
{8}
/*/
