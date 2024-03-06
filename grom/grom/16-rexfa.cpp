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
char getnext() {
    char c = rx[index];
    if (c != 10) index++;
    return c;
}
// ��������� �������
void primary(NFA & fa, NFA & part, char c) {
}
// ��������
void iteration(NFA & fa, NFA & part) {
}
// ������������
void concat(NFA & fa, NFA & part, NFA & tail) {
}
// �����������
void unite(NFA & fa, NFA & part, NFA & tail) {
}
// ������� ���������
int P(NFA & fa, NFA & part) {
    char c = getnext();
    int result;
    if (c == 10) {
        return 10;
    }
    else if (c == '(') {
        // ��������� � �������
        result = E(fa, part);
        if (result != 1) return result;
    }
    else if (c == '1') {
        // ���������
    }
    else if (c > 122) {
        // ������������ ����
    }
    else if (c > 96) {
        // ����������
    }
    return 0;
}
// ������� ��������
int U(NFA & fa, NFA & part) {
    char c = 0;
    int result = T(fa, part);
    return 1;
}
// ������������
int T(NFA & fa, NFA & part) {
    NFA tail;
    char c = 0;
    int result = T(fa, part);
    return 1;
}
// �����������
int E(NFA & fa, NFA & part) {
    NFA tail;
    char c = 0;
    int result = T(fa, part);
    return 1;
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
