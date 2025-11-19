#include <stdio.h>
#include "../include/system.h"
#include "test_runner.h"

static void test_produtos_vazios_inicial(void) {
    produtos_inicializar();
    ASSERT_TRUE(produtos_vazios());
    produtos_finalizar();
}

static void test_produtos_buscar_inexistente(void) {
    produtos_inicializar();
    Produto *prod = produtos_buscar_por_id(999);
    ASSERT_NULL(prod);
    produtos_finalizar();
}

static void test_produtos_buscar_apos_inicializacao(void) {
    produtos_inicializar();
    ASSERT_TRUE(produtos_vazios());
    Produto *prod = produtos_buscar_por_id(1);
    ASSERT_NULL(prod);
    produtos_finalizar();
}

void rodar_testes_produto(void) {
    printf("\n=== Testes de Produto ===\n");
    
    RUN_TEST(test_produtos_vazios_inicial);
    RUN_TEST(test_produtos_buscar_inexistente);
    RUN_TEST(test_produtos_buscar_apos_inicializacao);
    
    produtos_finalizar();
}

