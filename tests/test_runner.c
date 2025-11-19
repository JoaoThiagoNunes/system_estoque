#include <stdio.h>
#include "test_runner.h"

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;
const char *current_test_name = "";

void test_summary(void) {
    printf("\n=== Resumo dos Testes ===\n");
    printf("Total de testes: %d\n", tests_run);
    printf("Aprovados: %d\n", tests_passed);
    printf("Falhados: %d\n", tests_failed);
    
    if (tests_failed == 0) {
        printf("\n[TODOS OS TESTES PASSARAM!]\n");
    } else {
        printf("\n[ALGUNS TESTES FALHARAM]\n");
    }
}

