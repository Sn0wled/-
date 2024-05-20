// 2019 ReVoL Primer Template
// sa3LL.h
// синтаксический анализатор

#include "syntall.h"
// размер стека ћѕ-автомата
#define MAX_STACK 64

class syntaxan {
public:
    // конструктор
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // LL(1)
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
            s = sta.top();
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
                if (!next_token()) return 0;
            }
            else if (t <= 0) {
                fprintf(parse_stream, "\nsyntaxan: failure synta = %d\n\n", t);
                return 0;
            }
            else if (t <= MAX_RULE) {
                at = sta.pop();
                n = RLEN[t];
                for ( i = n - 1; i >= 0 ; i--) {
                    bt = RULE[t][i];
                    sta.push(bt);
                }
            }
            else {
                throw "syntaxan: invalid SYNTA";
            }
        }

        fprintf(parse_stream, "\nsyntaxan: success.\n\n");
        return 1;
    }
private:
    // ссылка на лексический анализатор
    lexan * lex;
    // поток результата
    FILE * parse_stream;
    // поток сообщений
    FILE * error_stream;
    // текущий токен
    sttoken tok;
    // стек ћѕ-автомата
    ststack<stack_t, MAX_STACK> sta;
    // возвращает очередной токен
    int next_token() {
        return lex->next_token(tok);
    }
};
