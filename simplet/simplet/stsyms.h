// 2019 ReVoL Primer Template
// stsyms.h
// таблица символов

// признак присутствия
#define ST_EXISTS -2
// признак отсутствия
#define ST_NOTFOUND -3

// символ таблицы символов
typedef sttoken stsym;

// таблица символов
template <int N>
class stsyms {
private:
    // таблица символов
    stsym st[N];
    // счетчик
    int count;
    // глубина
    int depth;
public:
    // конструктор
    stsyms() {
        count = 1;
        depth = 0;
        st[0].stt = TOK_EOT;
        st[0].str_val[0] = '$';
    }
    // деструктор
    ~stsyms() {
        printf("stsyms: size=%d, depth=%d.\n", N, depth - 1);
    }
    // возвращает количество элементов
    int size(void) {
        return count - 1;
    }
    // возвращает номер символа в таблице
    int find(stsym tok) {
        for (int i = 1; i < count; i++) {
            if (strcmp(tok.str_val, st[i].str_val) == 0) {
                return i;
            }
        }
        return ST_NOTFOUND;
    }
    // вставляет символ в таблицу
    int insert(stsym tok) {
        if (count >= N) throw "stsyms::insert table overflow";
        if (find(tok) == ST_NOTFOUND) {
            st[count++] = tok;
            if (depth < count) depth = count;
            return count;
        } else {
            return ST_EXISTS;
        }
    }
    // возвращает символ
    stsym & operator [] (int index) {
        if (index < 0 || index >= count) throw "stsyms::operator[] invalid index";
        return st[index];
    }
};
