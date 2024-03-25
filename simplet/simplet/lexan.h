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
        return TOK_UNKNOWN;
    }
    // принимает идентификатор
    int get_id(sttoken & tok) {
        return 1;
    }
    // определ€ет ключевое слово
    int is_keyword(sttoken & tok) {
        return 1;
    }
    // принимает целое число
    int is_number(sttoken & tok) {
        return 1;
    }
    // разбирает вещественную часть числа
    int is_float(sttoken & tok, int must) {
        return 1;
    }
    // разбирает строковый литерал
    int is_quote(sttoken & tok) {
        return 1;
    }
    // принимает операцию
    int is_opera(sttoken & tok) {
        return 1;
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
