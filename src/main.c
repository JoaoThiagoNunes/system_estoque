#include <stdio.h>
#include <stdlib.h>
#include "../include/system.h"
#include "../include/utils.h"
#include "../include/ui.h"

static void mostrar_menu(void) {
    limpar_tela();
    desenhar_box_titulo("SISTEMA DE ESTOQUE", 60);
    printf(ANSI_BOLD ANSI_CYAN "  CADASTROS" ANSI_RESET "\n");
    imprimir_menu_item(1, "Cadastrar categoria");
    imprimir_menu_item(2, "Cadastrar fornecedor");
    imprimir_menu_item(3, "Cadastrar produto");
    imprimir_menu_item(4, "Cadastrar cliente");
    imprimir_menu_item(5, "Cadastrar funcionario");
    printf("\n" ANSI_BOLD ANSI_CYAN "  CONSULTAS" ANSI_RESET "\n");
    imprimir_menu_item(6, "Listar categorias");
    imprimir_menu_item(7, "Listar fornecedores");
    imprimir_menu_item(8, "Listar produtos");
    imprimir_menu_item(9, "Listar clientes");
    imprimir_menu_item(10, "Listar funcionarios");
    printf("\n" ANSI_BOLD ANSI_CYAN "  OPERACOES" ANSI_RESET "\n");
    imprimir_menu_item(11, "Registrar entrada em estoque");
    imprimir_menu_item(12, "Registrar saida em estoque");
    imprimir_menu_item(13, "Registrar venda");
    printf("\n");
    desenhar_separador(58);
    imprimir_menu_item(0, "Sair");
    desenhar_box_fim(60);
    printf(ANSI_YELLOW "Escolha: " ANSI_RESET);
}

static void submenu_listar_fornecedores(void) {
    int opcao = -1;
    while (opcao != 0) {
        limpar_tela();
        desenhar_box_titulo("LISTAR FORNECEDORES", 50);
        imprimir_menu_item(1, "Primeiros 5 fornecedores");
        imprimir_menu_item(2, "Todos os fornecedores");
        printf("\n");
        desenhar_separador(48);
        imprimir_menu_item(0, "Voltar ao menu principal");
        desenhar_box_fim(50);
        printf(ANSI_YELLOW "Escolha: " ANSI_RESET);
        if (scanf("%d", &opcao) != 1) {
            fprintf(stderr, "Entrada invalida.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();
        switch (opcao) {
            case 1: listar_fornecedores_limitado(5); break;
            case 2: listar_fornecedores(); break;
            case 0: break;
            default: printf("Opcao invalida.\n"); break;
        }
    }
}

static void submenu_listar_clientes(void) {
    int opcao = -1;
    while (opcao != 0) {
        limpar_tela();
        desenhar_box_titulo("LISTAR CLIENTES", 50);
        imprimir_menu_item(1, "Primeiros 5 clientes");
        imprimir_menu_item(2, "Todos os clientes");
        printf("\n");
        desenhar_separador(48);
        imprimir_menu_item(0, "Voltar ao menu principal");
        desenhar_box_fim(50);
        printf(ANSI_YELLOW "Escolha: " ANSI_RESET);
        if (scanf("%d", &opcao) != 1) {
            fprintf(stderr, "Entrada invalida.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();
        switch (opcao) {
            case 1: listar_clientes_limitado(5); break;
            case 2: listar_clientes(); break;
            case 0: break;
            default: printf("Opcao invalida.\n"); break;
        }
    }
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
            case 1: cadastrar_categoria(); break;
            case 2: cadastrar_fornecedor(); break;
            case 3: cadastrar_produto(); break;
            case 4: cadastrar_cliente(); break;
            case 5: cadastrar_funcionario(); break;
            case 6: listar_categorias(); break;
            case 7: submenu_listar_fornecedores(); break;
            case 8: listar_produtos(); break;
            case 9: submenu_listar_clientes(); break;
            case 10: listar_funcionarios(); break;
            case 11: {
                limpar_tela();
                desenhar_box_titulo("REGISTRAR ENTRADA EM ESTOQUE", 50);
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
                limpar_tela();
                desenhar_box_titulo("REGISTRAR SAIDA EM ESTOQUE", 50);
                int id, qtd;
                printf("ID do produto: ");
                scanf("%d", &id);
                limpar_buffer();
                printf("Quantidade: ");
                scanf("%d", &qtd);
                limpar_buffer();
                registrar_saida(id, qtd);
                break;
            }
            case 13: {
                limpar_tela();
                desenhar_box_titulo("REGISTRAR VENDA", 50);
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
                limpar_tela();
                imprimir_titulo("Gerando Relatorio Final");
                gerar_relatorio_vendas();
                printf("\n");
                imprimir_sucesso("Relatorio gerado com sucesso!");
                printf("\n" ANSI_YELLOW "Pressione Enter para sair..." ANSI_RESET);
                limpar_buffer();
                getchar();
                break;
            default:
                imprimir_erro("Opcao invalida. Tente novamente.");
                printf(ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
                limpar_buffer();
                getchar();
                break;
        }
    }
    finalizar_sistema();
    return EXIT_SUCCESS;
}