// 2019 ReVoL Primer Template
// lexan.h
// ����������� ����������

#include "sttot.h"

class lexan {
    // ������� �����
    FILE * input_stream;
    // ����� ���������
    FILE * error_stream;
    // ������� ������ �����
    char cc;
    // ���������� ��������� ������ �����
    void next_char(void) {
        cc = getc(input_stream);
        //_putch(cc);
    }
    // ��������� ����������� ��
    sttype is_comment() {
        return TOK_UNKNOWN;
    }
    // ��������� �������������
    int get_id(sttoken & tok) {
        return 1;
    }
    // ���������� �������� �����
    int is_keyword(sttoken & tok) {
        return 1;
    }
    // ��������� ����� �����
    int is_number(sttoken & tok) {
        return 1;
    }
    // ��������� ������������ ����� �����
    int is_float(sttoken & tok, int must) {
        return 1;
    }
    // ��������� ��������� �������
    int is_quote(sttoken & tok) {
        return 1;
    }
    // ��������� ��������
    int is_opera(sttoken & tok) {
        return 1;
    }
public:
    // ���������� ��������� ����� ������
    int next_token(sttoken & tok) {
        // ���� ������ ������ �������
        while (1) {
            if (cc == EOF) {
                // ����� ������
                tok.stt = TOK_EOT;
                return 1;
            } else if (cc == 10) {
                // ������ ������������
                /*/
                // ���� � ����� ���� ����� LF
                tok.stt = TOK_LF;
                next_char();
                return 1;
                /*/
            } else if (cc == '/') {
                // ���� ������������ � ��
                sttype result = is_comment();
                if (result == TOK_DIV) {
                    // ��� �������� �������, � �� comment
                    tok.stt = TOK_DIV;
                    return 1;
                } else if (result == TOK_UNKNOWN) {
                    // ������ � �����������
                    return 0;
                }
                // comment ����������
            } else if (cc < 33) {
                // ����������� ������� � ������ ����������
            } else {
                // ������ ������ ��������� ������
                break;
            }
            // ��������� ������
            next_char();
        }
        // �������������� �����
        tok.reset();
        // ��������� ������ ������ �������
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
    // �����������
    lexan(FILE * input_stream, FILE * error_stream) {
        this->input_stream = input_stream;
        this->error_stream = error_stream;
        // ������ ������ ������
        next_char();
    }
};
