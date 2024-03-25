// 2019 ReVoL Primer Template
// sa5LLT.h
// синтаксический анализатор

#include "syntallo.h"
#include "stsyms.h"
#include "ststrip.h"
// размер стека МП-автомата
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

class syntaxan {
public:
    // конструктор
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // LL(1) трансляция в ПОЛИЗ
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
    // возвращает очередной токен
    int next_token() {
        return lex->next_token(tok);
    }
};
