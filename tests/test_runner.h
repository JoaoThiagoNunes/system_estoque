#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int tests_run;
extern int tests_passed;
extern int tests_failed;
extern const char *current_test_name;

#define ASSERT_EQ(a, b) \
    do { \
        if ((a) != (b)) { \
            printf("  [FALHOU] %s:%d: Esperado %d, obtido %d\n", \
                   __FILE__, __LINE__, (int)(b), (int)(a)); \
            tests_failed++; \
            return; \
        } \
    } while (0)

#define ASSERT_NE(a, b) \
    do { \
        if ((a) == (b)) { \
            printf("  [FALHOU] %s:%d: Valores nao deveriam ser iguais\n", \
                   __FILE__, __LINE__); \
            tests_failed++; \
            return; \
        } \
    } while (0)

#define ASSERT_FLOAT_EQ(a, b) \
    do { \
        float diff = ((a) > (b)) ? ((a) - (b)) : ((b) - (a)); \
        if (diff > 0.001f) { \
            printf("  [FALHOU] %s:%d: Esperado %.2f, obtido %.2f\n", \
                   __FILE__, __LINE__, (b), (a)); \
            tests_failed++; \
            return; \
        } \
    } while (0)

#define ASSERT_NULL(ptr) \
    do { \
        if ((ptr) != NULL) { \
            printf("  [FALHOU] %s:%d: Ponteiro deveria ser NULL\n", \
                   __FILE__, __LINE__); \
            tests_failed++; \
            return; \
        } \
    } while (0)

#define ASSERT_NOT_NULL(ptr) \
    do { \
        if ((ptr) == NULL) { \
            printf("  [FALHOU] %s:%d: Ponteiro nao deveria ser NULL\n", \
                   __FILE__, __LINE__); \
            tests_failed++; \
            return; \
        } \
    } while (0)

#define ASSERT_TRUE(cond) \
    do { \
        if (!(cond)) { \
            printf("  [FALHOU] %s:%d: Condicao deveria ser verdadeira\n", \
                   __FILE__, __LINE__); \
            tests_failed++; \
            return; \
        } \
    } while (0)

#define ASSERT_FALSE(cond) \
    do { \
        if (cond) { \
            printf("  [FALHOU] %s:%d: Condicao deveria ser falsa\n", \
                   __FILE__, __LINE__); \
            tests_failed++; \
            return; \
        } \
    } while (0)

#define ASSERT_STR_EQ(a, b) \
    do { \
        if (strcmp((a), (b)) != 0) { \
            printf("  [FALHOU] %s:%d: Esperado '%s', obtido '%s'\n", \
                   __FILE__, __LINE__, (b), (a)); \
            tests_failed++; \
            return; \
        } \
    } while (0)

#define RUN_TEST(test_func) \
    do { \
        current_test_name = #test_func; \
        tests_run++; \
        printf("Executando: %s\n", current_test_name); \
        int antes_falhas = tests_failed; \
        test_func(); \
        if (antes_falhas == tests_failed) { \
            tests_passed++; \
            printf("  [OK]\n"); \
        } \
    } while (0)

void test_summary(void);

#endif

