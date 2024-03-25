// 2019 ReVoL Primer Template
// sa2RD.h
// �������������� ����������

class syntaxan {
public:
    // �����������
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // ����������� �����
    int parse(void) {
        if (!next_token()) return 0;
        fprintf(parse_stream, "\nsyntaxan: success.\n\n");
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
    // ���������� ��������� �����
    int next_token() {
        return lex->next_token(tok);
    }
};
