// 2019 ReVoL Primer Template
// lexan.h
// лексический анализатор

#include "sttot.h"

class lexan {
    // входной поток
    FILE * input_stream;
    // поток сообщений
    FILE * error_stream;
    // текущий символ входа
    char cc;
    // возвращает очередной символ входа
    void next_char(void) {
        cc = getc(input_stream);
        //_putch(cc);
    }
    // разбирает комментарий —и
    sttype is_comment() {
        enum {A, B, C} state = A;
        while (true)
        {
            next_char();
            switch (state)
            {
            case A:
                switch (cc)
                {
                case EOF:
                    fprintf(error_stream, "\nlexan: unexpected end of file in comment\n\n");
                    return TOK_UNKNOWN;
                case '*':
                    state = B;
                    break;
                default:
                    return TOK_DIV;
                }
                break;
            case B:
                switch (cc)
                {
                case EOF:
                    fprintf(error_stream, "\nlexan: unexpected end of file in comment\n\n");
                    return TOK_UNKNOWN;
                case '*':
                    state = C;
                    break;
                default:
                    break;
                }
                break;
            case C:
                switch (cc)
                {
                case EOF:
                    fprintf(error_stream, "\nlexan: unexpected end of file in comment\n\n");
                    return TOK_UNKNOWN;
                case '*':
                    break;
                case '/':
                    return TOK_COMMENT;
                default:
                    state = B;
                    break;
                }
                break;
            default:
                break;
            }
        }
        return TOK_UNKNOWN;
    }
    // принимает идентификатор
    int get_id(sttoken & tok) {
        tok.stt = TOK_ID;
        int counter = 0;
        while (true)
        {
            switch (TOT[cc])
            {
            case ALPHA:
            case DIGIT:
                if (counter < MAX_ID) {
                    tok.append(cc);
                    counter++;
                    break;
                }
            default:
                return is_keyword(tok);
            }
            next_char();
        }
        return 1;
    }
    // определ€ет ключевое слово
    int is_keyword(sttoken & tok) {
        if (!strcmp(tok.str_val, "print")) {
            tok.stt = TOK_PRINT;
            return 1;
        }
        if (!strcmp(tok.str_val, "if")) {
            tok.stt = TOK_IF;
            return 1;
        }
        if (!strcmp(tok.str_val, "then")) {
            tok.stt = TOK_THEN;
            return 1;
        }
        if (!strcmp(tok.str_val, "end")) {
            tok.stt = TOK_END;
            return 1;
        }
        if (!strcmp(tok.str_val, "else")) {
            tok.stt = TOK_ELSE;
            return 1;
        }
        return 1;
    }
    // принимает целое число
    int is_number(sttoken & tok) {
        tok.stt = TOK_I4;
        while (true)
        {
            switch (TOT[cc])
            {
            case DIGIT:
                break;
            case CHDOT:
                return is_float(tok, 0);
            default:
                return 1;
            }
            next_char();
        }
        return 1;
    }
    // разбирает вещественную часть числа
    int is_float(sttoken & tok, int must) {
        tok.stt = TOK_R8;
        while (true) {
            next_char();
            switch (TOT[cc])
            {
            case CHDOT:
                fprintf(error_stream, "\nlexan: extra dot in float\n\n");
                return 0;
            case DIGIT:
                must = 0;
                break;
            default:
                if (must == 1) {
                    fprintf(error_stream, "\nlexan: single dot in float\n\n");
                }
                return 1;
            }
        }
        return 1;
    }
    // разбирает строковый литерал
    int is_quote(sttoken & tok) {
        tok.stt = TOK_QUOTE;
        while (true)
        {
            next_char();
            if (TOT[cc] == QUOTE) {
                next_char();
                if (TOT[cc] != QUOTE) {
                    return 1;
                }
                tok.append(cc);
            }
            else if (cc == EOF) {
                fprintf(error_stream, "\nlexan: unexpected end of file in quote\n\n");
                return 0;
            }
            else if (cc < 32) {
                fprintf(error_stream, "\nlexan: extra character in quote\n\n");
                return 0;
            }
            else {
                tok.append(cc);
            }
        }
        return 1;
    }
    // принимает операцию
    int is_opera(sttoken & tok) {
        switch (cc)
        {
        case '+':
            tok.stt = TOK_ADD;
            next_char();
            return 1;
        case '-':
            tok.stt = TOK_SUB;
            next_char();
            return 1;
        case '*':
            tok.stt = TOK_MUL;
            next_char();
            return 1;
        case '=':
            tok.stt = TOK_ASS;
            next_char();
            if (cc == '=') {
                tok.stt = TOK_EQ;
                next_char();
            }
            return 1;
        case '!':
            tok.stt = TOK_NOT;
            next_char();
            if (cc == '=') {
                tok.stt = TOK_NE;
                next_char();
            }
            return 1;
        case '<':
            tok.stt = TOK_LT;
            next_char();
            if (cc == '=') {
                tok.stt = TOK_LE;
                next_char();
            }
            return 1;
        case '>':
            tok.stt = TOK_GT;
            next_char();
            if (cc == '=') {
                tok.stt = TOK_GE;
                next_char();
            }
            return 1;
        case '(':
            tok.stt = TOK_LP;
            next_char();
            return 1;
        case ')':
            tok.stt = TOK_RP;
            next_char();
            return 1;
        case '{':
            tok.stt = TOK_LS;
            next_char();
            return 1;
        case '}':
            tok.stt = TOK_RS;
            next_char();
            return 1;
        case '[':
            tok.stt = TOK_LB;
            next_char();
            return 1;
        case ']':
            tok.stt = TOK_RB;
            next_char();
            return 1;
        case '&':
            next_char();
            if (cc == '&') {
                next_char();
                tok.stt = TOK_AND;
                return 1;
            }
            return 0;
        case '|':
            next_char();
            if (cc == '|') {
                next_char();
                tok.stt = TOK_OR;
                return 1;
            }
            return 0;
        default:
            printf("%c", cc);
            break;
        }
        return 0;
    }
public:
    // возвращает очередной токен потока
    int next_token(sttoken & tok) {
        // ищем первый символ лексемы
        while (1) {
            if (cc == EOF) {
                // конец текста
                tok.stt = TOK_EOT;
                return 1;
            } else if (cc == 10) {
                // строку подсчитываем
                /*/
                // если в €зыке есть токен LF
                tok.stt = TOK_LF;
                next_char();
                return 1;
                /*/
            } else if (cc == '/') {
                // слэш неоднозначен в —и
                sttype result = is_comment();
                if (result == TOK_DIV) {
                    // это операци€ делени€, а не comment
                    tok.stt = TOK_DIV;
                    return 1;
                } else if (result == TOK_UNKNOWN) {
                    // ошибка в комментарии
                    return 0;
                }
                // comment пропускаем
            } else if (cc < 33) {
                // управл€ющие символы и пробел пропускаем
            } else {
                // другой символ разбираем дальше
                break;
            }
            // следующий символ
            next_char();
        }
        // подготавливаем токен
        tok.reset();
        // разбираем первый символ лексемы
        switch (TOT[cc]) {
        case ALPHA:
            return get_id(tok);
        case DIGIT:
            return is_number(tok);
        case CHDOT:
            return is_float(tok, 1);
        case QUOTE:
            return is_quote(tok);
        default:
            return is_opera(tok);
        }
        return 0;
    }
    // конструктор
    lexan(FILE * input_stream, FILE * error_stream) {
        this->input_stream = input_stream;
        this->error_stream = error_stream;
        // первый символ потока
        next_char();
    }
};
