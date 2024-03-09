// 2018 ReVoL Primer Template
// 16-rexfa.cpp (�������������� ��������� � �������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// r16 -rexfa

// ��������������� ��������
int E(NFA & fa, NFA & part);
// ������ �� ���������
char * rx = 0;
// ������� ����� � ���������
int index = 0;
// ������� ������ ���������
char current() {
    return rx[index];
}
// ��������� ������ ���������
// rx[index++]
char getnext() {
    char c = rx[index];
    if (c != 10) index++;
    return c;
}
// ��������� �������
void primary(NFA & fa, NFA & part, char c) {
    TRAN tran;
    SYMB A = part.reg_state_from(fa, fa.get_new_state());
    SYMB B = part.reg_state_from(fa, fa.get_new_state());
    tran.a = A;
    tran.b = B;
    tran.c = c;
    part.tran_add(tran);
    part.initials.insert(A);
    part.finals.insert(B);
}
// ��������
void iteration(NFA & fa, NFA & part) {
    TRAN tran;
    SYMB A = part.reg_state_from(fa, fa.get_new_state());
    SYMB B = part.reg_state_from(fa, fa.get_new_state());
    tran.c = 0;
    tran.a = A;
    tran.b = part.initials[1];
    part.tran_add(tran);
    tran.b = B;
    part.tran_add(tran);
    tran.a = part.finals[1];
    part.tran_add(tran);
    tran.b = part.initials[1];
    part.tran_add(tran);
    part.initials.clear();
    part.finals.clear();
    part.initials.insert(A);
    part.finals.insert(B);
}
// ������������
void concat(NFA & fa, NFA & part, NFA & tail) {
    TRAN tran;
    tran.c = 0;
    tran.a = part.finals[1];
    tran.b = part.reg_state_from(tail, tail.initials[1]);
    part.tran_add(tran);
    part.finals.clear();
    part.finals.insert(part.reg_final_from(tail, tail.finals[1]));
    for (int i = 1; i <= tail.delta_count(); i++) {
        part.tran_add_from(tail, tail[i]);
    }
}
// �����������
void unite(NFA & fa, NFA & part, NFA & tail) {
    SYMB A = part.reg_state_from(fa, fa.get_new_state());
    SYMB B = part.reg_state_from(fa, fa.get_new_state());
    TRAN t;
    t.a = A;
    t.c = 0;
    t.b = part.initials[1];
    part.tran_add(t);
    t.b = part.reg_state_from(tail, tail.initials[1]);
    part.tran_add(t);
    t.b = B;
    t.a = part.finals[1];
    part.tran_add(t);
    t.a = part.reg_state_from(tail, tail.finals[1]);
    part.tran_add(t);
    for (int i = 1; i <= tail.delta_count(); i++) {
        part.tran_add_from(tail, tail[i]);
    }
    part.initials.clear();
    part.finals.clear();
    part.initials.insert(A);
    part.finals.insert(B);
}
// ������� ���������
int P(NFA & fa, NFA & part) {
    int result = 0;
    char c = getnext();
    if (c == 10) return 10;
    else if (c == '(') {
        result = E(fa, part);
        c = getnext();
        if (c != ')') result = 0;
    }
    else if (c == '1') {
        primary(fa, part, 0);
        result = 1;
    }
    else if (c > 122) {
        result = 0;
    }
    else if (c > 96) {
        primary(fa, part, c);
        result = 1;
    }
    return result;
}
// ������� ��������
int U(NFA & fa, NFA & part) {
    char c = 0;
    int result = P(fa, part);
    if (current() == STAR) {
        c = getnext();
        iteration(fa, part);
        while (current() == STAR)
        {
            c = getnext();
        }
    }
    return result;
}
// ������������
int T(NFA & fa, NFA & part) {
    NFA tail;
    char c = 0;
    int result = U(fa, part);
    while (current() > 96 && current() < 123 || current() == '(')
    {
        tail.clear();
        result = U(fa, tail);
        if (result == 0) break;
        concat(fa, part, tail);
    }
    return result;
}
// �����������
int E(NFA & fa, NFA & part) {
    NFA tail;
    char c = 0;
    int result = T(fa, part);
    while (current() == '+')
    {
        c = getnext();
        tail.clear();
        result = T(fa, tail);
        if (result != 1) break;
        unite(fa, part, tail);
    }
    return result;
}

// ����������� ���������� ��������� � �������� �������
int rex_to_fa(char * rex, NFA & fa) {
    rx = rex;
    NFA part;
    int result = E(fa, part);
    fa = part;
    return result;
}

// ����� ����� � ��������
// �������������� ��������� � �������
int algorithm_rex_to_fa(char * rex, NFA & fa, FILE * target) {
    // ��������
    int result = rex_to_fa(rex, fa);
    // ������� �� � �������
    fa.printi(stdout);
    // ������� �� � ����
    fa.printi(target);
    // ���������
    return result;
}
