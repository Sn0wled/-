// 2019 ReVoL Primer Template
// sa7LLA.h
// синтаксический анализатор

#include "syntall.h"
#include "stsyms.h"
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
    // атрибутный LL(1)
    int parse(void) {
        if (!next_token()) return 0;


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
