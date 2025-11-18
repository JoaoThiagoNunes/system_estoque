#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/system.h"
#include "test_runner.h"


static void test_fluxo_estoque_completo(void) {
    estoque_inicializar();
    produtos_inicializar();
    categorias_inicializar();
    fornecedores_inicializar();
    registrar_entrada(1, 10);
    Produto *prod = produtos_buscar_por_id(1);
    ASSERT_NULL(prod);
    registrar_saida(1, 5, "Teste de saida");
    prod = produtos_buscar_por_id(1);
    ASSERT_NULL(prod);
    produtos_finalizar();
    categorias_finalizar();
    fornecedores_finalizar();
    estoque_finalizar();
}

static void test_fluxo_venda_completo(void) {
    vendas_inicializar();
    produtos_inicializar();
    clientes_inicializar();
    funcionarios_inicializar(); 
    registrar_venda(999, 999, 999, 1);
    Produto *prod = produtos_buscar_por_id(999);
    ASSERT_NULL(prod);
    const Cliente *cli = clientes_buscar_por_id(999);
    ASSERT_NULL(cli);
    const Funcionario *func = funcionarios_buscar_por_id(999);
    ASSERT_NULL(func);
    produtos_finalizar();
    clientes_finalizar();
    funcionarios_finalizar();
    vendas_finalizar();
}

static void test_fluxo_busca_apos_inicializacao(void) {
    categorias_inicializar();
    fornecedores_inicializar();
    produtos_inicializar();
    clientes_inicializar();
    funcionarios_inicializar();
    ASSERT_TRUE(categorias_vazias());
    ASSERT_TRUE(fornecedores_vazios());
    ASSERT_TRUE(produtos_vazios());
    ASSERT_TRUE(clientes_vazios());
    ASSERT_NULL(categorias_buscar_por_id(1));
    ASSERT_NULL(fornecedores_buscar_por_id(1));
    ASSERT_NULL(produtos_buscar_por_id(1));
    ASSERT_NULL(clientes_buscar_por_id(1));
    ASSERT_NULL(funcionarios_buscar_por_id(1));   
    categorias_finalizar();
    fornecedores_finalizar();
    produtos_finalizar();
    clientes_finalizar();
    funcionarios_finalizar();
}

void rodar_testes_integracao(void) {
    printf("\n=== Testes de Integracao ===\n");
    RUN_TEST(test_fluxo_estoque_completo);
    RUN_TEST(test_fluxo_venda_completo);
    RUN_TEST(test_fluxo_busca_apos_inicializacao);
}

