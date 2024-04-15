// 2019 ReVoL Primer Template
// simplet.cpp
// основная функция

#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
// основные типы и символы
#include "types.h"
// лексический анализатор
#include "lexan.h"
// синтаксический анализатор
#include "sa1null.h"

int simplet(FILE * input) {
    // программные исключения
    try {
        // синтаксический разбор
        return (new syntaxan(new lexan(input, stdout), stdout, stdout))->parse();
    } catch(const char * e) {
        printf("\nException raised %s.\n\n", e);
    } catch(...) {
        printf("\nUnexpected exception raised.\n\n");
    }
    return 0; // неудача
}

int main(int argc, char * argv[]) {
    // открываем входной поток
    FILE * input = fopen("1.st", "rt");
    if (!input) {
        // проблемы с входным файлом
        printf("simplet: error while open input file\n\n");
        return 1; // неудача
    }
    // аппаратные исключения
    __try {
        return (simplet(input)) == 0 ? 1 : 0;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        unsigned int code = GetExceptionCode();
        if (code == EXCEPTION_ACCESS_VIOLATION) {
            printf("\nAccess violation raised.\n\n");
        } else if (code == EXCEPTION_STACK_OVERFLOW) {
            printf("\nStack overflow raised.\n\n");
        } else {
            printf("\nHardware exception raised.\n\n");
        }
    }
    return 1; // неудача
}
