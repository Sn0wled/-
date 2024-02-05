// 2018 ReVoL Primer Template
// 11-faau.cpp (�������������� �������� � ����������)
#include "stdafx.h"
#include "grammar.h"
// ��������� ������
// a11 -faau

// ���������� ������� �������� �� ���������� ���������
int has_tran_from_final(SYMB A, NFA& fa) {
	int dc = fa.delta_count();
	for (int i = 1; i <= dc; i++) {
		if (fa[i].a == A) return 1;
	}
	return 0;
}

// ����������� ������� � ����������
void fa_to_grau(NFA& fa, grammar& gr) {
	gr.set_start(gr.reg_from(fa, fa.initials[1]));
	RULE rule;
	TRAN tran;
	int dc = fa.delta_count();
	for (int i = 1; i <= dc; i++) {
		rule.clear();
		tran = fa[i];
		rule[0] = gr.reg_from(fa, tran.a);
		rule.append(gr.reg_char(tran.c));
		if (fa.finals.contains(tran.b)) {
			gr.rule_add(rule);
			if (has_tran_from_final(tran.b, fa)) {
				rule.append(gr.reg_from(fa, tran.b));
				gr.rule_add(rule);
			}
		}
		else {
			rule.append(gr.reg_from(fa, tran.b));
			gr.rule_add(rule);
		}
		/*if (!fa.finals.contains(tran.b) || has_tran_from_final(tran.b, fa)) {
			gr.rule_add(rule);
			rule.append(gr.reg_from(fa, tran.b));
		}
		gr.rule_add(rule);*/
	}
}

// ����� ����� � ��������
// �������������� �������� � ����������
int algorithm_fa_to_grau(NFA& fa, grammar& gr, FILE* target) {
	// ��������
	fa_to_grau(fa, gr);
	// ������� ���������� � �������
	gr.print(stdout);
	// ������� ���������� � ����
	gr.print(target);
	// ���������
	return 1;
}
/*/
.a11.sxg
{A}
(A,a)={B}
(B,b)={E}
(E,d)={F}
(E,c)={B}
{E,F}
/*/
