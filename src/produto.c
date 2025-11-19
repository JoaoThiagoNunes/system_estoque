#include <stdio.h>
#include <stdlib.h>
#include "../include/system.h"
#include "../include/utils.h"
#include "../include/ui.h"

typedef struct ProdutoNode {
    Produto value;
    struct ProdutoNode *next;
} ProdutoNode;

static ProdutoNode *produtosHead = NULL;
static int proximoProdutoId = 1;

static void inserir_produto(ProdutoNode *novo) {
    if (!produtosHead) {
        produtosHead = novo;
        return;
    }

    ProdutoNode *ponteiro = produtosHead;
    while (ponteiro->next) {
        ponteiro = ponteiro->next;
    }
    ponteiro->next = novo;
}

static ProdutoNode *produto_buscar_node(int id) {
    ProdutoNode *atual = produtosHead;
    while (atual) {
        if (atual->value.id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void produtos_inicializar(void) {
    produtosHead = NULL;
    proximoProdutoId = 1;
}

void produtos_finalizar(void) {
    ProdutoNode *atual = produtosHead;
    while (atual) {
        ProdutoNode *temp = atual->next;
        free(atual);
        atual = temp;
    }
    produtosHead = NULL;
}

int produtos_vazios(void) {
    return produtosHead == NULL;
}

Produto *produtos_buscar_por_id(int id) {
    ProdutoNode *node = produto_buscar_node(id);
    return node ? &node->value : NULL;
}

void cadastrar_produto(void) {
    if (categorias_vazias()) {
        printf("Nenhuma categoria cadastrada. Cadastre uma categoria primeiro.\n");
        return;
    }

    if (fornecedores_vazios()) {
        printf("Nenhum fornecedor cadastrado. Cadastre um fornecedor primeiro.\n");
        return;
    }

    Produto produto = {0};
    produto.id = proximoProdutoId++;

    ler_texto("Nome do produto: ", produto.nome, sizeof(produto.nome));

    printf("ID da categoria: ");
    if (scanf("%d", &produto.categoriaId) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (!categorias_buscar_por_id(produto.categoriaId)) {
        printf("Categoria %d nao encontrada.\n", produto.categoriaId);
        return;
    }

    printf("ID do fornecedor: ");
    if (scanf("%d", &produto.fornecedorId) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (!fornecedores_buscar_por_id(produto.fornecedorId)) {
        printf("Fornecedor %d nao encontrado.\n", produto.fornecedorId);
        return;
    }

    printf("Preco de compra: ");
    if (scanf("%f", &produto.precoCompra) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    printf("Preco de venda: ");
    if (scanf("%f", &produto.precoVenda) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    printf("Quantidade inicial em estoque: ");
    if (scanf("%d", &produto.quantidade) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    ler_texto("Codigo de barras: ", produto.codigoBarras, sizeof(produto.codigoBarras));
    ler_texto("Unidade de medida (kg, un, m, etc): ", produto.unidadeMedida, sizeof(produto.unidadeMedida));

    ProdutoNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para produto.\n");
        return;
    }

    novo->value = produto;
    novo->next = NULL;

    inserir_produto(novo);

    const Categoria *categoria = categorias_buscar_por_id(produto.categoriaId);
    printf("\n");
    desenhar_box_titulo("CADASTRO REALIZADO COM SUCESSO", 60);
    imprimir_sucesso("Produto cadastrado!");
    printf("\n");
    printf("ID: %d\n", produto.id);
    printf("Nome: %s\n", produto.nome);
    printf("Codigo de Barras: %s\n", produto.codigoBarras);
    printf("Categoria: %s\n", categoria ? categoria->nome : "N/D");
    printf("Unidade de Medida: %s\n", produto.unidadeMedida);
    printf("Quantidade: %d %s\n", produto.quantidade, produto.unidadeMedida);
    printf("Preco de Compra: R$ %.2f\n", produto.precoCompra);
    printf("Preco de Venda: R$ %.2f\n", produto.precoVenda);
    desenhar_box_fim(60);
    pausar_para_continuar();
}

void listar_produtos(void) {
    limpar_tela();
    imprimir_titulo("PRODUTOS");
    
    if (!produtosHead) {
        imprimir_info("Nenhum produto cadastrado.");
        printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
        limpar_buffer();
        getchar();
        return;
    }

    desenhar_box_titulo("LISTA DE PRODUTOS", 100);
    printf(ANSI_BOLD "%-4s | %-15s | %-25s | %-12s | %-10s | %-10s | %-15s\n" ANSI_RESET,
           "ID", "Cod. Barras", "Nome", "Estoque", "Preco Compra", "Preco Venda", "Categoria");
    desenhar_separador(98);
    
    ProdutoNode *ponteiro = produtosHead;
    while (ponteiro) {
        const Categoria *categoria = categorias_buscar_por_id(ponteiro->value.categoriaId);
        printf("%-4d | %-15s | %-25s | %-3d %-8s | R$ %6.2f | R$ %6.2f | %-15s\n",
               ponteiro->value.id,
               ponteiro->value.codigoBarras,
               ponteiro->value.nome,
               ponteiro->value.quantidade,
               ponteiro->value.unidadeMedida,
               ponteiro->value.precoCompra,
               ponteiro->value.precoVenda,
               categoria ? categoria->nome : "N/D");
        ponteiro = ponteiro->next;
    }
    
    desenhar_box_fim(100);
    printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
    limpar_buffer();
    getchar();
}

float calcular_valor_investido(void) {
    float valor_estoque_atual = 0;
    ProdutoNode *atual = produtosHead;
    while (atual) {
        valor_estoque_atual += atual->value.precoCompra * atual->value.quantidade;
        atual = atual->next;
    }
    float custo_vendas = calcular_custo_total_vendas();
    float custo_saidas = calcular_custo_total_saidas();
    
    return valor_estoque_atual + custo_vendas + custo_saidas;
}