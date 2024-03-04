// 2018 ReVoL Primer Template
// 13-dfa.cpp (преобразование НКА в ДКА)
#include "stdafx.h"
#include "grammar.h"
// командные строки
// a13a -dfa
// a13e -dfa
// a13b -dfa

// исследованные состояния
SSET inspected;

// вычисляет замыкание A состояния НКА state
void closure(SYMB state, SSET& A, NFA& fa1) {
}

// вычисляет замыкание A состояния ДКА A
void closureA(SSET& A, NFA& fa1) {
}

// вычисляет 2^(n-1)
int power2n(int n) {
	if (n > 31) throw "power2n: too many states found";
	int m = 1;
	m <<= (n - 1);
	return m;
}

// вычисляет идентификатор состояния ДКА, регистрирует его
// регистрирует финальное состояние, если есть
int reg_state(SSET& A, NFA& fa1, NFA& fa2) {
	char buf[16] = {};
	int number = 0;
	int final = 0;
	SYMB regstate;
	for (int i = 1; i <= A.count(); i++) {
		int s_id = A[i];
		number += power2n(s_id);
		if (fa1.finals.contains(s_id)) final = 1;
	}
	sprintf(buf, "%d", number);
	regstate = fa2.reg_state_id(buf);
	if (final) fa2.finals.insert(regstate);
	return regstate;
}

// ищет другие состояния
// A - состояние ДКА - множество состояний НКА
// initial - признак начального состояния
int follow_dfa_state(SSET A, NFA fa1, NFA& fa2, int initial = 0) {
	SYMB state_a = 0, state_b = 0;
	state_a = reg_state(A, fa1, fa2);
	inspected.insert(state_a);
	if (initial) fa2.initials.insert(state_a);
	SSET T, C;
	for (int t = 1; t <= fa1.delta_count(); t++) {
		TRAN tran = fa1[t];
		if (A.contains(tran.a)) {
			T.insert(t);
			C.insert(tran.c);
		}
	}
	for (int c = 1; c <= C.count(); c++) {
		SSET B;
		char sym = C[c];
		for (int t = 1; t <= T.count(); t++) {
			TRAN tran = fa1[T[t]];
			if (tran.c == sym) B.insert(tran.b);
		}
		state_b = reg_state(B, fa1, fa2);
		TRAN tran;
		tran.a = state_a;
		tran.b = state_b;
		tran.c = sym;
		fa2.tran_add(tran);
		if (!inspected.contains(state_b)) follow_dfa_state(B, fa1, fa2);
	}
	return 1;
}

// преобразует НКА в ДКА
int nfa_to_dfa(NFA& fa1, NFA& fa2) {
	inspected.clear();
	return follow_dfa_state(fa1.initials, fa1, fa2, 1);
}

// точка входа в алгоритм
// преобразование НКА в ДКА
int algorithm_dfa(NFA& fa1, FILE* target) {
	// выходной КА
	NFA fa2;
	// алгоритм
	int result = nfa_to_dfa(fa1, fa2);
	// выводим КА в консоль
	fa2.printn(stdout);
	// выводим КА в файл
	fa2.printn(target);
	// выходной КА
	fa1 = fa2;
	// результат
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
