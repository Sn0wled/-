// 2019 ReVoL Primer Template
// types.h
// типы

// максимальная длина ид
#define MAX_ID 7
// максимальная длина лексемы
#define MAX_QUOTE 31

// тип данных стека
typedef signed short stack_t;

// типы данных элементов программы
typedef enum stdtyp : stack_t { STDT_NULL = VT_NULL, STDT_I4 = VT_I4, STDT_R8 = VT_R8 } _stdtyp;

// символы грамматики и транслятора
typedef enum sttype : stack_t {
    OUT_START = 997,
    TOK_COMMENT,
    TOK_UNKNOWN,

    // токены
    TOK_EOT = 0,
    TOK_LF,
    TOK_DIM,
    TOK_ID,
    TOK_AS,
    TOK_LONG,
    TOK_EQ,
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_END,
    TOK_PRINT,
    TOK_NE,
    TOK_LT,
    TOK_GT,
    TOK_ADD,
    TOK_SUB,
    TOK_MUL,
    TOK_DIV,
    TOK_I4,
    TOK_LP,
    TOK_RP,
    TOK_LAST = TOK_RP,
    // нетерминалы
    SYM_M,
    SYM_S,
    SYM_E,
    SYM_A,
    SYM_R,
    SYM_R_,
    SYM_T,
    SYM_T_,
    SYM_P,
    SYM_P_,
    SYM_LAST = SYM_P_,
    // конец символов грамматики


    // символы генератора кода
    OUT_ID,
    OUT_I4,
    OUT_LABEL,
    OUT_DEFL,
    OUT_PUSH,
    OUT_POPL,
    OUT_SWAP,
    OUT_LONG,
    OUT_BZ,
    OUT_BR,
    OUT_DIM,
    OUT_ASS,
    OUT_ADD,
    OUT_SUB,
    OUT_MUL,
    OUT_DIV,
    OUT_EQ,
    OUT_NE,
    OUT_LT,
    OUT_GT,
    OUT_PRINT,
    OUT_END,
    // для тестирования
    OUT_INT,
    OUT_R8,
    OUT_LE,
    OUT_GE,
    TOK_R8,
    TOK_LB,
    TOK_RB,
    TOK_AND,
    TOK_OR,
    TOK_NOT,
    TOK_LE,
    TOK_GE,
    TOK_QUOTE,
    TOK_LS,
    TOK_RS,
    TOK_SEMI,
    TOK_COMMA
} _sttype;

// токен
struct sttoken {
    // тип токена
    sttype stt;
    // целочисленное значение
    int int_val;
    // вещественное значение
    double dbl_val;
    // тип данных
    stdtyp data_type;
    // строковое значение
    char str_val[1 + MAX_QUOTE];
    // конструктор
    sttoken() {
        reset();
    }
    // очищает объект
    void reset(void) {
        stt = TOK_EOT;
        int_val = 0;
        dbl_val = 0;
        data_type = STDT_NULL;
        text_reset();
    }
    // очищает строковое представление
    void text_reset(void) {
        for (int i = 0; i <= MAX_QUOTE; i++) str_val[i] = 0;
    }
    // добавляет символ
    int append(char c) {
        int len = strlen(str_val);
        if (len < MAX_QUOTE) {
            str_val[len] = c;
            return 1;
        }
        return 0;
    }
};

// шаблон стека
template <class T, int N>
class ststack {
    // массив элементов
    T st[N];
    // счетчик
    int count;
    // глубина
    int depth;
public:
    // конструктор
    ststack() {
        reset();
    }
    // деструктор
    ~ststack() {
        printf("ststack: size=%d, depth=%d.\n", N, depth);
    }
    // очищает объект
    void reset(void) {
        depth = count = 0;
        for (int i = 0; i < N; i++) st[i] = 0;
    }
    // возвращает количество элементов
    int size(void) {
        return count;
    }
    // проталкивает элемент
    void push(T value) {
        if (count >= N) throw "ststack::push stack overflow";
        st[count++] = value;
        if (depth < count) depth = count;
    }
    // выталкивает элемент
    T pop(void) {
        if (count < 1) throw "ststack::pop stack is empty";
        T value = st[--count];
        st[count] = 0;
        return value;
    }
    // выталкивает number элементов
    T pop(int number) {
        if (count < number) throw "ststack::pop(int) stack isn't so big as number";
        count -= number;
        return st[count];
    }
    // возвращает элемент на вершине
    T top(void) {
        if (count < 1) throw "ststack::top stack is empty";
        return st[count - 1];
    }
};
