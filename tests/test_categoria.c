#include <stdio.h>
#include "../include/system.h"
#include "test_runner.h"

static void test_categorias_vazias_inicial(void) {
    categorias_inicializar();
    ASSERT_TRUE(categorias_vazias());
    categorias_finalizar();
}

static void test_categorias_buscar_inexistente(void) {
    categorias_inicializar();
    const Categoria *cat = categorias_buscar_por_id(999);
    ASSERT_NULL(cat);
    categorias_finalizar();
}

static void test_categorias_buscar_apos_inicializacao(void) {
    categorias_inicializar();
    ASSERT_TRUE(categorias_vazias());
    const Categoria *cat = categorias_buscar_por_id(1);
    ASSERT_NULL(cat);
    categorias_finalizar();
}

void rodar_testes_categoria(void) {
    printf("\n=== Testes de Categoria ===\n");
    
    RUN_TEST(test_categorias_vazias_inicial);
    RUN_TEST(test_categorias_buscar_inexistente);
    RUN_TEST(test_categorias_buscar_apos_inicializacao);
    
    categorias_finalizar();
}

