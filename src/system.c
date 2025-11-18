#include <stdio.h>
#include "../include/system.h"

void inicializar_dados(void) {
    categorias_inicializar();
    fornecedores_inicializar();
    produtos_inicializar();
    clientes_inicializar();
    funcionarios_inicializar();
    estoque_inicializar();
    pedidos_inicializar();
    vendas_inicializar();

    printf("Listas inicializadas. Cadastre os dados pelo menu.\n");
}

void finalizar_sistema(void) {
    vendas_finalizar();
    pedidos_finalizar();
    estoque_finalizar();
    funcionarios_finalizar();
    clientes_finalizar();
    produtos_finalizar();
    fornecedores_finalizar();
    categorias_finalizar();
}

