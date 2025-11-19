#include <stdio.h>
#include <stdlib.h>
#include "../include/system.h"
#include "test_runner.h"

void rodar_testes_categoria(void);
void rodar_testes_produto(void);
void rodar_testes_estoque(void);
void rodar_testes_integracao(void);

int main(void) {
    inicializar_dados();
    
    rodar_testes_categoria();
    rodar_testes_produto();
    rodar_testes_estoque();
    rodar_testes_integracao();
    
    finalizar_sistema();
    test_summary();
    
    return (tests_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

