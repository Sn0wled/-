// 2018 ReVoL Primer Template
// 14-fainv.cpp (�������������� ��������)
#include "stdafx.h"
#include "grammar.h"
#include "main.h"
// ��������� ������
// a13e -fainv -dfa -fainv -dfa

// �������� �������
void fa_invert(NFA & fa) {
    for (int i = 1; i <= fa.delta_count(); i++) {
        TRAN& t = fa[i];
        SYMB tmp = t.a;
        t.a = t.b;
        t.b = tmp;
    }
    SSET tmp = fa.initials;
    fa.initials = fa.finals;
    fa.finals = tmp;
}

// ����� ����� � ��������
// �������������� ��������
int algorithm_fa_invert(NFA & fa, FILE * target) {
    // ��������
    fa_invert(fa);
    // ������� �� � �������
    fa.printn(stdout);
    // ������� �� � ����
    fa.printn(target);
    return 1;
}
