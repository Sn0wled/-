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
};
