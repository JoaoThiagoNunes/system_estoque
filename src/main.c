#include <stdio.h>
#include <stdlib.h>
#include "../include/system.h"
#include "../include/utils.h"

static void mostrar_menu(void) {
    printf("\n=== Sistema de Estoque ===\n");
    printf("01 - Cadastrar categoria\n");
    printf("02 - Cadastrar fornecedor\n");
    printf("03 - Cadastrar produto\n");
    printf("04 - Cadastrar cliente\n");
    printf("05 - Cadastrar funcionario\n\n");
    printf("06 - Listar categorias\n");
    printf("07 - Listar fornecedores\n");
    printf("08 - Listar produtos\n");
    printf("09 - Listar clientes\n");
    printf("10 - Listar funcionarios\n\n");
    printf("11 - Registrar entrada em estoque\n");
    printf("12 - Registrar saida em estoque\n");
    printf("13 - Registrar venda\n\n");
    printf(" 0 - Sair\n");
    printf("Escolha: ");
}

int main(void) {
    int opcao = -1;
    inicializar_dados();

    while (opcao != 0) {
        mostrar_menu();
        if (scanf("%d", &opcao) != 1) {
            fprintf(stderr, "Entrada invalida. Encerrando.\n");
            return EXIT_FAILURE;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                cadastrar_categoria();
                break;
            case 2:
                cadastrar_fornecedor();
                break;
            case 3:
                cadastrar_produto();
                break;
            case 4:
                cadastrar_cliente();
                break;
            case 5:
                cadastrar_funcionario();
                break;
            case 6:
                listar_categorias();
                break;
            case 7:
                listar_fornecedores();
                break;
            case 8:
                listar_produtos();
                break;
            case 9:
                listar_clientes();
                break;
            case 10:
                listar_funcionarios();
                break;
            case 11: {
                int id, qtd;
                printf("ID do produto: ");
                scanf("%d", &id);
                limpar_buffer();
                printf("Quantidade: ");
                scanf("%d", &qtd);
                limpar_buffer();
                registrar_entrada(id, qtd);
                break;
            }
            case 12: {
                int id, qtd;
                char motivo[60];
                printf("ID do produto: ");
                scanf("%d", &id);
                limpar_buffer();
                printf("Quantidade: ");
                scanf("%d", &qtd);
                limpar_buffer();
                printf("Motivo: ");
                scanf(" %59[^\n]", motivo);
                limpar_buffer();
                registrar_saida(id, qtd, motivo);
                break;
            }
            case 13: {
                int produtoId, clienteId, funcionarioId, qtd;
                printf("ID do produto: ");
                scanf("%d", &produtoId);
                limpar_buffer();
                printf("ID do cliente: ");
                scanf("%d", &clienteId);
                limpar_buffer();
                printf("ID do funcionario responsavel: ");
                scanf("%d", &funcionarioId);
                limpar_buffer();
                printf("Quantidade: ");
                scanf("%d", &qtd);
                limpar_buffer();
                registrar_venda(produtoId, clienteId, funcionarioId, qtd);
                break;
            }
            case 0:
                printf("=============================\nGerando Relatorio Final...\n");
                gerar_relatorio_vendas();
                printf("=============================\n");
                break;
            default:
                printf("Opção invalida.\n");
                break;
        }
    }

    finalizar_sistema();

    return EXIT_SUCCESS;
}

