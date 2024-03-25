// 2019 ReVoL Primer Template
// sa2RD.h
// синтаксический анализатор

class syntaxan {
public:
    // конструктор
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // рекурсивный спуск
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
