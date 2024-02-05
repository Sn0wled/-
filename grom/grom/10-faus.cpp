// 2018 ReVoL Primer Template
// 10-faus.cpp (���������� ������������ ��������� ��������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// a13a -faus
// a10 -faus

// ��������������� �������� � ���������
void fa_general(NFA & fa) {
    SYMB A = fa.reg_state_id("A");
    SYMB B = fa.reg_state_id("B");
    SYMB C = fa.reg_state_id("C");
    SYMB D = fa.reg_state_id("D");
    SYMB E = fa.reg_state_id("E");
    SYMB F = fa.reg_state_id("F");
    SYMB G = fa.reg_state_id("G");
    TRAN tran;
    tran.a = A;
    tran.b = B;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = A;
    tran.b = B;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = A;
    tran.b = C;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = B;
    tran.b = D;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = C;
    tran.b = E;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = D;
    tran.b = C;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = D;
    tran.b = E;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = E;
    tran.b = B;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = E;
    tran.b = D;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = F;
    tran.b = D;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = G;
    tran.b = F;
    tran.c = '0';
    fa.tran_add(tran);

    tran.a = G;
    tran.b = E;
    tran.c = '1';
    fa.tran_add(tran);

    tran.a = G;
    tran.b = F;
    tran.c = '1';
    fa.tran_add(tran);

    fa.initials.insert(A);
    fa.finals.insert(D);
    fa.finals.insert(E);
}

// ���������� ������������ ��������� ��������� ��������
void fa_remove_unreachable(NFA & fa1, NFA & fa2) {
    //fa_general(fa2);
    SSET r = fa1.initials;
    for (int i = 1; i <= r.count(); i++) {
        fa2.reg_initial_from(fa1, r[i]);
    }
    while (true)
    {
        int startCount = r.count();
        for (int i = 1; i <= fa1.delta_count(); i++) {
            if (r.contains(fa1[i].a)) r.insert(fa1[i].b);
        }
        if (startCount == r.count()) break;
    }
    for (int i = 1; i <= fa1.finals.count(); i++) {
        if (r.contains(fa1.finals[i])) fa2.reg_final_from(fa1, fa1.finals[i]);
    }
    for (int i = 1; i <= fa1.delta_count(); i++) {
        if (r.contains(fa1[i].b) && r.contains(fa1[i].a)) fa2.tran_add_from(fa1, fa1[i]);
    }
}

// ����� ����� � ��������
// ���������� ������������ ��������� ��
int algorithm_fa_remove_unreachable(NFA & fa1, FILE * target) {
    // �������� ��
    NFA fa2;
    // ��������
    fa_remove_unreachable(fa1, fa2);
    // ������� �� � �������
    fa2.printi(stdout);
    // ������� �� � ����
    fa2.printi(target);
    // �������������� ��
    fa1 = fa2;
    // ���������
    return 1;
}
/*/
.a13b.sxg
{A}
(A,a)={A}
(A,b)={B}
(B,a)={A}
(B,a)={S}
{S}
/*/
