#include <stdio.h>
#include "../include/system.h"
#include "test_runner.h"

static void test_registrar_entrada_produto_inexistente(void) {
    estoque_inicializar();
    produtos_inicializar();
    
    registrar_entrada(999, 10);
    
    Produto *prod = produtos_buscar_por_id(999);
    ASSERT_NULL(prod);
    
    produtos_finalizar();
    estoque_finalizar();
}

static void test_registrar_entrada_quantidade_invalida(void) {
    estoque_inicializar();
    produtos_inicializar();
    
    registrar_entrada(1, 0);
    registrar_entrada(1, -5);
    
    produtos_finalizar();
    estoque_finalizar();
}

static void test_registrar_saida_produto_inexistente(void) {
    estoque_inicializar();
    produtos_inicializar();
    
    registrar_saida(999, 10);
    
    Produto *prod = produtos_buscar_por_id(999);
    ASSERT_NULL(prod);
    
    produtos_finalizar();
    estoque_finalizar();
}

static void test_registrar_saida_quantidade_invalida(void) {
    estoque_inicializar();
    produtos_inicializar();
    
    registrar_saida(1, 0);
    registrar_saida(1, -5);
    
    produtos_finalizar();
    estoque_finalizar();
}

void rodar_testes_estoque(void) {
    printf("\n=== Testes de Estoque ===\n");
    
    RUN_TEST(test_registrar_entrada_produto_inexistente);
    RUN_TEST(test_registrar_entrada_quantidade_invalida);
    RUN_TEST(test_registrar_saida_produto_inexistente);
    RUN_TEST(test_registrar_saida_quantidade_invalida);
    
    estoque_finalizar();
}
