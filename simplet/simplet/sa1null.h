// 2019 ReVoL Primer Template
// sa1null.h
// синтаксический анализатор

class syntaxan {
public:
    // конструктор
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // формирует поток токенов
    int parse(void) {
        while (1) {
            if (!next_token()) return 0;
            print_tok(tok);
            if (tok.stt == TOK_EOT) break;
        }
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
    // выводит токен в выходной поток токенов
    void print_tok(sttoken tok) {
        switch (tok.stt) {
        case TOK_EOT:   fprintf(parse_stream, "EOT\n"); break;
        case TOK_LF:    fprintf(parse_stream, "LF\n"); break;
        case TOK_QUOTE: fprintf(parse_stream, "QUOTE %s\n", tok.str_val); break;
        case TOK_ID:    fprintf(parse_stream, "ID %s\n", tok.str_val); break;
        case TOK_I4:    fprintf(parse_stream, "I4 %d\n", tok.int_val); break;
        case TOK_R8:    fprintf(parse_stream, "R8 %g\n", tok.dbl_val); break;
        case TOK_COMMA: fprintf(parse_stream, ",\n"); break;
        case TOK_ADD:   fprintf(parse_stream, "+\n"); break;
        case TOK_SUB:   fprintf(parse_stream, "-\n"); break;
        case TOK_MUL:   fprintf(parse_stream, "*\n"); break;
        case TOK_DIV:   fprintf(parse_stream, "/\n"); break;
        case TOK_ASS:   fprintf(parse_stream, "==\n"); break;
        case TOK_EQ:    fprintf(parse_stream, "=\n"); break;
        case TOK_NE:    fprintf(parse_stream, "!=\n"); break;
        case TOK_LT:    fprintf(parse_stream, "<\n"); break;
        case TOK_LE:    fprintf(parse_stream, "<=\n"); break;
        case TOK_GT:    fprintf(parse_stream, ">\n"); break;
        case TOK_GE:    fprintf(parse_stream, ">=\n"); break;
        case TOK_LP:    fprintf(parse_stream, "(\n"); break;
        case TOK_RP:    fprintf(parse_stream, ")\n"); break;
        case TOK_LS:    fprintf(parse_stream, "{\n"); break;
        case TOK_RS:    fprintf(parse_stream, "}\n"); break;
        case TOK_LB:    fprintf(parse_stream, "[\n"); break;
        case TOK_RB:    fprintf(parse_stream, "]\n"); break;
        case TOK_AND:   fprintf(parse_stream, "&&\n"); break;
        case TOK_OR:    fprintf(parse_stream, "||\n"); break;
        case TOK_NOT:   fprintf(parse_stream, "!\n"); break;
        case TOK_PRINT: fprintf(parse_stream, "PRINT\n"); break;
        case TOK_LONG:  fprintf(parse_stream, "LONG\n"); break;
        case TOK_IF:    fprintf(parse_stream, "IF\n"); break;
        case TOK_THEN:  fprintf(parse_stream, "THEN\n"); break;
        case TOK_END:   fprintf(parse_stream, "END\n"); break;
        case TOK_ELSE:  fprintf(parse_stream, "ELSE\n"); break;
        case TOK_DIM:   fprintf(parse_stream, "DIM\n"); break;
        default:        fprintf(parse_stream, "Unknown\n");
        }
    }
};
