// 2019 ReVoL Primer Template
// sa4LR.h
// �������������� ����������

#include "syntalr.h"
// ������ ����� ��-��������
#define MAX_STACK 64

class syntaxan {
public:
    // �����������
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // LR(1)
    int parse(void) {
        if (!next_token()) return 0;
        stack_t input_tok;
        stack_t stack_top;
        stack_t table_result;
        sta.push(0);
        while (true)
        {
            input_tok = tok.stt;
            stack_top = sta.top();
            table_result = SYNTA[stack_top][input_tok];
            if (table_result == ACC) break;
            else if (table_result < 0) {
                pop_n(RLEN[-table_result]);
                printf("%d", table_result);
                sta.push(SYNTA[sta.top()][RSYM[-table_result]]);
            }
            else if (table_result > 0 && table_result <= MAX_DFA_STATE) {
                sta.push(table_result);
                next_token();
            }
            else {
                throw "error";
            }
        }

        fprintf(parse_stream, "\nsyntaxan: success\n\n");
        return 1;
    }
private:
    // ������ �� ����������� ����������
    lexan * lex;
    // ����� ����������
    FILE * parse_stream;
    // ����� ���������
    FILE * error_stream;
    // ������� �����
    sttoken tok;
    // ���� ��-��������
    ststack<stack_t, MAX_STACK> sta;
    // ���������� ��������� �����
    int next_token() {
        return lex->next_token(tok);
    }
    void pop_n(int n) {
        for (int i = 0; i < n; i++) {
            sta.pop();
        }
    }
};
