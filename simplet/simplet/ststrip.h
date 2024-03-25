// 2019 ReVoL Primer Template
// ststrip.h
// классы ленты внутреннего представления

// элемент ленты
typedef sttoken exstel;

// лента
template <int N>
class ststrip {
    // массив элементов
    exstel st[N];
    // счетчик элементов
    int count;
    // счетчик меток
    int label;
    // глубина
    int depth;
public:
    // конструктор
    ststrip() {
        reset();
        st[0].stt = OUT_START;
    }
    // деструктор
    ~ststrip() {
        printf("ststrip: size=%d, depth=%d.\n", N, depth - 1);
    }
    // очищает объект
    void reset(void) {
        count = 1;
        depth = label = 0;
        for (int i = 0; i < N; i++) st[i].reset();
    }
    // возвращает количество элементов
    int size(void) {
        return count - 1;
    }
    // возвращает новый идентификатор метки
    int new_label() {
        return ++label;
    }
    // возвращает указанный элемент
    exstel & operator [] (int index) {
        if (index < 1 || index >= count) throw "ststrip::operator[] invalid index";
        return st[index];
    }
    // добавляет элемент
    void add(exstel e) {
        if (count >= N) throw "ststrip::add strip overflow";
        st[count++] = e;
        if (depth < count) depth = count;
    }
    // ищет на ленте определение метки с идентификатором id
    int find_DEF(int id) {
        for (int i = 1; i < count; i++) {
            if (st[i].stt == OUT_END) return -1; // конец ленты
            if (st[i].stt == OUT_LABEL && st[i].int_val == id) {
                if (st[i + 1].stt == OUT_DEFL) {
                    return (i + 2);
                }
            }
        }
        return -1;
    }
    // вывод в текстовый файл
    void print(FILE * f) {
        fprintf(f, "\nstrip\n");
        for (int i = 1; i < count; i++) {
            fprintf(f, "%03d ", i);
            switch (st[i].stt) {
            case OUT_ID:    fprintf(f, "ID %s\n", st[i].str_val); break;
            case OUT_I4:    fprintf(f, "I4 %d\n", st[i].int_val); break;
            case OUT_R8:    fprintf(f, "R8 %g\n", st[i].dbl_val); break;
            case OUT_LABEL: fprintf(f, "LABEL %d\n", st[i].int_val); break;
            case OUT_DEFL:  fprintf(f, "DEFL\n"); break;
            case OUT_PUSH:  fprintf(f, "PUSH\n"); break;
            case OUT_POPL:  fprintf(f, "POPL\n"); break;
            case OUT_SWAP:  fprintf(f, "SWAP\n"); break;
            case OUT_BZ:    fprintf(f, "BZ\n"); break;
            case OUT_BR:    fprintf(f, "BR\n"); break;
            case OUT_EQ:    fprintf(f, "EQ\n"); break;
            case OUT_NE:    fprintf(f, "NE\n"); break;
            case OUT_LT:    fprintf(f, "LT\n"); break;
            case OUT_GT:    fprintf(f, "GT\n"); break;
            case OUT_LE:    fprintf(f, "LE\n"); break;
            case OUT_GE:    fprintf(f, "GE\n"); break;
            case OUT_DIM:   fprintf(f, "DIM\n"); break;
            case OUT_ASS:   fprintf(f, "ASS\n"); break;
            case OUT_ADD:   fprintf(f, "ADD\n"); break;
            case OUT_SUB:   fprintf(f, "SUB\n"); break;
            case OUT_MUL:   fprintf(f, "MUL\n"); break;
            case OUT_DIV:   fprintf(f, "DIV\n"); break;
            case OUT_PRINT: fprintf(f, "PRINT\n"); break;
            case OUT_LONG:  fprintf(f, "LONG\n"); break;
            case OUT_INT:   fprintf(f, "INT\n"); break;
            case OUT_END:   fprintf(f, "END\n"); break;
            default: fprintf(f, "UNKNOWN\n");
            }
        }
        fprintf(f, "\n");
    }
};

// вычислительный стек ПОЛИЗ
template <int N>
class exstack {
private:
    // массив элементов
    exstel st[N];
    // счетчик
    int count;
    // глубина
    int depth;
public:
    // конструктор
    exstack() {
        count = 0;
        depth = 0;
    }
    // деструктор
    ~exstack() {
        printf("exstack: size=%d, depth=%d.\n", N, depth);
    }
    // возвращает количество элементов
    int size(void) {
        return count;
    }
    // проталкивает элемент
    void push(exstel & e) {
        if (count >= N) throw "exstack::push exe-stack overflow";
        st[count++] = e;
        if (depth < count) {
            depth = count;
        }
    }
    // выталкивает элемент
    void pop(exstel & e) {
        if (count < 1) throw "exstack::push exe-stack is empty";
        e = st[--count];
        st[count].reset();
    }
};
