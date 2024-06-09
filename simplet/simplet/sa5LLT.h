// 2019 ReVoL Primer Template
// sa5LLT.h
// синтаксический анализатор

#include "syntallo.h"
#include "stsyms.h"
#include "ststrip.h"
#include <map>
#include <string>
#include <stack>
// размер стека ћѕ-автомата
#define MAX_STACK 64
// размер вычислительного стека
#define MAX_EXEST 64
// размер таблицы символов
#define MAX_SYMS 16
// размер стека меток
#define MAX_LABEL 16
// размер ленты
#define MAX_STRIP 64
// предел числа итераций
#define MAX_IT 999
//#include "syntallo.h"

class syntaxan {
public:
	// конструктор
	syntaxan(lexan* lex, FILE* parse_stream, FILE* error_stream) {
		this->lex = lex;
		this->parse_stream = parse_stream;
		this->error_stream = error_stream;
	}
	// LL(1) трансл€ци€ в ѕќЋ»«
	int parse(void) {
		if (!next_token()) return 0;
		int i, n;
		stack_t at = TOK_EOT, bt = TOK_EOT;
		stack_t s = TOK_EOT;
		stack_t t = TOK_EOT;
		get_rule_len();
		sta.push(TOK_EOT);
		sta.push(START);
		for (;;) {
			s = clear_stack();
			t = SYNTA[s][tok.stt];
			// если t <= 0 - ошибка
			// иначе если t == ACC, это допуск
			// иначе если t == POP, это выброс
			// иначе, если t <= MAX_RULE, это правило
			// иначе это ошибка управл€ющей таблицы
			if (t == ACC) {
				break;
			}
			else if (t == POP) {
				at = sta.pop();
				//fprintf(parse_stream, "\npop %d ", at);
				clear_stack();
				if (!next_token()) return 0;
			}
			else if (t <= 0) {
				fprintf(parse_stream, "\nsyntaxan: failure synta = %d\n\n", t);
				return 0;
			}
			else if (t <= MAX_RULE) {
				at = sta.pop();
				n = RLEN[t];
				//fprintf(parse_stream, "\n%d -> ", at);
				std::stack<int> st;
				for (i = n - 1; i >= 0; i--) {
					bt = RULE[t][i];
					sta.push(bt);
					st.push(bt);
					//fprintf(parse_stream, "%d ", bt);
				}
				/*while (!st.empty())
				{
					fprintf(parse_stream, "%d ", st.top());
					st.pop();
				}*/
			}
			else {
				throw "syntaxan: invalid SYNTA";
			}
		}
		out(OUT_END);
		strip.print(parse_stream);
		execute();
		fprintf(parse_stream, "\nsyntaxan: success.\n\n");
		return 1;
	}
private:
	ststack<stack_t, MAX_STACK> sta;
	// ссылка на лексический анализатор
	lexan* lex;
	// поток результата
	FILE* parse_stream;
	// поток сообщений
	FILE* error_stream;
	// текущий токен
	sttoken tok;
	// таблица символов
	stsyms<MAX_SYMS> syms;
	// исполн€ющий стек
	exstack<MAX_EXEST> exe;
	// лента полиз
	ststrip<MAX_STRIP> strip;
	// стек меток
	ststack<int, MAX_LABEL> stl;

	// возвращает очередной токен
	int next_token() {
		int r = lex->next_token(tok);
		//fprintf(parse_stream, "\nget %s", tok.str_val);
		return r;
	}
	void out(sttype tt) {
		int i = 0, j = 0;
		sttoken t = tok;
		t.stt = tt;
		switch (tt) {
		case OUT_PUSH:
			j = strip.new_label();
			stl.push(j);
			t.int_val = j;
			t.stt = OUT_LABEL;
			break;
		case OUT_POPL:
			j = stl.pop();
			t.stt = OUT_LABEL;
			t.int_val = j;
			break;
		case OUT_SWAP:
			i = stl.pop();
			j = stl.pop();
			stl.push(i);
			t.int_val = j;
			t.stt = OUT_LABEL;
		}
		strip.add(t);
	}
	stack_t clear_stack() {
		stack_t s;
		while ((s = sta.top()) > SYM_LAST) {
			s = sta.pop();
			out((sttype)s);
		}
		return s;
	}

	void execute() {
		int strip_pointer = 1;
		sttype stt;
		exstel X, Y;
		int j;
		int it_counter = 1;
		while (true)
		{
			X.reset();
			Y.reset();
			stt = strip[strip_pointer].stt;
			switch (stt)
			{
			case OUT_ID:
			case OUT_I4:
			case OUT_LONG:
				exe.push(strip[strip_pointer++]);
				break;
			case OUT_LABEL:
				X.int_val = strip[strip_pointer++].int_val;
				X.stt = OUT_I4;
				exe.push(X);
				break;
			case OUT_DEFL:
				exe.pop(X);
				strip_pointer++;
				break;
			case OUT_PUSH:
				break;
			case OUT_POPL:
				break;
			case OUT_SWAP:
				break;
			case OUT_BZ:
				exe_pop(Y);
				exe_pop(X);
				if (X.int_val == 0) {
					j = strip.find_DEF(Y.int_val);
					if (j == -1) throw "exe label not found";
					strip_pointer = j;
				}
				else {
					strip_pointer++;
				}
				break;
			case OUT_BR:
				exe_pop(Y);
				j = strip.find_DEF(Y.int_val);
				if (j == -1) throw "exe label not found";
				strip_pointer = j;
				break;
			case OUT_DIM:
				exe.pop(Y);
				exe.pop(X);	
				X.data_type = Y.data_type;
				j = syms.insert(X);
				if (j == ST_EXISTS) throw "exe duplicate declaration";
				strip_pointer++;
				break;
			case OUT_ASS:
				exe_pop(X);
				exe.pop(Y);
				j = syms.find(Y);
				if (j == ST_NOTFOUND) throw "exe identifier not found";
				syms[j].int_val = X.int_val;
				strip_pointer++;
				break;
			case OUT_ADD:
			case OUT_SUB:
			case OUT_MUL:
			case OUT_DIV:
			case OUT_EQ:
			case OUT_NE:
			case OUT_LT:
			case OUT_GT:
				exe_pop(Y);
				exe_pop(X);
				switch (stt)
				{
					case OUT_ADD:
						X.int_val += Y.int_val;
						break;
					case OUT_SUB:
						X.int_val -= Y.int_val;
						break;
					case OUT_MUL:
						X.int_val *= Y.int_val;
					case OUT_DIV:
						if (Y.int_val == 0) throw "exe division by zero";
						X.int_val /= Y.int_val;
						break;
					case OUT_EQ:
						X.int_val = X.int_val == Y.int_val;
						break;
					case OUT_NE:
						X.int_val = X.int_val != Y.int_val;
						break;
					case OUT_LT:
						X.int_val = X.int_val < Y.int_val;
						break;
					case OUT_GT:
						X.int_val = X.int_val > Y.int_val;
						break;
				
				}
				exe.push(X);
				strip_pointer++;
				break;
			case OUT_PRINT:
				exe_pop(Y);
				fprintf(parse_stream, "exe print %d\n", Y.int_val);
				strip_pointer++;
				break;
			case OUT_END:
				fprintf(error_stream, "exe done\n\n");
				return;
			case OUT_INT:
				break;
			case OUT_R8:
				break;
			case OUT_LE:
				break;
			case OUT_GE:
				break;
			}
			if (++it_counter > MAX_IT) throw "exe deadlock";
		}
	}
	void exe_pop(exstel& e) {
		exe.pop(e);
		if (e.stt == OUT_I4) {

		}
		else if (e.stt == OUT_ID) {
			int j = syms.find(e);
			if (j == ST_NOTFOUND) throw "exe_pop identifier not found";
			e.int_val = syms[j].int_val;
			e.stt = OUT_I4;
		}
		else {
			// неправильна€ лента ѕќЋ»« 
			throw "exe_pop internal error";
		}
	}
};